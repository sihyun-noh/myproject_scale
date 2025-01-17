#include "../ui.h"
#include "log.h"
#include "syscfg.h"
#include "scale_read_485.h"
#include "esp_system.h"

static const char *TAG = "ui_indicator_model_select_screen";

static void mbox_close_cb(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_current_target(e);
  LOGI(TAG, "Button %s clicked", lv_msgbox_get_active_btn_text(obj));
  if (strcmp(lv_msgbox_get_active_btn_text(obj), "Close") == 0) {
    lv_msgbox_close(obj);
  }
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    LV_UNUSED(obj);
    char str_buf[10] = { 0 };
    strncpy(str_buf, lv_list_get_btn_text(indicator_list, obj), sizeof(str_buf));
    LOGI(TAG, "Clicked: %s", str_buf);
    syscfg_set(CFG_DATA, "INDICATOR_MODEL", str_buf);
    if (strncmp(str_buf, "BX11", 4) == 0) {
      char *str = "Selected indicator model is BX11 ";
      static const char *btns[] = { "Close", "" };
      lv_obj_t *mbox_selected_indicator_model = lv_msgbox_create(NULL, "Success!", str, btns, true);
      lv_obj_add_event_cb(mbox_selected_indicator_model, mbox_close_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox_selected_indicator_model);
    } else if (strncmp(str_buf, "WTM-500", 7) == 0) {
      char *str = "Selected indicator model is WTM-500 ";
      static const char *btns[] = { "Close", "" };
      lv_obj_t *mbox_selected_indicator_model = lv_msgbox_create(NULL, "Success!", str, btns, true);
      lv_obj_add_event_cb(mbox_selected_indicator_model, mbox_close_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox_selected_indicator_model);
    } else if (strncmp(str_buf, "none", 4) == 0) {
      char *str = "Retry selection";
      static const char *btns[] = { "Close", "" };
      lv_obj_t *mbox_selected_indicator_model = lv_msgbox_create(NULL, "Notific", str, btns, true);
      lv_obj_add_event_cb(mbox_selected_indicator_model, mbox_close_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox_selected_indicator_model);
    }
  }
}

static void mbox_close_reboot_cb(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_current_target(e);
  LOGI(TAG, "Button %s clicked", lv_msgbox_get_active_btn_text(obj));
  if (strcmp(lv_msgbox_get_active_btn_text(obj), "OK") == 0) {
    esp_restart();
    lv_msgbox_close(obj);
  } else if (strcmp(lv_msgbox_get_active_btn_text(obj), "NO") == 0) {
    _ui_screen_change(&ui_Main_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, &ui_main_screen_init);
    lv_msgbox_close(obj);
    lv_obj_clean(ui_Indicator_Model_Select_Screen);  // Function execution to prevent memory leaks
  }
}

static void ui_Indicator_Model_Select_Screen_Comfirm_Btn_e_hendler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target(e);
  if (code == LV_EVENT_CLICKED) {
    //_ui_screen_change(&ui_Main_Screen, LV_SCR_LOAD_ANIM_FADE_ON, 100, 100, &ui_main_screen_init);

    char *str = "Would you like to restart now? ";
    static const char *_btns[] = { "OK", "NO", "" };
    lv_obj_t *mbox_restart = lv_msgbox_create(NULL, "Restart!", str, _btns, true);
    lv_obj_add_event_cb(mbox_restart, mbox_close_reboot_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox_restart);

    // lv_obj_clean(ui_Indicator_Model_Select_Screen);  // Function execution to prevent memory leaks
  }
}
void ui_indicator_model_select_screen_init(void) {
  /*Create a list*/
  ui_Indicator_Model_Select_Screen = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_Indicator_Model_Select_Screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  indicator_list = lv_list_create(ui_Indicator_Model_Select_Screen);
  lv_obj_set_size(indicator_list, 300, 250);
  lv_obj_set_x(indicator_list, -50);
  lv_obj_set_y(indicator_list, 0);
  lv_obj_set_align(indicator_list, LV_ALIGN_CENTER);

  /*Add buttons to the list*/
  lv_obj_t *btn;
  lv_list_add_text(indicator_list, "CAS");
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "WTM-500");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_list_add_text(indicator_list, "BAYKON");
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "BX11");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_FILE, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_list_add_text(indicator_list, "OTHER");
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_OK, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
  btn = lv_list_add_btn(indicator_list, LV_SYMBOL_CLOSE, "none");
  lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t *ui_Indicator_Model_Select_Screen_Comfirm_Btn = lv_btn_create(ui_Indicator_Model_Select_Screen);
  lv_obj_set_width(ui_Indicator_Model_Select_Screen_Comfirm_Btn, LV_SIZE_CONTENT);
  lv_obj_set_height(ui_Indicator_Model_Select_Screen_Comfirm_Btn, LV_SIZE_CONTENT);
  lv_obj_set_x(ui_Indicator_Model_Select_Screen_Comfirm_Btn, 160);
  lv_obj_set_y(ui_Indicator_Model_Select_Screen_Comfirm_Btn, 90);
  lv_obj_set_align(ui_Indicator_Model_Select_Screen_Comfirm_Btn, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_Indicator_Model_Select_Screen_Comfirm_Btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_Indicator_Model_Select_Screen_Comfirm_Btn, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_Indicator_Model_Select_Screen_Comfirm_Btn, lv_color_hex(0xff0060),
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_event_cb(ui_Indicator_Model_Select_Screen_Comfirm_Btn,
                      ui_Indicator_Model_Select_Screen_Comfirm_Btn_e_hendler, LV_EVENT_ALL, NULL);

  lv_obj_t *ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label =
      lv_label_create(ui_Indicator_Model_Select_Screen_Comfirm_Btn);
  lv_obj_set_width(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, -3);
  lv_obj_set_y(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, 1);
  lv_label_set_text(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, "완 료");
  lv_obj_set_style_text_font(ui_Indicator_Model_Select_Screen_Comfirm_Btn_Label, &NanumBar24,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}
