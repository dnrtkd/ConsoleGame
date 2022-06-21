// ** Framework v0.4.3
// ** 숙제 : Bullet & Enemy 충돌 구현.
#include "Headers.h"





// ** 진입점.	
int main(void)
{
	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);

	system("mode con:cols=150 lines=30");

	system("title 홍길동 Framework v0.6");

	player.chance = 3;
	player.damage = 5;
	player.delay=300;
	player.name = (char*)"홍길동";
	player.obj.Info.Color = 10;
	player.obj.Speed = 2;
	player.obj.TransInfo.Position.x= 0;
	player.obj.TransInfo.Position.y = 0;
	player.obj.Info.Texture[0] = (char*)"◀■〓";
	player.obj.Info.Texture[1] = (char*)"◀■〓";
	player.obj.TransInfo.Scale.x = strlen("◀■〓");
	player.obj.TransInfo.Scale.y = 2;
	player.delay = 100; //0.1초
	player.level = 1;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	EnemyData[0] = new Enemy;
	EnemyData[0]->delay = 2000;
	EnemyData[0]->hp = 50;
	EnemyData[0]->obj.Speed = 2;
	EnemyData[0]->obj.Info.Color = 8;
	EnemyData[0]->obj.Info.Texture[0] = (char*)"○□▶";
	EnemyData[0]->obj.Info.Texture[1] = (char*)"○□▶";
	EnemyData[0]->obj.TransInfo.Scale.x = strlen("○□▶");
	EnemyData[0]->obj.TransInfo.Scale.y = 2;
	EnemyData[0]->obj.TransInfo.Rotation.x = -1;
	EnemyData[0]->obj.TransInfo.Rotation.y = 0;
	EnemyData[0]->timer = 0;
	EnemyData[0]->obj.Info.Option = 0; //인덱스
	EnemyData[0]->count = 1;
	EnemyData[0]->lateTime = 0;

	EnemyData[1] = new Enemy;
	EnemyData[1]->delay = 100;
	EnemyData[1]->hp = 100;
	EnemyData[1]->obj.Speed = 2;
	EnemyData[1]->obj.Info.Color = 8;
	EnemyData[1]->obj.Info.Texture[0] = (char*)"    ∩";
	EnemyData[1]->obj.Info.Texture[1] = (char*)"€◎§";
	EnemyData[1]->obj.Info.Texture[2] = (char*)"    ∪";
	EnemyData[1]->obj.TransInfo.Scale.x = strlen("    ∩");
	EnemyData[1]->obj.TransInfo.Scale.y = 3;
	EnemyData[1]->obj.TransInfo.Rotation.x = -1;
	EnemyData[1]->obj.TransInfo.Rotation.y = 0;
	EnemyData[1]->timer = 0;
	EnemyData[1]->obj.Info.Option = 1;
	EnemyData[1]->count = 10;
	EnemyData[1]->lateTime = 3;

	EnemyData[2] = new Enemy;
	EnemyData[2]->delay = 2000;
	EnemyData[2]->hp = 50;
	EnemyData[2]->obj.Speed = 2;
	EnemyData[2]->obj.Info.Color = 7;
	EnemyData[2]->obj.Info.Texture[0] = (char*)"＜▤▤▤▶";
	EnemyData[2]->obj.Info.Texture[1] = (char*)"    ㅁ◎§";
	EnemyData[2]->obj.Info.Texture[2] = (char*)"＜▤▤▤▶";
	EnemyData[2]->obj.TransInfo.Scale.x = strlen("＜▤▤▤▶");
	EnemyData[2]->obj.TransInfo.Scale.y = 3;
	EnemyData[2]->obj.TransInfo.Rotation.x = -1;
	EnemyData[2]->obj.TransInfo.Rotation.y = 0;
	EnemyData[2]->timer = 0;
	EnemyData[2]->obj.Info.Option = 2;
	EnemyData[2]->count = 3;
	EnemyData[2]->lateTime = 2;

	EnemyData[3] = new Enemy;
	EnemyData[3]->delay = 200;
	EnemyData[3]->hp = 50;
	EnemyData[3]->obj.Speed = 2;
	EnemyData[3]->obj.Info.Color = 7;
	EnemyData[3]->obj.Info.Texture[0] = (char*)"                ▤▤▤▤⊙";
	EnemyData[3]->obj.Info.Texture[1] = (char*)"＜▤▤▤§▤▤▤▤▤▤▤⊙";
	EnemyData[3]->obj.Info.Texture[2] = (char*)"＜▤▤▤§▤▤▤▤▤▤▤⊙";
	EnemyData[3]->obj.Info.Texture[3] = (char*)"＜▤▤▤§▤▤▤▤▤▤▤⊙";
	EnemyData[3]->obj.Info.Texture[4] = (char*)"                ▤▤▤▤⊙";
	EnemyData[3]->obj.TransInfo.Scale.x = strlen("＜▤▤▤§▤▤▤▤▤▤▤⊙");
	EnemyData[3]->obj.TransInfo.Scale.y = 5;
	EnemyData[3]->obj.TransInfo.Rotation.x = -1;
	EnemyData[3]->obj.TransInfo.Rotation.y = 0;
	EnemyData[3]->timer = 0;
	EnemyData[3]->obj.Info.Option = 3;
	EnemyData[3]->count = 30;
	EnemyData[3]->lateTime = 2;

	BulletData[0] = new Bullet;
	BulletData[0]->obj.Info.Color = 3;
	BulletData[0]->obj.Info.Texture[0] = (char*)"-";
	BulletData[0]->obj.Speed = 4;
	BulletData[0]->obj.TransInfo.Scale.x = strlen("-");
	BulletData[0]->obj.TransInfo.Scale.y = 1;
	BulletData[0]->obj.TransInfo.Rotation.x = 1;
	BulletData[0]->obj.TransInfo.Rotation.y = 0;
	BulletData[0]->obj.Info.Option = 0;

	BulletData[1] = new Bullet;
	BulletData[1]->obj.Info.Color = 15;
	BulletData[1]->obj.Info.Texture[0] = (char*)"*";
	BulletData[1]->obj.Speed = 3;
	BulletData[1]->obj.TransInfo.Scale.x = strlen("*");
	BulletData[1]->obj.TransInfo.Scale.y = 1;
	BulletData[1]->obj.TransInfo.Rotation.x = -1;
	BulletData[1]->obj.TransInfo.Rotation.y = 0;
	BulletData[1]->obj.Info.Option = 1;

	BulletData[2] = new Bullet;
	BulletData[2]->obj.Info.Color = 15;
	BulletData[2]->obj.Info.Texture[0] = (char*)"◎◎";
	BulletData[2]->obj.Info.Texture[1] = (char*)"◎◎";
	BulletData[2]->obj.Speed = 2;
	BulletData[2]->obj.TransInfo.Scale.x = strlen("◎◎");
	BulletData[2]->obj.TransInfo.Scale.y = 2;
	BulletData[2]->obj.TransInfo.Rotation.x = -1;
	BulletData[2]->obj.TransInfo.Rotation.y = 0;
	BulletData[2]->obj.Info.Option = 2;

	BulletData[3] = new Bullet;
	BulletData[3]->obj.Info.Color = 5;
	BulletData[3]->obj.Info.Texture[0] = (char*)"+";
	BulletData[3]->obj.Speed = 5;
	BulletData[3]->obj.TransInfo.Scale.x = strlen("+");
	BulletData[3]->obj.TransInfo.Scale.y = 1;
	BulletData[3]->obj.TransInfo.Rotation.x = 1;
	BulletData[3]->obj.TransInfo.Rotation.y = 0;
	BulletData[3]->obj.Info.Option = 3;

	EffectData[0] = new Effect;
	EffectData[0]->obj.Info.Color = 12;
	EffectData[0]->obj.Info.Texture[0] = (char *)"º";
	EffectData[0]->obj.Speed = 3;
	EffectData[0]->obj.TransInfo.Scale.x = strlen("º");
	EffectData[0]->obj.TransInfo.Scale.y = 1.0f;
	EffectData[0]->time = 0;
	EffectData[0]->obj.Info.Option = 0;

	EffectData[1] = new Effect;
	EffectData[1]->obj.Info.Color = 11;
	EffectData[1]->obj.Info.Texture[0] = (char*)"☆";
	EffectData[1]->obj.Speed = 1;
	EffectData[1]->obj.TransInfo.Scale.x = strlen("☆");
	EffectData[1]->obj.TransInfo.Scale.y = 1.0f;
	EffectData[1]->time = 0;
	EffectData[1]->obj.Info.Option = 1;

	ItemData[0] = new Item;
	ItemData[0]->Info.Color = 4;
	ItemData[0]->Info.Texture[0] = (char*)"[Ｌ]";
	ItemData[0]->Speed = 1;
	ItemData[0]->TransInfo.Scale.x = strlen("■■■");
	ItemData[0]->TransInfo.Scale.y =1;
	ItemData[0]->TransInfo.Rotation.x = 0;
	ItemData[0]->TransInfo.Rotation.y = 0;
	ItemData[0]->Info.Option = 0;

	ItemData[1] = new Item;
	ItemData[1]->Info.Color = 4;
	ItemData[1]->Info.Texture[0] = (char*)"■■■";
	ItemData[1]->Info.Texture[1] = (char*)"■Ｈ■";
	ItemData[1]->Info.Texture[2] = (char*)"■■■";
	ItemData[1]->Speed = 2;
	ItemData[1]->TransInfo.Scale.x = strlen("■■■");
	ItemData[1]->TransInfo.Scale.y = 3;
	ItemData[1]->TransInfo.Rotation.x = 0;
	ItemData[1]->TransInfo.Rotation.y = 0;
	ItemData[1]->Info.Option = 1;

	ItemData[2] = new Item;
	ItemData[2]->Info.Color = 4;
	ItemData[2]->Info.Texture[0] = (char*)"■■■";
	ItemData[2]->Info.Texture[1] = (char*)"■Ｂ■";
	ItemData[2]->Info.Texture[2] = (char*)"■■■";
	ItemData[2]->Speed = 2;
	ItemData[2]->TransInfo.Scale.x = strlen("■■■");
	ItemData[2]->TransInfo.Scale.y = 3;
	ItemData[2]->TransInfo.Rotation.x = 0;
	ItemData[2]->TransInfo.Rotation.y = 0;
	ItemData[2]->Info.Option = 2;

	LevelUp = new LargeText;
	LevelUp->texture[0] =(char*)"   __             __            ____";
	LevelUp->texture[1] =(char*)"  / /__ _  _____ / / __ _____  / / /";
	LevelUp->texture[2] =(char*)" / / -_) |/ / -_) / / // / _ \/_/_/ ";
	LevelUp->texture[3] =(char*)"/_/\__/|___/\__/_/  \_,_/ .__(_|_)  ";
	LevelUp->texture[4] =(char*)"                       /_/          ";
	LevelUp->timer = 0;
	LevelUp->color = 15;


	
	//Wall[0] = new Object;
	//Wall[0]->Info.Texture[0] = (char*)"     □□□□□□□□□□□";
	//Wall[0]->Info.Texture[1] = (char*)"  □□□□□□□□□□□□□□";
	//Wall[0]->Info.Texture[2] = (char*)"□□□□□□□□□□□□□□□□";

	//Wall[0]->Speed = 2;
	//Wall[0]->TransInfo.Rotation.x = -1;           Wall[0]->TransInfo.Rotation.y = 0;
	//Wall[0]->TransInfo.Scale.x = strlen("□□□□□□□□□□□□□□□□");  Wall [0]->TransInfo.Scale.y = 3;
	//Wall[0]->TransInfo.Position.x = 0;            Wall [0]->TransInfo.Position.y =0;
	//Wall[0]->Info.Option = 0;
	//Wall[0]->Info.Color = 15;

	Wall[1] = new Object;
	Wall[1]->Info.Texture[0] = (char*)"　　□□□□□□□□□□□　　　　";
	Wall[1]->Info.Texture[1] = (char*)"　□□□□□□□　□□□□□□□　";
	Wall[1]->Info.Texture[2] = (char*)"□□□□□□□　　　□□□□□□□";
	Wall[1]->Speed = 2;
	Wall[1]->TransInfo.Rotation.x = -1;           Wall[1]->TransInfo.Rotation.y = 0;
	Wall[1]->TransInfo.Scale.x = strlen("□□□□□□□　　　□□□□□□□");  Wall[1]->TransInfo.Scale.y = 3;
	Wall[1]->TransInfo.Position.x = 180;            Wall[1]->TransInfo.Position.y = 27;
	Wall[1]->Info.Option = 1;
	Wall[1]->Info.Color = 15;

	Wall[2] = new Object;
	Wall[2]->Info.Texture[0] = (char*)"□□□□□□□□□□□□□□□□□□";
	Wall[2]->Info.Texture[1] = (char*)"□□□□□□□□□□□□□□□□□□";
	Wall[2]->Info.Texture[2] = (char*)"□□□□□□□□□□□□□□□□□□";
	Wall[2]->Speed = 2;
	Wall[2]->TransInfo.Rotation.x = -1;           Wall[2]->TransInfo.Rotation.y = 0;
	Wall[2]->TransInfo.Scale.x = strlen("□□□□□□□□□□□□□□□□□□");  Wall[2]->TransInfo.Scale.y = 3;
	Wall[2]->TransInfo.Position.x = 180;            Wall[2]->TransInfo.Position.y = 28;
	Wall[2]->Info.Option = 2;
	Wall[2]->Info.Color = 15;

	Wall[3] = new Object;
	Wall[3]->Info.Texture[0] = (char*)" ______  ";
	Wall[3]->Info.Texture[1] = (char*)"(       )";
	Wall[3]->Info.Texture[2] = (char*)"--(____) ";
	Wall[3]->Speed = 1;
	Wall[3]->TransInfo.Rotation.x = -1;   Wall[3]->TransInfo.Rotation.y = 0;
	Wall[3]->TransInfo.Scale.x = strlen(" ______  "); Wall[3]->TransInfo.Scale.y = 3;
	Wall[2]->Info.Option = 3;
	Wall[3]->Info.Color = 15;


	
	
	for (int i = 0; i < 128; i++) //불렛 초기화
	{

		bullets[i] = nullptr;
	}

	for (int i = 0; i < 128; i++) //불렛 초기화
	{

		eBullets[i] = nullptr;
	}

	for (int i = 0; i < 32; i++)
	{
		enemies[i] = nullptr;
	}

	for (int i = 0; i < 32; i++)
	{
		hitEffect[i] = nullptr;
	}

	for (size_t i = 0; i < 16; i++)
	{
		Walls[i] = nullptr;
	}

	ScreenPosition.x = 0;
	ScreenPosition.y = 0;

	while (1)
	{
		if (time + 80 < GetTickCount())
		{
			time = GetTickCount();

			system("cls");
			SceneManaer();
		}
	}
	return 0;
}



// ** 게이지 (월 : 예정)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]