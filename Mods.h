#pragma once

namespace Mods
{
	void godMode(const uint client) {
		gm[client] = !gm[client];
		*(char*)(0x0FCA41E + (0x280 * client)) = gm[client] ? 0xFF : 0x00;
		iPrintln(client, gm[client] ? const_cast<char*>("God Mode: ^5On") : const_cast<char*>("God Mode: ^1Off"));
		sleep(100);
	}
	void infiniteAmmo(const uint client) {
		ammo[client] = !ammo[client];
		unsigned int addresses[6] = { 0x0110a6a8, 0x0110a628, 0x0110a690, 0x0110a618, 0x0110a69c, 0x0110a6b4 };
		for (uint i = 0; i < 6; ++i) {
			*(char*)addresses[i] = ammo[client] ? 0x01 : 0x00;
		}
		iPrintln(client, ammo[client] ? const_cast<char*>("Infinite Ammo: ^5On") : const_cast<char*>("Infinite Ammo: ^1Off"));
	}
	void setThird(const uint client, int type)
	{
		char buf[100];
		Com_sprintf(buf, sizeof(buf), "q cg_thirdperson %i", type);
		svgssc(client, 0, buf);
	}
	void thirdPerson(const uint client)
	{
		thp[client] = !thp[client];
		setThird(client, thp[client] ? 1 : 0);
		iPrintln(client, thp[client] ? const_cast<char*>("Third Person : ^5On") : const_cast<char*>("Third Person : ^1Off"));
		sleep(100);
	}
	void UFO(const uint client)
	{
		ufo[client] = !ufo[client];
		*(char*)(0x0110d87f + (0x3980 * client)) = ufo[client] ? 0x02 : 0x00;
		iPrintln(client, ufo[client] ? const_cast<char*>("UFO Mode : ^5On") : const_cast<char*>("UFO Mode : ^1Off"));
		sleep(100);
	}
	void speedX2(const uint client)
	{
		speed[client] = !speed[client];
		*(char*)(0x110D641 + (0x3980 * client)) = speed[client] ? 0xFF : 0x80;
		iPrintln(client, speed[client] ? const_cast<char*>("Speed X2 : ^5On") : const_cast<char*>("Speed X2 : ^1Off"));
		sleep(100);
	}
	void invisible(const uint client)
	{
		invis[client] = !invis[client];
		*(char*)(0x110D653 + (0x3980 * client)) = invis[client] ? 0x02 : 0x00;
		iPrintln(client, invis[client] ? const_cast<char*>("Invisibility : ^5On") : const_cast<char*>("Invisibility : ^1Off"));
		sleep(100);
	}
	void freezeClient(const uint client)
	{
		freeze[client] = !freeze[client];
		*(char*)(0x0110d87f + (0x3980 * client)) = freeze[client] ? 0x07 : 0x00;
		iPrintln(client, freeze[client] ? const_cast<char*>("^1Frozen") : const_cast<char*>("^5Unfrozen"));
		sleep(100);
	}
	void suicide(const uint client)
	{
		if (!sui[client]) {
			*(char*)(0xFCA381 + (0x280 * client)) = 0x01;
			iPrintln(client, "^1Suicide");
			sui[client] = true;
			sleep(200);
			*(char*)(0xFCA381 + (0x280 * client)) = 0x00;
			sui[client] = false;
		}
		else iPrintln(client, "^1Error");
	}
	void setPerks(const uint client) {
		sap[client] = !sap[client];
		iPrintln(client, sap[client] ? const_cast<char*>("Perks : ^5All") : const_cast<char*>("Perks : ^5Normal"));
	}
	void SAP(const uint client)
	{
		if (sap[client]) {
			perks[client] = *(char*)(0x110A76D + (0x3980 * client));
			sleep(10);
			char bytes[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };
			PS3::write_process(0x110A76D + (0x3980 * client), &bytes, sizeof(bytes));
		}
		else {
			*(char*)(0x110A76D + (0x3980 * client)) = perks[client];
		}
		sleep(100);
	}
	void perksThread(uint64_t arg) {
		sleep(10000);
		for (;;) {
			for (uint i = 0; i < 18; ++i) {
				SAP(i);
			}
		}
	}
	void setFOV(const uint client) {
		char buf[30];
		Com_sprintf(buf, 30, "FOV Set to: ^5%i", fov_array[client][next[client]]);
		iPrintln(client, buf);
		FOV(client, fov_array[client][next[client] = (next[client] == 3) ? 0 : next[client] + 1]);
		// Com_sprintf(buf, 30, "FOV Set to: ^5%i", fov_array[client][(next[client] == 0) ? 3 : next[client] - 1]);
		sleep(200);
	}

#pragma region weapons

