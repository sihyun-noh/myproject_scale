// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: ms_type

#include "../ui.h"

void ui_list_select_screen_init(void) {
  ui_list_select = lv_obj_create(NULL);
  lv_obj_clear_flag(ui_list_select, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  ui_ListSelectScreen_List_Panel = lv_obj_create(ui_list_select);
  lv_obj_set_width(ui_ListSelectScreen_List_Panel, 450);
  lv_obj_set_height(ui_ListSelectScreen_List_Panel, 250);
  lv_obj_set_x(ui_ListSelectScreen_List_Panel, 0);
  lv_obj_set_y(ui_ListSelectScreen_List_Panel, 30);
  lv_obj_set_scroll_snap_x(ui_ListSelectScreen_List_Panel, LV_SCROLL_SNAP_CENTER);
  lv_obj_set_scroll_dir(ui_ListSelectScreen_List_Panel, LV_DIR_VER);  // only scroll vertically
  lv_obj_set_flex_flow(ui_ListSelectScreen_List_Panel, LV_FLEX_FLOW_ROW_WRAP);
  lv_obj_set_align(ui_ListSelectScreen_List_Panel, LV_ALIGN_CENTER);
  // lv_obj_set_style_bg_color(ui_prod_num_register_btn, lv_color_hex(0x232D3F), LV_PART_MAIN | LV_STATE_DEFAULT);

  // lv_obj_clear_flag(ui_ListSelectScreen_List_Panel, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  ui_ListSelectScreen_Comfirm_Panel = lv_obj_create(ui_list_select);
  lv_obj_set_width(ui_ListSelectScreen_Comfirm_Panel, 270);
  lv_obj_set_height(ui_ListSelectScreen_Comfirm_Panel, 40);
  lv_obj_set_x(ui_ListSelectScreen_Comfirm_Panel, 0);
  lv_obj_set_y(ui_ListSelectScreen_Comfirm_Panel, -122);
  lv_obj_set_align(ui_ListSelectScreen_Comfirm_Panel, LV_ALIGN_CENTER);
  lv_obj_clear_flag(ui_ListSelectScreen_Comfirm_Panel, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  ui_ListSelectScreen_Comfirm_Label = lv_label_create(ui_ListSelectScreen_Comfirm_Panel);
  lv_obj_set_width(ui_ListSelectScreen_Comfirm_Label, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_ListSelectScreen_Comfirm_Label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(ui_ListSelectScreen_Comfirm_Label, LV_ALIGN_LEFT_MID);
  lv_label_set_long_mode(ui_ListSelectScreen_Comfirm_Label, LV_LABEL_LONG_SCROLL);
  lv_label_set_text(ui_ListSelectScreen_Comfirm_Label, " ");

  ui_ListSelectScreen_Comfirm_Btn = lv_btn_create(ui_list_select);
  lv_obj_set_width(ui_ListSelectScreen_Comfirm_Btn, 80);
  lv_obj_set_height(ui_ListSelectScreen_Comfirm_Btn, 40);
  lv_obj_set_x(ui_ListSelectScreen_Comfirm_Btn, 185);
  lv_obj_set_y(ui_ListSelectScreen_Comfirm_Btn, -122);
  lv_obj_set_align(ui_ListSelectScreen_Comfirm_Btn, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_ListSelectScreen_Comfirm_Btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_ListSelectScreen_Comfirm_Btn, LV_OBJ_FLAG_SCROLLABLE);     /// Flags

  lv_obj_add_event_cb(ui_ListSelectScreen_Comfirm_Btn, ui_ListSelectScreen_Comfirm_Btn_e_handler, LV_EVENT_ALL, NULL);

  ui_ListSelectScreen_Comfirm_Btn_Label = lv_label_create(ui_ListSelectScreen_Comfirm_Btn);
  lv_obj_set_width(ui_ListSelectScreen_Comfirm_Btn_Label, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_ListSelectScreen_Comfirm_Btn_Label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(ui_ListSelectScreen_Comfirm_Btn_Label, LV_ALIGN_CENTER);
  lv_label_set_text(ui_ListSelectScreen_Comfirm_Btn_Label, "적 용");
  lv_obj_set_style_text_font(ui_ListSelectScreen_Comfirm_Btn_Label, &NanumBar18, LV_PART_MAIN | LV_STATE_DEFAULT);

  ui_ListSelectScreen_Delete_Btn = lv_btn_create(ui_list_select);
  lv_obj_set_width(ui_ListSelectScreen_Delete_Btn, 80);
  lv_obj_set_height(ui_ListSelectScreen_Delete_Btn, 40);
  lv_obj_set_x(ui_ListSelectScreen_Delete_Btn, -185);
  lv_obj_set_y(ui_ListSelectScreen_Delete_Btn, -122);
  lv_obj_set_align(ui_ListSelectScreen_Delete_Btn, LV_ALIGN_CENTER);
  lv_obj_add_flag(ui_ListSelectScreen_Delete_Btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(ui_ListSelectScreen_Delete_Btn, LV_OBJ_FLAG_SCROLLABLE);     /// Flag
  lv_obj_set_style_bg_color(ui_ListSelectScreen_Delete_Btn, lv_color_hex(0xff0060), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_add_event_cb(ui_ListSelectScreen_Delete_Btn, ui_ListSelectScreen_Delete_Btn_e_handler, LV_EVENT_ALL, NULL);

  ui_ListSelectScreen_Delete_Btn_Label = lv_label_create(ui_ListSelectScreen_Delete_Btn);
  lv_obj_set_width(ui_ListSelectScreen_Delete_Btn_Label, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(ui_ListSelectScreen_Delete_Btn_Label, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(ui_ListSelectScreen_Delete_Btn_Label, LV_ALIGN_CENTER);
  lv_label_set_text(ui_ListSelectScreen_Delete_Btn_Label, "등록삭제");
  lv_obj_set_style_text_font(ui_ListSelectScreen_Delete_Btn_Label, &NanumBar18, LV_PART_MAIN | LV_STATE_DEFAULT);
}
