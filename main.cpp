#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Sprites.h"

int main(int argc, char* args[])
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int imgFlags = IMG_INIT_PNG;

	bool quit = false;
	bool left = false, right = false, up = false, down = false;

	int mouse_x, mouse_y, camera_x = 0, camera_y = 0;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 delta = 0;
	short fps = 60;
	short timePerFrame = 1000 / 60; // miliseconds

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	setWalking();
	setTheatre();

	SDL_Rect theatre[30];

	theatre[0].x = 344;
	theatre[0].y = 646;
	theatre[0].w = 142;
	theatre[0].h = 28;

	SDL_Rect walkingSprite[20];

	for (int i = 0; i < 20; i++)
	{
		walkingSprite[i].x = 1 + ((i % 5) * 41);
		walkingSprite[i].y = 1 + ((i / 5) * 41);
		walkingSprite[i].w = 40;
		walkingSprite[i].h = 40;
	}

	enum
	{
		right1, right2, right3, right4, right5,
		left1, left2, left3, left4, left5,
		up1, up2, up3, up4, up5,
		down1, down2, down3, down4, down5
	};

	Sprite map; map.loadFromFile("Sprites/another.png");
	Actor character; character.loadFromFile("Sprites/walking.png");

	SDL_Event event;

	int frame = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					up = true;
					break;
				case SDLK_a:
					left = true;
					break;
				case SDLK_s:
					down = true;
					break;
				case SDLK_d:
					right = true;
					break;
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
					up = false;
					break;
				case SDLK_a:
					left = false;
					break;
				case SDLK_s:
					down = false;
					break;
				case SDLK_d:
					right = false;
					break;
				}
			}
		}

		if (!startTime)
			startTime = SDL_GetTicks();
		else
			delta = endTime - startTime;

		if (delta < timePerFrame)
			SDL_Delay(timePerFrame - delta);
		if (delta > timePerFrame)
			fps = 1000 / delta;

		SDL_GetMouseState(&mouse_x, &mouse_y);

		if (left) { character.anim = left1 + (frame / 15); character.move(-1, 0, theatre); }
		if (right) { character.anim = right1 + (frame / 15); character.move(1, 0, theatre); }
		if (up) { character.anim = up1 + (frame / 15); character.move(0, -1, theatre); }
		if (down) { character.anim = down1 + (frame / 15); character.move(0, 1, theatre); }

		if (left || right || up || down)
		{
			if (frame < 59)
				frame++;
			else
				frame = 0;
		}

		camera.x = (character.x + character.CHAR_WIDTH / 2) - SCREEN_WIDTH / 2;
		camera.y = (character.y + character.CHAR_HEIGHT / 2) - SCREEN_HEIGHT / 2;

		if (camera.x < 0) { camera.x = 0; }
		if (camera.y < 0) { camera.y = 0; }
		if (camera.x > LEVEL_WIDTH - camera.w) { camera.x = LEVEL_WIDTH - camera.w; }
		if (camera.y > LEVEL_HEIGHT - camera.h) { camera.y = LEVEL_HEIGHT - camera.h; }

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		/*--------------------------------------------------------------*/

		map.render(0, 0, &camera);

		character.render(character.x - camera.x, character.y - camera.y, &walkingSprite[character.anim]);

		/*--------------------------------------------------------------*/

		SDL_RenderPresent(renderer);

		startTime = endTime;
		endTime = SDL_GetTicks();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();

	return 0;
}