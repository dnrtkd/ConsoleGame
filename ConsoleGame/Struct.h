#pragma once

struct Vector2
{
	int x = 0, y = 0;

	// ** �⺻ ������
	Vector2() {};

	// ** ���� ������
	Vector2(int _x, int _y)
		: x(_x), y(_y){ };

};

struct Trasnsform
{
	Vector2 Position;
	Vector2 Rotation;
	Vector2 Scale;
};

struct Information
{
	char* Texture;
	int Color;
	int Option;
};

struct Object
{
	char* Name;
	int Speed;

	Information Info;
	Trasnsform TransInfo;
};


struct DrawTextInfo
{
	Information Info;
	Trasnsform TransInfo;
};

enum Scene
{
	Title = 0,
	Menu = 1,
	Battle = 2,
	GameClear = 3
};