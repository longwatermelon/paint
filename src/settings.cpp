#include "../include/settings.h"
#include <json.h>


void read_settings()
{
	if (!std::ifstream("settings.json"))
	{
		std::cout << "settings.json not found, creating settings.json with default configurations\n";
		
		json::Json j;
		j.get_raw("cache-num") = 10;

		json::dump("settings.json", j);
	}
	else
	{
		json::Json j = json::load_from_path("settings.json");
		settings::cache_num = std::get<int>(j["cache-num"]);

		std::cout << "finished configuring settings\n";
	}
}