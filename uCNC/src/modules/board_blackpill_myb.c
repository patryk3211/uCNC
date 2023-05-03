#include "../cnc.h"

// Code specific to my Blackpill controller board

#include "lcd/tft_driver.h"
#include "lcd/gfx.h"

#include "gui/colors.h"
#include "gui/icons.h"

#include "lcd/fonts/freesans9pt7b.h"
#include "lcd/fonts/freesans12pt7b.h"
#include "lcd/fonts/freemonobold12pt7b.h"

#include "gui/main_screen.h"

GfxRenderChain MainScreenChain;
GfxRenderChain CurrentUpdateChain;

uint32_t bbm_currentTime;
float bbm_oldPositions[3];

char MainScreenPositionTexts[3][17];
char StepText[16];
char FeedText[20];

float bbm_stepSize = 1;
uint32_t bbm_feedRate = 100;

#define SHOW_SCREEN(chain) \
    tft_submit_multiple(chain.grc_operations, chain.grc_length); \
    gfx_activate_event_list(chain.grc_eventList); \
    tft_start_render()

#define UPDATE_SCREEN(screen) \
    CurrentUpdateChain = gfx_create_update_chain(&screen, 1); \
    if(CurrentUpdateChain.grc_length > 0) { \
        tft_submit_multiple(CurrentUpdateChain.grc_operations, CurrentUpdateChain.grc_length); \
        tft_start_render(); \
    }

void tft_render_finished() {
    gfx_delete_render_chain(CurrentUpdateChain);
}

void bbm_position_to_str(float pos, char* dest) {
    if(pos < 0) {
        dest[-1] = '-';
        pos = -pos;
    } else {
        dest[-1] = ' ';
    }

    dest[0] = '0' + (int)(pos / 100) % 10;
    dest[1] = '0' + (int)(pos / 10) % 10;
    dest[2] = '0' + (int)(pos) % 10;
    dest[3] = '.';
    dest[4] = '0' + (int)(pos * 10) % 10;
    dest[5] = '0' + (int)(pos * 100) % 10;
}

void bbm_update_rates(float step, uint32_t feed) {
    if(step != bbm_stepSize) {
        bbm_stepSize = step;
        sprintf(StepText, "Step: %d.%02dmm", (int)step, (int)(step * 100) % 100);
        mainscreen_control_box_rates_children[0].ge_dirty = 1;
    }
    if(feed != bbm_feedRate) {
        bbm_feedRate = feed;
        sprintf(FeedText, "Feed: %dmm/min", (int)feed);
        mainscreen_control_box_rates_children[1].ge_dirty = 1;
    }
}

#ifdef ENABLE_MAIN_LOOP_MODULES
    uint8_t bbm_main_loop(void *args, bool *handler) {
        tft_main_loop();

        if(mcu_millis() - bbm_currentTime > 200) {
            // Update the screen every 200ms
            int32_t steps[3];
            itp_get_rt_position(steps);

            float positions[3];
            for(int i = 0; i < 3; ++i) {
                positions[i] = steps[i] / g_settings.step_per_mm[i];

                if(positions[i] != bbm_oldPositions[i]) {
                    bbm_position_to_str(positions[i], MainScreenPositionTexts[i] + 3);
                    mainscreen_position_box_children[3 + i].ge_dirty = 1;
                    bbm_oldPositions[i] = positions[i];
                } else {
                    mainscreen_position_box_children[3 + i].ge_dirty = 0;
                }
            }

            UPDATE_SCREEN(MainScreen);

            mainscreen_control_box_rates_children[0].ge_dirty = 0;
            mainscreen_control_box_rates_children[1].ge_dirty = 0;

            bbm_currentTime = mcu_millis();
        }

        return 0;
    }

    CREATE_EVENT_LISTENER(cnc_dotasks, bbm_main_loop);
#endif

void bbm_move_by(float x, float y, float z) {
    motion_data_t data = { };

    data.feed = bbm_feedRate;
    data.spindle = 0;
    data.dwell = 0;
    data.motion_mode = MOTIONCONTROL_MODE_FEED;

    float current[3];
    mc_get_position(current);
    current[0] += x;
    current[1] += y;
    current[2] += z;
    mc_line(current, &data);
}

void bbm_move_xpos() {
    bbm_move_by(bbm_stepSize, 0, 0);
}

void bbm_move_xneg() {
    bbm_move_by(-bbm_stepSize, 0, 0);
}

void bbm_move_ypos() {
    bbm_move_by(0, bbm_stepSize, 0);
}

void bbm_move_yneg() {
    bbm_move_by(0, -bbm_stepSize, 0);
}

void bbm_move_zpos() {
    bbm_move_by(0, 0, bbm_stepSize);
}

void bbm_move_zneg() {
    bbm_move_by(0, 0, -bbm_stepSize);
}

#ifdef ENABLE_IO_MODULES
    uint8_t bbm_tp_irq(void *args, bool *handler) {
        // args[0] = input
        // args[1] = diff
        uint8_t* argsB = args;

        if(!(argsB[0] & 0x01)) {
            // Touch panel IRQ is active low
            tft_tp_irq();
        }

        return 0;
    }

    CREATE_EVENT_LISTENER(input_change, bbm_tp_irq);
#endif

DECL_MODULE(board_blackpill_myb) {
    LOAD_MODULE(tft_driver);

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

    SHOW_SCREEN(MainScreenChain);

    #ifdef ENABLE_MAIN_LOOP_MODULES
        ADD_EVENT_LISTENER(cnc_dotasks, bbm_main_loop);
    #endif

    #ifdef ENABLE_IO_MODULES
        ADD_EVENT_LISTENER(input_change, bbm_tp_irq);
    #endif
}
