#pragma once
#include <math.h>

namespace Aimbot
{
	bool isDead(const uint client) {
		return *(bool*)(G_Client(client) + 0x3313);
	}

	bool checkTeam(int Client, int OtherClient) {
		int attacker = *(int*)(G_Client(Client) + 0x33D7);
		int victim = *(int*)(G_Client(OtherClient) + 0x33D7);
		return (attacker == victim);
	}

	bool checkIfLiving(const uint client) {
		return (*(char*)(G_Entity(client) + 0x19F) != 0);
	}

	bool clientIsInGame(const uint client) {
		return (*(int*)G_Client(client) != 0);
	}

	struct Vec3 {
		float x, y, z;
	};

	Vec3 difference;
	Vec3 getVec(Vec3 Attacker, Vec3 Target) {
		difference.x = (Target.x - Attacker.x);
		difference.y = (Target.y - Attacker.y);
		difference.z = (Target.z - Attacker.z);
		return difference;
	}

	float dx, dy, dz;
	float get3dDistance(Vec3 c1, Vec3 c2) {
		float dx = c2.x - c1.x;
		float dy = c2.y - c1.y;
		float dz = c2.z - c1.z;

		return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
	}

	Vec3 vec;
	Vec3 getPlayerOrigin(const uint client) {
		return *(Vec3*)(G_Client(client) + 0x1C);
	}

	Vec3 vecV;
	Vec3 getPlayerOriginVictim(const uint client) {
		vecV = *(Vec3*)(G_Client(client) + 0x1C);
		vecV.z -= 24;
		return vecV;
	}

	int nearest;
	int GetNearestPlayer(const uint client) {
		float MaxDistance = 99999999;
		for (int i = 0; i < 12; i++)
		{
			Vec3 Attacker = getPlayerOrigin(client);
			Vec3 Vic = getPlayerOrigin(i);
			float ActualDistance = get3dDistance(Attacker, Vic);
			if ((i != client) && checkIfLiving(i) && clientIsInGame(i)) {
				if (PS3::cstrcmp(Dvar_GetString("ui_gametype"), "dm") == 0) {
					if (ActualDistance < MaxDistance) {
						nearest = i;
						MaxDistance = ActualDistance;
					}
				}
				else {
					if (!checkTeam(client, i)) {
						if (ActualDistance < MaxDistance) {
							nearest = i;
							MaxDistance = ActualDistance;
						}
					}
				}
			}
		}
		return nearest;
	}

	float angles[3];
	float* vectoangles(Vec3 Angles) {
		float forward;
		float yaw, pitch;
		float PI = 3.1415926535897931;
		if (Angles.x == 0 && Angles.y == 0) {
			yaw = 0;
			if (Angles.z > 0) pitch = 90.00;
			else pitch = 270.00;
		}
		else
		{
			if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
			else if (Angles.y > 0) yaw = 90.00;
			else yaw = 270;
			if (yaw < 0) yaw += 360.00;

			forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
			pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
			if (pitch < 0) pitch += 360.00;
		}
		angles[0] = -pitch;
		angles[1] = yaw;
		angles[2] = 0;

		return angles;
	}

	void setViewAngles(const uint client) {
		int Victim = GetNearestPlayer(client);
		float* Angles = vectoangles(getVec(getPlayerOrigin(client), getPlayerOriginVictim(Victim)));
		SetClientViewAnlges(G_Entity(client), Angles);
	}

	void aimbotTog(const uint client) {
		aimbot_bool[client] = !aimbot_bool[client];
		iPrintln(client, aimbot_bool[client] ? const_cast<char*>("Aimbot ^2Enabled") : const_cast<char*>("Aimbot ^2Disabled"));
		// iPrintln(client, "^1Notice^7: Turn aimbot off befor the game ends!");
	}
	void aimbotR1(const uint client) {
		aimbot_bool[client] = !aimbot_bool[client];
		iPrintln(client, aimbot_bool[client] ? const_cast<char*>("Aimbot ^1Unnecessary") : const_cast<char*>("Aimbot ^2Required"));
	}
	void aimbotThread(uint64_t arg) {
		sleep(10000);
		for (;;) {
			for (uint i = 0; i < 18; ++i) {
				if (aimbot_bool[i]) {
					if (Buttons::DetectBtn(i, Buttons::L1)) {
						setViewAngles(i);
					}
				}
				else {
					sleep(200);
				}
			}
		}
	}
};