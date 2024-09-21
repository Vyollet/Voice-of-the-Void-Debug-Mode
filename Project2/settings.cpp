#include "includes.hpp"

void settings::initialize_settings()
{
	this->menu_open = true;
	this->teleport = false;
	this->debug_console = true;
	this->init_hooks = true;
	this->hulk = false;
	this->lines = false;
	this->names = false;
	this->esp = true;
	this->box = false;
	this->noclip = false;
	this->fly = false;
	this->food = false;
	this->sleep = false;
	this->server = false;
	this->time = false;
	this->time_change = 0.05f;
	this->list_objects = false;
	this->parse_functions = true;
	this->draw_distance = false;
	this->distance = 50.0f;
	this->nodamage = false;
	this->all_objects = false;
	this->game_time = false;
	this->money = false;
	this->fuel = false;
	this->health_car = false;
	this->logs = false;
	this->tips = true;
	this->prop = false;
	this->teleport = false;
	this->spawnmenu = false;
	this->cheatmenu = false;
}
