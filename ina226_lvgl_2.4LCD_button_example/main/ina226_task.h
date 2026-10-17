#pragma once

struct ina226_value_t
{
    float voltage;
    float current;
    float power;
};

void ina226_task(void *pvParameters);
