#pragma once

class settings
{
public:
	bool teleport;
	bool debug_console;
	bool init_hooks;
	bool hulk;
	bool time;
	float time_change;
	bool lines;
	bool names;
	bool box;
	bool noclip;
	bool fly;
	bool food;
	bool sleep;
	bool server;
	bool esp;
	bool pause;
	bool list_objects;
	bool draw_distance;
	float distance;
	bool nodamage;
	bool all_objects;
	bool game_time;
	bool money;
	bool menu_open;
	bool logs;
	bool tips;
	bool fuel;
	bool health_car;
	bool prop;

	void initialize_settings();
};