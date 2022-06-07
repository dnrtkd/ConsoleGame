#pragma once

struct Vector2
{
	float x; float y;

	// ** 기본 생성자
	Vector2() {};

	// ** 복사 생성자
	Vector2(float _x, float _y)
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
	char* Texture[5];
	int Color;
	int Option;
};

struct Object
{
	int Speed;

	Information Info;
	Trasnsform TransInfo;
};

struct Effect
{
	int time;
	Object obj;
};

struct Enemy
{
	Object obj;
	int time;
	int hitTime;
	int hp;
	int delay;
};

struct Player
{
	char* name;
	Object obj;
	int chance;
	int damage;
	int delay;
	int level;
};



struct DrawTextInfo
{
	Information Info;
	Trasnsform TransInfo;
};

enum Scene
{
	Title = 0,
	//nu = 1,
	Stage1 = 1,
	Stage2= 2,
	GameClear = 3
};


struct Bullet
{
	Object obj;
	int tagetIndex;
};

typedef Object Item;

struct LageText
{
	char* texture[5][5];
	long time; // 텍스트가 사라질 시간을 카운트
	int color;
};