#include "../cnc.h"

// Code specific to my Blackpill controller board

//#include "lcd/tft_driver.h"
//#include "lcd/gfx.h"

//#include "gui/colors.h"
//#include "gui/icons.h"

//#include "lcd/fonts/freesans9pt7b.h"
//#include "lcd/fonts/freesans12pt7b.h"
//#include "lcd/fonts/freemonobold12pt7b.h"

//#include "gui/main_screen.h"

// Custom settings
// #ifdef ENABLE_SETTINGS_MODULES

// #ifndef PROBE_IN_ANGLE_DEFAULT
// #define PROBE_IN_ANGLE_DEFAULT 255
// #endif
// #ifndef PROBE_OUT_ANGLE_DEFAULT
// #define PROBE_OUT_ANGLE_DEFAULT 90
// #endif
// #ifndef PROBE_CLEARANCE_HEIGHT_DEFAULT
// #define PROBE_CLEARANCE_HEIGHT_DEFAULT 3
// #endif

// #define BBM_PROBE_IN_ANGLE 1200
// #define BBM_PROBE_OUT_ANGLE 1201
// #define BBM_PROBE_CLEARANCE_HEIGHT 1202

// static uint32_t bbm_settings_address;

// static struct BBM_Settings {
//     uint8_t probe_in_angle;
//     uint8_t probe_out_angle;

//     float probe_clearance_height;
// } bbm_settings;

// #endif

// // Global variables
// //GfxRenderChain MainScreenChain;
// //GfxRenderChain CurrentUpdateChain;

// uint32_t bbm_currentTime;
// float bbm_oldPositions[3];

// char MainScreenPositionTexts[3][17];
// char StepText[16];
// char FeedText[20];

// float bbm_stepSize = 1;
// uint32_t bbm_feedRate = 100;

// // Macros
// #ifndef PROBE_SERVO
// #define PROBE_SERVO SERVO0
// #endif

// #define SHOW_SCREEN(chain) \
//     tft_submit_multiple(chain.grc_operations, chain.grc_length); \
//     gfx_activate_event_list(chain.grc_eventList); \
//     tft_start_render()

// #define UPDATE_SCREEN(screen) \
//     CurrentUpdateChain = gfx_create_update_chain(&screen, 1); \
//     if(CurrentUpdateChain.grc_length > 0) { \
//         tft_submit_multiple(CurrentUpdateChain.grc_operations, CurrentUpdateChain.grc_length); \
//         tft_start_render(); \
//     }

// // Functions
// //void tft_render_finished() {
// //    gfx_delete_render_chain(CurrentUpdateChain);
// //}

// void bbm_position_to_str(float pos, char* dest) {
//     if(pos < 0) {
//         dest[-1] = '-';
//         pos = -pos;
//     } else {
//         dest[-1] = ' ';
//     }

//     dest[0] = '0' + (int)(pos / 100) % 10;
//     dest[1] = '0' + (int)(pos / 10) % 10;
//     dest[2] = '0' + (int)(pos) % 10;
//     dest[3] = '.';
//     dest[4] = '0' + (int)(pos * 10) % 10;
//     dest[5] = '0' + (int)(pos * 100) % 10;
// }

// //void bbm_update_rates(float step, uint32_t feed) {
// //    if(step != bbm_stepSize) {
// //        bbm_stepSize = step;
// //        sprintf(StepText, "Step: %d.%02dmm", (int)step, (int)(step * 100) % 100);
// //        mainscreen_control_box_rates_children[0].ge_dirty = 1;
// //    }
// //    if(feed != bbm_feedRate) {
// //        bbm_feedRate = feed;
// //        sprintf(FeedText, "Feed: %dmm/min", (int)feed);
// //        mainscreen_control_box_rates_children[1].ge_dirty = 1;
// //    }
// //}

// void bbm_extend_probe() {
//     float position[AXIS_COUNT];
//     mc_sync_position();
//     mc_get_position(position);

//     motion_data_t md = {0};
//     md.motion_mode = MOTIONCONTROL_MODE_FEED;
//     md.feed = g_settings.homing_fast_feed_rate;
//     md.spindle = 0;
//     md.dwell = 0;

//     float oldZPos = position[AXIS_Z];
//     if(position[AXIS_Z] < 0) {
//         position[AXIS_Z] = bbm_settings.probe_clearance_height;
//     } else {
//         position[AXIS_Z] += bbm_settings.probe_clearance_height;
//     }

//     mc_line(position, &md);
//     itp_sync();

//     mcu_set_servo(PROBE_SERVO, bbm_settings.probe_out_angle);
//     cnc_delay_ms(1500);

//     position[AXIS_Z] = oldZPos;
//     mc_line(position, &md);
//     itp_sync();
// }

// void bbm_retract_probe() {
//     mcu_set_servo(PROBE_SERVO, bbm_settings.probe_in_angle);
//     cnc_delay_ms(1500);
// }

