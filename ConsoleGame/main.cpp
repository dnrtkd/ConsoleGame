// ** Framework v0.4.3
// ** ���� : Bullet & Enemy �浹 ����.
#include "Headers.h"





// ** ������.	
int main(void)
{
	// ** Ŀ���� �Ⱥ��̰� �������.
	HideCursor(false);

	system("mode con:cols=150 lines=50");

	system("title ȫ�浿 Framework v0.6");


	player.chance = 3;
	player.damage = 5;
	player.delay=100;
	player.name = (char*)"ȫ�浿";
	player.obj.Info.Color = 10;
	player.obj.Speed = 1;
	player.obj.TransInfo.Position.x= 0;
	player.obj.TransInfo.Position.y = 0;
	player.obj.Info.Texture[0] = (char*)"�����";
	player.obj.Info.Texture[1] = (char*)"�����";
	player.obj.TransInfo.Scale.x = strlen("�����");
	player.obj.TransInfo.Scale.y = 2;
	player.delay = 100; //0.1��
	player.level = 2;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	enemy1 = new Enemy;
	enemy1->delay = 1000;
	enemy1->hp = 50;
	enemy1->obj.Speed = 1;
	enemy1->obj.Info.Color = 5;
	enemy1->obj.Info.Texture[0] = (char*)"��.��";
	enemy1->obj.Info.Texture[1] = (char*)"��.��";
	enemy1->obj.TransInfo.Scale.x = strlen("��.��");
	enemy1->obj.TransInfo.Scale.y = 2;
	enemy1->time = 0;

	BulletData[0] = new Bullet;
	BulletData[0]->Info.Color = 3;
	BulletData[0]->Info.Texture[0] = (char*)">";
	BulletData[0]->Speed = 3;
	BulletData[0]->TransInfo.Scale.x = strlen(">");
	BulletData[0]->TransInfo.Scale.y = 1;

	BulletData[1] = new Bullet;
	BulletData[1]->Info.Color = 15;
	BulletData[1]->Info.Texture[0] = (char*)"*";
	BulletData[1]->Speed = 3;
	BulletData[1]->TransInfo.Scale.x = strlen("*");
	BulletData[1]->TransInfo.Scale.y = 1;
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