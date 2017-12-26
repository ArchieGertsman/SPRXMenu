#pragma once
#include "Graphics.h"
#include "Mods.h"
#include "Aimbot.h"

namespace Selection
{
	using namespace Graphics;

	void addOption(const uint client, const char* text) {
		changeText(Huds::options[client][num_options[client]], text);
		++num_options[client];
		++max_scroll[client];
		Huds::background[client]->elem.Height += 20;
		Huds::credits[client]->elem.Y += 20;
	}

	void addIntOption(const uint client, const char* text, int* num) {
		char buf[30];
		snprintf(buf, sizeof(buf), "%s: < %i >", text, *num);
		addOption(client, buf);
	}

	void addTextScrollOption(const uint client, const char* title, const char* text) {
		char buf[30];
		snprintf(buf, sizeof(buf), "%s: < %s >", title, text);
		addOption(client, buf);
	}

	void initOptions(const uint client) {
		addOption(client, "Main Mods");
		addOption(client, "Weapons");
		addOption(client, "Models");
		addOption(client, "Visions");
		addOption(client, "Menu Settings");
		addOption(client, "Cheater Menu");
		addOption(client, "Lobby Settings");
		addOption(client, "Teleportation");
		addOption(client, "Account");
		addOption(client, "Clients");
	}

	void resetOptionColors(const uint client) {
		for (uint i = 0; i < num_options[client]; ++i) {
			changeTransparency(Huds::options[client][i], 255);
			changeColor(Huds::options[client][i], Colors::white);
		}
		changeColor(Huds::options[client][0], Colors::black);
	}

	void clearOptions(const uint client) {
		for (uint i = 0; i < num_options[client]; ++i) {
			changeText(Huds::options[client][i], "");
		}
		num_options[client] = 0;
		max_scroll[client] = num_options[client];
		scroll[client] = 0;
	}

	void resetMenu(const uint client) {
		Graphics::Huds::background[client]->elem.Height = 28;
		Huds::credits[client]->elem.Y = 146;
	}

	void loadSub(const uint client, char* menu) {
		cur_menu[client] = menu;
		clearOptions(client);
		resetMenu(client);
		resetScroll(client);
		if (cur_menu[client] == "main") {
			initOptions(client);
		}
		else if (cur_menu[client] == "main_mods") {
			addOption(client, "God Mode");
			addOption(client, "Infinite Ammo");
			addOption(client, "Third Person"); 
			addOption(client, "Set All Perks");
			addOption(client, "UFO Mode");
			addOption(client, "Speed X2");
			addOption(client, "Invisible");
			addOption(client, "Field of View");
			addOption(client, "Freeze");
			addOption(client, "Suicide");
		}
		else if (cur_menu[client] == "weapons") {
			addOption(client, "Default Weapon");
			addOption(client, "ACR 6.8");
			addOption(client, "UMP45");
			addOption(client, "PP90M1");
			addOption(client, "AA12");
			addOption(client, "RPG-7");
			addOption(client, "Dragonov");
			addOption(client, "Walking AC-130");
			addOption(client, "-Camos-");
		}
		else if (cur_menu[client] == "camos") {
			addOption(client, "None");
			addOption(client, "Gold");
			addOption(client, "Classic");
			addOption(client, "Snow");
			addOption(client, "Multicam");
			addOption(client, "Digital Urban");
			addOption(client, "Hex");
			addOption(client, "Choco");
			addOption(client, "Snake");
			addOption(client, "-Camos Page 2-");
		}
		else if (cur_menu[client] == "camos2") {
			addOption(client, "Red");
			addOption(client, "Blue");
			addOption(client, "Autum");
			addOption(client, "Marine");
			addOption(client, "Winter");
		}
		else if (cur_menu[client] == "models"){
			addOption(client, "Third Person");
			addOption(client, "Neutral Flag");
			addOption(client, "Trash Can");
			addOption(client, "Care Package");
			addOption(client, "SND Bomb");
			addOption(client, "Claymore");
			addOption(client, "Chicken");
			addOption(client, "Sentry Gun");
			addOption(client, "Juggernaut");
			addOption(client, "Predator");
		}
		else if (cur_menu[client] == "settings") {
			addTextScrollOption(client, "Color", menu_color[cur_menu_color]);
			addOption(client, "op2");
			addOption(client, "op3");
		}
		else if (cur_menu[client] == "cheater") {
			addOption(client, "Fair Aimbot");
			addOption(client, "Laser");
			addOption(client, "Red Boxes");
			addOption(client, "Chrome Players");
			addOption(client, "No Recoil");
			addOption(client, "Super UAV");
			addOption(client, "Explosive Bullets");
			addOption(client, "Keyboard");
		}
		else if (cur_menu[client] == "lobby") {
			addOption(client, "Super Jump");
			addOption(client, "Super Speed");
			addOption(client, "End Game");
		}
		else if (cur_menu[client] == "teleport") {
			addOption(client, "Save Position");
			addOption(client, "Teleport to Saved Pos");
		}
		else if (cur_menu[client] == "clients") {
			saveClients(client);
			for (uint i = 0; i < 18; ++i) {
				if (clients[client][i] != "Empty") {
					addOption(client, clients[client][i]);
				}
			}
		}
		else if (cur_menu[client] == clients[client][0]) {
			addOption(client, "Give Co-Host");
			addOption(client, "Give Admin");
			addOption(client, "Verify");
			addOption(client, "Remove Rights");
			addOption(client, "Kick [with message]");
		}
		else {
			addOption(client, "Option 1");
			addOption(client, "Option 2");
			addOption(client, "Option 3");
			addOption(client, "Option 4");
		}
		resetOptionColors(client);
	}

