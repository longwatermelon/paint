#pragma once
#include "utils.h"
#include <vector>
#include <SDL.h>


class Graphics
{
public:
	Graphics() = default;

	Graphics(const char* title);

	~Graphics();

	void render();

	void clear();

	void draw_pixel(int x, int y, SDL_Color col);

	void draw_line(float x1, float y1, float x2, float y2, SDL_Color col);

	SDL_Renderer* rend() const { return m_rend; }
	SDL_Window* window() const { return m_window; }

	std::vector<uint32_t> texbuf() const { return m_texbuf; }
	void set_texbuf(std::vector<uint32_t> texbuf) { m_texbuf = texbuf; }

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_rend{ nullptr };

	std::vector<uint32_t> m_texbuf;
	SDL_Texture* m_tex;

	SDL_Rect m_fullscreen_rect{ 0, 0, SCREEN_W, SCREEN_H };
};