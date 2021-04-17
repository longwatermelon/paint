#pragma once
#include "graphics.h"
#include <memory>
#include <vector>


enum class Mode
{
	NORMAL
};


class Paint
{
public:
	Paint() = default;

	Paint(const char* title);

	void mainloop();

	void mouse_down(int prev_x, int prev_y);

private:
	std::unique_ptr<Graphics> m_gfx;

	Mode m_mode{ Mode::NORMAL };
};