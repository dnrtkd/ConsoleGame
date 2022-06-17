#pragma once
#include <string.h>
 struct Vector2
{
	float x; float y;

	// ** �⺻ ������
	Vector2() {};

	// ** ���� ������
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
	int delay;  //�Ѿ� ���� �ӵ�

	int count; //�� ���ʿ� �� �Ѿ� ����

	int hp;

	double lateTimer;
	double lateTime; //�� �� �Ѿ� ����� ��ü�ð�
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
	long timer; // �ؽ�Ʈ�� ����� �ð��� ī��Ʈ
	int color;
};

struct Event //���� , �ð� ,�̺�Ʈ ��뿩��
{
	int count;
	int max;
	int time;
	bool use;

	Event() {};
	Event(int _max) { max = _max; count = 0; time = GetTickCount(); use = false; }
};


