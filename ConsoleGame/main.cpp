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
	player.level = 4;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	enemy1 = new Enemy;
	enemy1->delay = 2000;
	enemy1->hp = 50;
	enemy1->obj.Speed = 1;
	enemy1->obj.Info.Color = 5;
	enemy1->obj.Info.Texture[0] = (char*)"○□▶";
	enemy1->obj.Info.Texture[1] = (char*)" ▼▶ ";
	enemy1->obj.TransInfo.Scale.x = strlen("○□▶");
	enemy1->obj.TransInfo.Scale.y = 2;
	enemy1->obj.TransInfo.Rotation.x = -1;
	enemy1->obj.TransInfo.Rotation.y = 0;
	enemy1->time = 0;
	

	BulletData[0] = new Bullet;
	BulletData[0]->obj.Info.Color = 3;
	BulletData[0]->obj.Info.Texture[0] = (char*)">";
	BulletData[0]->obj.Speed = 3;
	BulletData[0]->obj.TransInfo.Scale.x = strlen(">");
	BulletData[0]->obj.TransInfo.Scale.y = 1;
	BulletData[0]->obj.TransInfo.Rotation.x = 1;
	BulletData[0]->obj.TransInfo.Rotation.y = 0;

	BulletData[1] = new Bullet;
	BulletData[1]->obj.Info.Color = 15;
	BulletData[1]->obj.Info.Texture[0] = (char*)"*";
	BulletData[1]->obj.Speed = 3;
	BulletData[1]->obj.TransInfo.Scale.x = strlen("*");
	BulletData[1]->obj.TransInfo.Scale.y = 1;
	BulletData[1]->obj.TransInfo.Rotation.x = -1;
	BulletData[1]->obj.TransInfo.Rotation.y = 0;

	BulletData[2] = new Bullet;
	BulletData[2]->obj.Info.Color = 5;
	BulletData[2]->obj.Info.Texture[0] = (char*)"+";
	BulletData[2]->obj.Speed = 3;
	BulletData[2]->obj.TransInfo.Scale.x = strlen("+");
	BulletData[2]->obj.TransInfo.Scale.y = 1;
	BulletData[2]->obj.TransInfo.Rotation.x = 1;
	BulletData[2]->obj.TransInfo.Rotation.y = 0;

	hit = new Effect;
	hit->obj.Info.Color = 12;
	hit->obj.Info.Texture[0] = (char *)"♨";
	hit->obj.Speed = 1;
	hit->obj.TransInfo.Scale.x = strlen("♨");
	hit->obj.TransInfo.Scale.y = 1.0f;
	hit->time = 0;

	hit = new Effect;
	hit->obj.Info.Color = 12;
	hit->obj.Info.Texture[0] = (char*)"♨";
	hit->obj.Speed = 1;
	hit->obj.TransInfo.Scale.x = strlen("♨");
	hit->obj.TransInfo.Scale.y = 1.0f;
	hit->time = 0;

	ItemData[0] = new Item;
	ItemData[0]->Info.Color = 4;
	ItemData[0]->Info.Texture[0] = (char*)"[Ｌ]";
	ItemData[0]->Speed = 1;
	ItemData[0]->TransInfo.Scale.x = strlen("[Ｌ]");
	ItemData[0]->TransInfo.Scale.y = 1;
	ItemData[0]->TransInfo.Rotation.x = 0;
	ItemData[0]->TransInfo.Rotation.y = 0;
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