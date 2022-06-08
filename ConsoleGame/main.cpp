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
	player.obj.Speed = 3;
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
	EnemyData[0]->obj.Speed = 1;
	EnemyData[0]->obj.Info.Color = 8;
	EnemyData[0]->obj.Info.Texture[0] = (char*)"○□▶";
	EnemyData[0]->obj.Info.Texture[1] = (char*)" ▼▶ ";
	EnemyData[0]->obj.TransInfo.Scale.x = strlen("○□▶");
	EnemyData[0]->obj.TransInfo.Scale.y = 2;
	EnemyData[0]->obj.TransInfo.Rotation.x = -1;
	EnemyData[0]->obj.TransInfo.Rotation.y = 0;
	EnemyData[0]->time = 0;
	EnemyData[0]->obj.Info.Option = 0; //인덱스

	EnemyData[1] = new Enemy;
	EnemyData[1]->delay = 3000;
	EnemyData[1]->hp = 100;
	EnemyData[1]->obj.Speed = 1;
	EnemyData[1]->obj.Info.Color = 8;
	EnemyData[1]->obj.Info.Texture[0] = (char*)"    ∩";
	EnemyData[1]->obj.Info.Texture[1] = (char*)"€◎§";
	EnemyData[1]->obj.Info.Texture[2] = (char*)"    ∪";
	EnemyData[1]->obj.TransInfo.Scale.x = strlen("    ∩");
	EnemyData[1]->obj.TransInfo.Scale.y = 3;
	EnemyData[1]->obj.TransInfo.Rotation.x = -1;
	EnemyData[1]->obj.TransInfo.Rotation.y = 0;
	EnemyData[1]->time = 0;
	EnemyData[1]->obj.Info.Option = 1;

	EnemyData[2] = new Enemy;
	EnemyData[2]->delay = 2000;
	EnemyData[2]->hp = 50;
	EnemyData[2]->obj.Speed = 1;
	EnemyData[2]->obj.Info.Color = 7;
	EnemyData[2]->obj.Info.Texture[0] = (char*)"＜▤▤▤▶";
	EnemyData[2]->obj.Info.Texture[1] = (char*)"    ㅁ◎§";
	EnemyData[2]->obj.Info.Texture[2] = (char*)"＜▤▤▤▶";
	EnemyData[2]->obj.TransInfo.Scale.x = strlen("＜▤▤▤▶");
	EnemyData[2]->obj.TransInfo.Scale.y = 3;
	EnemyData[2]->obj.TransInfo.Rotation.x = -1;
	EnemyData[2]->obj.TransInfo.Rotation.y = 0;
	EnemyData[2]->time = 0;
	EnemyData[2]->obj.Info.Option = 2;

	BulletData[0] = new Bullet;
	BulletData[0]->obj.Info.Color = 3;
	BulletData[0]->obj.Info.Texture[0] = (char*)"-";
	BulletData[0]->obj.Speed = 3;
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
	EffectData[1]->obj.Info.Color = 12;
	EffectData[1]->obj.Info.Texture[0] = (char*)"☆";
	EffectData[1]->obj.Speed = 1;
	EffectData[1]->obj.TransInfo.Scale.x = strlen("☆");
	EffectData[1]->obj.TransInfo.Scale.y = 1.0f;
	EffectData[1]->time = 0;
	EffectData[1]->obj.Info.Option = 1;

	ItemData[0] = new Item;
	ItemData[0]->Info.Color = 4;
	ItemData[0]->Info.Texture[0] = (char*)"■■■";
	ItemData[0]->Info.Texture[1] = (char*)"■Ｌ■";
	ItemData[0]->Info.Texture[2] = (char*)"■■■";
	ItemData[0]->Speed = 1;
	ItemData[0]->TransInfo.Scale.x = strlen("■■■");
	ItemData[0]->TransInfo.Scale.y =3;
	ItemData[0]->TransInfo.Rotation.x = 0;
	ItemData[0]->TransInfo.Rotation.y = 0;
	ItemData[0]->Info.Option = 0;

	ItemData[1] = new Item;
	ItemData[1]->Info.Color = 4;
	ItemData[1]->Info.Texture[0] = (char*)"■■■";
	ItemData[1]->Info.Texture[1] = (char*)"■Ｈ■";
	ItemData[1]->Info.Texture[2] = (char*)"■■■";
	ItemData[1]->Speed = 1;
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
	ItemData[2]->Speed = 1;
	ItemData[2]->TransInfo.Scale.x = strlen("■■■");
	ItemData[2]->TransInfo.Scale.y = 3;
	ItemData[2]->TransInfo.Rotation.x = 0;
	ItemData[2]->TransInfo.Rotation.y = 0;
	ItemData[2]->Info.Option = 2;
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