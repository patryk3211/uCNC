#include "SDL2/SDL.h"
#include "drivers/sdl/lv_sdl_window.h"

#include "src/modules/tft_display/style/style.h"

int main()
{
	lv_init();

	lv_display_t *display = lv_sdl_window_create(480, 320);

	style_init(display);

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
