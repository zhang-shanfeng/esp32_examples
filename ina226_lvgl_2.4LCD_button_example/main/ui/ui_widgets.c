#include "ui_widgets.h"

#include "custom_fonts.h"

lv_obj_t *ui_create_kv_row(lv_obj_t *parent, const struct ui_kv_row_cfg_t *cfg)
{
    lv_obj_t *row = lv_obj_create(parent);
    lv_obj_remove_style_all(row);
    lv_obj_set_layout(row, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(
        row, lv_pct(100), cfg->height ? cfg->height : LV_SIZE_CONTENT);
    lv_obj_set_flex_align(row,
                          LV_FLEX_ALIGN_SPACE_BETWEEN,
                          LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_START);
    if (cfg->pad_ver) { lv_obj_set_style_pad_ver(row, cfg->pad_ver, 0); }
    if (cfg->pad_hor) { lv_obj_set_style_pad_hor(row, cfg->pad_hor, 0); }

    lv_obj_t *left = lv_label_create(row);

    if (cfg->title_font)
    {
        lv_obj_set_style_text_font(left, cfg->title_font, LV_STATE_DEFAULT);
    }

    if (cfg->has_title_color)
    {
        lv_obj_set_style_text_color(left, cfg->title_color, 0);
    }
    lv_label_set_text(left, cfg->title);

    /* 右侧动态数据标签 */
    lv_obj_t *right = lv_label_create(row);
    /* 设置一个固定宽度，以解决容器大小不固定 */
    lv_obj_set_width(right, LV_SIZE_CONTENT);
    if (cfg->value_font)
    {
        lv_obj_set_style_text_font(right, cfg->value_font, 0);
    }
    if (cfg->has_value_color)
    {
        lv_obj_set_style_text_color(right, cfg->value_color, 0);
    }
    lv_label_set_text(right, cfg->value);

    return right;
}