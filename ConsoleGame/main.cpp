// ** Framework v0.4.3
// ** 숙제 : Bullet & Enemy 충돌 구현.
#include "Headers.h"





// ** 진입점.	
int main(void)
{
	// ** 커서를 안보이게 만들어줌.
	HideCursor(false);

	system("mode con:cols=150 lines=50");

	system("title 홍길동 Framework v0.6");


	player.chance = 3;
	player.damage = 5;
	player.delay=100;
	player.name = (char*)"홍길동";
	player.obj.Info.Color = 10;
	player.obj.Speed = 1;
	player.obj.TransInfo.Position.x= 0;
	player.obj.TransInfo.Position.y = 0;
	player.obj.Info.Texture[0] = (char*)"◀■〓";
	player.obj.Info.Texture[1] = (char*)"◀■〓";
	player.obj.TransInfo.Scale.x = strlen("◀■〓");
	player.obj.TransInfo.Scale.y = 2;
	player.delay = 200; //0.1초
	player.level = 1;
	long time=0;
	
	player.obj.TransInfo.Position.x = 10;
	player.obj.TransInfo.Position.y = 20;

	for (int i = 0; i < 128; i++) //불렛 초기화
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



// ** 게이지 (월 : 예정)
//  [           \\]
//  [         \\\\]
//  [      \\\\\\\]
//  [    \\\\\\\\\]
//  [  \\\\\\\\\\\]
//  [\\\\\\\\\\\\\]