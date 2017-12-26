#pragma once

namespace
{
game_hudelem_s* Hudelem_Alloc() {
	for (int i = 0; i < 1024; i++) {
		game_hudelem_s* elem = (game_hudelem_s*)(0x00F0E10C + (i * 0xB4));
		if (!elem->elem.type) return elem;
	}
	return (game_hudelem_s*)-1;
}

int G_LocalizedStringIndex(const char* Text) {
	return LocalizedStringIndex(Text);
}

int getLevelTime() {
	return *(int*)0xFC3DB0;
}

void changeColor(game_hudelem_s* elem, color_s color) {
	elem->elem.color.r = color.r;
	elem->elem.color.g = color.g;
	elem->elem.color.b = color.b;
}

void changeGlowColor(game_hudelem_s* elem, color_s color) {
	elem->elem.glowColor.r = color.r;
	elem->elem.glowColor.g = color.g;
	elem->elem.glowColor.b = color.b;
}

void changeTransparency(game_hudelem_s* elem, int a) {
	elem->elem.color.a = a;
}

void changeGlowTransparency(game_hudelem_s* elem, int a) {
	elem->elem.glowColor.a = a;
}

void setShader(game_hudelem_s** elem, int clientIndex, int Width, int Height, float X, float Y, color_s color)
{
	*elem = Hudelem_Alloc();
	(*elem)->clientNum = clientIndex;
	(*elem)->elem.type = 4;
	*(int*)0x00F3B198 = 1;
	(*elem)->elem.materialIndex = 1;
	*(int*)0x00F3B198 = 0;
	(*elem)->elem.Width = Width;
	(*elem)->elem.Height = Height;
	(*elem)->elem.X = X;
	(*elem)->elem.Y = Y;
	(*elem)->elem.alignOrg = 0;
	(*elem)->elem.color = color;
}

void setText(game_hudelem_s** elem, int clientIndex, const char* Text, int Font, float FontScale, float X, float Y, int Allign, color_s color, color_s glow) {
	*elem = Hudelem_Alloc();
	(*elem)->clientNum = clientIndex;
	(*elem)->elem.type = 1;
	(*elem)->elem.text = G_LocalizedStringIndex(Text);
	(*elem)->elem.font = Font;
	(*elem)->elem.fontScale = FontScale;
	if (Allign != 0) {
		(*elem)->elem.alignOrg = 5;
		(*elem)->elem.alignScreen = Allign; 
		(*elem)->elem.X = X; 
		(*elem)->elem.Y = Y;
	}
	else {
		(*elem)->elem.X = X; 
		(*elem)->elem.Y = Y;
	}
	(*elem)->elem.color = color;
	(*elem)->elem.glowColor = glow;
}

void changeText(game_hudelem_s* elem, const char* Text) {
	elem->elem.text = G_LocalizedStringIndex(Text);
}

void moveOverTime(game_hudelem_s* elem, short time, float X, float Y) {
	elem->elem.fromX = elem->elem.X;
	elem->elem.fromY = elem->elem.Y;
	elem->elem.moveStartTime = getLevelTime();
	elem->elem.moveTime = time;
	elem->elem.X = X;
	elem->elem.Y = Y;
}

void moveShaderXY(game_hudelem_s* elem, float X, float Y) {
	elem->elem.X = X;
	elem->elem.Y = Y;
}

void scaleOverTime(game_hudelem_s* elem, short time, short width, short height) {
	elem->elem.fromHeight = elem->elem.Height;
	elem->elem.fromWidth = elem->elem.Width;
	elem->elem.scaleStartTime = getLevelTime();
	elem->elem.scaleTime = time;
	elem->elem.Width = width;
	elem->elem.Height = height;
}

void fontScaleOverTime(game_hudelem_s* elem, float FontSize, short time) {
	elem->elem.fromFontScale = elem->elem.fontScale;
	elem->elem.fontScaleStartTime = getLevelTime();
	elem->elem.fontScaleTime = time;
	elem->elem.fontScale = FontSize;
}

void fontScale(game_hudelem_s* elem, float FontSize) {
	elem->elem.fromFontScale = elem->elem.fontScale;
	elem->elem.fontScale = FontSize;
}

void setGlow(game_hudelem_s* Text, int GlowR, int GlowG, int GlowB, int GlowA) {
	Text->elem.glowColor.r = GlowR;
	Text->elem.glowColor.g = GlowG;
	Text->elem.glowColor.b = GlowB;
	Text->elem.glowColor.a = GlowA;
}

void fadeOverTime(game_hudelem_s* elem, int Time, float a) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.color.a = a;
	elem->elem.fadeTime = Time;
	elem->elem.fadeStartTime = getLevelTime();
}

void fadeOverTime1(game_hudelem_s* elem, int Time, float a) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.glowColor.a = a;
	elem->elem.fadeTime = Time;
	elem->elem.fadeStartTime = getLevelTime();
}

void fadeOverTimeColor(game_hudelem_s* elem, int Time, color_s color) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.color.r = color.r;
	elem->elem.color.g = color.g;
	elem->elem.color.b = color.b;
	elem->elem.fadeTime = Time;
	elem->elem.fadeStartTime = getLevelTime();
}

void fadeOverTimeGlow(game_hudelem_s* elem, int Time, float r, float g, float b) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.glowColor.r = r;
	elem->elem.glowColor.g = g;
	elem->elem.glowColor.b = b;
	elem->elem.fadeTime = Time;
	elem->elem.fadeStartTime = getLevelTime();
}
}