// void bbm_move_by(float x, float y, float z) {
//     motion_data_t data = { };

//     data.feed = bbm_feedRate;
//     data.spindle = 0;
//     data.dwell = 0;
//     data.motion_mode = MOTIONCONTROL_MODE_FEED;

//     float current[3];
//     mc_get_position(current);
//     current[0] += x;
//     current[1] += y;
//     current[2] += z;
//     mc_line(current, &data);
// }

// void bbm_move_xpos() {
//     bbm_move_by(bbm_stepSize, 0, 0);
// }

// void bbm_move_xneg() {
//     bbm_move_by(-bbm_stepSize, 0, 0);
// }

// void bbm_move_ypos() {
//     bbm_move_by(0, bbm_stepSize, 0);
// }

// void bbm_move_yneg() {
//     bbm_move_by(0, -bbm_stepSize, 0);
// }

// void bbm_move_zpos() {
//     bbm_move_by(0, 0, bbm_stepSize);
// }

// void bbm_move_zneg() {
//     bbm_move_by(0, 0, -bbm_stepSize);
// }

//     /*bool bbm_main_loop(void *args) {
//         tft_main_loop();

//         if(mcu_millis() - bbm_currentTime > 200) {
//             // Update the screen every 200ms
//             int32_t steps[3];
//             itp_get_rt_position(steps);

//             float positions[3];
//             for(int i = 0; i < 3; ++i) {
//                 positions[i] = steps[i] / g_settings.step_per_mm[i];

//                 if(positions[i] != bbm_oldPositions[i]) {
//                     bbm_position_to_str(positions[i], MainScreenPositionTexts[i] + 3);
//                     mainscreen_position_box_children[3 + i].ge_dirty = 1;
//                     bbm_oldPositions[i] = positions[i];
//                 } else {
//                     mainscreen_position_box_children[3 + i].ge_dirty = 0;
//                 }
//             }

//             UPDATE_SCREEN(MainScreen);

//             mainscreen_control_box_rates_children[0].ge_dirty = 0;
//             mainscreen_control_box_rates_children[1].ge_dirty = 0;

//             bbm_currentTime = mcu_millis();
//         }

//         return EVENT_CONTINUE;
//     }
//     CREATE_EVENT_LISTENER(cnc_dotasks, bbm_main_loop);*/

// // Event handlers
// #ifdef ENABLE_MOTION_CONTROL_MODULES
//     bool bbm_home_axis_start(void *args) {
//         uint8_t axis = ((homing_status_t*)args)->axis;
//         if(axis == AXIS_Z)
//             bbm_extend_probe();
//         return EVENT_HANDLED;
//     }
//     CREATE_EVENT_LISTENER(mc_home_axis_start, bbm_home_axis_start);

//     bool bbm_home_axis_finish(void *args) {
//         uint8_t axis = ((homing_status_t*)args)->axis;
//         if(axis == AXIS_Z)
//             bbm_retract_probe();
//         return EVENT_HANDLED;
//     }
//     CREATE_EVENT_LISTENER(mc_home_axis_finish, bbm_home_axis_finish);
// #endif

// #ifdef ENABLE_IO_MODULES
//     /*bool bbm_tp_irq(void *args) {
//         // args[0] = input
//         // args[1] = diff
//         //uint8_t* argsB = args;

//         //if(!(argsB[0] & 0x01)) {
//         //    // Touch panel IRQ is active low
//         //    tft_tp_irq();
//         //}

//         return EVENT_CONTINUE;
//     }

//     CREATE_EVENT_LISTENER(input_change, bbm_tp_irq);*/

//     bool bbm_probe_enable(void *args) {
//         bbm_extend_probe();
//         return EVENT_HANDLED;
//     }
//     CREATE_EVENT_LISTENER(probe_enable, bbm_probe_enable);

//     bool bbm_probe_disable(void *args) {
//         bbm_retract_probe();
//         return EVENT_HANDLED;
//     }
//     CREATE_EVENT_LISTENER(probe_disable, bbm_probe_disable);

// #endif

// #ifdef ENABLE_SETTINGS_MODULES

// bool bbm_settings_save(void *args) {
//     settings_args_t *set = (settings_args_t *)args;
//     if(set->address == SETTINGS_ADDRESS_OFFSET) {
//         settings_save(bbm_settings_address, (uint8_t*)&bbm_settings, sizeof(struct BBM_Settings));
//         return EVENT_CONTINUE;
//     }

//     return EVENT_CONTINUE;
// }
// CREATE_EVENT_LISTENER(settings_save, bbm_settings_save);

// bool bbm_settings_load(void *args) {
//     settings_args_t *set = (settings_args_t *)args;
//     if(set->address == SETTINGS_ADDRESS_OFFSET) {
//         settings_load(bbm_settings_address, (uint8_t*)&bbm_settings, sizeof(struct BBM_Settings));
//         return EVENT_CONTINUE;
//     }

