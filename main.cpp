#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

typedef uint32_t uint32;
typedef uint8_t uint8;

void init();
void update_graphics();
bool update_events();
void quit();

int sdl_width = 800;
int sdl_height = 600;

SDL_Window *sdl_window;
SDL_Surface *sdl_surface;

int main() {

	init();

  	while (update_events()) {

  		update_graphics();
  	}

  	quit();

	return 0;
}

void init() {

	SDL_Init(SDL_INIT_VIDEO);
	SDL_PumpEvents();

	sdl_window = SDL_CreateWindow(
  	"main",
  	SDL_WINDOWPOS_UNDEFINED,
  	SDL_WINDOWPOS_UNDEFINED,
  	sdl_width,
  	sdl_height,
  	SDL_WINDOW_SHOWN);

	SDL_Surface *tmp = SDL_CreateRGBSurfaceWithFormat(0, sdl_width, sdl_height, 32, SDL_PIXELFORMAT_RGBA32);

	sdl_surface = SDL_GetWindowSurface(sdl_window);
	SDL_BlitSurface(tmp, 0, sdl_surface, 0);
	SDL_FreeSurface(tmp);
}

void update_graphics() {

	if (SDL_MUSTLOCK(sdl_surface))
		SDL_LockSurface(sdl_surface);

	uint32 *pixel = (uint32*)sdl_surface->pixels;
	
	for (int row = 0; row < sdl_height; ++row) {
		for (int col = 0; col < sdl_width; ++col, ++pixel) {

			uint8 r = 255.0/sdl_height*row, g = 255.0/sdl_width*col, b = 0, a = 255;

			*pixel = (a << 24) | (r << 16) | (g << 8) | b;
		}
	}

	if (SDL_MUSTLOCK(sdl_surface)) 
		SDL_UnlockSurface(sdl_surface);

	SDL_UpdateWindowSurface(sdl_window);
}

bool update_events() {

	SDL_Event sdl_event;
	// process event queue
	while (SDL_PollEvent(&sdl_event)) {
		switch (sdl_event.type) {
	
			case SDL_QUIT:
				return false;

			case SDL_KEYDOWN:
				switch (sdl_event.key.keysym.sym) {

					case SDLK_w:
						std::cout<<"w"<<std::endl;
						break;
					case SDLK_a:
						std::cout<<"a"<<std::endl;
						break;
					case SDLK_s:
						std::cout<<"s"<<std::endl;
						break;
					case SDLK_d:
						std::cout<<"d"<<std::endl;
						break;
				}
			break;

		}
	}

	return true;
}

void quit() {

	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}