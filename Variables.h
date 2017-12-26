#pragma once
#include "PS3.h"

namespace
{
	typedef unsigned int uint;

	bool loaded[18];
	bool open[18];
	bool info_open[18];
	int num_options[18];
	int scroll[18];
	int max_scroll[18];
	float ycoord[18];
	char* cur_menu[18];
	bool int_option[18];
	uint num_clients[18];
	char* clients[18][18];

	enum Status {
		nostatus,
		verified,
		admin,
		cohost,
		host
	} status[18];

	uint getHostNumber();
	void initMods(const uint);

	void initVars(const uint client) {
		for (uint i = 0; i < 18; ++i) {
			status[i] = nostatus;
		}
		status[getHostNumber()] = host;
		loaded[client] = false;
		open[client] = false;
		info_open[client] = true;
		num_options[client] = 0;
		scroll[client] = 0;
		max_scroll[client] = num_options[client];
		ycoord[client] = 347;
		cur_menu[client] = "main";
		int_option[client] = false;
		num_clients[client] = 0;
		initMods(client);
	}

#pragma region Mods

	bool aimbot_bool[18];
	bool gm[18];
	bool ammo[18];
	bool thp[18];
	bool ufo[18];
	bool speed[18];
	bool invis[18];
	bool freeze[18];
	bool sui[18];
	int perks[18];
	bool sap[18];
	uint fov[18];
	uint fov_array[18][4];
	uint next[18];
	bool jump[18];
	bool super_speed[18];
	bool laser[18];
	bool boxes[18];
	bool chrome[18];
	bool recoil[18];
	bool uav[18];
	bool bullets[18];
	float* tele_pos[18];

	void fovInit(const uint client) {
		fov[client] = 65;
		fov_array[client][0] = 65; 
		fov_array[client][1] = 80; 
		fov_array[client][2] = 90; 
		fov_array[client][3] = 100;
		next[client] = 1;
	}

	void initMods(const uint client) {
		aimbot_bool[client] = false;
		gm[client] = false;
		ammo[client] = false;
		thp[client] = false;
		ufo[client] = false;
		speed[client] = false;
		invis[client] = false;
		freeze[client] = false;
		sui[client] = false;
		perks[client] = *(char*)(0x110A76D + (0x3980 * client));
		sap[client] = false;
		fovInit(client);
		jump[client] = false;
		super_speed[client] = false;
		laser[client] = false;
		boxes[client] = false;
		chrome[client] = false;
		recoil[client] = false;
		uav[client] = false;
		bullets[client] = false;
		// for (uint i = 0; i < 3; ++i) { tele_pos[client][i] = 0.0f; }
		// tele_pos[client][2] = 10.0f;
	}

#pragma endregion
}