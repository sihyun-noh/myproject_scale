// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: ms_type

#include "../ui.h"
#include "log.h"

static const char *TAG = "ui_mode_1_main_set_reg_Screen";

static bool ta1_selected;
static bool ta2_selected;
static bool ta3_selected;
// static bool ta4_selected;
// static bool ta5_selected;

static textareas_t use_text_area;

void ui_all_delete_btn_e_handler(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  textareas_t *ta = lv_event_get_user_data(e);
  if (event_code == LV_EVENT_CLICKED) {
    lv_textarea_set_text(ta->ta1, "\0");
    lv_textarea_set_text(ta->ta2, "\0");
    lv_textarea_set_text(ta->ta3, "\0");
  }
}

void ui_comfirm_btn_e_hendler(lv_event_t *e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  textareas_t *ta = lv_event_get_user_data(e);
  if (event_code == LV_EVENT_CLICKED) {
    _ui_screen_change(&ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, &ui_Screen1_screen_init);
    lv_event_send(ta->ta1, LV_EVENT_READY, NULL);
    lv_event_send(ta->ta2, LV_EVENT_READY, NULL);
    lv_event_send(ta->ta3, LV_EVENT_READY, NULL);
    // lv_obj_clean(ui_Screen2);
  }
}

void textarea_event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);

  if (code == LV_EVENT_FOCUSED) {
    ta1_selected = true;
    ta2_selected = false;
    ta3_selected = false;
    // ta4_selected = false;
    // ta5_selected = false;
    LOGI(TAG, "event call ta1");
  } else if (code == LV_EVENT_READY) {
    // upper_weight_value = atoi(lv_textarea_get_text(ta));
    sscanf(lv_textarea_get_text(ta), "%f", &upper_weight_value);
    LOGI(TAG, "Enter was pressed. The current text is: %f", upper_weight_value);
  }
  /*Todo : */
}

void textarea_event_handler1(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);
  if (code == LV_EVENT_FOCUSED) {
    ta2_selected = true;
    ta1_selected = false;
    ta3_selected = false;
    // ta4_selected = false;
    // ta5_selected = false;
    LOGI(TAG, "event call ta2");
  } else if (code == LV_EVENT_READY) {
    // lower_weight_value = atoi(lv_textarea_get_text(ta));
    sscanf(lv_textarea_get_text(ta), "%f", &lower_weight_value);
    LOGI(TAG, "Enter was pressed. The current text is: %f", lower_weight_value);
  }

  // /*Todo : */
}

void textarea_event_handler2(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *ta = lv_event_get_target(e);
  if (code == LV_EVENT_FOCUSED) {
    ta3_selected = true;
    ta1_selected = false;
    ta2_selected = false;
    // ta4_selected = false;
    // ta5_selected = false;
    LOGI(TAG, "event call ta3");
  } else if (code == LV_EVENT_READY) {
    prod_num_value = atoi(lv_textarea_get_text(ta));
    LOGI(TAG, "Enter was pressed. The current text is: %d", prod_num_value);
  }
  // /*Todo : */
}
void btnm_event_handler(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_target(e);
  // lv_obj_t * ta = lv_event_get_user_data(e);
  const char *txt = lv_btnmatrix_get_btn_text(obj, lv_btnmatrix_get_selected_btn(obj));
  lv_obj_t *ta = use_text_area.ta1;

  if (ta1_selected) {
    ta = use_text_area.ta1;
    LOGI(TAG, "Send data to ta1");
  } else if (ta2_selected) {
    ta = use_text_area.ta2;
    LOGI(TAG, "Send data to ta2");
  } else if (ta3_selected) {
    ta = use_text_area.ta3;
    LOGI(TAG, "Send data to ta3");
  }

  if (strcmp(txt, "C") == 0)
    lv_textarea_del_char(ta);
  else if (strcmp(txt, LV_SYMBOL_NEW_LINE) == 0)
    lv_event_send(ta, LV_EVENT_READY, NULL);
  else
    lv_textarea_add_text(ta, txt);
}

