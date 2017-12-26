#pragma once

namespace {
opd_s Dvar_GetString_t  = { 0x002911A8, TOC };
opd_s SetClientViewAnlges_t = { 0x001767E0, TOC };
opd_s G_GivePlayerWeapon_t = { 0x001C3034, TOC };
opd_s Add_Ammo_t = { 0x0018A29C, TOC };
opd_s BG_TakePlayerWeapon_t = { 0x001C409C, TOC };
opd_s ReturnIndex_t = { 0x3CFD0, TOC };
opd_s LocalizedStringIndex_t = { 0x001BE6CC, TOC };
opd_s GetMaterialIndex_t = { 0x001BE744, TOC };
opd_s HudelemDestroyAll_t = { 0x001872E8, TOC };
opd_s Cbuf_AddText_t = { 0x1DB240, TOC };
opd_s player_die_t = { 0x183748, TOC };
opd_s Com_sprintf_t = { 0x00298874, TOC };
opd_s SV = { 0x228FA8, TOC };
opd_s Keyboard_t = { 0x026F5BC, TOC };
opd_s kick = { 0x00223BD0, TOC };

const char*(*Dvar_GetString)(const char* Dvar) = (const char*(*)(const char*))&Dvar_GetString_t;
void(*SetClientViewAnlges)(int Ent, float* Angles) = (void(*)(int, float*))&SetClientViewAnlges_t;
void(*G_GivePlayerWeapon)(int* G_Client, int iWeaponIndex, char altModelIndex) = (void(*)(int*, int, char))&G_GivePlayerWeapon_t;
void(*Add_Ammo)(int* G_Entity, unsigned int weaponIndex, char weaponModel, int count, int fillClip) = (void(*)(int*, unsigned int, char, int, int))&Add_Ammo_t;
void(*BG_TakePlayerWeapon)(int *playerState, int WeaponIndex, int takeAwayAmmo) = (void(*)(int*, int, int))&BG_TakePlayerWeapon_t;
void(*ReturnIndex)(int buffer, const char* Weapon) = (void(*)(int, const char*))&ReturnIndex_t;
int(*LocalizedStringIndex)(const char* Text) = (int(*)(const char*))&LocalizedStringIndex_t;
int(*GetMaterialIndex)(const char* Material) = (int(*)(const char*))&GetMaterialIndex_t;
void(*HudelemDestroyAll)() = (void(*)())&HudelemDestroyAll_t;
void(*Cbuf_AddText)(int localClientNum, const char *text) = (void(*)(int, const char*))&Cbuf_AddText_t;
void(*Keyboard)(int, char*, char*, int, int, int) = (void(*)(int, char*, char*, int, int, int))&Keyboard_t;
int(*Com_sprintf)(char *dest, int size, const char *fmt, ...) = (int(*)(char*, int, char const *, ...))&Com_sprintf_t;
void(*svgssc)(int client, int type, char* cmd) = (void(*)(int, int, char*))&SV;
int(*kickwmessage)(int client, const char* message) = (int(*)(int, const char*))&kick;
// void(*player_die)(gentity_s *self, gentity_s *inflictor, gentity_s *attacker, int damage, int meansOfDeath, int iWeapon, const float *vDir, hitLocation_t hitLoc, int psTimeOffset) = (void(*)(gentity_s*, gentity_s*, gentity_s*, int, int, int, const float*, hitLocation_t, int))&player_die_t;

#define G_Client(client) (0x0110A280 + (client * 0x3980))
#define G_Entity(client) (0x00FCA280 + (client * 0x280))

bool isDead(int client) {
	return *(bool*)(G_Client(client) + 0x3313);
}

bool inGame() {
	return !(*(char*)0x018d4c64 != 1);
}

void iPrintln(const uint client, char* text) {
	char buf[100];
	Com_sprintf(buf, 100, "f \"%s%s", text, "\"");
	svgssc(client, 0, buf);
}

void iPrintlnBold(const uint client, char* text) {
	char buf[100];
	Com_sprintf(buf, 100, "c \"%s%s", text, "\"");
	svgssc(client, 0, buf);
}

void setVision(const uint client, char* Vision) {
	char buf[100];
	Com_sprintf(buf, 100, "J \"%s%s", Vision, "\"");
	svgssc(client, 0, buf);
}

void FOV(const uint client, int fov)
{
	char buf[100];
	Com_sprintf(buf, 100, "q cg_fov %i", fov);
	svgssc(client, 0, buf);
}

void setDvar(const uint client, char* Dvar)
{
	char buf[100];
	Com_sprintf(buf, 100, "f \"%s%s", Dvar, "\"");
	svgssc(client, 0, buf);
}

char** getPlayerNames() {
	char* name[18];
	for (int i = 0; i < 18; i++) {
		name[i] = (!PS3::cstrcmp(readString(0x110d60c + (0x3980 * i)), "")) ? (char*)"Empty" : readString(0x110d60c + (0x3980 * i));
	}
	return name;
}
uint getHostNumber() {
	char* host = readString(0x1BBBC2C);
	uint num = 0;
	for (int i = 0; i < 18; i++) {
		if (!PS3::cstrcmp(readString(0x110d60c + (0x3980 * i)), host)) {
			num = i;
		}
	}
	return num;
}
uint getClientNumber(const uint client) {
	uint num = 0;
	for (uint i = 0; i < 18; ++i) {
		if (client == i) {
			num = i;
		}
	}
	return num;
}
bool isHost(const uint client) {
	return (getClientNumber(client) == getHostNumber());
}
void saveClients(const uint client) {
	for (uint i = 0; i < 18; ++i) {
		clients[client][i] = getPlayerNames()[i];
	}
}

const char* gameMode() {
	return Dvar_GetString("ui_gamemode");
}
const char* mapName() {
	return Dvar_GetString("ui_mapname");
}
const char* hostName() {
	return Dvar_GetString("sv_hostname");
}

}