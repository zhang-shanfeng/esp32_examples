#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "esp_log.h"

static char *TAG = "UNIQUE_ID_EXAMPLE";

void app_main(void)
{
    uint8_t mac[6];
    esp_base_mac_addr_get(mac);
    ESP_LOGI("UNIQUE", "Device MAC: %02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}