	void selectOption(const uint client, const int scroll) {
		if (cur_menu[client] == "main") {
			switch (scroll) {
			case 0: loadSub(client, "main_mods");	break;
			case 1: loadSub(client, "weapons");		break;
			case 2: loadSub(client, "models");		break;
			case 3: loadSub(client, "visions");		break;
			case 4: loadSub(client, "settings");	break;
			case 5: loadSub(client, "cheater");		break;
			case 6: loadSub(client, "lobby");		break;
			case 7: loadSub(client, "teleport");	break;
			case 8: loadSub(client, "account");		break;
			case 9: loadSub(client, "clients");		break;
			default: break;
			}
		}
		else if (cur_menu[client] == "main_mods") {
			switch (scroll) {
			case 0: Mods::godMode(client);		break;
			case 1: Mods::infiniteAmmo(client); break;
			case 2: Mods::thirdPerson(client);	break;
			case 3: Mods::setPerks(client);		break;
			case 4: Mods::UFO(client);			break;
			case 5: Mods::speedX2(client);		break;
			case 6: Mods::invisible(client);	break;
			case 7: Mods::setFOV(client);		break;
			case 8: Mods::freezeClient(client);	break;
			case 9: Mods::suicide(client);		break;
			default: break;
			}
		}
		else if (cur_menu[client] == "weapons") {
			switch (scroll) {
			case 0: Mods::giveWeapon(client, "defaultweapon_mp", "^2Default Weapon ^7Added. ^1Press [{weapnext}]", 0);	break;
			case 1: Mods::giveWeapon(client, "iw5_acr_mp", "^2ACR 8.6 ^7Added. ^1Press [{weapnext}]", 0);				break;
			case 2: Mods::giveWeapon(client, "iw5_ump45_mp", "^2UMP45 ^7Added. ^1Press [{weapnext}]", 0);				break;
			case 3: Mods::giveWeapon(client, "iw5_pp90m1_mp", "^2PP90M1 ^7Added. ^1Press [{weapnext}]", 0);				break;
			case 4: Mods::giveWeapon(client, "iw5_aa12_mp", "^2AA12 ^7Added. ^1Press [{weapnext}]", 0);					break;
			case 5: Mods::giveWeapon(client, "rpg_mp", "^2RPG7 ^7Added. ^1Press [{weapnext}]", 0);						break;
			case 6: Mods::giveWeapon(client, "iw5_dragunov_mp", "^2Dragunov ^7Added. ^1Press [{weapnext}]", 0);			break;
			case 7: Mods::walkingAC130(client);																			break;
			case 8: loadSub(client, "camos");																			break;
			default: break;
			}
		}
		else if (cur_menu[client] == "camos") {
			switch (scroll) {
			case 0: Mods::changeCamo(client, Mods::none, "Camo: ^2None. ^1Press [{weapnext}]");						break;
			case 1: Mods::changeCamo(client, Mods::Gold, "Camo: ^2Gold. ^1Press [{weapnext}]");						break;
			case 2: Mods::changeCamo(client, Mods::Classic, "Camo: ^2Classic. ^1Press [{weapnext}]");				break;
			case 3: Mods::changeCamo(client, Mods::Snow, "Camo: ^2Snow. ^1Press [{weapnext}]");						break;
			case 4: Mods::changeCamo(client, Mods::Multicam, "Camo: ^2Multicam. ^1Press [{weapnext}]");				break;
			case 5: Mods::changeCamo(client, Mods::Digital_Urban, "Camo: ^2Digital Urban. ^1Press [{weapnext}]");	break;
			case 6: Mods::changeCamo(client, Mods::Hex, "Camo: ^2Hex. ^1Press [{weapnext}]");						break;
			case 7: Mods::changeCamo(client, Mods::Choco, "Camo: ^2Choco. ^1Press [{weapnext}]");					break;
			case 8: Mods::changeCamo(client, Mods::Snake, "Camo: ^2Snake. ^1Press [{weapnext}]");					break;
			case 9: loadSub(client, "camos2");																		break;
			default: break;
			}
		}
		else if (cur_menu[client] == "camos2") {
			switch (scroll) {
			case 0: Mods::changeCamo(client, Mods::Blue, "Camo: ^2Blue. ^1Press [{weapnext}]");		break;
			case 1: Mods::changeCamo(client, Mods::Red, "Camo: ^2Red. ^1Press [{weapnext}]");		break;
			case 2: Mods::changeCamo(client, Mods::Autumn, "Camo: ^2Autumn. ^1Press [{weapnext}]"); break;
			case 3: Mods::changeCamo(client, Mods::Marine, "Camo: ^2Marine. ^1Press [{weapnext}]"); break;
			case 4: Mods::changeCamo(client, Mods::Winter, "Camo: ^2Winter. ^1Press [{weapnext}]"); break;
			default: break;
			}
		}
		else if (cur_menu[client] == "models") {
			switch (scroll) {
			case 0: iPrintln(client, "op 1"); break;
			case 1: iPrintln(client, "op 2"); break;
			case 2: iPrintln(client, "op 3"); break;
			case 3: iPrintln(client, "op 4"); break;
			default: break;
			}
		}
		else if (cur_menu[client] == "visions") {
			
		}
		else if (cur_menu[client] == "settings") {
			switch (scroll) {
			case 0: menuColor(client); break;
			default: break;
			}
		}
		else if (cur_menu[client] == "cheater") {
			switch (scroll) {
			case 0: Aimbot::aimbotTog(client);		break;
			case 1: Mods::laserToggle(client);		break;
			case 2: Mods::redBoxes(client);			break;
			case 3: Mods::chromePlayers(client);	break;
			case 4: Mods::noRecoil(client);			break;
			case 5: Mods::superUAV(client);			break;
			case 6: Mods::explosiveBullets(client); break;
			case 7: Mods::KeyBoard(client);			break;
			default: break;
			}
		}
		else if (cur_menu[client] == "lobby") {
			switch (scroll) {
			case 0: Mods::superJump(client);	break;
			case 1: Mods::superSpeed(client);	break;
			case 2: Mods::endGame();			break;
			default: break;
			}
		}
		else if (cur_menu[client] == "teleport") {
			switch (scroll) {
			case 0: Mods::savePos(client, &tele_pos[client]);		break;
			case 1: Mods::setLocation(client, &tele_pos[client]);	break;
			default: break;
			}
		}
		else if (cur_menu[client] == "clients") {
			for (uint i = 0; i < 18; ++i) {
				if (scroll == i) loadSub(client, clients[client][i]);
				iPrintln(client, clients[client][i]);
			}
		}
		else if (cur_menu[client] == clients[client][0]) {
			switch (scroll) {
			case 0: Mods::giveCoHost(0);						break;
			case 1: Mods::giveAdmin(0);							break;
			case 2: Mods::verify(0);							break;
			case 3: Mods::unverify(0);							break;
			case 4: Mods::kickClient(0, "See you");				break;
			default: break;
			}
		}
		sleep(200);
	}

	void returnMenu(const uint client) {
		if (cur_menu[client] == "main") {
			closeMenu(client);
			Selection::clearOptions(client);
			Selection::resetMenu(client);
			Selection::initOptions(client);
		}
		else if (cur_menu[client] == "camos") loadSub(client, "weapons");
		else if (cur_menu[client] == "camos2") loadSub(client, "camos");
		else if (cur_menu[client] == clients[client][0]) loadSub(client, "clients");
		else loadSub(client, "main");
		sleep(200);
	}

	void updateInt(const uint client) {
		if (cur_menu[client] == "settings" && scroll[client] == 0) {
			if (Buttons::DetectBtn(client, Buttons::Left)) {
				if (cur_menu_color <= 0) cur_menu_color = 7;
				else --cur_menu_color;
			}
			if (Buttons::DetectBtn(client, Buttons::Right)) {
				if (cur_menu_color >= 7) cur_menu_color = 0;
				else ++cur_menu_color;
			}
			Selection::loadSub(client, "settings");
			sleep(70);
		}
	}
}