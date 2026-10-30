#include "page_ina226.h"

#include "custom_fonts.h"
#include "esp_lvgl_port.h"
#include "ui_styles.h"
#include "ui_widgets.h"

static void ina226_ui_init(lv_obj_t *parent);
static struct ui_kv_row_cfg_t make_ina226_kv_cfg(const char *title,
                                                 const char *value);
static void create_page_header(lv_obj_t *parent, const char *text);
static void create_main_show_cont(lv_obj_t *parent);
static void create_spinbox_group(lv_obj_t *parent);

lv_obj_t *ina226_page_root = NULL;

static struct ina226_ui_t ina226_ui;
extern lv_group_t *ina226_group;

void switch_to_ina226_page(void)
{
    if (lvgl_port_lock(0))
    {
        // 如果没有创建过，则创建
        if (ina226_page_root == NULL)
        {
            ina226_page_root = lv_obj_create(NULL);
            ina226_ui_init(ina226_page_root);
        }
        // 切换页面
        lv_screen_load(ina226_page_root);

        lvgl_port_unlock();
    }
}

void ina226_ui_init(lv_obj_t *parent)
{
    /* Screen 根样式 */
    static lv_style_t style_root;
    lv_style_init(&style_root);
    lv_style_set_bg_color(&style_root, lv_color_black());
    lv_style_set_bg_opa(&style_root, LV_OPA_100);
    lv_style_set_size(&style_root, lv_pct(100), lv_pct(100));

    static int32_t col_dsc[] = {
        LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
    static int32_t row_dsc[] = {
        LV_GRID_CONTENT, LV_GRID_CONTENT, LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

    lv_obj_set_grid_dsc_array(parent, col_dsc, row_dsc);
    lv_obj_set_style_pad_row(parent, 10, 0);
    lv_obj_set_style_pad_column(parent, 10, 0);

    /* 给根容器 设置样式 */
    lv_obj_add_style(parent, &style_root, LV_STATE_DEFAULT);

    create_page_header(parent, "INA226 电压、电流、功率测量");

    create_main_show_cont(parent);

    create_spinbox_group(parent);
}

void page_ina226_update_number(struct ina226_value_t values)
{
    if (lvgl_port_lock(100))
    {
        lv_label_set_text_fmt(
            ina226_ui.label_voltage_val, "%.3fV", values.voltage);
        lv_label_set_text_fmt(
            ina226_ui.label_current_val, "%.3fA", values.current);
        lv_label_set_text_fmt(ina226_ui.label_power_val, "%.3fW", values.power);

        lvgl_port_unlock();
    }
}

/**************************************************************************************************
 * @brief 工厂函数，用于创造 ui_kv_row_cfg_t 配置
 *
 * @param title
 * @param value
 * @return struct ui_kv_row_cfg_t
 * @date 2026-10-28
 * @details
 * @Call 该函数调用的其他函数
 * @Caller 调用该函数的其他函数
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static struct ui_kv_row_cfg_t make_ina226_kv_cfg(const char *title,
                                                 const char *value)
{
    return (struct ui_kv_row_cfg_t){
        .title = title,
        .value = value,
        .title_font = &alibaba_puhuiti_regular_24_4bpp,
        .value_font = &ibm_plex_mono_medium_24_2bpp,
        .height = 0,
        .pad_ver = 4,
        .pad_hor = 0,
        .has_title_color = true,
        .title_color = lv_palette_darken(LV_PALETTE_DEEP_ORANGE, 1),
        .has_value_color = true,
        .value_color = lv_color_white(),
    };
}

static void create_page_header(lv_obj_t *parent, const char *text)
{
    /* 顶部（标题容器样式） */
    static lv_style_t style_top_cont;
    static bool inited = false;

    if (!inited)
    {
        lv_style_init(&style_top_cont);
        lv_style_set_bg_color(&style_top_cont, lv_color_hex(0x30475E));
        lv_style_set_bg_opa(&style_top_cont, LV_OPA_100);
        lv_style_set_text_color(&style_top_cont,
                                lv_palette_lighten(LV_PALETTE_AMBER, 1));
        lv_style_set_pad_ver(&style_top_cont, 4);
        lv_style_set_size(&style_top_cont, lv_pct(100), LV_SIZE_CONTENT);
    }

    /* 顶部容器 */
    lv_obj_t *top_cont = lv_obj_create(parent);
    lv_obj_remove_style_all(top_cont); /* 清除默认样式 */
    lv_obj_set_grid_cell(
        top_cont, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_CENTER, 0, 1);
    lv_obj_add_style(top_cont, &style_top_cont, LV_STATE_DEFAULT);

    lv_obj_t *label_title = lv_label_create(top_cont);
    lv_obj_set_style_text_color(
        label_title, lv_palette_lighten(LV_PALETTE_AMBER, 1), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(
        label_title, &smiley_sans_oblique_24_4bpp, LV_STATE_DEFAULT);
    lv_label_set_text(label_title, text);
    lv_obj_set_align(label_title, LV_ALIGN_CENTER);
}

void create_main_show_cont(lv_obj_t *parent)
{
    /*
        布局说明
        左右布局
        左侧显示：电压，电流，功率显示
        右侧显示：启动按钮
        需要两层 flex
    */

    /* 创建一个容器 */
    lv_obj_t *left = lv_obj_create(parent);
    lv_obj_remove_style_all(left);
    lv_obj_set_grid_cell(
        left, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    lv_obj_set_layout(left, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(left, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        left, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    border_style_apply(left);
    lv_obj_set_style_border_color(
        left, lv_palette_lighten(LV_PALETTE_ORANGE, 1), 0);
    lv_obj_set_style_pad_all(left, 4, 0);
    lv_obj_set_height(left, LV_SIZE_CONTENT);

    /* 电压行参数配置 */
    struct ui_kv_row_cfg_t cfg = make_ina226_kv_cfg("电压", "0.000V");
    /* 创建电压行 */
    ina226_ui.label_voltage_val = ui_create_kv_row(left, &cfg);

    /* 电流行参数配置 */
    cfg = make_ina226_kv_cfg("电流", "0.000A");
    /* 创建电流行 */
    ina226_ui.label_current_val = ui_create_kv_row(left, &cfg);

    /* 功率行参数配置 */
    cfg = make_ina226_kv_cfg("功率", "0.000W");
    /* 创建功率行 */
    ina226_ui.label_power_val = ui_create_kv_row(left, &cfg);

    /* 右侧：放启动按钮 */
    lv_obj_t *right = lv_obj_create(parent);
    lv_obj_remove_style_all(right);
    lv_obj_set_grid_cell(
        right, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
    border_style_apply(right);
    lv_obj_set_height(right, LV_SIZE_CONTENT);

    lv_obj_t *btn_start = lv_button_create(right);
    lv_obj_align(btn_start, LV_ALIGN_CENTER, 0, 0);
    lv_obj_t *btn_start_label = lv_label_create(btn_start);
    lv_obj_set_style_text_font(btn_start, &ibm_plex_mono_medium_18_2bpp, 0);
    lv_label_set_text(btn_start_label, "Start");

    lv_group_add_obj(ina226_group, btn_start);
}

/**************************************************************************************************
 * @brief Create a spinbox group object
 * 电流最大报警值
 * 电压最大报警值
 * 功率最大报警值
 * @param parent
 * @date 2026-10-28
 * @details
 * @Call 该函数调用的其他函数
 * @Caller 调用该函数的其他函数
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
void create_spinbox_group(lv_obj_t *parent)
{
    // lv_obj_update_layout(parent);
    static lv_style_t cont_style;
    lv_style_init(&cont_style);
    lv_style_set_layout(&cont_style, LV_LAYOUT_FLEX);
    lv_style_set_flex_flow(&cont_style, LV_FLEX_FLOW_ROW);
    lv_style_set_pad_all(&cont_style, 4);

    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_remove_style_all(cont);
    lv_obj_set_grid_cell(
        cont, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 2, 1);

    lv_obj_add_style(cont, &cont_style, 0);
    lv_obj_set_flex_align(
        cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    border_style_apply(cont);
    lv_obj_set_style_border_color(
        cont, lv_palette_darken(LV_PALETTE_BLUE, 1), 0);

    ina226_ui.current_spinbox = lv_spinbox_create(cont);
    lv_spinbox_set_range(ina226_ui.current_spinbox, 0, 10000);
    lv_spinbox_set_digit_format(ina226_ui.current_spinbox, 5, 2);
    lv_spinbox_step_prev(ina226_ui.current_spinbox);
    lv_obj_set_style_pad_all(ina226_ui.current_spinbox, 3, 0);
    lv_obj_set_style_text_font(
        ina226_ui.current_spinbox, &ibm_plex_mono_medium_24_2bpp, 0);
    lv_obj_set_style_radius(ina226_ui.current_spinbox, 8, 0);
    lv_obj_set_size(ina226_ui.current_spinbox, 120, LV_SIZE_CONTENT);

    lv_group_add_obj(ina226_group, ina226_ui.current_spinbox);
}