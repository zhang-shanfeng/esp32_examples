idf_component_register(SRCS "temp_sensor_main.c"
                       PRIV_REQUIRES 
                            esp_driver_tsens
                            driver
                       INCLUDE_DIRS ".")
