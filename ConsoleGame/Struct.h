#pragma once
#include <string.h>
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
	float Speed;

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

	int timer;
	int delay;  //총알 연사 속도

	int count; //한 차례에 쏠 총알 개수

	int hp;

	double lateTimer;
	double lateTime; //한 번 총알 쏘고난후 지체시간
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

struct LargeText
{
	char* texture[5];
	long timer; // 텍스트가 사라질 시간을 카운트
	int color;
};

struct Event //개수 , 시간 ,이벤트 사용여부
{
	int count;
	int max;
	int time;
	bool use;

	Event() {};
	Event(int _max) { max = _max; count = 0; time = GetTickCount(); use = false; }
};