/*
enum TypewriterTextTypes
{
Normal = 0x800,
Classic = 0x4000
};

game_hudelem_s* typewriter;
bool typran;

void SetTypewriter(int clientIndex, char* Text, int IconType, int Font, float FontSize, float X, float Y, char align, int WriteType = Normal, short Lettertime = 200, short fxDecayStartTime = 7000, short fxDecayDuration = 1000, char R = 255, char G = 255, char B = 255, char A = 255, char GlowR = 255, char GlowG = 255, char GlowB = 255, char GlowA = 0)
{
if (!typran)
{
game_hudelem_s* elem = setText(clientIndex, Text, Font, FontSize, X, Y, align, R, G, B, A, GlowR, GlowG, GlowB, GlowA);
elem->elem.flags = WriteType;
elem->elem.fxBirthTime = getLevelTime();
elem->elem.fxLetterTime = Lettertime;
elem->elem.fxDecayStartTime = fxDecayStartTime;
elem->elem.fxDecayDuration = fxDecayDuration;
typewriter = elem;
typran = true;
}
else
{
game_hudelem_s* elem = typewriter;
elem->clientNum = clientIndex;
elem->elem.type = 1;
elem->elem.text = G_LocalizedStringIndex(Text);
elem->elem.font = Font;
elem->elem.fontScale = FontSize;
if (align != 0)
{
elem->elem.alignOrg = 5; elem->elem.alignScreen = align; elem->elem.X = X; elem->elem.Y = Y;
}
else
{
elem->elem.X = X; elem->elem.Y = Y;
}
elem->elem.color.r = R;
elem->elem.color.g = G;
elem->elem.color.b = B;
elem->elem.color.a = A;
elem->elem.glowColor.r = GlowR;
elem->elem.glowColor.g = GlowG;
elem->elem.glowColor.b = GlowB;
elem->elem.glowColor.a = GlowA;
elem->elem.flags = WriteType;
elem->elem.fxBirthTime = getLevelTime();
elem->elem.fxLetterTime = Lettertime;
elem->elem.fxDecayStartTime = fxDecayStartTime;
elem->elem.fxDecayDuration = fxDecayDuration;
}
}

game_hudelem_s* typewriter1;
bool Message;

void SetMessage(int clientIndex, char* Text, char* Text2, int WriteType = Normal, short Lettertime = 200, short fxDecayStartTime = 7000, short fxDecayDuration = 1000, char R = 255, char G = 255, char B = 255, char A = 255, char GlowR = 255, char GlowG = 255, char GlowB = 255, char GlowA = 0)
{
if (!Message)
{
game_hudelem_s* elem1 = setText(clientIndex, Text, 3, 1.5, 325, 130, 1, R, G, B, A, GlowR, GlowG, GlowB, GlowA);
elem1->elem.flags = WriteType;
elem1->elem.fxBirthTime = getLevelTime();
elem1->elem.fxLetterTime = Lettertime;
elem1->elem.fxDecayStartTime = fxDecayStartTime;
elem1->elem.fxDecayDuration = fxDecayDuration;
typewriter = elem1;
game_hudelem_s* elem = setText(clientIndex, Text2, 3, 1.5, 325, 150, 1, R, G, B, A, GlowR, GlowG, GlowB, GlowA);
elem->elem.flags = WriteType;
elem->elem.fxBirthTime = getLevelTime();
elem->elem.fxLetterTime = Lettertime;
elem->elem.fxDecayStartTime = fxDecayStartTime;
elem->elem.fxDecayDuration = fxDecayDuration;
typewriter1 = elem;
Message = true;
typran = true;
}
else
{
game_hudelem_s* elem1 = typewriter;
elem1->clientNum = clientIndex;
elem1->elem.type = 1;
elem1->elem.text = G_LocalizedStringIndex(Text);
elem1->elem.font = 3;
elem1->elem.fontScale = 1.5;
elem1->elem.alignOrg = 5; elem1->elem.alignScreen = 1; elem1->elem.X = 325; elem1->elem.Y = 130;
elem1->elem.color.r = R;
elem1->elem.color.g = G;
elem1->elem.color.b = B;
elem1->elem.color.a = A;
elem1->elem.glowColor.r = GlowR;
elem1->elem.glowColor.g = GlowG;
elem1->elem.glowColor.b = GlowB;
elem1->elem.glowColor.a = GlowA;
elem1->elem.flags = WriteType;
elem1->elem.fxBirthTime = getLevelTime();
elem1->elem.fxLetterTime = Lettertime;
elem1->elem.fxDecayStartTime = fxDecayStartTime;
elem1->elem.fxDecayDuration = fxDecayDuration;
game_hudelem_s* elem = typewriter1;
elem->clientNum = clientIndex;
elem->elem.type = 1;
elem->elem.text = G_LocalizedStringIndex(Text2);
elem->elem.font = 3;
elem->elem.fontScale = 1.5;
elem->elem.alignOrg = 5; elem->elem.alignScreen = 1; elem->elem.X = 325; elem->elem.Y = 150;
elem->elem.color.r = R;
elem->elem.color.g = G;
elem->elem.color.b = B;
elem->elem.color.a = A;
elem->elem.glowColor.r = GlowR;
elem->elem.glowColor.g = GlowG;
elem->elem.glowColor.b = GlowB;
elem->elem.glowColor.a = GlowA;
elem->elem.flags = WriteType;
elem->elem.fxBirthTime = getLevelTime();
elem->elem.fxLetterTime = Lettertime;
elem->elem.fxDecayStartTime = fxDecayStartTime;
elem->elem.fxDecayDuration = fxDecayDuration;
}
}
*/

