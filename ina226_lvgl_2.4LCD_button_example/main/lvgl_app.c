#include "lvgl_app.h"

#include <stdio.h>

#include "button_task.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "lvgl.h"
#include "lvgl_setup.h"
#include "page_home.h"
#include "page_ina226.h"
#include "ui_styles.h"
#include "ui_widgets.h"

static const char *TAG = "lcd_lvgl_task";
lv_group_t *ina226_group;
lv_indev_t *indev;

void lvgl_app_init(void)
{
    lcd_init();

    lvgl_init(io_handle, panel_handle);

    ina226_group = lv_group_create();

    indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev, keypad_read_cb);

    lv_indev_set_group(indev, ina226_group);

    styles_init();
    border_style_init();

    switch_to_home_page();  // 上电默认显示页面

    vTaskDelay(pdMS_TO_TICKS(1000));
    switch_to_ina226_page();
}