#include "../include/settings.h"
#include <json.h>


void read_settings()
{
	if (!std::ifstream("paint.json"))
	{
		std::cout << "paint.json not found, using default settings\n";
		settings::cache_num = 50;
	}
	else
	{
		json::Json j = json::load_from_path("paint.json");
		settings::cache_num = std::get<int>(j["cache-num"]);

		std::cout << "finished configuring settings\n";
	}
}