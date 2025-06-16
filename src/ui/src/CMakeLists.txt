SET(SOURCES ui_comp_homebutton.c
    ui_comp.c
    ui_Stand_by.c
    ui_Clock.c
    ui_SD_Card.c
    ui_Serial.c
    ui_Control_Center.c
    ui_Apps_Menu.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    ui_img_standby_png.c
    ui_img_dynamic_clock_png.c
    ui_img_file_png.c
    ui_img_air_mouse_png.c
    ui_img_badusb_png.c
    ui_img_machine_learning_png.c
    ui_img_spam_apple_png.c
    ui_img_webserial_png.c
    ui_img_control_center_png.c
    ui_img_app_bg_png.c
    ui_img_sd_card_png.c
    ui_img_battery_3_png.c
    ui_img_micro_sd_card_4_png.c
    ui_img_rectangle_12_png.c)

add_library(ui ${SOURCES})