static void event_cb(lv_event_t *e) {
  lv_obj_t *obj = lv_event_get_current_target(e);
  LOGI(TAG, "Button %s clicked", lv_msgbox_get_active_btn_text(obj));
  if (strcmp(lv_msgbox_get_active_btn_text(obj), "Close") == 0) {
    lv_msgbox_close(obj);
  }
}

void ui_register_pord_num_btn_e_hendler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *target = lv_event_get_target(e);
  textareas_t *ta = lv_event_get_user_data(e);

  char set_str[50] = { 0 };
  char get_str[50] = { 0 };
  char s_key[10] = { 0 };
  char cmp_pord_num[10] = { 0 };
  char cfg_pord_num[10] = { 0 };
  if (code == LV_EVENT_CLICKED) {
    lv_event_send(ta->ta1, LV_EVENT_READY, NULL);
    lv_event_send(ta->ta2, LV_EVENT_READY, NULL);
    lv_event_send(ta->ta3, LV_EVENT_READY, NULL);

    /*start num 0, and Make sure enter it starts from number 0.*/
    memset(get_str, 0x00, sizeof(get_str));
    snprintf(s_key, sizeof(s_key), "Prod%02d", prod_num_value);
    LOGI(TAG, "key:%s", s_key);
    syscfg_get(CFG_DATA, s_key, get_str, sizeof(get_str));
    LOGI(TAG, "value:%s", get_str);
    /*compare same product num*/
    snprintf(cmp_pord_num, sizeof(cmp_pord_num), "%02d", prod_num_value);
    snprintf(cfg_pord_num, sizeof(cfg_pord_num), "%.2s", get_str);
    if (strcmp(cfg_pord_num, cmp_pord_num) == 0) {
      static const char *btns[] = { "Close", "" };
      lv_obj_t *mbox1 = lv_msgbox_create(NULL, "Oops!", "It's already registered.", btns, true);
      lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox1);
    } else if (prod_num_value > PROD_NUM) {
      // erroe when entering product number over PROD_NUM value
      char s_message[30] = { 0 };
      static const char *btns[] = { "Close", "" };
      snprintf(s_message, sizeof(s_message), "Available from 0 to %d", PROD_NUM);
      lv_obj_t *mbox2 = lv_msgbox_create(NULL, "Oops!", s_message, btns, true);
      lv_obj_add_event_cb(mbox2, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox2);
    } else if (lower_weight_value >= upper_weight_value && prod_num_value != 0) {
      // pord_num 0 is a special method that does not determine whether it works or not.
      static const char *btns[] = { "Close", "" };
      lv_obj_t *mbox3 = lv_msgbox_create(
          NULL, "Oops!", "Invalid values.\nThe lower input is equal or more than the upper input value.", btns, true);
      lv_obj_add_event_cb(mbox3, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
      lv_obj_center(mbox3);
    } else {
      if (strlen(get_str) == 0) {
        LOGI(TAG, "Set register ");
        int upper_int_part = (int)upper_weight_value;
        int lower_int_part = (int)lower_weight_value;
        float upper_decimal_part = upper_weight_value - upper_int_part;
        float lower_decimal_part = lower_weight_value - lower_int_part;
        int upper_dacimal_to_int_part = (int)upper_decimal_part * 1000;  // decimal point 3
        int lower_decimal_to_int_part = (int)lower_decimal_part * 1000;

        snprintf(set_str, sizeof(set_str), "%02d,upper:%02d.%03d,lower:%02d.%03d", prod_num_value, upper_int_part,
                 upper_dacimal_to_int_part, lower_int_part, lower_decimal_to_int_part);
        LOGI(TAG, "syscfg_data : %s", set_str);
        syscfg_set(CFG_DATA, s_key, set_str);

        static const char *btns[] = { "Close", "" };
        lv_obj_t *mbox4 = lv_msgbox_create(NULL, "OK!", "Registered", btns, true);
        lv_obj_add_event_cb(mbox4, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_center(mbox4);
      }
    }
  }
}

