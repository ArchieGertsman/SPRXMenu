#pragma once
#include "UI.h"

namespace Graphics
{
	namespace Colors {
		color_s black = { 0, 0, 0, 0 };
		color_s white = { 255, 255, 255, 0 };
		color_s blue = { 0, 0, 255, 0 };
		color_s baby_blue = { 55, 180, 222, 0 };
		color_s purple = { 255, 0, 255, 0 };
		color_s green = { 0, 255, 0, 0 };
		color_s yellow = { 204, 214, 11, 0 };
		color_s orange = { 255, 140, 0, 0 };
		color_s red = { 255, 0, 0, 0 };
	}

	namespace Huds
	{
		game_hudelem_s* background[18];
		game_hudelem_s* title_background[18];
		game_hudelem_s* scroller[18];

		game_hudelem_s* title[18];
		game_hudelem_s* options[18][20];
		game_hudelem_s* clear_options[18][20];
		game_hudelem_s* credits[18];

		game_hudelem_s* info_box_top[18];
		game_hudelem_s* info_box[18];
		game_hudelem_s* info_box_title[18];
		game_hudelem_s* info_box_text[18][4];

		void initInfo(const uint client) {
			setShader(&info_box_top[client], client, 170, 30, -70, 185, Colors::baby_blue);
			setShader(&info_box[client], client, 170, 90, -70, 214, Colors::black);

			setText(&info_box_title[client], client, "How to Use", 3, 1.6, 15, 163, 1, Colors::white, Colors::black);
			setText(&info_box_text[client][0], client, "Open [{+actionslot 1}] / Select [{+gostand}]", 3, 1.0, 15, 190, 1, Colors::white, Colors::black);
			setText(&info_box_text[client][1], client, "Up [{+actionslot 1}] / Down [{+actionslot 2}]", 3, 1.0, 15, 210, 1, Colors::white, Colors::black);
			setText(&info_box_text[client][2], client, "Close + Back [{+usereload}]", 3, 1.0, 15, 230, 1, Colors::white, Colors::black);
			setText(&info_box_text[client][3], client, "Open/Close Info [{+actionslot 3}]", 3, 1.0, 15, 250, 1, Colors::white, Colors::black);

			fadeOverTime(info_box_top[client], 75, 255);
			fadeOverTime(info_box[client], 75, 150);
			fadeOverTime(info_box_title[client], 75, 255);
			for (uint i = 0; i < 4; ++i) {
				fadeOverTime(info_box_text[client][i], 75, 255);
			}
		}

		void init(const uint client) {
			initInfo(client);
			setShader(&title_background[client], client, 200, 46, 500, 85, Colors::baby_blue);
			setShader(&background[client], client, 200, 28, 500, 130, Colors::black);
			setShader(&scroller[client], client, 200, 20, 500, 145, Colors::white);

			setText(&title[client], client, "Evolutions E|MT", 3, 1.9, 600, 240, 5, Colors::white, Colors::black);
			setText(&credits[client], client, "By: Hacked Tutorials & Evolutions", 3, 0.7, 505, 146, 0, Colors::white, Colors::black);
			for (uint i = 0; i < 20; ++i) {
				setText(&Huds::options[client][i], client, "", 3, 1.3, 600, ycoord[client], 5, Colors::white, Colors::black);
				ycoord[client] += 45;
			}
		}
	}

	void resetScroll(const uint client) {
		scroll[client] = 0;
		Huds::scroller[client]->elem.Y = 145;
		for (int i = 1; i < num_options[client]; ++i) {
			changeColor(Huds::options[client][i], Colors::white);
		}
		changeColor(Huds::options[client][0], Colors::black);
	}

	void openMenu(const uint client) {
		fadeOverTime(Huds::title_background[client], 75, 255);
		fadeOverTime(Huds::background[client], 75, 150);
		fadeOverTime(Huds::scroller[client], 75, 230);

		fadeOverTime(Huds::title[client], 75, 255);
		fadeOverTime(Huds::credits[client], 75, 255);

		for (uint i = 0; i < num_options[client]; ++i) {
			fadeOverTime(Huds::options[client][i], 75, 255);
		}

		changeColor(Huds::options[client][0], Colors::black);
		open[client] = true;
		sleep(100);
	}

