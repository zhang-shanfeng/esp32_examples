#include "page_home.h"

#include "esp_lvgl_port.h"
#include "lvgl.h"

LV_FONT_DECLARE(ibm_plex_mono_medium_16_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_18_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_20_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_22_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_24_2bpp);
LV_FONT_DECLARE(ibm_plex_mono_medium_26_2bpp);
LV_FONT_DECLARE(alibaba_puhuiti_regular_22_4bpp);
LV_FONT_DECLARE(alibaba_puhuiti_regular_24_4bpp);
LV_FONT_DECLARE(smiley_sans_oblique_24_4bpp);

static void home_ui_init(lv_obj_t *parent);

lv_obj_t *home_page = NULL;
void switch_to_home_page(void)
{
    if (lvgl_port_lock(0))
    {
        // 如果没有创建过，则创建
        if (home_page == NULL)
        {
            home_page = lv_obj_create(NULL);
            home_ui_init(home_page);
        }
        // 切换页面
        lv_screen_load(home_page);

        lvgl_port_unlock();
    }
}

void home_ui_init(lv_obj_t *parent)
{
    lv_obj_t *container = lv_obj_create(parent);

    lv_obj_set_size(container, lv_pct(100), lv_pct(100));
    lv_obj_t *logo = lv_label_create(container);
    lv_label_set_text(logo, "INA226 V1.0");

    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);
}
