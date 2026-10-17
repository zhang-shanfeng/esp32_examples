/**************************************************************************************************
 * @file button_task.c
 * @author freerealmshn@gmail.com
 * @brief
 * @version V0.1.0
 * @date 2026-10-07
 *
 * @copyright Copyright (c) 2025 by zhang-shanfeng, All Rights Reserved.
 * @website https://zhang-shanfeng.github.io
 *
 *************************************************************************************************/
#include "button_task.h"

#include "button_adc.h"
#include "esp_log.h"
#include "iot_button.h"

static const char *TAG = "button_task";

struct adc_button_range_t
{
    uint16_t min_mv;
    uint16_t max_mv;
};

static const struct adc_button_range_t button_ranges[] = {
    {.min_mv = 500, .max_mv = 650},   /* 2.2K */
    {.min_mv = 720, .max_mv = 820},   /* 3.3K */
    {.min_mv = 980, .max_mv = 1180},  /* 4.7K */
    {.min_mv = 1236, .max_mv = 1436}, /* 6.8K */
    {.min_mv = 1550, .max_mv = 1750}, /* 10K */
    {.min_mv = 1880, .max_mv = 2080}, /* 15K */
    {.min_mv = 2176, .max_mv = 2376}, /* 22K */
    {.min_mv = 2440, .max_mv = 2640}, /* 33K */
};

/**************************************************************************************************
 * @brief 按键单击事件回调函数
 *
 * @param arg 注册时传递的参数
 * @param usr_data 注册时传递的数据
 * @date 2026-10-07
 * @details
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static void button_single_click_cb(void *arg, void *usr_data)
{
    // 可以通过 usr_data 区分是哪个按键，或者在注册时传入不同回调

    int data = (int)(intptr_t)usr_data;
    switch (data)
    {
        case 1:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 2:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 3:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 4:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 5:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 6:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 7:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;
        case 8:
            ESP_LOGI(TAG, "Single Click on button index: %d", data);
            break;

        default:
            break;
    }
}

/**************************************************************************************************
 * @brief 按键长按事件回调函数
 *
 * @param arg 注册时传递的参数
 * @param usr_data 注册时传递的数据
 * @date 2026-10-07
 * @details
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static void button_long_press_start_cb(void *arg, void *usr_data)
{
    ESP_LOGI(
        TAG, "Long Press Start on button index: %d", (int)(intptr_t)usr_data);
}

/**************************************************************************************************
 * @brief 按键长按保持事件回调函数
 *
 * @param arg 注册时传递的参数
 * @param usr_data 注册时传递的数据
 * @date 2026-10-07
 * @details
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static void button_long_press_hold_cb(void *arg, void *usr_data)
{
    ESP_LOGI(
        TAG, "Long Press Hold on button index: %d", (int)(intptr_t)usr_data);
}

/**************************************************************************************************
 * @brief 按键双击事件回调函数
 *
 * @param arg 注册时传递的参数
 * @param usr_data 注册时传递的数据
 * @date 2026-10-07
 * @details
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static void button_double_click_cb(void *arg, void *usr_data)
{
    ESP_LOGI(TAG, "Double Click on button index: %d", (int)(intptr_t)usr_data);
}

// --- 创建单个 ADC 按键的辅助函数 ---

/**************************************************************************************************
 * @brief 创建单个 ADC 按键
 *
 * @param index
 * @param min_mv
 * @param max_mv
 * @return button_handle_t
 * @date 2026-10-07
 * @details
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
static button_handle_t create_adc_button(uint8_t index,
                                         uint16_t min_mv,
                                         uint16_t max_mv)
{
    // 1. 基础配置，通常留空或设置通用参数
    const button_config_t btn_cfg = {
        .long_press_time = 1500,  // 可选：自定义长按阈值，0 表示使用默认
        .short_press_time = 135,
    };

    // 2. ADC 专属配置
    button_adc_config_t adc_cfg = {
        .unit_id = ADC_UNIT_1,         // ADC1
        .adc_channel = ADC_CHANNEL_4,  // 假设使用 GPIO5
        .button_index = index,         // 按键在通道上的索引，需唯一
        .min = min_mv,                 // 电压下限 (mV)
        .max = max_mv,                 // 电压上限 (mV)
    };

    // 3. 使用 v4.x 专用 API 创建
    button_handle_t btn = NULL;
    esp_err_t ret = iot_button_new_adc_device(&btn_cfg, &adc_cfg, &btn);
    if (ret != ESP_OK || btn == NULL)
    {
        ESP_LOGE(TAG, "Failed to create ADC button %d", index);
        return NULL;
    }

    return btn;
}

/**************************************************************************************************
 * @brief 按键初始化函数，初始化完成后直接交由 button 组件的事件系统自行运行
 *
 * @date 2026-10-07
 * @details
 * @Call 该函数调用的其他函数
 * @Caller 调用该函数的其他函数
 * @author freerealmshn@gmail.com
 * @note
 *************************************************************************************************/
void button_task_init(void)
{
    for (int i = 0; i < 8; i++)
    {
        button_handle_t btn = create_adc_button(
            i, button_ranges[i].min_mv, button_ranges[i].max_mv);

        if (btn)
        {
            iot_button_register_cb(btn,
                                   BUTTON_SINGLE_CLICK,
                                   NULL,
                                   button_single_click_cb,
                                   (void *)(intptr_t)(i + 1));

            iot_button_register_cb(btn,
                                   BUTTON_LONG_PRESS_START,
                                   NULL,
                                   button_long_press_start_cb,
                                   (void *)(intptr_t)(i + 1));

            iot_button_register_cb(btn,
                                   BUTTON_DOUBLE_CLICK,
                                   NULL,
                                   button_double_click_cb,
                                   (void *)(intptr_t)(i + 1));
            iot_button_register_cb(btn,
                                   BUTTON_LONG_PRESS_HOLD,
                                   NULL,
                                   button_long_press_hold_cb,
                                   (void *)(intptr_t)(i + 1));
        }
    }
}