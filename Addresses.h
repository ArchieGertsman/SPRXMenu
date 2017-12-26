#pragma once

namespace Buttons
{
	enum Buttons
	{
		Up = 0x3135,
		Down = 0x3137,
		Left = 0x3139,
		Right = 0x3231,
		X = 0x3235,
		Square = 0x3131,
		Triangle = 0x3430,
		L1 = 0x3133,
		L2 = 0x3700,
		L3 = 0x3900,
		R1 = 0x3100,
		R2 = 0x3500,
		R3 = 0x3237
	};
	bool DetectBtn(int clientIndex, Buttons Btn)
	{
		return *(short*)(*(int*)0x017BB210 + (clientIndex * 0x68B80) + 0x21022) == Btn;
	}
}