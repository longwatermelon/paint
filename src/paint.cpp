#include "../include/paint.h"
#include "../include/settings.h"


Paint::Paint(const char* title)
{
	m_gfx = std::make_unique<Graphics>(title);
}


void Paint::mainloop()
{
	bool running = true;
	SDL_Event evt;

	bool mouse = false;

	int prev_x, prev_y;
	SDL_GetMouseState(&prev_x, &prev_y);

	std::vector<std::vector<uint32_t>> backups{ m_gfx->texbuf() };

	int radius = 1;

	read_settings();

	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_MOUSEBUTTONDOWN: mouse = true; break;
			case SDL_MOUSEBUTTONUP:
				mouse = false;
				backups.emplace_back(m_gfx->texbuf());
				if (backups.size() >= settings::cache_num)
				{
					backups.erase(backups.begin());
				}
				break;
			case SDL_KEYDOWN:
				switch (evt.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_gfx->clear();
					backups.clear();
					backups.emplace_back(m_gfx->texbuf());
					break;
				case SDLK_z:
					if (backups.size() > 1)
					{
						backups.erase(backups.end() - 1);
						m_gfx->set_texbuf(backups[backups.size() - 1]);
					}
					break;
				case SDLK_e:
					m_mode = Mode::ERASE;
					break;
				case SDLK_d:
					m_mode = Mode::NORMAL;
					break;
				case SDLK_UP:
					if (++radius >= 50) radius = 50;
					break;
				case SDLK_DOWN:
					if (--radius <= 0) radius = 1;
					break;
				}
				break;
			}
		}

		if (mouse) mouse_down(prev_x, prev_y, radius);
		
		SDL_GetMouseState(&prev_x, &prev_y);

		m_gfx->render();
	}
}


void Paint::mouse_down(int px, int py, int radius)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	switch (m_mode)
	{
	case Mode::NORMAL:
		m_gfx->draw_line(px, py, x, y, { 255, 255, 255 }, radius);
		break;
	case Mode::ERASE:
		m_gfx->draw_line(px, py, x, y, { 0, 0, 0 }, radius);
		break;
	}
}