#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Sprites.h"

void typewrite(int x_center, int y, std::string text, bool type_writer_effect, float size = 1);
bool waitKey();
bool AdamEncounter(SDL_Rect camera);
bool KatyEncounter(SDL_Rect camera);

//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// START MAIN ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* args[])
{
	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	enum characters
	{
		Adam, Katy
	};

	enum positions
	{
		right1, right2, right3, right4, right5,
		left1, left2, left3, left4, left5,
		up1, up2, up3, up4, up5,
		down1, down2, down3, down4, down5
	};

	bool quit = false;
	bool left = false, right = false, up = false, down = false;
	bool characters[26];
	for (int i = 0; i < 26; i++) { characters[i] = false; }

	int mouse_x, mouse_y;

	Uint32 startTime = 0;
	Uint32 endTime = 0;
	Uint32 delta = 0;
	short fps = 60;
	short timePerFrame = 1000 / 60; // miliseconds

	SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect walkingSprite[20];
	SDL_Rect theatre[40];
	SDL_Rect backstage[3];

	/*--------------------------------------- OBSTACLES IN THEATRE ----------------------------------------*/

	theatre[0].x = 40;   theatre[1].x = 344;  theatre[2].x = 322;  theatre[3].x = 322;  theatre[4].x = 322;
	theatre[0].y = 0;    theatre[1].y = 646;  theatre[2].y = 700;  theatre[3].y = 754;  theatre[4].y = 808;
	theatre[0].w = 0;    theatre[1].w = 142;  theatre[2].w = 242;  theatre[3].w = 292;  theatre[4].w = 292;
	theatre[0].h = 0;    theatre[1].h = 30;   theatre[2].h = 30;   theatre[3].h = 30;   theatre[4].h = 30;

	theatre[5].x = 322;  theatre[6].x = 322;  theatre[7].x = 322;  theatre[8].x = 324;  theatre[9].x = 372;
	theatre[5].y = 862;  theatre[6].y = 916;  theatre[7].y = 970;  theatre[8].y = 1024; theatre[9].y = 1078;
	theatre[5].w = 292;  theatre[6].w = 292;  theatre[7].w = 292;  theatre[8].w = 308;  theatre[9].w = 292;
	theatre[5].h = 30;   theatre[6].h = 30;   theatre[7].h = 30;   theatre[8].h = 30;   theatre[9].h = 30;
	
	theatre[10].x = 372; theatre[11].x = 704; theatre[12].x = 704; theatre[13].x = 704; theatre[14].x = 704;
	theatre[10].y = 1132;theatre[11].y = 646; theatre[12].y = 700; theatre[13].y = 754; theatre[14].y = 808;
	theatre[10].w = 292; theatre[11].w = 392; theatre[12].w = 392; theatre[13].w = 392; theatre[14].w = 392;
	theatre[10].h = 30;  theatre[11].h = 30;  theatre[12].h = 30;  theatre[13].h = 30;  theatre[14].h = 30;

	theatre[15].x = 704; theatre[16].x = 704; theatre[17].x = 736; theatre[18].x = 754; theatre[19].x = 754;
	theatre[15].y = 862; theatre[16].y = 916; theatre[17].y = 970; theatre[18].y = 1024;theatre[19].y = 1078;
	theatre[15].w = 392; theatre[16].w = 392; theatre[17].w = 328; theatre[18].w = 292; theatre[19].w = 292;
	theatre[15].h = 30;  theatre[16].h = 30;  theatre[17].h = 30;  theatre[18].h = 30;  theatre[19].h = 30;

	theatre[20].x = 754; theatre[21].x = 1312;theatre[22].x = 1236;theatre[23].x = 1186;theatre[24].x = 1186;
	theatre[20].y = 1132;theatre[21].y = 646; theatre[22].y = 700; theatre[23].y = 754; theatre[24].y = 808;
	theatre[20].w = 292; theatre[21].w = 143; theatre[22].w = 243; theatre[23].w = 292; theatre[24].w = 292;
	theatre[20].h = 30;  theatre[21].h = 30;  theatre[22].h = 30;  theatre[23].h = 30;  theatre[24].h = 30;

	theatre[25].x = 1186;theatre[26].x = 1186;theatre[27].x = 1186;theatre[28].x = 1166;theatre[29].x = 1136;
	theatre[25].y = 862; theatre[26].y = 916; theatre[27].y = 970; theatre[28].y = 1024;theatre[29].y = 1078;
	theatre[25].w = 292; theatre[26].w = 292; theatre[27].w = 292; theatre[28].w = 309; theatre[29].w = 292;
	theatre[25].h = 30;  theatre[26].h = 30;  theatre[27].h = 30;  theatre[28].h = 30;  theatre[29].h = 30;

	theatre[30].x = 1136;theatre[31].x = 0;   theatre[32].x = 1550;theatre[33].x = 0;   theatre[34].x = 724;
	theatre[30].y = 1132;theatre[31].y = 300; theatre[32].y = 300; theatre[33].y = 1295;theatre[34].y = 419;
	theatre[30].w = 292; theatre[31].w = 250; theatre[32].w = 250; theatre[33].w = 1800;theatre[34].w = 353;
	theatre[30].h = 30;  theatre[31].h = 1000;theatre[32].h = 1000;theatre[33].h = 5;   theatre[34].h = 58;

	theatre[35].x = 24;  theatre[36].x = 1537;theatre[37].x = 1537;theatre[38].x = 24;  theatre[39].x = 0;
	theatre[35].y = 178; theatre[36].y = 178; theatre[37].y = 244; theatre[38].y = 244; theatre[39].y = 0;
	theatre[35].w = 238; theatre[36].w = 238; theatre[37].w = 238; theatre[38].w = 238; theatre[39].w = 0;
	theatre[35].h = 1;   theatre[36].h = 1;   theatre[37].h = 1;   theatre[38].h = 1;   theatre[39].h = 0;

	/*--------------------------------------- OBSTACLES IN BACKSTAGE ----------------------------------------*/

	backstage[0].x = 3;    backstage[1].x = 0;    backstage[2].x = 0;
	backstage[0].y = 0;    backstage[1].y = 300;  backstage[2].y = 0;
	backstage[0].w = 0;    backstage[1].w = 1825; backstage[2].w = 0;
	backstage[0].h = 0;    backstage[1].h = 1300; backstage[2].h = 0;

	/*--------------------------------------------------------------------------------------------------------*/

	for (int i = 0; i < 20; i++) // dimensions for walking sprite sheet (unfinished)
	{
		walkingSprite[i].x = (i % 5) * 36;
		walkingSprite[i].y = (i / 5) * 83;
		walkingSprite[i].w = 35;
		walkingSprite[i].h = 82;
	}

	SDL_Rect* room = theatre;

	Sprite sTheatre; sTheatre.loadFromFile("Sprites/another.png");
	Sprite sBackstage; sBackstage.loadFromFile("Sprites/backstage.png");
	Sprite exclaim; exclaim.loadFromFile("Sprites/exclaim.png");
	Sprite curtain; curtain.loadFromFile("Sprites/curtain.png");
	Sprite curtain2; curtain2.loadFromFile("Sprites/curtain.png");
	Actor nolan; nolan.loadFromFile("Sprites/walking.png");

	nolan.x = 1350;
	nolan.y = 1200;
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

					if (nolan.x + 30 > 170 && nolan.x < 220 &&
						nolan.y >= 0 && nolan.y < 75)
					{
						room = backstage;
						LEVEL_WIDTH = 2200;
					}
					else if (nolan.x + nolan.CHAR_WIDTH > 833 && nolan.x < 895 &&
							 nolan.y + 70 > 1056 && nolan.y + 70 < 1077 && !characters[characters::Katy])
					{
						characters[characters::Katy] = true;

						if (!KatyEncounter(camera))
						{
							quit = true;
						}
					}
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

		if (left) { nolan.anim = positions::left1 + (frame / 12); nolan.move(-1, 0, room, room[0].x); }
		if (right) { nolan.anim = positions::right1 + (frame / 12); nolan.move(1, 0, room, room[0].x); }
		if (up) { nolan.anim = positions::up1 + (frame / 12); nolan.move(0, -1, room, room[0].x); }
		if (down) { nolan.anim = positions::down1 + (frame / 12); nolan.move(0, 1, room, room[0].x); }

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

		if (room == theatre)
		{
			nolan.layer = 0;

			curtain2.underneath_again = curtain2.underneath;
			if ((nolan.x < 24 + curtain.getWidth() && nolan.x + nolan.CHAR_WIDTH > 24 &&
				 nolan.y + 70 < 244 && nolan.y + 70 > 36) ||
				(nolan.x < 1537 + curtain.getWidth() && nolan.x + nolan.CHAR_WIDTH > 1537 &&
				 nolan.y + 70 < 244 && nolan.y + 70 > 36))
			{ curtain2.underneath = true; curtain2.swapAlpha(); nolan.layer = 1; }
			else { curtain2.underneath = false; curtain2.swapAlpha(); }

			curtain.underneath_again = curtain.underneath; // 24, 36
			if ((nolan.x < 24 + curtain.getWidth() && nolan.x + nolan.CHAR_WIDTH > 24 &&
				 nolan.y + 70 < 36 + curtain.getHeight() && nolan.y + 70 > 36) ||
				(nolan.x < 1537 + curtain.getWidth() && nolan.x + nolan.CHAR_WIDTH > 1537 &&
				 nolan.y + 70 < 36 + curtain.getHeight() && nolan.y + 70 > 36))
			{ curtain.underneath = true; curtain.swapAlpha(); nolan.layer = 2; }
			else
			{ curtain.underneath = false; curtain.swapAlpha(); }

			sTheatre.render(0, 0, &camera);
			if (nolan.layer == 2)
				nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);
			curtain.render(24 - camera.x, 36 - camera.y, NULL);
			curtain.render(1537 - camera.x, 36 - camera.y, NULL);
			if (nolan.layer == 1)
				nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);
			curtain2.render(24 - camera.x, 102 - camera.y, NULL);
			curtain2.render(1537 - camera.x, 102 - camera.y, NULL);
			if (nolan.layer == 0)
				nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);

			if ((nolan.x < 1245 || nolan.y < 1100) && !characters[characters::Adam])
			{
				characters[characters::Adam] = true;
				left = false;
				right = false;
				up = false;
				down = false;

				for (int i = 0; i < 10; i++)
				{
					sTheatre.render(0, 0, &camera);
					nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);
					if (i % 2 == 0) { exclaim.render(1260 - camera.x, 1100 - camera.y, NULL); std::cout << "yee haw"; }

					SDL_RenderPresent(renderer);

					SDL_Delay(100);
				}


				if (!AdamEncounter(camera))
					quit = true;
			}
		}

		else if (room == backstage)
		{
			sBackstage.render(0, 0, &camera);
			nolan.render(nolan.x - camera.x, nolan.y - camera.y, &walkingSprite[nolan.anim]);
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
	Sprite button; button.loadFromFile("Sprites/button.png");

	int act = 0, select = 0, count = 0, 
		x = SCREEN_WIDTH / 2,
		y = SCREEN_HEIGHT - dialogue.getHeight() + 40,
		mouse_x, mouse_y;
	bool button1 = true, button2 = true;

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
						break;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN && act > 0)
			{
				if (mouse_y >= SCREEN_HEIGHT / 2 && mouse_y <= SCREEN_HEIGHT / 2 + 46 &&
					mouse_x >= (SCREEN_WIDTH - button.getWidth()) / 2 && mouse_x <= (SCREEN_WIDTH - button.getWidth()) / 2 + 225)
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
		dialogue.render((SCREEN_WIDTH - dialogue.getWidth()) / 2, SCREEN_HEIGHT - dialogue.getHeight() - 1, NULL);
		typewrite(170, Adam.getHeight() - 13, "Adam", false);

		switch (act)
		{
			case 0:
				typewrite(x, y, "Hi Im Adam I drive manual", true, 2);
				SDL_Delay(500); act++; break;
			case 1:
				typewrite(x, y, "Hi Im Adam I drive manual", false, 2);

				if (button1)
				{
					button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
					typewrite(x, SCREEN_HEIGHT / 2 + 15, "Hi Adam", false);
				}
				if (button2)
				{
					button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
					typewrite(x, SCREEN_HEIGHT / 2 + 80, "fffthg switgnsdsjjsjj", false);
				}

				SDL_RenderPresent(renderer);

				switch (select)
				{
				case 0:
					break;
				default:
					if (button2) { button2 = false; }
					else { button2 = true; }
					if (count > 8) {
						select = 0; act++; count = 0;
					} count++; SDL_Delay(100); break;
				} break;
			case 2:
				typewrite(x, y, "Wowie me too", true, 2);
				SDL_RenderPresent(renderer);
				if (!waitKey()) { return false; } act++; break;
			case 3:
				typewrite(x, y, "adwuhrjfdauiabhdsluh", true, 2);
				typewrite(x, y + 30, "djsioweujkha oiadnjj", true, 2);
				SDL_Delay(500); act++; break;
			case 4:
				typewrite(x, y, "adwuhrjfdauiabhdsluh", false, 2);
				typewrite(x, y + 30, "djsioweujkha oiadnjj", false, 2);

				if (button1)
				{
					button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
					typewrite(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 15, "umm m m m", false);
				}
				if (button2)
				{
					button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
					typewrite(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 80, "sorry i i", false);
				}

				switch (select)
				{
				case 1:
					if (button1) { button1 = false; }
					else { button1 = true; }
					if (count > 8) {
						select = 0; act++; count = 0;
					} count++; SDL_Delay(100); break;
				case 2:
					if (button2) { button2 = false; }
					else { button2 = true; }
					if (count > 8) {
						select = 0; act++; count = 0;
					} count++; SDL_Delay(100); break;
				} break;
			case 5:
				typewrite(x, y, "Yay friends", true, 2);
				SDL_Delay(500);
				act++; break;
			default:
				break;
		}

		/*--------------------------------------------------------------*/

		SDL_RenderPresent(renderer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// START KATY ENCOUNTER 1 /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

bool KatyEncounter(SDL_Rect camera)
{
	SDL_Event event;

	Sprite map; map.loadFromFile("Sprites/another.png");
	Sprite Katy; Katy.loadFromFile("Sprites/Characters/Katy.png");
	Sprite Sophia; Sophia.loadFromFile("Sprites/Characters/Sophia.png");
	Sprite dialogue; dialogue.loadFromFile("Sprites/dialogue.png");
	Sprite button; button.loadFromFile("Sprites/button.png");

	int act = 0, select = 0, count = 0,
		x = SCREEN_WIDTH / 2,
		y = SCREEN_HEIGHT - dialogue.getHeight() + 40,
		mouse_x, mouse_y;
	bool button1 = true, button2 = true;
	std::string speaker = "Katy";

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
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN && act > 0)
			{
				if (mouse_y >= SCREEN_HEIGHT / 2 && mouse_y <= SCREEN_HEIGHT / 2 + 46 &&
					mouse_x >= (SCREEN_WIDTH - button.getWidth()) / 2 && mouse_x <= (SCREEN_WIDTH - button.getWidth()) / 2 + 225)
					select = 1;
				else if (mouse_y >= SCREEN_HEIGHT / 2 + 70)
					select = 2;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		/*--------------------------------------------------------------*/

		map.render(0, 0, &camera);
		
		if (act >= 9)
		{
			Katy.render((SCREEN_WIDTH - Katy.getWidth()) / 4, 0, NULL);
			Sophia.render(3 * (SCREEN_WIDTH - Sophia.getWidth()) / 4, 0, NULL);
		}
		else
			Katy.render((SCREEN_WIDTH - Katy.getWidth()) / 2, 0, NULL);

		dialogue.render((SCREEN_WIDTH - dialogue.getWidth()) / 2, SCREEN_HEIGHT - dialogue.getHeight(), NULL);
		typewrite(170, SCREEN_HEIGHT - dialogue.getHeight() + 4, speaker, false);

		switch (act)
		{
		case 0:
			typewrite(x, y, "yee haw its Katy", true, 2);
			SDL_Delay(500); act++; break;
		case 1:
			typewrite(x, y, "yee haw its Katy", false, 2);

			if (button1)
			{
				button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
				typewrite(x, SCREEN_HEIGHT / 2 + 15, "YEE HAW ITS KATY", false);
			}
			if (button2)
			{
				button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
				typewrite(x, SCREEN_HEIGHT / 2 + 85, "yee haw its Katy", false);
			}

			SDL_RenderPresent(renderer);

			switch (select)
			{
			case 1:
				if (button1) { button1 = false; }
				else { button1 = true; }
				if (count > 8) {
					select = 0; act++; count = 0;
				} count++; SDL_Delay(100); break;
			case 2:
				if (button2) { button2 = false; }
				else { button2 = true; }
				if (count > 8) {
					select = 0; act = 7; count = 0;
				} count++; SDL_Delay(100); break;
			} break;
		case 2:
			typewrite(x, y, "aww cmon you can do better than that", true, 2);
			if (!waitKey())
				return false;
			act++; break;
		case 3:
			typewrite(x, y, "I said YEE HAW ITS KATY", true, 2);
			SDL_Delay(500); act++; break;
		case 4:
			typewrite(x, y, "I said YEE HAW ITS KATY", false, 2);
			if (!waitKey())
				return false;
			act++; break;
		case 5:
			typewrite(x, y + 10, "YEE HAW ITS KATY", true, 4);
			act++; break;
		case 6:
			typewrite(x, y + 10, "YEE HAW ITS KATY", false, 4);

			button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2, NULL);
			typewrite(x, SCREEN_HEIGHT / 2 + 15, "YEE HAW", false, 2);

			button.render((SCREEN_WIDTH - button.getWidth()) / 2, SCREEN_HEIGHT / 2 + 70, NULL);
			typewrite(x, SCREEN_HEIGHT / 2 + 80, "ITS KATY", false, 2);

			SDL_RenderPresent(renderer);

			switch (select)
			{
			case 0:
				break;
			default:
				act = 8; break;
			}

			break;
		case 7:
			typewrite(x, y, "weak", true, 2);
			if (!waitKey())
				return false;
			act = 3; break;
		case 8:
			typewrite(x, SCREEN_HEIGHT / 2 + 80, "YEEEEEEE HAAAAAW", false, 6);
			SDL_RenderPresent(renderer);
			SDL_Delay(2000); act++; speaker = "Sophia"; break;
		case 9:
			typewrite(x, y, "um", true, 2);
			if (!waitKey())
				return false;
			act++; break;
		case 10:
			typewrite(x, y, "wtf katy", true, 2);
			SDL_Delay(500); act++; break;
		case 11:
			typewrite(x, y, "wtf katy", false, 2);
			break;
		default:
			break;
		}

		/*--------------------------------------------------------------*/

		SDL_RenderPresent(renderer);
	}
}

void typewrite(int x_center, int y, std::string text, bool type_writer_effect, float size)
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
		int letter = static_cast<int>(text[i]); // -er mage

		if (letter <= 90)
			letter -= 65;
		else if (letter >= 97)
			letter -= 71;

		if (size == 1)
			words.render((x_center - (text.size() * 8) / 2) + i * 8, y, &character[letter]);
		else
			words.renderScaled((x_center - (text.size() * 8 * size) / 2) + i * 8 * size, y, size, &character[letter]);

		if (type_writer_effect)
		{
			SDL_RenderPresent(renderer);
			SDL_Delay(1000 / text.size());
		}
	}
}

bool waitKey()
{
	SDL_Event event;

	while (true)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				return false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					return true;
					break;
				}
			}
		}
	}
}