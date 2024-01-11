/*
 * Copyright (c) 2021 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zmk/event_manager.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display/widgets/megumin.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

const void **images;
uint8_t images_len;

LV_IMG_DECLARE(normal_img1);
LV_IMG_DECLARE(normal_img2);
LV_IMG_DECLARE(normal_img3);
LV_IMG_DECLARE(normal_img4);
LV_IMG_DECLARE(normal_img5);
LV_IMG_DECLARE(normal_img6);

const void *normal_images[] = {
    &normal_img1, &normal_img2, &normal_img3, &normal_img4, &normal_img5, &normal_img5,
};

void set_img_src(void *var, lv_anim_value_t val) {
    lv_obj_t *img = (lv_obj_t *)var;
    lv_img_set_src(img, images[val]);
}

void update_megumin(struct zmk_widget_megumin *widget, int wpm) {

    LOG_DBG("Set source to normal Megumin images!");
    lv_anim_init(&widget->anim);
    lv_anim_set_var(&widget->anim, widget->obj);
    lv_anim_set_time(&widget->anim, 500);
    lv_anim_set_repeat_delay(&widget->anim, 500);
    lv_anim_set_values(&widget->anim, 0, 5);
    lv_anim_set_exec_cb(&widget->anim, set_img_src);
    lv_anim_set_repeat_count(&widget->anim, LV_ANIM_REPEAT_INFINITE);
    images = normal_images;
    lv_anim_start(&widget->anim);
}

int zmk_widget_megumin_init(struct zmk_widget_megumin *widget, lv_obj_t *parent) {
    widget->obj = lv_img_create(parent, NULL);

    lv_img_set_auto_size(widget->obj, true);
    update_megumin(widget, 0);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_megumin_obj(struct zmk_widget_megumin *widget) { return widget->obj; }