	void closeMenu(const uint client) {
		fadeOverTime(Huds::background[client], 75, 0);
		fadeOverTime(Huds::title_background[client], 75, 0);
		fadeOverTime(Huds::scroller[client], 75, 0);

		fadeOverTime(Huds::title[client], 75, 0);
		fadeOverTime(Huds::credits[client], 75, 0);

		for (uint i = 0; i < num_options[client]; ++i) {
			fadeOverTime(Huds::options[client][i], 75, 0);
		}

		open[client] = false;
		resetScroll(client);
		cur_menu[client] = "main";
		sleep(100);
	}

	void closeInfo(const uint client) {
		fadeOverTime(Huds::info_box_top[client], 75, 0);
		fadeOverTime(Huds::info_box[client], 75, 0);
		fadeOverTime(Huds::info_box_title[client], 75, 0);
		for (uint i = 0; i < 4; ++i) {
			fadeOverTime(Huds::info_box_text[client][i], 75, 0);
		}
	}

	void openInfo(const uint client) {
		fadeOverTime(Huds::info_box_top[client], 75, 255);
		fadeOverTime(Huds::info_box[client], 75, 150);
		fadeOverTime(Huds::info_box_title[client], 75, 255);
		for (uint i = 0; i < 4; ++i) {
			fadeOverTime(Huds::info_box_text[client][i], 75, 255);
		}
	}

	void infoBox(const uint client) {
		info_open[client] = !info_open[client];
		info_open[client] ? openInfo(client) : closeInfo(client);
		iPrintln(client, info_open[client] ? const_cast<char*>("Info Box Opened") : const_cast<char*>("Info Box Closed"));
	}

	void updateScroll(uint client) {
		moveOverTime(Huds::scroller[client], 75, 500, 145 + (scroll[client] * 20));
		for (uint i = 0; i < max_scroll[client]; ++i) {
			if (i == scroll[client]) fadeOverTimeColor(Huds::options[client][i], 75, Colors::black);
			else fadeOverTimeColor(Huds::options[client][i], 75, Colors::white);
		}
		sleep(90);
	}

	char* menu_color[8] = { "Default", "Blue", "Purple", "Red", "Orange", "Yellow", "Green", "Rainbow" };
	// color_s rainbow_colors[7] = { Colors::baby_blue, Colors::blue, Colors::purple, Colors::red, Colors::orange, Colors::yellow, Colors::green };
	color_s rainbow_colors[7];
	void initRainbow() {
		rainbow_colors[0] = Colors::baby_blue;
		rainbow_colors[1] = Colors::blue;
		rainbow_colors[2] = Colors::purple;
		rainbow_colors[3] = Colors::red;
		rainbow_colors[4] = Colors::orange;
		rainbow_colors[5] = Colors::yellow;
		rainbow_colors[6] = Colors::green;
	}
	uint cur_menu_color = 0;

	bool rainbow = false;
	void rainbowThread(uint64_t arg) {
		sleep(10000);
		for (;;) {
			for (uint i = 0; i < 18; ++i) {
				if (rainbow) {
					for (uint j = 1; j < 5; ++j) {
						fadeOverTimeColor(Huds::title_background[i], 200, rainbow_colors[j]);
						sleep(200);
					}
				}
			}
		}
	}
	void menuColor(const uint client) {
		initRainbow();
		if (cur_menu_color < 7) {
			rainbow = false;
			fadeOverTimeColor(Huds::title_background[client], 200, rainbow_colors[cur_menu_color]);
			fadeOverTimeColor(Huds::info_box_top[client], 200, rainbow_colors[cur_menu_color]);
		}
		else {
			rainbow = !rainbow;
			iPrintln(client, "rainbow");
		}
		char buf[30];
		Com_sprintf(buf, 30, "%i", cur_menu_color);
		iPrintln(client, buf);
		sleep(100);
	}
}