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

#define LCD_WIDTH 160
#define LCD_HEIGHT 80

esp_lcd_panel_io_handle_t io_handle = NULL;
esp_lcd_panel_handle_t panel_handle = NULL;

LV_FONT_DECLARE(fire_code_16);
LV_FONT_DECLARE(fire_code_20);

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

        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,

        .bits_per_pixel = 16,
        .data_endian = LCD_RGB_DATA_ENDIAN_LITTLE,  // LCD_RGB_DATA_ENDIAN_LITTLE
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
     *
     * 这里先给出常见 80x160 模块的示例。
     */

    ESP_ERROR_CHECK(esp_lcd_panel_set_gap(panel_handle, 1, 26));

    // --------------------------------------------------
    // 7. 颜色反转
    // --------------------------------------------------

    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));

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

        .buffer_size = LCD_WIDTH * LCD_HEIGHT,

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
                .buff_spiram = false,
                .sw_rotate = false,
            },
    };

    return lvgl_port_add_disp(&display_cfg);
}

static lv_obj_t *label;
void ui_init(void)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x2A1A0E), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);

    label = lv_label_create(scr);
    lv_obj_set_style_text_color(label, lv_color_hex(0xD9361E), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &fire_code_20, LV_STATE_DEFAULT);
    lv_label_set_text(label, "Hello ST7789!\n0");

    // lv_obj_center(label);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
}

void ui_update_number(float value)
{
    char buf[32];  // 缓冲区大小根据实际情况调整
    snprintf(buf, sizeof(buf), "num:%.2f", value);
    lv_label_set_text(label, buf);
}