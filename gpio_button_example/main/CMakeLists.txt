set(app_srcs
    "main.c"
    "button_task.c"
    "lcd_lvgl_task.c"
    "fire_code_14.c"
    "fire_code_16.c"
    "fire_code_18.c"
    "fire_code_20.c"
    "utility.cpp"
)

idf_component_register(SRCS ${app_srcs}
                       PRIV_REQUIRES spi_flash
                       INCLUDE_DIRS "")

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-function)