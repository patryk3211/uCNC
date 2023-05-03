const struct GuiElement mainscreen_header_children[] = {
    GUI_TEXT(6, 2, TFT_WHITE, "CNC Controller v1.0.0", FreeSans12pt7b)
};

struct GuiElement mainscreen_position_box_children[] = {
    GUI_BORDER(-1, -1, PARENT_WIDTH(2), PARENT_HEIGHT(2), TFT_CYAN, 1),

    GUI_TEXT(4, 4, TFT_WHITE, "Position", FreeSans12pt7b),
    GUI_TEXT_RIGHT(PARENT_WIDTH(-4), 4, TFT_WHITE, "[mm]", FreeSans12pt7b),

    GUI_TEXT(8, 8 + 24 * 1, TFT_RED,   0, FreeMonoBold12pt7b), // Pos X
    GUI_TEXT(8, 8 + 24 * 2, TFT_GREEN, 0, FreeMonoBold12pt7b), // Pos Y
    GUI_TEXT(8, 8 + 24 * 3, TFT_BLUE,  0, FreeMonoBold12pt7b)  // Pos Z
};

struct GuiElement mainscreen_control_box_rates_children[] = {
    GUI_BUTTON(4, 0, PARENT_WIDTH(-8), 24, TFT_YELLOW, TFT_BLACK, 0, ALIGN_LEFT, FreeSans9pt7b, 0), // Step size
    GUI_BUTTON(4, 28, PARENT_WIDTH(-8), 24, TFT_YELLOW, TFT_BLACK, 0, ALIGN_RIGHT, FreeSans9pt7b, 0) // Feed rate
};

void bbm_move_xpos();
void bbm_move_xneg();
void bbm_move_ypos();
void bbm_move_yneg();
void bbm_move_zpos();
void bbm_move_zneg();

const struct GuiElement mainscreen_control_box_children[] = {
    GUI_BORDER(-1, -1, PARENT_WIDTH(2), PARENT_HEIGHT(2), TFT_YELLOW, 1),

    GUI_BOX_STATIC(0, 0, PARENT_WIDTH(0), 56, TFT_YELLOW, mainscreen_control_box_rates_children),

    GUI_IMAGE_BUTTON( 60,  64, 48, 48, 3, TFT_COLOR(0, 1, 0), TFT_GREEN, icon_button_up, 0, &bbm_move_ypos),
    GUI_IMAGE_BUTTON( 60, 120, 48, 48, 3, TFT_COLOR(0, 1, 0), TFT_GREEN, icon_button_down, 0, &bbm_move_yneg),
    GUI_IMAGE_BUTTON(  8,  92, 48, 48, 3, TFT_COLOR(1, 0, 0), TFT_RED  , icon_button_left, 0, &bbm_move_xneg),
    GUI_IMAGE_BUTTON(112,  92, 48, 48, 3, TFT_COLOR(1, 0, 0), TFT_RED  , icon_button_right, 0, &bbm_move_xpos),

    GUI_IMAGE_BUTTON(192,  64, 48, 48, 3, TFT_COLOR(0, 0, 1), TFT_BLUE, icon_button_up, 0, &bbm_move_zpos),
    GUI_IMAGE_BUTTON(192, 120, 48, 48, 3, TFT_COLOR(0, 0, 1), TFT_BLUE, icon_button_down, 0, &bbm_move_zneg),
};

struct GuiElement mainscreen_alarm_box_children[] = {
    GUI_BORDER(-1, -1, PARENT_WIDTH(2), PARENT_HEIGHT(2), TFT_RED, 2),

    GUI_TEXT_CENTERED(0, 2, PARENT_WIDTH(0), TFT_RED, "Alarm", FreeSans12pt7b)
};

const struct GuiElement mainscreen_me_children[] = {
    GUI_BOX_STATIC(0, 0, PARENT_WIDTH(0), 32, TFT_BLUE, mainscreen_header_children),

    GUI_BOX_STATIC(16, 48, PARENT_WIDTH(-32), 112, TFT_BLACK, mainscreen_position_box_children),
    GUI_BOX_STATIC(16, 176, PARENT_WIDTH(-32), 176, TFT_BLACK, mainscreen_control_box_children),

    GUI_BOX_STATIC(16, 368, PARENT_WIDTH(-32), 33, TFT_BLACK, mainscreen_alarm_box_children),

    GUI_BUTTON( 16, 440, 80, 24, TFT_BLUE, TFT_WHITE, "[Zero]", ALIGN_CENTER, FreeSans9pt7b, 0),
    GUI_BUTTON(120, 440, 80, 24, TFT_BLUE, TFT_WHITE, "[Menu]", ALIGN_CENTER, FreeSans9pt7b, 0),
    GUI_BUTTON(224, 440, 80, 24, TFT_BLUE, TFT_WHITE, "[Home]", ALIGN_CENTER, FreeSans9pt7b, 0)
};

const struct GuiElement MainScreen = GUI_BOX_STATIC(0, 0, 320, 480, TFT_BLACK, mainscreen_me_children);
