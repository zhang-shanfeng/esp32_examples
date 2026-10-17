#include "lcd_lvgl_task.h"

#include <stdio.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"

static const char *TAG = "lcd_lvgl_task";

#define LCD_HOST SPI2_HOST

#define LCD_SCLK_GPIO 12
#define LCD_MOSI_GPIO 11
#define LCD_CS_GPIO 39
#define LCD_DC_GPIO 40
#define LCD_RST_GPIO 38
#define LCD_BL_GPIO 41

#define LCD_WIDTH 320
#define LCD_HEIGHT 240

esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_handle_t panel_handle = NULL;

LV_FONT_DECLARE(ibm_plex_mono_medium_16_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_18_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_20_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_22_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_24_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_26_2bpp);
LV_FONT_DECLARE(alibaba_puhuiti_regular_22_4bpp);
LV_FONT_DECLARE(alibaba_puhuiti_regular_24_4bpp);
LV_FONT_DECLARE(smiley_sans_oblique_24_4bpp);

void lcd_init(void)
{
    esp_err_t ret;

    // --------------------------------------------------
    // 1. 初始化 SPI Bus
    // --------------------------------------------------

    spi_bus_config_t bus_config = {
        .sclk_io_num = LCD_SCLK_GPIO,
        .mosi_io_num = LCD_MOSI_GPIO,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,

        .max_transfer_sz = LCD_WIDTH * LCD_HEIGHT * sizeof(uint16_t),
    };

    ret = spi_bus_initialize(LCD_HOST, &bus_config, SPI_DMA_CH_AUTO);

    ESP_ERROR_CHECK(ret);

    // --------------------------------------------------
    // 2. 创建 SPI LCD Panel IO
    // --------------------------------------------------

    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = LCD_DC_GPIO,
        .cs_gpio_num = LCD_CS_GPIO,

        .pclk_hz = 20 * 1000 * 1000,

        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,

        .spi_mode = 0,

        .trans_queue_depth = 10,
    };

    ret = esp_lcd_new_panel_io_spi(
        (esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle);

    ESP_ERROR_CHECK(ret);

    // --------------------------------------------------
    // 3. 创建 ST7789 Panel
    // --------------------------------------------------

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RST_GPIO,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,  // 颜色通道的排列顺序
        .bits_per_pixel = 16,
        .data_endian = LCD_RGB_DATA_ENDIAN_BIG,  // 多字节数据的字节序
    };

    ret = esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);

    ESP_ERROR_CHECK(ret);

    // --------------------------------------------------
    // 4. Reset
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));

    // --------------------------------------------------
    // 5. 初始化
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

    // --------------------------------------------------
    // 6. ST7789 特殊配置
    // --------------------------------------------------

    /*
     * 很多 ST7789 模块没有完整的 240x320 显示区域，
     * 因此需要设置 offset。
     * 0.96寸
     * x_gap:
     * y_gap:
     *
     * 1.14寸 240X135
     * x_gap 40
     * y_gap 53
     */

    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 0, 0));

    // --------------------------------------------------
    // 7. 颜色反转(颜色显示不对时可以改这个配置试试)
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, false));

    // --------------------------------------------------
    // 8. 开启显示
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    // --------------------------------------------------
    // 9. 背光
    // --------------------------------------------------

    gpio_config_t bl_config = {
        .pin_bit_mask = 1ULL << LCD_BL_GPIO,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };

    ESP_ERROR_CHECK(gpio_config(&bl_config));

    gpio_set_level(LCD_BL_GPIO, 1);

    ESP_LOGI(TAG, "ST7789 initialized");
}

