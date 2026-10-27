/**************************************************************************************************
 * @file ui_widgets.h
 * @author freerealmshn@gmail.com (xiaotupo@163.com)
 * @brief
 * @version V0.1.0
 * @date 2026-10-27
 *
 * @copyright Copyright (c) 2025 by zhang-shanfeng, All Rights Reserved.
 * @website https://zhang-shanfeng.github.io
 *
 *************************************************************************************************/
#pragma once

#include "lvgl.h"

struct ui_kv_row_cfg_t
{
    const char *title;
    const char *value;
    const lv_font_t *title_font;
    const lv_font_t *value_font;
    lv_color_t title_color;
    bool has_title_color;
    lv_color_t value_color;
    bool has_value_color;
    lv_coord_t height;
    lv_coord_t pad_ver; /* 上下内边距 */
    lv_coord_t pad_hor; /* 左右内边距 */
};

lv_obj_t *ui_create_kv_row(lv_obj_t *parent, const struct ui_kv_row_cfg_t *cfg);