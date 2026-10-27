#include "lvgl_app.h"

#include <stdio.h>

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

void lvgl_app_init(void)
{
    lcd_init();

    lvgl_init(io_handle, panel_handle);

    styles_init();
    border_style_init();

    switch_to_home_page();  // 上电默认显示页面

    vTaskDelay(pdMS_TO_TICKS(2000));
    switch_to_ina226_page();
}