	int BG_GetViewmodelWeaponIndex(int clientIndex) {
		return *(int*)(G_Client(clientIndex) + 0x370);
	}
	void takeWeapon(int clientIndex, int WeaponIndex, int takeAwayAmmo) {
		BG_TakePlayerWeapon((int*)G_Client(clientIndex), WeaponIndex, takeAwayAmmo);
	}
	int BG_FindWeaponIndexForName(const char* Weapon) {
		ReturnIndex(0x1100000, Weapon);
		return *(int*)0x1100000;
	}
	void giveWeapon(int clientIndex, const char* Weapon, char* Msg, int _index = -1, int Akimbo = 0) {
		int index = _index ? _index : BG_FindWeaponIndexForName(Weapon);
		G_GivePlayerWeapon((int*)G_Client(clientIndex), index, Akimbo);
		Add_Ammo((int*)G_Entity(clientIndex), index, 0, 9999, 1);
		iPrintln(clientIndex, Msg);
		sleep(200);
	}
	enum Camo {
		none,
		Classic,
		Snow,
		Multicam,
		Digital_Urban,
		Hex,
		Choco,
		Snake,
		Blue,
		Red,
		Autumn,
		Gold,
		Marine,
		Winter
	};
	void changeCamo(int clientIndex, Camo camo, char* Msg)  {
		int Index = BG_GetViewmodelWeaponIndex(clientIndex);
		takeWeapon(clientIndex, Index, 0);
		int CalcIndex = 0 | ((Index >> 12 & 15) << 12) | ((Index >> 16) << 16) | Index & 0xFF;
		giveWeapon(clientIndex, "", "", CalcIndex + (camo << 8));
		iPrintln(clientIndex, Msg);
		sleep(200);
	}
	void WriteMemory_char(int Address, int range, unsigned char Offset) {
		*(unsigned char*)(Address + range) = Offset;
	}
	void walkingAC130(const uint client) {
		unsigned char Offset[3] = { 0x00, 0x00, 0x69 };
		for (int i = 0; i < 3; ++i) {
			WriteMemory_char(0x110A4FD + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110A5F1 + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110A625 + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110A62D + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110A6A5 + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110D5C5 + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110D5F1 + (0x3980 * client), i, Offset[i]);
			WriteMemory_char(0x110D9D5 + (0x3980 * client), i, Offset[i]);
		}
		iPrintln(client, "^5AC130");
		sleep(200);
	}

#pragma endregion

	void laserToggle(const uint client) {
		laser[client] = !laser[client];
		*(char*)(0x000b6703 + (0x3980 * client)) = laser[client] ? 0x01 : 0x00;
		iPrintln(client, laser[client] ? const_cast<char*>("Laser: ^5On") : const_cast<char*>("Laser: ^1Off"));
	}
	void redBoxes(const uint client) {
		boxes[client] = !boxes[client];
		*(char*)(0x0110a293 + (0x3980 * client)) = boxes[client] ? 0x50 : 0x00;
		iPrintln(client, boxes[client] ? const_cast<char*>("Red Boxes: ^5On") : const_cast<char*>("Red Boxes: ^1Off"));
	}
	void chromePlayers(const uint client) {
		chrome[client] = !chrome[client];
		unsigned char on[2] = { 0x05, 0x70 };
		unsigned char off[2] = { 0x05, 0x6A };
		*(char*)(0x3984DF + (0x3980 * client)) = chrome[client] ? 0x01 : 0x00;
		PS3::write_process(0x3984F2 + (0x3980 * client), chrome[client] ? &on : &off, sizeof(on));
		iPrintln(client, chrome[client] ? const_cast<char*>("Chrome Players: ^5On") : const_cast<char*>("Chrome Players: ^1Off"));
	}
	void noRecoil(const uint client) {
		recoil[client] = !recoil[client];
		*(char*)(0x0110a5f6 + (0x3980 * client)) = recoil[client] ? 0x04 : 0x00;
		iPrintln(client, recoil[client] ? const_cast<char*>("No Recoil: ^5On") : const_cast<char*>("No Recoil: ^1Off"));
	}
	void setRadar(const uint client, int on) {
		char buf[100];
		Com_sprintf(buf, 100, "q g_compassshowenemies %i", on);
		svgssc(client, 0, buf);
	}
	void superUAV(const uint client) {
		uav[client] = !uav[client];
		setRadar(client, static_cast<int>(uav[client]));
		iPrintln(client, uav[client] ? const_cast<char*>("Super UAV: ^5On") : const_cast<char*>("Super UAV: ^1Off"));
	}
	void explosiveBullets(const uint client) {
		bullets[client] = !bullets[client];
		unsigned char on[2] = { 0xC5, 0xFF };
		unsigned char off[2] = { 0x00, 0x00 };
		PS3::write_process(0x0110A773 + (0x3980 * client), bullets[client] ? &on : &off, sizeof(on));
		iPrintln(client, bullets[client] ? const_cast<char*>("Explosive Bullets: ^5On") : const_cast<char*>("Explosive Bullets: ^1Off"));
	}
	
