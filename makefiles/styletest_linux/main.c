#include "SDL2/SDL.h"
#include "drivers/sdl/lv_sdl_window.h"
#include "drivers/sdl/lv_sdl_mouse.h"
#include "drivers/sdl/lv_sdl_keyboard.h"

#include "src/modules/tft_display/style/style.h"

int main()
{
	lv_init();

	lv_display_t *display = lv_sdl_window_create(480, 320);
	lv_indev_t *mouse = lv_sdl_mouse_create();
	lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
	lv_indev_t *keyboard = lv_sdl_keyboard_create();

	style_init(display, keyboard);

	uint32_t lastTick = SDL_GetTicks();
	while(1)
	{
		SDL_Delay(5);
		uint32_t newTick = SDL_GetTicks();
		lv_tick_inc(newTick - lastTick);
		lastTick = newTick;
		lv_timer_handler();
	}

	return 0;
}