lv_display_t *lvgl_init(esp_lcd_panel_io_handle_t io_handle,
                        esp_lcd_panel_handle_t panel_handle)
{
    lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();

    lvgl_port_init(&lvgl_cfg);

    // --------------------------------------------------
    // LVGL display 配置
    // --------------------------------------------------

    const lvgl_port_display_cfg_t display_cfg = {

        .io_handle = io_handle,
        .panel_handle = panel_handle,

        .buffer_size = LCD_WIDTH * 100,

        .double_buffer = true,

        .hres = LCD_WIDTH,
        .vres = LCD_HEIGHT,

        .monochrome = false,

        .color_format = LV_COLOR_FORMAT_RGB565_SWAPPED,

        .rotation =
            {
                .swap_xy = true,
                .mirror_x = true,
                .mirror_y = false,
            },

        .flags =
            {
                .buff_dma = true,
                /*
                false: 缓冲区放在内部 RAM
                true: 缓冲区移到 8MB PSRAM
                但是实测发现设为 true时屏幕会花屏，可能不能和 DMA 配合
                */
                .buff_spiram = false,
                .sw_rotate = false,
            },
    };

    return lvgl_port_add_disp(&display_cfg);
}

static lv_obj_t *title_label;
static lv_obj_t *label_voltage_val;
static lv_obj_t *label_current_val;
static lv_obj_t *label_power_val;
void ui_init(void)
{
    lv_obj_t *scr = lv_screen_active();
    // lv_obj_invalidate(scr);  // 强制刷新整个屏幕
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

    /* 顶部背景容器 */
    // 1. 创建一个基础的 obj 作为背景
    lv_obj_t *title_bg = lv_obj_create(scr);

    // 2. 设置背景容器的宽度为屏幕宽度的 100%，高度为 40 像素（可按需调整）
    lv_obj_set_size(title_bg, lv_pct(100), 40);

    // 3. 将背景容器对齐到屏幕顶部
    lv_obj_align(title_bg, LV_ALIGN_TOP_MID, 0, 0);

    // 4. 设置背景颜色 (这里用深灰色举例，你可以换成你喜欢的颜色)
    lv_obj_set_style_bg_color(title_bg, lv_color_hex(0x222831), 0);
    lv_obj_set_style_bg_opa(title_bg, LV_OPA_COVER, 0);

    // 5. 去除容器默认的圆角、边框和阴影，让它看起来像个平整的横幅
    lv_obj_set_style_radius(title_bg, 0, 0);
    lv_obj_set_style_border_width(title_bg, 0, 0);
    lv_obj_set_style_shadow_width(title_bg, 0, 0);

    // 6. 去除容器内部的 padding，防止影响子对象的对齐
    lv_obj_set_style_pad_all(title_bg, 0, 0);

    /* title label 设置*/
    title_label = lv_label_create(title_bg);
    lv_obj_set_style_text_color(
        title_label, lv_palette_lighten(LV_PALETTE_AMBER, 1), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(
        title_label, &smiley_sans_oblique_24_4bpp, LV_STATE_DEFAULT);
    lv_label_set_text(title_label, "INA226 电压、电流、功率测量");

    // 对齐设置
    lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);

    /* 创建一个容器用来装下面的数据 */
    lv_obj_t *data_container = lv_obj_create(scr);
    lv_obj_set_size(data_container, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_align_to(data_container, title_bg, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 6);

    /* 去除 data_container  的默认样式 */
    lv_obj_set_style_bg_opa(data_container, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(data_container, 0, 0);
    lv_obj_set_style_pad_all(data_container, 0, 0);
    lv_obj_remove_flag(data_container, LV_OBJ_FLAG_SCROLLABLE);

    /* 开启 Flex 布局（垂直排列） */
    lv_obj_set_flex_flow(data_container, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(data_container,
                          LV_FLEX_ALIGN_START,
                          LV_FLEX_ALIGN_START,
                          LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_row(data_container, 5, 0);

    /* 第一行：电压 */
    lv_obj_t *row_vol = lv_obj_create(data_container);  // 每行做一个容器
    lv_obj_set_size(
        row_vol, lv_pct(100), LV_SIZE_CONTENT);  // 宽度 100%，高度包裹内容
    lv_obj_set_style_bg_opa(row_vol, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row_vol, 0, 0);

    lv_obj_set_style_pad_all(row_vol, 0, 0);
    lv_obj_set_style_pad_row(row_vol, 0, 0);
    lv_obj_set_style_pad_column(row_vol, 0, 0);
    lv_obj_remove_flag(row_vol, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *label_vol_title = lv_label_create(row_vol);
    lv_label_set_text(label_vol_title, "电压");
    lv_obj_set_style_text_font(
        label_vol_title, &alibaba_puhuiti_regular_24_4bpp, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_vol_title, lv_color_white(), 0);

    label_voltage_val = lv_label_create(row_vol);
    lv_label_set_text(label_voltage_val, "0.000 V");
    lv_obj_set_style_text_font(
        label_voltage_val, &ibm_plex_mono_medium_24_2bpp, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_voltage_val,
                                lv_palette_lighten(LV_PALETTE_DEEP_ORANGE, 1),
                                LV_STATE_DEFAULT);
    lv_obj_align(
        label_voltage_val, LV_ALIGN_RIGHT_MID, 0, 0);  // 数值靠右对齐（可选）

    /* 第二行：电流 */
    lv_obj_t *row_cur = lv_obj_create(data_container);
    lv_obj_set_size(row_cur, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(row_cur, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row_cur, 0, 0);
    lv_obj_set_style_pad_all(row_cur, 0, 0);  // 清空内边距
    lv_obj_set_style_pad_row(row_cur, 0, 0);
    lv_obj_set_style_pad_column(row_cur, 0, 0);
    lv_obj_remove_flag(row_cur, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *label_cur_title = lv_label_create(row_cur);
    lv_label_set_text(label_cur_title, "电流");
    lv_obj_set_style_text_font(
        label_cur_title, &alibaba_puhuiti_regular_24_4bpp, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(
        label_cur_title, lv_color_white(), LV_STATE_DEFAULT);

    label_current_val = lv_label_create(row_cur);
    lv_label_set_text(label_current_val, "0.000 A");
    lv_obj_set_style_text_font(
        label_current_val, &ibm_plex_mono_medium_24_2bpp, LV_STATE_DEFAULT);
    lv_obj_align(label_current_val, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_set_style_text_color(
        label_current_val, lv_color_white(), LV_STATE_DEFAULT);

    /* 第三行：功率 */
    lv_obj_t *row_pow = lv_obj_create(data_container);
    lv_obj_set_size(row_pow, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_opa(row_pow, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(row_pow, 0, 0);
    lv_obj_set_style_pad_all(row_pow, 0, 0);  // 清空内边距
    lv_obj_set_style_pad_row(row_pow, 0, 0);
    lv_obj_set_style_pad_column(row_pow, 0, 0);
    lv_obj_remove_flag(row_pow, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *label_pow_title = lv_label_create(row_pow);
    lv_label_set_text(label_pow_title, "功率");
    lv_obj_set_style_text_font(
        label_pow_title, &alibaba_puhuiti_regular_24_4bpp, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_pow_title, lv_color_white(), 0);

    label_power_val = lv_label_create(row_pow);
    lv_label_set_text(label_power_val, "0.000 W");
    lv_obj_set_style_text_font(
        label_power_val, &ibm_plex_mono_medium_24_2bpp, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_power_val,
                                lv_palette_lighten(LV_PALETTE_ORANGE, 1),
                                LV_STATE_DEFAULT);
    lv_obj_align(label_power_val, LV_ALIGN_RIGHT_MID, 0, 0);
}

void ui_update_number(struct ina226_value_t values)
{
    if (lvgl_port_lock(100))
    {
        lv_label_set_text_fmt(label_voltage_val, "%.3fV", values.voltage);
        lv_label_set_text_fmt(label_current_val, "%.3fA", values.current);
        lv_label_set_text_fmt(label_power_val, "%.3fW", values.power);

        lvgl_port_unlock();
    }
}