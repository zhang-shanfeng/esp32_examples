/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/temperature_sensor.h"

static const char *TAG = "example";

/* 引脚定义 */
#define LED_GPIO_PIN GPIO_NUM_1 /* LED连接的GPIO端口 */

TaskHandle_t led_task_handle = NULL;
bool g_enable_led = false;

void led_task(void *pvParameters)
{
    // gpio_reset_pin(LED_GPIO_PIN); // 要把这行注释起来，否则运行会出错，因为 GPIO_NUM_1 是保留用途
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_INPUT_OUTPUT);
    gpio_set_level(LED_GPIO_PIN, 1); // 初始化 LED 为关闭状态,高电平熄灭
    uint8_t led_state = 0;

    while (1)
    {
        if (g_enable_led)
        {
            ESP_LOGI(TAG, "LED Task Running");
            gpio_set_level(LED_GPIO_PIN, led_state = !led_state);
        }
        UBaseType_t free_stack = uxTaskGetStackHighWaterMark(NULL);
        if (free_stack < 256)
        { // 少于 1KB 空闲
            ESP_LOGW("STACK", "LED task low stack: %u words", free_stack);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    xTaskCreate(led_task, "led_task", 2048, NULL, 5, &led_task_handle);

    ESP_LOGI(TAG, "Install temperature sensor, expected temp ranger range: 10~50 ℃");
    temperature_sensor_handle_t temp_sensor = NULL;
    temperature_sensor_config_t temp_sensor_config = TEMPERATURE_SENSOR_CONFIG_DEFAULT(10, 50);
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor_config, &temp_sensor));

    ESP_LOGI(TAG, "Enable temperature sensor");
    ESP_ERROR_CHECK(temperature_sensor_enable(temp_sensor));

    ESP_LOGI(TAG, "Read temperature");

    float tsens_value; // 存储温度传感器的温度
    while (1)
    {
        ESP_ERROR_CHECK(temperature_sensor_get_celsius(temp_sensor, &tsens_value));
        ESP_LOGI(TAG, "Temperature value %.02f ℃", tsens_value);

        g_enable_led = (tsens_value >= 22.0f);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
