#include "../include/paint.h"


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

	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT: running = false; break;
			case SDL_MOUSEBUTTONDOWN: mouse = true; break;
			case SDL_MOUSEBUTTONUP: mouse = false; break;
			case SDL_KEYDOWN:
				switch (evt.key.keysym.sym)
				{
				case SDLK_ESCAPE: m_gfx->clear(); break;
				}
			}
		}

		if (mouse) mouse_down(prev_x, prev_y);

		
		SDL_GetMouseState(&prev_x, &prev_y);

		m_gfx->render();
	}
}


void Paint::mouse_down(int px, int py)
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	switch (m_mode)
	{
	case Mode::NORMAL:
		m_gfx->draw_line(px, py, x, y, { 255, 255, 255 });
		break;
	}
}