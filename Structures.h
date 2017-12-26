#pragma once

namespace
{
	union color_s
	{
		struct
		{
			int8_t r;
			int8_t g;
			int8_t b;
			int8_t a;
		};
		int32_t rgba;
	};

	struct hudelem_s
	{
		int type;
		float X;
		float Y;
		float Z;
		int targetEntNum;
		float fontScale;
		float fromFontScale;
		int fontScaleStartTime;
		int fontScaleTime;
		int font;
		int alignOrg;
		int alignScreen;
		color_s color;
		color_s fromColor;
		int fadeStartTime;
		int fadeTime;
		int label;
		int Width;
		int Height;
		int materialIndex;
		int fromWidth;
		int fromHeight;
		int scaleStartTime;
		int scaleTime;
		float fromX;
		float fromY;
		int fromAlignOrg;
		int fromAlignScreen;
		int moveStartTime;
		int moveTime;
		int time;
		int duration;
		float value;
		int text;
		float sort;
		color_s glowColor;
		int fxBirthTime;
		int fxLetterTime;
		int fxDecayStartTime;
		int fxDecayDuration;
		int soundID;
		int flags;
	};

	struct game_hudelem_s
	{
		hudelem_s elem;
		int clientNum;
		int team;
		int archived;
	};
}