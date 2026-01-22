/*
 * ESPIDF nvs 实验
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"


static const char *TAG = "NVS_EXAMPLE";

void app_main(void)
{
    esp_err_t err;

    // === 步骤1：初始化 NVS ===
    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND){
        // nvs 分区已满或版本不兼容，擦除后重试
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    // === 步骤2：打开命名空间 ===
    nvs_handle_t my_handle;
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(err));
        return;
    }

    // === 步骤3：读取 counter ===
    int32_t counter = 0; // 默认值
    err = nvs_get_i32(my_handle, "counter", &counter);
    switch (err)
    {
    case ESP_OK:
        ESP_LOGI(TAG, "Read counter: %ld", counter);
        break;
    case ESP_ERR_NVS_NOT_FOUND:
        ESP_LOGI(TAG, "The counter doesn't exist yet. Starting from 0.");
        break;
    default:
        ESP_LOGE(TAG, "Error (%s) reading counter!", esp_err_to_name(err));
        break;
    }

    // === 步骤4：counter +1 并写回 ===
    counter++;
    ESP_LOGI(TAG, "Updating counter to %ld", counter);
    err = nvs_set_i32(my_handle, "counter", counter);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write counter (%s)!", esp_err_to_name(err));
    }

    // === 步骤5：写入/读取字符串 ===
    const char* message = "Hello from NVS!";
    err = nvs_set_str(my_handle, "message", message);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write message (%s)!", esp_err_to_name(err));
    }

    // 读取字符串（需要先获取长度）
    size_t required_size = 0;
    err = nvs_get_str(my_handle, "message", NULL, &required_size);
    if (err == ESP_OK) {
        char* buffer = malloc(required_size);
        nvs_get_str(my_handle, "message", buffer, &required_size);
        ESP_LOGI(TAG, "Read message: %s", buffer);
        free(buffer);
    } else {
        ESP_LOGE(TAG, "Failed to read message (%s)", esp_err_to_name(err));
    }

    // === 步骤6：提交并关闭 ===
    nvs_commit(my_handle);
    nvs_close(my_handle);

    // === 步骤7：验证重启后数据保留 ===
    ESP_LOGI(TAG, "Restart your device to see the counter increase!");
}