void ui_Screen2_screen_init(void) {
  ui_Screen2 = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  lv_obj_t *ui_prod_num_register_btn = lv_btn_create(ui_Screen2);
  lv_obj_set_width(ui_prod_num_register_btn, 70);
  lv_obj_set_height(ui_prod_num_register_btn, 50);
  lv_obj_set_x(ui_prod_num_register_btn, -190);
  lv_obj_set_y(ui_prod_num_register_btn, 65);
  lv_obj_set_align(ui_prod_num_register_btn, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_prod_num_register_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_prod_num_register_btn, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_prod_num_register_btn, lv_color_hex(0x0079ff), LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_event_cb(ui_prod_num_register_btn, ui_register_pord_num_btn_e_hendler, LV_EVENT_ALL, &use_text_area);

  lv_obj_t *Screen2_prod_num_register_btn_label = lv_label_create(ui_prod_num_register_btn);
  lv_obj_set_width(Screen2_prod_num_register_btn_label, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(Screen2_prod_num_register_btn_label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(Screen2_prod_num_register_btn_label, -3);
  lv_obj_set_y(Screen2_prod_num_register_btn_label, 1);
  lv_label_set_text(Screen2_prod_num_register_btn_label, "등 록");
  lv_obj_set_style_text_font(Screen2_prod_num_register_btn_label, &NanumBar24, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_comfirm_btn = lv_btn_create(ui_Screen2);
  lv_obj_set_width(ui_comfirm_btn, 70);
  lv_obj_set_height(ui_comfirm_btn, 50);
  lv_obj_set_x(ui_comfirm_btn, -190);
  lv_obj_set_y(ui_comfirm_btn, 125);
  lv_obj_set_align(ui_comfirm_btn, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_comfirm_btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_comfirm_btn, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_comfirm_btn, lv_color_hex(0x0079ff), LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_event_cb(ui_comfirm_btn, ui_comfirm_btn_e_hendler, LV_EVENT_ALL, &use_text_area);

  lv_obj_t *Label_2_1 = lv_label_create(ui_comfirm_btn);
  lv_obj_set_width(Label_2_1, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(Label_2_1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(Label_2_1, -3);
  lv_obj_set_y(Label_2_1, 1);
  lv_label_set_text(Label_2_1, "완 료");
  lv_obj_set_style_text_font(Label_2_1, &NanumBar24, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Button_all_delete = lv_btn_create(ui_Screen2);
  lv_obj_set_width(ui_Button_all_delete, 70);
  lv_obj_set_height(ui_Button_all_delete, 50);
  lv_obj_set_x(ui_Button_all_delete, -110);
  lv_obj_set_y(ui_Button_all_delete, 125);
  lv_obj_set_align(ui_Button_all_delete, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_Button_all_delete, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_Button_all_delete, LV_OBJ_FLAG_SCROLLABLE);     /// Flags
  lv_obj_set_style_bg_color(ui_Button_all_delete, lv_color_hex(0xff0060), LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_add_event_cb(ui_Button_all_delete, ui_all_delete_btn_e_handler, LV_EVENT_ALL, &use_text_area);

  lv_obj_t *ui_Label_all_dalete = lv_label_create(ui_Button_all_delete);
  lv_obj_set_width(ui_Label_all_dalete, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_Label_all_dalete, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(ui_Label_all_dalete, -3);
  lv_obj_set_y(ui_Label_all_dalete, 1);
  lv_label_set_text(ui_Label_all_dalete, "삭 제");
  lv_obj_set_style_text_font(ui_Label_all_dalete, &NanumBar24, LV_PART_MAIN | LV_STATE_DEFAULT);

  use_text_area.ta1 = lv_textarea_create(ui_Screen2);
  lv_textarea_set_one_line(use_text_area.ta1, true);
  lv_obj_set_width(use_text_area.ta1, 125);  /// 1
  lv_obj_set_height(use_text_area.ta1, 40);  /// 1
  lv_obj_align(use_text_area.ta1, LV_ALIGN_TOP_MID, -130, 10);
  lv_obj_add_event_cb(use_text_area.ta1, textarea_event_handler, LV_EVENT_READY, NULL);
  lv_obj_add_event_cb(use_text_area.ta1, textarea_event_handler, LV_EVENT_FOCUSED, NULL);
  lv_obj_add_state(use_text_area.ta1, LV_STATE_DEFAULT); /*To be sure the cursor is visible*/

  use_text_area.ta2 = lv_textarea_create(ui_Screen2);
  lv_textarea_set_one_line(use_text_area.ta2, true);
  lv_obj_set_width(use_text_area.ta2, 125);  /// 1
  lv_obj_set_height(use_text_area.ta2, 40);  /// 1
  lv_obj_align(use_text_area.ta2, LV_ALIGN_TOP_MID, -130, 60);
  lv_obj_add_event_cb(use_text_area.ta2, textarea_event_handler1, LV_EVENT_READY, NULL);
  lv_obj_add_event_cb(use_text_area.ta2, textarea_event_handler1, LV_EVENT_FOCUSED, NULL);
  lv_obj_add_state(use_text_area.ta2, LV_STATE_DEFAULT); /*To be sure the cursor is visible*/

  use_text_area.ta3 = lv_textarea_create(ui_Screen2);  // 정상 text
  lv_textarea_set_one_line(use_text_area.ta3, true);
  lv_obj_set_width(use_text_area.ta3, 125);  /// 1
  lv_obj_set_height(use_text_area.ta3, 40);  /// 1
  lv_obj_align(use_text_area.ta3, LV_ALIGN_TOP_MID, -130, 110);
  lv_obj_add_event_cb(use_text_area.ta3, textarea_event_handler2, LV_EVENT_READY, NULL);
  lv_obj_add_event_cb(use_text_area.ta3, textarea_event_handler2, LV_EVENT_FOCUSED, NULL);
  lv_obj_add_state(use_text_area.ta3, LV_STATE_DEFAULT); /*To be sure the cursor is visible*/

  static const char *btnm_map[] = { "1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "\n", "C", "0", ".", "" };

  lv_obj_t *btnm = lv_btnmatrix_create(ui_Screen2);
  lv_obj_set_size(btnm, 300, 320);
  lv_obj_align(btnm, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_set_style_text_font(btnm, &NanumBar24, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_VALUE_CHANGED, NULL);
  lv_obj_clear_flag(btnm, LV_OBJ_FLAG_CLICK_FOCUSABLE); /*To keep the text area focused on button clicks*/
  lv_btnmatrix_set_map(btnm, btnm_map);

  lv_obj_t *ui_Label8 = lv_label_create(ui_Screen2);
  lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(ui_Label8, -215);
  lv_obj_set_y(ui_Label8, 20);
  lv_obj_set_align(ui_Label8, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label8, "초 과");
  lv_obj_set_style_text_font(ui_Label8, &NanumBar18, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label9 = lv_label_create(ui_Screen2);
  lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(ui_Label9, -215);
  lv_obj_set_y(ui_Label9, 70);
  lv_obj_set_align(ui_Label9, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label9, "부 족");
  lv_obj_set_style_text_font(ui_Label9, &NanumBar18, LV_PART_MAIN | LV_STATE_DEFAULT);

  lv_obj_t *ui_Label10 = lv_label_create(ui_Screen2);
  lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(ui_Label10, -215);
  lv_obj_set_y(ui_Label10, 120);
  lv_obj_set_align(ui_Label10, LV_ALIGN_TOP_MID);
  lv_label_set_text(ui_Label10, "품 번");
  lv_obj_set_style_text_font(ui_Label10, &NanumBar18, LV_PART_MAIN | LV_STATE_DEFAULT);
}