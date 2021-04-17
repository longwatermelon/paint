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

	int radius = 1;

	m_backups.emplace_back(m_gfx->texbuf());

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

				m_backups.emplace_back(m_gfx->texbuf());
				if (m_backups.size() >= settings::cache_num)
				{
					m_backups.erase(m_backups.begin());
				}
				break;
			case SDL_KEYDOWN:
				switch (evt.key.keysym.sym)
				{
				case SDLK_c:
					m_gfx->clear();
					m_backups.clear();
					m_backups.emplace_back(m_gfx->texbuf());
					break;
				case SDLK_z:
					if (m_backups.size() > 1)
					{
						m_backups.erase(m_backups.end() - 1);
						m_gfx->set_texbuf(m_backups[m_backups.size() - 1]);
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
				case SDLK_LSHIFT:
					if (radius == 1)
						radius = 50;
					else
						radius = 1;
					break;
				case SDLK_l:
					m_mode = Mode::LINE;

					if (mouse)
					{
						mouse = false;

						m_backups.emplace_back(m_gfx->texbuf());
						if (m_backups.size() >= settings::cache_num)
						{
							m_backups.erase(m_backups.begin());
						}
					}
					break;
				}
				break;
			}
		}

		if (mouse)
			mouse_down(prev_x, prev_y, radius);

		m_gfx->render();

		if (m_mode == Mode::LINE)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			SDL_SetRenderDrawColor(m_gfx->rend(), 255, 255, 255, 255);
			SDL_RenderDrawLine(m_gfx->rend(), prev_x, prev_y, x, y);
			SDL_SetRenderDrawColor(m_gfx->rend(), 0, 0, 0, 255);

			SDL_RenderPresent(m_gfx->rend());
		}
		
		if (m_mode != Mode::LINE)
			SDL_GetMouseState(&prev_x, &prev_y);
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
	case Mode::LINE:
		m_gfx->draw_line(px, py, x, y, { 255, 255, 255 }, radius);
		save_to_backup(m_gfx->texbuf());
		m_mode = Mode::NORMAL;
		break;
	}
}


void Paint::save_to_backup(std::vector<uint32_t>& elem)
{
	m_backups.emplace_back(elem);

	if (m_backups.size() >= settings::cache_num)
		m_backups.erase(m_backups.begin());
}