#include "SDL2/SDL.h"
#include "drivers/sdl/lv_sdl_window.h"
#include "drivers/sdl/lv_sdl_mouse.h"
#include "drivers/sdl/lv_sdl_keyboard.h"

#include "src/modules/lvgl/style/style.h"
#include "src/modules/system_menu.h"
#include "src/modules/lvgl/lvgl_support.h"

int main()
{
	lvgl_support_init();
	
	lv_display_t *display = lv_sdl_window_create(480, 320);
	lv_indev_t *mouse = lv_sdl_mouse_create();
	lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
	lv_indev_t *keyboard = lv_sdl_keyboard_create();

	lvgl_use_display(display);
	LVGL_ADD_INDEV(mouse);
	LVGL_ADD_INDEV(mousewheel);
	LVGL_ADD_INDEV(keyboard);

	lvgl_support_end_init();

	EVENT_INVOKE(cnc_reset, 0);

	while(1)
	{
		SDL_Delay(5);
		EVENT_INVOKE(cnc_dotasks, 0);
	}

	return 0;
}

uint32_t mcu_millis()
{
	return SDL_GetTicks();
}

void cnc_delay_ms(uint32_t ms)
{
	SDL_Delay(ms);
}

