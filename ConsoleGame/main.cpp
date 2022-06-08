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
	player.level = 1;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	EnemyData[0] = new Enemy;
	EnemyData[0]->delay = 2000;
	EnemyData[0]->hp = 50;
	EnemyData[0]->obj.Speed = 1;
	EnemyData[0]->obj.Info.Color = 8;
	EnemyData[0]->obj.Info.Texture[0] = (char*)"�ۡࢺ";
	EnemyData[0]->obj.Info.Texture[1] = (char*)" �墺 ";
	EnemyData[0]->obj.TransInfo.Scale.x = strlen("�ۡࢺ");
	EnemyData[0]->obj.TransInfo.Scale.y = 2;
	EnemyData[0]->obj.TransInfo.Rotation.x = -1;
	EnemyData[0]->obj.TransInfo.Rotation.y = 0;
	EnemyData[0]->time = 0;
	EnemyData[0]->obj.Info.Option = 0; //�ε���

	EnemyData[1] = new Enemy;
	EnemyData[1]->delay = 3000;
	EnemyData[1]->hp = 100;
	EnemyData[1]->obj.Speed = 1;
	EnemyData[1]->obj.Info.Color = 8;
	EnemyData[1]->obj.Info.Texture[0] = (char*)"    ��";
	EnemyData[1]->obj.Info.Texture[1] = (char*)"��ݡ�";
	EnemyData[1]->obj.Info.Texture[2] = (char*)"    ��";
	EnemyData[1]->obj.TransInfo.Scale.x = strlen("    ��");
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
	EnemyData[2]->obj.Info.Texture[0] = (char*)"���ǢǢǢ�";
	EnemyData[2]->obj.Info.Texture[1] = (char*)"    ���ݡ�";
	EnemyData[2]->obj.Info.Texture[2] = (char*)"���ǢǢǢ�";
	EnemyData[2]->obj.TransInfo.Scale.x = strlen("���ǢǢǢ�");
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
	BulletData[2]->obj.Info.Texture[0] = (char*)"�ݡ�";
	BulletData[2]->obj.Info.Texture[1] = (char*)"�ݡ�";
	BulletData[2]->obj.Speed = 2;
	BulletData[2]->obj.TransInfo.Scale.x = strlen("�ݡ�");
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
	EffectData[0]->obj.Info.Texture[0] = (char *)"��";
	EffectData[0]->obj.Speed = 3;
	EffectData[0]->obj.TransInfo.Scale.x = strlen("��");
	EffectData[0]->obj.TransInfo.Scale.y = 1.0f;
	EffectData[0]->time = 0;
	EffectData[0]->obj.Info.Option = 0;

	EffectData[1] = new Effect;
	EffectData[1]->obj.Info.Color = 12;
	EffectData[1]->obj.Info.Texture[0] = (char*)"��";
	EffectData[1]->obj.Speed = 1;
	EffectData[1]->obj.TransInfo.Scale.x = strlen("��");
	EffectData[1]->obj.TransInfo.Scale.y = 1.0f;
	EffectData[1]->time = 0;
	EffectData[1]->obj.Info.Option = 1;

	ItemData[0] = new Item;
	ItemData[0]->Info.Color = 4;
	ItemData[0]->Info.Texture[0] = (char*)"����";
	ItemData[0]->Info.Texture[1] = (char*)"��̡�";
	ItemData[0]->Info.Texture[2] = (char*)"����";
	ItemData[0]->Speed = 1;
	ItemData[0]->TransInfo.Scale.x = strlen("����");
	ItemData[0]->TransInfo.Scale.y =3;
	ItemData[0]->TransInfo.Rotation.x = 0;
	ItemData[0]->TransInfo.Rotation.y = 0;
	ItemData[0]->Info.Option = 0;

	ItemData[1] = new Item;
	ItemData[1]->Info.Color = 4;
	ItemData[1]->Info.Texture[0] = (char*)"����";
	ItemData[1]->Info.Texture[1] = (char*)"��ȡ�";
	ItemData[1]->Info.Texture[2] = (char*)"����";
	ItemData[1]->Speed = 1;
	ItemData[1]->TransInfo.Scale.x = strlen("����");
	ItemData[1]->TransInfo.Scale.y = 3;
	ItemData[1]->TransInfo.Rotation.x = 0;
	ItemData[1]->TransInfo.Rotation.y = 0;
	ItemData[1]->Info.Option = 1;

	ItemData[2] = new Item;
	ItemData[2]->Info.Color = 4;
	ItemData[2]->Info.Texture[0] = (char*)"����";
	ItemData[2]->Info.Texture[1] = (char*)"��¡�";
	ItemData[2]->Info.Texture[2] = (char*)"����";
	ItemData[2]->Speed = 1;
	ItemData[2]->TransInfo.Scale.x = strlen("����");
	ItemData[2]->TransInfo.Scale.y = 3;
	ItemData[2]->TransInfo.Rotation.x = 0;
	ItemData[2]->TransInfo.Rotation.y = 0;
	ItemData[2]->Info.Option = 2;
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