#include <string>
#include "main.h"

lv_obj_t * title;
// autonNum is public static variable

/*
static lv_res_t setAuton(lv_obj_t * btn){
  uint8_t id = lv_obj_get_free_num(btn);

  autonNum = id>5?id-5:id;
  //------------- AUTONOMOUS ROUTINES ------------//
  // 1: Front tile, side and mid pole (17)        //
  // 2: Front tile, opponent and mid pole (12)    //
  // 3: Back tile, side pole and park (13)        //
  // 4: Back tile, pole cap, floor cap, park (13) //
  // 5: Skills                                    //
  // 1-5 for RED, 6-10 for BLUE                   //
  //----------------------------------------------//

  return LV_RES_OK;
}
*/

using namespace std;

static const char * btnm_map[] = {"1", "2", "3", "4", "5", ""};
static const string display_map[] =
{"1 Red","2 Red","3 Red","4 Red","Skills","1 Blue","2 Blue","3 Blue","4 Blue","5 Blue"};

/*Called when a button is released ot long pressed*/
static lv_res_t btnm_action_red(lv_obj_t * btnm, const char *txt)
{
  if(txt == btnm_map[0]) autonNum = 1;
  else if(txt == btnm_map[1]) autonNum = 2;
  else if(txt == btnm_map[2]) autonNum = 3;
  else if(txt == btnm_map[3]) autonNum = 4;
  else if(txt == btnm_map[4]) autonNum = 5;

  string output = "Auton Selected: " + display_map[autonNum-1];
  lv_label_set_text(title, output.c_str());

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

static lv_res_t btnm_action_blue(lv_obj_t * btnm, const char *txt)
{
  if(txt == btnm_map[0]) autonNum = 6;
  else if(txt == btnm_map[1]) autonNum = 7;
  else if(txt == btnm_map[2]) autonNum = 8;
  else if(txt == btnm_map[3]) autonNum = 9;
  else if(txt == btnm_map[4]) autonNum = 10;

  string output = "Auton Selected: " + display_map[autonNum-1];
  lv_label_set_text(title, output.c_str());

  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

lv_res_t calibSensors(lv_obj_t * btn){
  return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void initSelector(){
  int btnm_height = (LV_VER_RES-130)/ 2;

  /*Create a title label*/
	title = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(title, "Auton Selected: ____");
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_MID, 0, 15);

  /*Create a new style for the button matrix back ground*/
  static lv_style_t style_bg;
  lv_style_copy(&style_bg, &lv_style_plain);
  style_bg.body.main_color = LV_COLOR_MAKE(0x30,0x30,0x30);
  style_bg.body.grad_color = LV_COLOR_MAKE(0x30,0x30,0x30);
  style_bg.line.color = LV_COLOR_TRANSP;
  style_bg.body.padding.hor = 0;
  style_bg.body.padding.ver = 0;
  style_bg.body.padding.inner = 0;

  /*Create 2 button styles*/
  static lv_style_t style_btn_rel_red;
  static lv_style_t style_btn_pr_red;
  lv_style_copy(&style_btn_rel_red, &lv_style_btn_rel);
  style_btn_rel_red.body.main_color = LV_COLOR_MAKE(0x55, 0x00, 0x00);
  style_btn_rel_red.body.grad_color = LV_COLOR_MAKE(0x55, 0x00, 0x00);
  style_btn_rel_red.body.border.color = LV_COLOR_MAKE(0xDD, 0x00, 0x00);
  style_btn_rel_red.body.border.width = 3;
  style_btn_rel_red.body.border.opa = LV_OPA_50;
  style_btn_rel_red.body.radius = 7;

  lv_style_copy(&style_btn_pr_red, &style_btn_rel_red);
  style_btn_pr_red.body.main_color = LV_COLOR_MAKE(0xDD, 0x00, 0x00);
  style_btn_pr_red.body.grad_color = LV_COLOR_MAKE(0xDD, 0x00, 0x00);
  style_btn_pr_red.text.color = LV_COLOR_WHITE;

  static lv_style_t style_btn_rel;
  static lv_style_t style_btn_pr;
  lv_style_copy(&style_btn_rel, &lv_style_btn_rel);
  style_btn_rel.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0x55);
  style_btn_rel.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0x55);
  style_btn_rel.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0xDD);
  style_btn_rel.body.border.width = 3;
  style_btn_rel.body.border.opa = LV_OPA_50;
  style_btn_rel.body.radius = 7;

  lv_style_copy(&style_btn_pr, &style_btn_rel);
  style_btn_pr.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xDD);
  style_btn_pr.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xDD);
  style_btn_pr.text.color = LV_COLOR_WHITE;

  ////////////// Red Selector //////////////
  lv_obj_t * btnmRed = lv_btnm_create(lv_scr_act(), NULL);
  lv_btnm_set_map(btnmRed, btnm_map);
  lv_btnm_set_action(btnmRed, btnm_action_red);
  lv_obj_set_size(btnmRed, LV_HOR_RES-15,  btnm_height);
  lv_btnm_set_style(btnmRed, LV_BTNM_STYLE_BG, &style_bg);
  lv_btnm_set_style(btnmRed, LV_BTNM_STYLE_BTN_REL, &style_btn_rel_red);
  lv_btnm_set_style(btnmRed, LV_BTNM_STYLE_BTN_PR, &style_btn_pr_red);
  lv_obj_align(btnmRed, title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

  ////////////// Blue Selector //////////////
  lv_obj_t * btnmBlue = lv_btnm_create(lv_scr_act(), btnmRed);
  lv_btnm_set_action(btnmBlue, btnm_action_blue);
  //lv_btnm_set_style(btnmBlue, LV_BTNM_STYLE_BG, &style_bg);
  lv_btnm_set_style(btnmBlue, LV_BTNM_STYLE_BTN_REL, &style_btn_rel);
  lv_btnm_set_style(btnmBlue, LV_BTNM_STYLE_BTN_PR, &style_btn_pr);
  lv_obj_align(btnmBlue, btnmRed, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  ////////////// Calibration Button //////////////
  static lv_style_t style_btn_calib_rel;
  lv_style_copy(&style_btn_calib_rel, &style_btn_rel);
  style_btn_calib_rel.body.main_color = LV_COLOR_MAKE(0x80,0x80,0x80);
  style_btn_calib_rel.body.grad_color = LV_COLOR_MAKE(0x80,0x80,0x80);
  style_btn_calib_rel.body.border.color = LV_COLOR_MAKE(0xDD, 0x00, 0x00);
  style_btn_calib_rel.body.border.width = 3;
  style_btn_calib_rel.body.border.opa = LV_OPA_50;
  style_btn_calib_rel.body.radius = 20;
  style_btn_calib_rel.text.color = LV_COLOR_WHITE;

  static lv_style_t style_btn_calib_pr;
  lv_style_copy(&style_btn_calib_pr, &style_btn_pr);
  style_btn_calib_pr.body.main_color = LV_COLOR_MAKE(0x60,0x60,0x60);
  style_btn_calib_pr.body.grad_color = LV_COLOR_MAKE(0x60,0x60,0x60);
  style_btn_calib_pr.body.border.color = LV_COLOR_MAKE(0xDD, 0x00, 0x00);
  style_btn_calib_pr.body.border.width = 3;
  style_btn_calib_pr.body.border.opa = LV_OPA_50;
  style_btn_calib_pr.body.radius = 20;
  style_btn_calib_rel.text.color = LV_COLOR_WHITE;

  lv_obj_t * calibBtn = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(calibBtn, LV_HOR_RES-15,  40);
  lv_obj_align(calibBtn, btnmBlue, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
  lv_btn_set_style(calibBtn, LV_BTN_STYLE_REL, &style_btn_calib_rel);
  lv_btn_set_style(calibBtn, LV_BTN_STYLE_PR, &style_btn_calib_pr);
  lv_btn_set_action(calibBtn, LV_BTN_ACTION_CLICK, calibSensors);

  lv_obj_t * label = lv_label_create(calibBtn, NULL);
  lv_label_set_text(label, "Calibrate");
}
/*
void debugLabels(){
  ADIAnalogIn cataPot(catapultPotPort);
  Motor catapult(catapultPort);

  title = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(title, NULL, LV_ALIGN_OUT_TOP_LEFT, 10, 30);

  lv_obj_t * catapultPow = lv_label_create(lv_scr_act(), NULL);
  lv_obj_align(catapultPow, title, LV_ALIGN_OUT_TOP_LEFT, 0, 60);

  while(true){
    string val = "Pot: "+to_string(cataPot.get_value());
    lv_label_set_text(title, val.c_str());

    val = "Pow: "+to_string(catapult.get_power());
    lv_label_set_text(catapultPow, val.c_str());

    delay(300);
  }
}
*/
void clearScreen(){
  lv_obj_clean(lv_scr_act());
}
