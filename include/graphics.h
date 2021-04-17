#pragma once
#include "utils.h"
#include <vector>
#include <SDL.h>


class Graphics
{
public:
	Graphics() = default;

	Graphics(const char* title)
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		m_rend = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		m_tex = SDL_CreateTexture(m_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
		m_texbuf = std::vector<uint32_t>(SCREEN_W * SCREEN_H);

		SDL_SetRenderDrawColor(m_rend, 0, 0, 0, 255);
		SDL_RenderClear(m_rend);
		SDL_RenderPresent(m_rend);
	}

	~Graphics()
	{
		SDL_DestroyRenderer(m_rend);
		SDL_DestroyWindow(m_window);
	}

	SDL_Renderer* rend() const { return m_rend; }
	SDL_Window* window() const { return m_window; }

	void render()
	{
		SDL_UpdateTexture(m_tex, 0, m_texbuf.data(), SCREEN_W * sizeof(uint32_t));

		SDL_RenderCopy(m_rend, m_tex, 0, &m_fullscreen_rect);

		SDL_RenderPresent(m_rend);
	}

	void clear()
	{
		for (int i = 0; i < SCREEN_W * SCREEN_H; ++i)
		{
			m_texbuf[i] = 0x000000;
		}
	}

	void draw_pixel(int x, int y, SDL_Color col)
	{
		m_texbuf[y * SCREEN_W + x] = 0x00000000 | col.r << 16 | col.g << 8 | col.b;
	}

	void draw_line(float x1, float y1, float x2, float y2, SDL_Color col)
	{
		float dx = x2 - x1;
		float dy = y2 - y1;

		if (dx == 0.f && dy == 0.f) draw_pixel(x1, y1, col);

		if (abs(dx) > abs(dy))
		{
			if (x1 > x2)
			{
				std::swap(x1, x2);
				std::swap(y1, y2);
			}

			float a = dy / dx;
			float y = y1;

			for (float x = x1; x < x2; ++x)
			{
				draw_pixel(x, y, col);
				y += a;
			}
		}
		else
		{
			if (y1 > y2)
			{
				std::swap(y1, y2);
				std::swap(x1, x2);
			}

			float a = dx / dy;
			float x = x1;

			for (float y = y1; y < y2; ++y)
			{
				draw_pixel(x, y, col);
				x += a;
			}
		}
	}

	std::vector<uint32_t> texbuf() const { return m_texbuf; }
	void set_texbuf(std::vector<uint32_t> texbuf) { m_texbuf = texbuf; }

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_rend{ nullptr };

	std::vector<uint32_t> m_texbuf;
	SDL_Texture* m_tex;

	SDL_Rect m_fullscreen_rect{ 0, 0, SCREEN_W, SCREEN_H };
};