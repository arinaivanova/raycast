#include <cstdint>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <SDL2/SDL.h>

#include "rc_math.h"
#include "rc_util.h"

typedef uint32_t uint32;
typedef uint8_t uint8;

void init();
void update_graphics();
bool update_events();
void quit();

const int sdl_width = 800, sdl_height = 600;

SDL_Window *sdl_window;
SDL_Surface *sdl_surface;

// camera coordinates and orientation
rc::vec2d pos = {2.0, 5.0};
rc::vec2d dir = {1.0, 0.0};
const double fov = M_PI/2;

const int map_w = 6, map_h = 6;
// 1 = wall square, 0 = floor
int map[6][6] = {
	{1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1},
};
// voxel width
const int vox_w = 1;

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

	// load textures
	//map_surface = SDL_LoadBMP("map.bmp");
}

void update_graphics() {

	if (SDL_MUSTLOCK(sdl_surface))
		SDL_LockSurface(sdl_surface);

	uint32 *pixel = (uint32*)sdl_surface->pixels;
	
	// clear pixel buffer
	memset(pixel, 0, sdl_surface->pitch*sdl_height);


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

					case SDLK_a:
						dir = rc::rot(dir, M_PI/12);
						break;

					case SDLK_d:
						dir = rc::rot(dir, -M_PI/12);
						break;

					case SDLK_w:
						pos = rc::bound(pos + dir*0.2, 0, 0, map_w, map_h);
						break;

					case SDLK_s:
						pos = rc::bound(pos - dir*0.2, 0, 0, map_w, map_h);
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