	void superJump(const uint client) {
		jump[client] = !jump[client];
		unsigned char on[3] = { 0x44, 0xf9, 0xc0 };
		unsigned char off[3] = { 0x42, 0x9c, 0x00 };
		PS3::write_process(0x000019780 + (0x3980 * client), jump[client] ? &on : &off, sizeof(on));
		iPrintln(client, jump[client] ? const_cast<char*>("Super Jump: ^5On") : const_cast<char*>("Super Jump: ^1Off"));
		sleep(100);
	}
	void superSpeed(const uint client) {
		super_speed[client] = !super_speed[client];
		unsigned char on[4] = { 0x38, 0xa0, 0x07, 0xd0 };
		unsigned char off[4] = { 0x38, 0xa0, 0x00, 0xbe };
		PS3::write_process(0x000173bb0 + (0x3980 * client), super_speed[client] ? &on : &off, sizeof(on));
		iPrintln(client, super_speed[client] ? const_cast<char*>("Super Speed: ^5On") : const_cast<char*>("Super Speed: ^1Off"));
	}
	void endGame() {
		char buffer[0x100];
		sprintf(buffer, "cmd mr %i %i %s", *(int*)(0x832524), -1, "endround");
		Cbuf_AddText(0, buffer);
	}
	/*
	void KeyBoard(const uint client, char* Title) {
		Keyboard(0, Title, "", 40, 0x72DCE8, 0x7239A0);
		while (*(int*)0x73145C != 0) {
			continue;
		}
		iPrintln(client, readString(0x2380E22));
	}*/
	char* KeyBoard1(char* Title = "Hah, gay!!!") {
		opd_s key = { 0x026F5BC, TOC };
		void(*Run)(int, char*, char*, int, int, int) = (void(*)(int, char*, char*, int, int, int))&key;
		Run(0, Title, "", 40, 0x72DCE8, 0x7239A0);
		while (readInt(0x73145C, 4) != 0) {
			continue;
		}
		return readString(0x2380E22);
	}
	void KeyBoard(const uint client) {
		iPrintln(client, KeyBoard1());
	}

	float* getOrigin(const uint client) {
		readFloat(0x0110A29C + (0x3980 * client), 3);
	}
	void setLocation(const uint client, float** location) {
		writeFloat(0x0110A29C + (0x3980 * client), *location, 3);
		char buf[30];
		Com_sprintf(buf, 30, "^5Teleported to: %i %i %i", (int)location[client][0], (int)location[client][1], (int)location[client][2]);
		iPrintln(client, buf);
		sleep(100);
	}
	void savePos(const uint client, const float** savedPos) {
		*savedPos = getOrigin(client);
		iPrintln(client, "^5Position Saved");
		sleep(100);
	}

	void giveCoHost(const uint client) {
		status[client] = cohost;
		iPrintln(client, "Status: Co-Host");
	}
	void giveAdmin(const uint client) {
		status[client] = admin;
		iPrintln(client, "Status: Admin");
	}
	void verify(const uint client) {
		status[client] = verified;
		iPrintln(client, "Status: Verified");
	}
	void unverify(const uint client) {
		status[client] = nostatus;
		iPrintln(client, "Status: None");
	}
	void kickClient(const uint client, const char* msg) {
		kickwmessage(client, msg);
	}
}