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
	player.delay = 200; //0.1��
	player.level = 1;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	for (int i = 0; i < 128; i++) //�ҷ� �ʱ�ȭ
	{

		bullets[i] = nullptr;
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