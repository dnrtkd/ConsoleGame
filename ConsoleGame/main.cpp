// ** Framework v0.4.3
// ** ���� : Bullet & Enemy �浹 ����.
#include "Headers.h"





// ** ������.	
int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);

	system("mode con:cols=150 lines=30");

	system("title ȫ�浿 Framework v0.6");


	player.chance = 3;
	player.damage = 5;
	player.delay=300;
	player.name = (char*)"ȫ�浿";
	player.obj.Info.Color = 10;
	player.obj.Speed = 3;
	player.obj.TransInfo.Position.x= 0;
	player.obj.TransInfo.Position.y = 0;
	player.obj.Info.Texture[0] = (char*)"�����";
	player.obj.Info.Texture[1] = (char*)"�����";
	player.obj.TransInfo.Scale.x = strlen("�����");
	player.obj.TransInfo.Scale.y = 2;
	player.delay = 100; //0.1��
	player.level = 4;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	enemy1 = new Enemy;
	enemy1->delay = 2000;
	enemy1->hp = 50;
	enemy1->obj.Speed = 1;
	enemy1->obj.Info.Color = 5;
	enemy1->obj.Info.Texture[0] = (char*)"�ۡࢺ";
	enemy1->obj.Info.Texture[1] = (char*)" �墺 ";
	enemy1->obj.TransInfo.Scale.x = strlen("�ۡࢺ");
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
	hit->obj.Info.Texture[0] = (char *)"��";
	hit->obj.Speed = 1;
	hit->obj.TransInfo.Scale.x = strlen("��");
	hit->obj.TransInfo.Scale.y = 1.0f;
	hit->time = 0;

	hit = new Effect;
	hit->obj.Info.Color = 12;
	hit->obj.Info.Texture[0] = (char*)"��";
	hit->obj.Speed = 1;
	hit->obj.TransInfo.Scale.x = strlen("��");
	hit->obj.TransInfo.Scale.y = 1.0f;
	hit->time = 0;

	ItemData[0] = new Item;
	ItemData[0]->Info.Color = 4;
	ItemData[0]->Info.Texture[0] = (char*)"[��]";
	ItemData[0]->Speed = 1;
	ItemData[0]->TransInfo.Scale.x = strlen("[��]");
	ItemData[0]->TransInfo.Scale.y = 1;
	ItemData[0]->TransInfo.Rotation.x = 0;
	ItemData[0]->TransInfo.Rotation.y = 0;
	for (int i = 0; i < 128; i++) //�ҷ� �ʱ�ȭ
	{

		bullets[i] = nullptr;
	}

	for (int i = 0; i < 128; i++) //�ҷ� �ʱ�ȭ
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



// ** ������ (�� : ����)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]