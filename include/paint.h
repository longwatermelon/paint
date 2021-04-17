#pragma once
#include "graphics.h"
#include <memory>
#include <vector>


enum class Mode
{
	NORMAL,
	ERASE,
	LINE
};


class Paint
{
public:
	Paint() = default;

	Paint(const char* title);

	void mainloop();

	void mouse_down(int prev_x, int prev_y, int radius);

	void save_to_backup(std::vector<uint32_t>& elem);

private:
	std::unique_ptr<Graphics> m_gfx;

	Mode m_mode{ Mode::NORMAL };

	std::vector<std::vector<uint32_t>> m_backups;
};