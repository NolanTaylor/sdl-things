#pragma once

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 650;
const int LEVEL_WIDTH = 1800;
const int LEVEL_HEIGHT = 1300;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

class Sprite
{
public:
	Sprite() { mTexture = NULL; w = 0; h = 0; }

	~Sprite() { free(); }

	bool loadFromFile(std::string path)
	{
		free();

		SDL_Texture* newTexture = NULL;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		w = loadedSurface->w;
		h = loadedSurface->h;

		SDL_FreeSurface(loadedSurface);

		mTexture = newTexture;
		return mTexture != NULL;
	}

	void free()
	{
		if (mTexture != NULL)
		{
			SDL_DestroyTexture(mTexture);
			mTexture = NULL;
			w = 0;
			h = 0;
		}
	}

	void render(int x, int y, SDL_Rect* clip = NULL)
	{
		SDL_Rect renderQuad = { x, y, w, h };

		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
	}

	int getWidth() { return w; }
	int getHeight() { return h; }

private:
	SDL_Texture* mTexture;

	int w;
	int h;
};

class Actor : public Sprite
{
public:
	int x = 0;
	int y = 0;
	const int CHAR_WIDTH = 40;
	const int CHAR_HEIGHT = 40;

	int anim = 0;

	void move(int move_x, int move_y, SDL_Rect* room = NULL)
	{
		x += move_x;

		if ((x < 0) || (x + CHAR_WIDTH > LEVEL_WIDTH)) { x -= move_x; }

		y += move_y;

		if ((y < 0) || (y + CHAR_HEIGHT > LEVEL_HEIGHT)) { y -= move_y; }

		for (int i = 0; i < 30; i++)
		{
			if (x + CHAR_WIDTH > room[i].x && x < room[i].x + room[i].w && y + CHAR_HEIGHT > room[i].y && y + (CHAR_HEIGHT / 2) < room[i].y + room[i].h)
			{
				x -= move_x; y -= move_y;
			}
		}
	}
};