//     return EVENT_CONTINUE;
// }
// CREATE_EVENT_LISTENER(settings_load, bbm_settings_load);

// bool bbm_settings_erase(void *args) {
//     settings_args_t *set = (settings_args_t *)args;
//     if(set->address == SETTINGS_ADDRESS_OFFSET) {
//         settings_erase(bbm_settings_address, sizeof(struct BBM_Settings));
//         return EVENT_CONTINUE;
//     }

//     return EVENT_CONTINUE;
// }
// CREATE_EVENT_LISTENER(settings_erase, bbm_settings_erase);

// bool bbm_protocol_settings(void *args) {
// 	protocol_send_gcode_setting_line_int(BBM_PROBE_IN_ANGLE, bbm_settings.probe_in_angle);
//     protocol_send_gcode_setting_line_int(BBM_PROBE_OUT_ANGLE, bbm_settings.probe_out_angle);
//     protocol_send_gcode_setting_line_int(BBM_PROBE_CLEARANCE_HEIGHT, bbm_settings.probe_clearance_height);

// 	return EVENT_CONTINUE;
// }
// CREATE_EVENT_LISTENER(protocol_send_cnc_settings, bbm_protocol_settings);

// bool bbm_settings_change(void *args) {
// 	setting_args_t *set = (setting_args_t *)args;
// 	switch(set->id) {
//         case BBM_PROBE_IN_ANGLE:
//             bbm_settings.probe_in_angle = (uint8_t)set->value;
//             return EVENT_HANDLED;
//         case BBM_PROBE_OUT_ANGLE:
//             bbm_settings.probe_out_angle = (uint8_t)set->value;
//             return EVENT_HANDLED;
//         case BBM_PROBE_CLEARANCE_HEIGHT:
//             bbm_settings.probe_clearance_height = set->value;
//             return EVENT_HANDLED;
//         default:
//             return EVENT_CONTINUE;
//     }
// }
// CREATE_EVENT_LISTENER(settings_change, bbm_settings_change);

// #endif

// Main module declaration
DECL_MODULE(board_blackpill_myb) {
    /*LOAD_MODULE(tft_driver);

    strcpy(MainScreenPositionTexts[0], "X: 000.00 ###.##");
    strcpy(MainScreenPositionTexts[1], "Y: 000.00 ###.##");
    strcpy(MainScreenPositionTexts[2], "Z: 000.00 ###.##");

    strcpy(StepText, "Step: 1.00mm");
    strcpy(FeedText, "Feed: 100mm/min");

    for(int i = 0; i < 3; ++i)
        mainscreen_position_box_children[3 + i].ge_text.ge_text = MainScreenPositionTexts[i];
    mainscreen_control_box_rates_children[0].ge_button.ge_text = StepText;
    mainscreen_control_box_rates_children[1].ge_button.ge_text = FeedText;

    // Initialize render chains
    MainScreenChain = gfx_create_render_chain(&MainScreen, 1);

    SHOW_SCREEN(MainScreenChain);*/


        //ADD_EVENT_LISTENER(cnc_dotasks, bbm_main_loop);

    // #ifdef ENABLE_MOTION_CONTROL_MODULES
    //     ADD_EVENT_LISTENER(mc_home_axis_start, bbm_home_axis_start);
    //     ADD_EVENT_LISTENER(mc_home_axis_finish, bbm_home_axis_finish);
    // #endif

    // #ifdef ENABLE_IO_MODULES
    //     //ADD_EVENT_LISTENER(input_change, bbm_tp_irq);

    //     ADD_EVENT_LISTENER(probe_enable, bbm_probe_enable);
    //     ADD_EVENT_LISTENER(probe_disable, bbm_probe_disable);
    // #endif

    // #ifdef ENABLE_SETTINGS_MODULES
    //     bbm_settings_address = settings_register_external_setting(sizeof(struct BBM_Settings));
    //     ADD_EVENT_LISTENER(settings_save, bbm_settings_save);
    //     ADD_EVENT_LISTENER(settings_load, bbm_settings_load);
    //     ADD_EVENT_LISTENER(settings_erase, bbm_settings_erase);
    //     ADD_EVENT_LISTENER(protocol_send_cnc_settings, bbm_protocol_settings);
    //     ADD_EVENT_LISTENER(settings_change, bbm_settings_change);

    //     if(settings_load(bbm_settings_address, (uint8_t*)&bbm_settings, sizeof(struct BBM_Settings))) {
    //         bbm_settings.probe_in_angle = PROBE_IN_ANGLE_DEFAULT;
    //         bbm_settings.probe_out_angle = PROBE_OUT_ANGLE_DEFAULT;
    //         bbm_settings.probe_clearance_height = PROBE_CLEARANCE_HEIGHT_DEFAULT;
    //         settings_save(bbm_settings_address, (uint8_t*)&bbm_settings, sizeof(struct BBM_Settings));
    //     }
    // #endif

    // mcu_set_servo(PROBE_SERVO, bbm_settings.probe_in_angle);
}
