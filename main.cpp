#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <chrono>

#include <SDL2/SDL.h>

#include "rc_math.h"
#include "rc_util.h"

namespace rc {

	template <size_t H, size_t W>
	struct map {

		const int w, h;
		double vox_w;

		std::vector<std::vector<size_t>> vox;

		map() : w(W), h(H), vox_w(1.0) {}
	};
}

void init();
template <size_t H, size_t W>
rc::vec2d ray_vox_int(const rc::vec2d &ray_dir, const rc::map<H, W> &map); // ray-voxel intersection
void update_graphics();
bool update_events(double d_time);
void quit();

const int sdl_width = 600, sdl_height = 600;
// camera coordinates and orientation
rc::vec2d pos = {1, 2.5};
//rc::vec2d dir = {cos(M_PI/4), sin(M_PI/4)};
rc::vec2d dir = {1, 0};
const double fov = M_PI*0.5;
rc::map<6, 6> world_map;

SDL_Window *sdl_window;
SDL_Surface *sdl_surface;

int main() {

	init();

	// 1 = wall square, 0 = floor
	world_map.vox = {
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1},
	};

	auto time_prev = std::chrono::high_resolution_clock::now();
	// time (seconds) per current frame
	double d_time = 0;

  	while (update_events(d_time)) {

  		update_graphics();

  		// update frame time
  		auto time_cur = std::chrono::high_resolution_clock::now();
  		d_time = std::chrono::duration_cast<std::chrono::microseconds>(time_cur - time_prev).count() * 1e-6;
  		time_prev = time_cur;
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

template <size_t H, size_t W>
rc::vec2d ray_vox_int(const rc::vec2d &ray_dir, const rc::map<H, W> &map) {

	rc::vec2d ray;

	// initial ray step inside camera position voxel
	{
		rc::vec2d d = {
			(int)pos.x - pos.x + map.vox_w*(ray_dir.x > 0),
			(int)pos.y - pos.y + map.vox_w*(ray_dir.y > 0)
		};
		double d1 = d.x/ray_dir.x;
		double d2 = d.y/ray_dir.y;

		if (d1>d2)
			d.x = d2*ray_dir.x;
		else
			d.y = d1*ray_dir.y;

		ray = d;
	}

	// step ray until wall is hit from closest outside camera voxel; assumes wall surrounds map
	{
		//...
	}

	return ray;
}

void update_graphics() {

	if (SDL_MUSTLOCK(sdl_surface))
		SDL_LockSurface(sdl_surface);

	uint32 *pixel = (uint32*)sdl_surface->pixels;
	
	// clear pixel buffer
	memset(pixel, 0, sdl_surface->pitch*sdl_height);

	// cast ray into map through each column of screen until wall is hit
	for (int col = 0; col < sdl_width; ++col) {

		const double d_angle = fov/sdl_width;
		const rc::vec2d ray_dir = rc::rot(dir, d_angle * (col - sdl_width*0.5));
		const rc::vec2d ray = ray_vox_int(ray_dir, world_map);
		const double dist = rc::mag(ray);

		// draw wall
		double perp_dist = abs(ray_dir.x * dist);
		double wall_height = std::min(1.0*sdl_height, sdl_height*0.5 / perp_dist);

		for(int row = (sdl_height-wall_height)*0.5; row < (sdl_height+wall_height)*0.5; ++row) {

			pixel[row*sdl_width+col] = rc::color(255, 0, 0);
		}
	}

	if (SDL_MUSTLOCK(sdl_surface)) 
		SDL_UnlockSurface(sdl_surface);

	SDL_UpdateWindowSurface(sdl_window);
}

bool update_events(double d_time) {

	SDL_Event sdl_event;
	// process event queue

	while (SDL_PollEvent(&sdl_event)) {
		switch (sdl_event.type) {
	
			case SDL_QUIT:
				return false;

			case SDL_KEYDOWN:

				const double rot_speed = 9*d_time;
				const double move_speed = 8*d_time;

				switch (sdl_event.key.keysym.sym) {

					case SDLK_a:
						dir = rc::rot(dir, -rot_speed);
						break;

					case SDLK_d:
						dir = rc::rot(dir, rot_speed);
						break;

					case SDLK_w:
						pos = rc::bound(pos + dir*move_speed, 0, 0, world_map.w-1, world_map.h-1);
						break;

					case SDLK_s:
						pos = rc::bound(pos - dir*move_speed, 0, 0, world_map.w-1, world_map.h-1);
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