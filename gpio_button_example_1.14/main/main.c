/*
 * button Demo
 *
 * `idf.py add-dependency "espressif/button^4.2.1"`
 */
#include "button_task.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lcd_lvgl_task.h"
#include "sdkconfig.h"
#include "utility_c.h"

static const char *TAG = "gpio_button_example";

extern esp_lcd_panel_io_handle_t io_handle;
extern esp_lcd_panel_handle_t panel_handle;
float num = 0.16f;
void app_main(void)
{
    button_task_init();
    lcd_init();
    lvgl_init(io_handle, panel_handle);

    if (lvgl_port_lock(0))
    {
        ui_init();
        lvgl_port_unlock();
    }

    while (1)
    {
#ifdef CONFIG_ENABLE_FixedString_TEST_FUNC
        test();
#endif
        num += 0.245f;
        if (lvgl_port_lock(0))
        {
            ui_update_number(num);
            lvgl_port_unlock();
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
