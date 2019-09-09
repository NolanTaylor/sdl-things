#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Sprites.h"

void typewrite(int x, int y, std::string text, bool type_writer_effect);

//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// START MAIN ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* args[])
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	bool quit = false;
	bool left = false, right = false, up = false, down = false;
	bool AdamEncounter(SDL_Rect camera);

	int mouse_x, mouse_y;

	enum characters
	{
		Adam
	};

	enum positions
	{
		right1, right2, right3, right4, right5,
		left1, left2, left3, left4, left5,
		up1, up2, up3, up4, up5,
		down1, down2, down3, down4, down5
	};

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 delta = 0;
	short fps = 60;
	short timePerFrame = 1000 / 60; // miliseconds

	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect walkingSprite[20];
	SDL_Rect theatre[30];

	/*--------------------------------------- OBSTACLES IN THEATRE ----------------------------------------*/

	theatre[0].x = 344;  theatre[1].x = 322;  theatre[2].x = 322;  theatre[3].x = 322;  theatre[4].x = 322;
	theatre[0].y = 646;  theatre[1].y = 700;  theatre[2].y = 754;  theatre[3].y = 808;  theatre[4].y = 862;
	theatre[0].w = 142;  theatre[1].w = 242;  theatre[2].w = 292;  theatre[3].w = 292;  theatre[4].w = 292;
	theatre[0].h = 30;   theatre[1].h = 30;   theatre[2].h = 30;   theatre[3].h = 30;   theatre[4].h = 30;

	theatre[5].x = 322;  theatre[6].x = 322;  theatre[7].x = 324;  theatre[8].x = 372;  theatre[9].x = 372;
	theatre[5].y = 916;  theatre[6].y = 970;  theatre[7].y = 1024; theatre[8].y = 1078; theatre[9].y = 1132;
	theatre[5].w = 292;  theatre[6].w = 292;  theatre[7].w = 308;  theatre[8].w = 292;  theatre[9].w = 292;
	theatre[5].h = 30;   theatre[6].h = 30;   theatre[7].h = 30;   theatre[8].h = 30;   theatre[9].h = 30;
	
	theatre[10].x = 704; theatre[11].x = 704; theatre[12].x = 704; theatre[13].x = 704; theatre[14].x = 704;
	theatre[10].y = 646; theatre[11].y = 700; theatre[12].y = 754; theatre[13].y = 808; theatre[14].y = 862;
	theatre[10].w = 392; theatre[11].w = 392; theatre[12].w = 392; theatre[13].w = 392; theatre[14].w = 392;
	theatre[10].h = 30;  theatre[11].h = 30;  theatre[12].h = 30;  theatre[13].h = 30;  theatre[14].h = 30;

	theatre[15].x = 704; theatre[16].x = 736; theatre[17].x = 754;
	theatre[15].y = 916; theatre[16].y = 970; theatre[17].y = 1024;
	theatre[15].w = 392; theatre[16].w = 328; theatre[17].w = 292;
	theatre[15].h = 30;  theatre[16].h = 30;  theatre[17].h = 30;

	/*--------------------------------------------------------------------------------------------------------*/

	for (int i = 0; i < 20; i++) // dimensions for walking sprite sheet (unfinished)
	{
		walkingSprite[i].x = 1 + ((i % 5) * 41);
		walkingSprite[i].y = 1 + ((i / 5) * 41);
		walkingSprite[i].w = 40;
		walkingSprite[i].h = 40;
	}

	Sprite map; map.loadFromFile("Sprites/another.png");
	Sprite exclaim; exclaim.loadFromFile("Sprites/exclaim.png");
	bool characters[26];
	for (int i = 0; i < 26; i++) { characters[i] = false; }
	Actor nolan; nolan.loadFromFile("Sprites/walking.png");

	nolan.x = 1350;
	nolan.y = 1225;
	nolan.anim = positions::left1;

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
				case SDLK_SPACE:
					std::cout << "nolan: " << nolan.x << "," << nolan.y << std::endl <<
								 "camera: " << camera.x << "," << camera.y << std::endl;
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

		if (left) { nolan.anim = positions::left1 + (frame / 15); nolan.move(-1, 0, theatre); }
		if (right) { nolan.anim = positions::right1 + (frame / 15); nolan.move(1, 0, theatre); }
		if (up) { nolan.anim = positions::up1 + (frame / 15); nolan.move(0, -1, theatre); }
		if (down) { nolan.anim = positions::down1 + (frame / 15); nolan.move(0, 1, theatre); }

		if (left || right || up || down)
		{
			if (frame < 59)
				frame++;
			else
				frame = 0;
		}

		camera.x = (nolan.x + nolan.CHAR_WIDTH / 2) - SCREEN_WIDTH / 2;
		camera.y = (nolan.y + nolan.CHAR_HEIGHT / 2) - SCREEN_HEIGHT / 2;

		if (camera.x < 0) { camera.x = 0; }
		if (camera.y < 0) { camera.y = 0; }
		if (camera.x > LEVEL_WIDTH - camera.w) { camera.x = LEVEL_WIDTH - camera.w; }
		if (camera.y > LEVEL_HEIGHT - camera.h) { camera.y = LEVEL_HEIGHT - camera.h; }

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		/*--------------------------------------------------------------*/

		map.render(0, 0, &camera);

		nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);

		if (nolan.x < 1245 && nolan.y > 1000 && characters[characters::Adam] == false)
		{
			characters[characters::Adam] = true;
			left = false;
			right = false;
			up = false;
			down = false;

			for (int i = 0; i < 10; i++)
			{
				map.render(0, 0, &camera);
				nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);
				if (i % 2 == 0) {exclaim.render(1260 - camera.x, 1100 - camera.y, NULL); std::cout << "yee haw";}

				SDL_RenderPresent(renderer);

				SDL_Delay(100);
			}


			if (AdamEncounter(camera) == false)
				quit = true;
		}

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

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START ADAM ENCOUNTER 1 /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

