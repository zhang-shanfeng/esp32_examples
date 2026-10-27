#pragma once

#include "ina226_task.h"
#include "lvgl.h"

struct ina226_ui_t
{
    lv_obj_t *label_voltage_val;
    lv_obj_t *label_current_val;
    lv_obj_t *label_power_val;
    lv_obj_t *current_spinbox;
    lv_obj_t *voltage_spinbox;
    lv_obj_t *power_spinbox;
};

void switch_to_ina226_page(void);
void page_ina226_update_number(struct ina226_value_t values);