bool AdamEncounter(SDL_Rect camera)
{
	SDL_Event event;

	Sprite map; map.loadFromFile("Sprites/another.png");
	Sprite Adam; Adam.loadFromFile("Sprites/Characters/Adam.png");
	Sprite dialogue; dialogue.loadFromFile("Sprites/dialogue.png");
	Sprite button1; button1.loadFromFile("Sprites/button.png");
	Sprite button2; button2.loadFromFile("Sprites/button.png");

	int act = 0, select = 0, mouse_x, mouse_y;

	while (true)
	{

		SDL_GetMouseState(&mouse_x, &mouse_y);

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				return false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_q:
						return true;
						break;

					case SDLK_SPACE:
						//act++;
						break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN && act > 0)
			{
				if (mouse_y >= SCREEN_HEIGHT / 2 && mouse_y <= SCREEN_HEIGHT / 2 + 46 &&
					mouse_x >= (SCREEN_WIDTH - button1.getWidth()) / 2 && mouse_x <= (SCREEN_WIDTH - button1.getWidth()) / 2 + 225)
				{
					select = 1;
					std::cout << "leftover_salad";
				}
				else if (mouse_y >= SCREEN_HEIGHT / 2 + 70)
				{
					select = 2;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		/*--------------------------------------------------------------*/

		map.render(0, 0, &camera);
		Adam.render((SCREEN_WIDTH - Adam.getWidth()) / 2, 0, NULL);

		switch (act)
		{
			case 0:
				dialogue.render((SCREEN_WIDTH - Adam.getWidth()) / 2, Adam.getHeight(), NULL);
				SDL_RenderPresent(renderer);
				SDL_Delay(2000);
				act++;
				break;
			case 1:
				dialogue.render((SCREEN_WIDTH - Adam.getWidth()) / 2, Adam.getHeight(), NULL);
				button1.render((SCREEN_WIDTH - button1.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
				typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 10, "Hi Adam", false);
				button2.render((SCREEN_WIDTH - button2.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
				typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 80, "fffthg switgnsdsjjsjj", false);
				
				switch (select)
				{
					case 1:
						for (int i = 0; i < 8; i++)
						{
							map.render(0, 0, &camera);
							Adam.render((SCREEN_WIDTH - Adam.getWidth()) / 2, 0, NULL);
							dialogue.render((SCREEN_WIDTH - Adam.getWidth()) / 2, Adam.getHeight(), NULL);
							if (i % 2)
							{
								button1.render((SCREEN_WIDTH - button1.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
								typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 10, "Hi Adam", false);
							}
							button2.render((SCREEN_WIDTH - button2.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
							typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 80, "fffthg switgnsdsjjsjj", false);
							SDL_Delay(100);
							SDL_RenderPresent(renderer);
						}
						select = 0;
						act++;
						break;
					case 2:
						for (int i = 0; i < 8; i++)
						{
							map.render(0, 0, &camera);
							Adam.render((SCREEN_WIDTH - Adam.getWidth()) / 2, 0, NULL);
							dialogue.render((SCREEN_WIDTH - Adam.getWidth()) / 2, Adam.getHeight(), NULL);
							if (i % 2)
							{
								button2.render((SCREEN_WIDTH - button2.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
								typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 80, "fffthg switgnsdsjjsjj", false);
							}
							button1.render((SCREEN_WIDTH - button1.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
							typewrite((SCREEN_WIDTH - button1.getWidth()) / 2 + 10, SCREEN_HEIGHT / 2 + 10, "Hi Adam", false);
							SDL_Delay(100);
							SDL_RenderPresent(renderer);
						}
						select = 0;
						act++;
						break;
				}

				break;
			case 2:
				break;
			default:
				break;
		}

		/*--------------------------------------------------------------*/

		SDL_RenderPresent(renderer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////// TYPE_WRITER EFFECT FOR DIALOGUE? /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void typewrite(int x, int y, std::string text, bool type_writer_effect)
{
	Sprite words; words.loadFromFile("Sprites/text.png");
	SDL_Rect character[63];

	for (int i = 0; i < 63; i++)
	{
		character[i].x = ((i % 9) * 11);
		character[i].y = ((i / 9) * 14);
		character[i].w = 10;
		character[i].h = 13;
	}

	for (std::string::size_type i = 0; i < text.size(); i++)
	{
		int letter = static_cast<int>(text[i]);

		if (letter <= 90)
			letter -= 65;
		else if (letter >= 97)
			letter -= 71;

		words.render(x + i * 8, y, &character[letter]);

		if (type_writer_effect)
		{
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}
	}
}