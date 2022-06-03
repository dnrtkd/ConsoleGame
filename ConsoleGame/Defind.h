#pragma once

static int SceneState = 0;

static Player player;

static Bullet* BulletData[6];
static Item* ItemData[4];
static int Score=0;

static Bullet* bullets[128] = { nullptr };
static Bullet* eBullets[128] = { nullptr };
static Effect* hitEffect[32] = { nullptr };
static Enemy* enemies[32] = { nullptr };
static Item* appearItem = nullptr;
static Enemy* enemy1;
static Enemy* enemy2;
static Effect* hit;


static int maxWidth = 150;
static int maxHight = 30;

//딜레이 계산할때 쓰는 함수
static long delayTime = 0;
static long enemyResporn = 0;
static long itemTimer = 0;

static double GameTime = 0;

// ** 초기화 함수 (디폴트 매개변수 : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0);

// ** 이름을 셋팅하는 함수
char* SetName();

// ** 커서의 위치를 변경

void SetCursorPosition(const int _x, const int _y);

// ** Text의 색을 변경함.
void SetTextColor(const int _Color);

// ** 출력할 Text의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(const char* _str, const int _x, const int _y, const int _Color = 15);

// ** 출력할 숫자의 위치와 색상을 변경해준다. [Color 값은 기본값 : 흰색(15)]
void OnDrawText(const int _Value, const int _x, const int _y, const int _Color = 15);

// ** 커서를 보이거나(true) / 안보이게(false) 만들어줌.
void HideCursor(const bool _Visible);

// ** 충돌처리를 함.
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

// ** Bullet를 생성함.
Bullet* CreateBullet(Bullet *bul, float _x, float _Y);

void PlayerShoot(Object* obj);

// ** 키입력 
void UpdateInput();

void SceneManaer();

void SetPosition(int _x, int _y, char* _str, int _Color);

void Stage_ONE();

void TitleScene();

Enemy* CreateEnemy(Enemy* src, int x, int y);

void AppearEnemy(Enemy* src);

void EnemyShoot(Enemy* enemy);

void EnemyHit();

void Enemydied();

void HitEffect(int _x, int _Y);

float GetDistance(const Object* _ObjectA, const Object* _ObjectB);

Effect* createEffect(Effect* src, float _x, float _y);

Vector2 GetDirection(const Object* _ObjectA, const Object* _ObjectB);

Bullet* CreateGBullet(Bullet* src, float _x, float _y);//유도탄

Bullet* CreateBullet(Bullet* src, float _x, float _y, Vector2 dir);

void move(Object* obj, Vector2 direction);

void invokeTem(const Item* item);

Item* CreateItem(Item* src, int x, int y);
// ** 함수 정의부
Item* CreateItem(Item* src,int x, int y)
{
	Item* item = new Item;

	item->Info.Color = src->Info.Color;
	item->Speed = src->Speed;
	item->TransInfo.Scale.x = src->TransInfo.Scale.x;
	item->TransInfo.Scale.y = src->TransInfo.Scale.y;
	for (size_t i = 0; i < item->TransInfo.Scale.y; i++)
	{
		item->Info.Texture[i] = src->Info.Texture[i];
	}
	item->TransInfo.Position.x = x;
	item->TransInfo.Position.y = y;
	item->TransInfo.Rotation.x = src->TransInfo.Rotation.x;
	item->TransInfo.Rotation.y = src->TransInfo.Rotation.y;
	return item;
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { (SHORT)_x,(SHORT)_y }; // 콘솔 순서쌍

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);//커서 위치 이동
	SetTextColor(_Color);

	printf_s("%s", _str);
}


void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY)
{
	// ** 3항 연상자. 
	// ** _Name 의 값이 nullptr 이라면  SetName() 함수를 실행하고 아니라면,
	// ** _Name의 값을 그대로 대입한다.
	_Object->Info.Texture [0]= (_Texture == nullptr) ? SetName() : _Texture;

	// ** 이동속도 
	_Object->Speed = 0;

	// ** 좌표값
	_Object->TransInfo.Position = Vector2(_PosX, _PosY);

	// ** 회전값 (현재 사용되지 않음.)
	_Object->TransInfo.Rotation = Vector2(0, 0);

	// ** 크기값
	_Object->TransInfo.Scale = Vector2(
		strlen(_Object->Info.Texture[0]), 1);

	_Object->Info.Color = 15;
	_Object->TransInfo.Scale.y = 1;
}

char* SetName()
{
	// ** 문자열을 입력 받을 임시 변수를 배열로 생성한다. (포인터 변수에는 바로 입력받을수 없음.)
	char Buffer[128] = "";

	// ** 이름 입력
	cout << "입력 : "; cin >> Buffer;

	// ** 포인터 변수을 선언하여 입력받은 문자열의 길이만큼 크기를 할당함.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** 입력받은 문자열의 내용을 복사함.
	strcpy(pName, Buffer);

	// ** 반환
	return pName;
}

void SetCursorPosition(const int _x, const int _y)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void SetTextColor(const int _Color)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}

void OnDrawText(const char* _str, const int _x, const int _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);
	cout << _str;
}

void OnDrawText(Object* obj)
{
	SetTextColor(obj->Info.Color);

	for (int i = 0; i < obj->TransInfo.Scale.y; i++)
	{
		SetCursorPosition(obj->TransInfo.Position.x, obj->TransInfo.Position.y+i);

		cout<<obj->Info.Texture[i];
	}
}

void OnDrawText(const int _Value, const int _x, const int _y, const int _Color)
{
	SetCursorPosition(_x, _y);
	SetTextColor(_Color);

	char* pText = new char[4];
	_itoa(_Value, pText, 10);
	cout << _Value;
}

void HideCursor(const bool _Visible)
{
	CONSOLE_CURSOR_INFO CursorInfo;

	CursorInfo.bVisible = _Visible;
	CursorInfo.dwSize = 1;

	SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);
}

bool Collision(const Object* _ObjectA, const Object* _ObjectB)
{
	// ** (_Object->TransInfo.Position.x + _Object->TransInfo.Scale.x)   : 우측
	// ** _Object->TransInfo.Position.x   : 좌측
	// ** Rect 충돌시 우측선은 항상 크다.
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		(_ObjectA->TransInfo.Position.y +_ObjectA->TransInfo.Scale.y) > _ObjectB->TransInfo.Position.y &&
		(_ObjectB->TransInfo.Position.y + _ObjectB->TransInfo.Scale.y) > _ObjectA->TransInfo.Position.y)
	{
		
		return true;
	}
	else return false;
		
}

Bullet* CreateBullet(Bullet* src,float _x,float _y)
{
	Bullet* bul = new Bullet;

	bul->obj.Info.Color = src->obj.Info.Color;
	bul->obj.Info.Texture[0] = src->obj.Info.Texture[0];
	bul->obj.Speed = src->obj.Speed;
	bul->obj.TransInfo.Scale.x = src->obj.TransInfo.Scale.x;
	bul->obj.TransInfo.Scale.y = src->obj.TransInfo.Scale.y;
	bul->obj.TransInfo.Position.x = _x;
	bul->obj.TransInfo.Position.y = _y;
	bul->obj.TransInfo.Rotation.x = src->obj.TransInfo.Rotation.x;
	bul->obj.TransInfo.Rotation.y = src->obj.TransInfo.Rotation.y;
	return bul;
}

Bullet* CreateGBullet(Bullet* src, float _x, float _y)
{
	Bullet* bul = new Bullet;

	bul->obj.Info.Color = src->obj.Info.Color;
	bul->obj.Info.Texture[0] = src->obj.Info.Texture[0];
	bul->obj.Speed = src->obj.Speed;
	bul->obj.TransInfo.Scale.x = src->obj.TransInfo.Scale.x;
	bul->obj.TransInfo.Scale.y = src->obj.TransInfo.Scale.y;
	bul->obj.TransInfo.Position.x = _x;
	bul->obj.TransInfo.Position.y = _y;
	bul->obj.TransInfo.Rotation.x = src->obj.TransInfo.Rotation.x;
	bul->obj.TransInfo.Rotation.y = src->obj.TransInfo.Rotation.y;

	
	float dis = 0;
	float Min = 0;
	int index = 0;
	for (size_t j = 0; j < 32; j++)
	{
		if (enemies[j])
		{
			dis = GetDistance(&enemies[j]->obj,& bul->obj);
			if (Min == 0)
				Min = dis;
			if (dis < Min)
			{
				Min =  dis;
				index = j;
			}
		}
	}
	bul->tagetIndex = index;
	return bul;
}

Bullet* CreateBullet(Bullet* src, float _x, float _y,Vector2 dir)
{
	Bullet* bul = new Bullet;

	bul->obj.Info.Color = src->obj.Info.Color;
	bul->obj.Info.Texture[0] = src->obj.Info.Texture[0];
	bul->obj.Speed = src->obj.Speed;
	bul->obj.TransInfo.Scale.x = src->obj.TransInfo.Scale.x;
	bul->obj.TransInfo.Scale.y = src->obj.TransInfo.Scale.y;
	bul->obj.TransInfo.Position.x = _x;
	bul->obj.TransInfo.Position.y = _y;
	bul->obj.TransInfo.Rotation.x = dir.x;
	bul->obj.TransInfo.Rotation.y = dir.y;
	return bul;
}



Effect* createEffect(Effect* src,float _x,float _y)
{
	Effect* eff = new Effect;

	eff->obj.Info.Color = src->obj.Info.Color;
	eff->obj.Info.Texture[0] = src->obj.Info.Texture[0];
	eff->obj.Speed = src->obj.Speed;
	eff->obj.TransInfo.Scale.x = src->obj.TransInfo.Scale.x;
	eff->obj.TransInfo.Scale.y = src->obj.TransInfo.Scale.y;
	eff->obj.TransInfo.Position.x = _x;
	eff->obj.TransInfo.Position.y = _y;
	eff->obj.TransInfo.Rotation.x = src->obj.TransInfo.Rotation.x;
	eff->obj.TransInfo.Rotation.y = src->obj.TransInfo.Rotation.y;
	eff->time = GetTickCount();
	return eff;
}


void UpdateInput()
{
	// ** [상] 키를 입력받음.
	if (GetAsyncKeyState(VK_UP)&& player.obj.TransInfo.Position.y>2)
		player.obj.TransInfo.Position.y -= player.obj.Speed;

	// ** [하] 키를 입력받음.
	if (GetAsyncKeyState(VK_DOWN) && player.obj.TransInfo.Position.y < 26)
		player.obj.TransInfo.Position.y += player.obj.Speed;

	// ** [좌] 키를 입력받음.
	if (GetAsyncKeyState(VK_LEFT) && player.obj.TransInfo.Position.x > 1)
		player.obj.TransInfo.Position.x -= player.obj.Speed;

	// ** [우] 키를 입력받음.
	if (GetAsyncKeyState(VK_RIGHT) && player.obj.TransInfo.Position.x < 148)
		player.obj.TransInfo.Position.x += player.obj.Speed;
}
//에너미나 플레이어를 인수로 받고 불렛을 반환
void PlayerShoot(Object* obj)
{
	if (delayTime + player.delay < GetTickCount())
	{
		delayTime = GetTickCount();
		if (player.level == 1)
		{
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x+obj->TransInfo.Scale.x+3, obj->TransInfo.Position.y);
					break;
				}
			}
		}
		else if (player.level == 2)
		{
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y+1);
					break;
				}
			}
		}
		else if (player.level == 3)
		{
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y + 1);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, 
						obj->TransInfo.Position.y + 1,Vector2(1,0.5));
					break;
				}
			}
		}
		else if (player.level == 4)
		{
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateBullet(BulletData[0],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3, obj->TransInfo.Position.y + 1);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateGBullet(BulletData[2],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3,
						obj->TransInfo.Position.y -2);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateGBullet(BulletData[2],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3,
						obj->TransInfo.Position.y + 2);
					break;
				}
			}
		}

		
	}
}

Enemy* CreateEnemy(Enemy* src,int _x,int _y)
{
	Enemy* des = new Enemy;
	des->delay = src->delay;
	des->hp = src->hp;
	des->obj.Info.Color = src->obj.Info.Color;
	for (int i = 0; i < src->obj.TransInfo.Scale.y; i++)
	{
		des->obj.Info.Texture[i] = src->obj.Info.Texture[i];
	}
	des->obj.TransInfo.Scale.x = src->obj.TransInfo.Scale.x;
	des->obj.TransInfo.Scale.y = src->obj.TransInfo.Scale.y;
	des->obj.TransInfo.Rotation.x = src->obj.TransInfo.Rotation.x;
	des->obj.TransInfo.Rotation.y = src->obj.TransInfo.Rotation.y;
	des->obj.TransInfo.Position.x = _x;
	des->obj.TransInfo.Position.y= _y;
	des->obj.Speed = src->obj.Speed;
	des->time = 0;
	des->obj.Info.Option = src->obj.Info.Option;
	return des;
}

void AppearEnemy(Enemy* src)
{
	srand(time(0));
	int _x = rand() % 5 + 145;
	int _y = rand() % 30;
	if (enemyResporn +1000< GetTickCount())
	{
		enemyResporn = GetTickCount();
		for (int i = 0; i < 32; i++)
		{
			if (enemies[i] == nullptr)
			{
				enemies[i] = CreateEnemy(src,_x,_y);
				break;
			}
		}
	}

}

void EnemyShoot(Enemy* enemy)
{
	if (enemy->time+ enemy->delay < GetTickCount())
	{
		enemy->time = GetTickCount();
		if (enemy->obj.Info.Option == 0)
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y);
					eBullets[i]->obj.TransInfo.Rotation = GetDirection(&player.obj, &eBullets[i]->obj);
					break;
				}
			}
		}
		else if (enemy->obj.Info.Option == 1) //2번 적 객체
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y+1);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-0.64, 0.36);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y+1);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, 0);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y+1);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-0.64, -0.36);
					break;
				}
			}
		}
		
	}

}

Vector2 GetDirection(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	float Distance = sqrt((x * x) + (y * y));

	return Vector2(x / Distance, y / Distance);
}

float GetDistance(const Object* _ObjectA, const Object* _ObjectB)
{
	float x = _ObjectA->TransInfo.Position.x - _ObjectB->TransInfo.Position.x;
	float y = _ObjectA->TransInfo.Position.y - _ObjectB->TransInfo.Position.y;

	float Distance = sqrt((x * x) + (y * y));

	return Distance;
}

void EnemyHit()
{
	for (int i = 0; i < 32; i++)
	{
		if (enemies[i])
		{
			for (int j = 0; j < 128; j++)
			{
				if (bullets[j])
				{
					if (Collision(&enemies[i]->obj, &bullets[j]->obj))
					{
						enemies[i]->hp -= 10;
						HitEffect(bullets[j]->obj.TransInfo.Position.x - 3, bullets[j]->obj.TransInfo.Position.y);
						
						delete bullets[j];
						bullets[j] = nullptr;
					}
				}
			}
		}
	}
}

void HitEffect(int _x,int _y)
{
	for (size_t i = 0; i < 32; i++)
	{
		if (hitEffect[i] == nullptr)
		{
			hitEffect[i] = createEffect(hit, _x, _y);
			break;
		}
	}
}


void Enemydied()
{
	for (int i = 0; i < 32; i++)
	{
		if (enemies[i])
		{
			if (enemies[i]->hp <= 0)
			{
				delete enemies[i];
				enemies[i] = nullptr;
				Score += 50;
			}
		}
	}
}

void invokeTem(const Item* item)
{
	//if (item->Info.Option == 0)// 인덱스
		player.level++;
}

void SceneManaer()
{
	switch (SceneState)
	{
	case Scene::Title:
		TitleScene();
		break;
	case Scene::Stage1:
		Stage_ONE();
		break;
	case Scene::Stage2:
		break;
	case Scene::GameClear:
		break;
	}
}

void TitleScene()
{
	int Width = (150 / 2) - (strlen("     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ", 1);
	SetPosition(Width, Height + 2, (char*)"     |  |'  .-.  ''   .-' |  | |  ||  ,'.|  |      |  .--. '|  .--. ''  .-./    ", 2);
	SetPosition(Width, Height + 3, (char*)",--. |  ||  | |  |`.  `-. |  | |  ||  |' '  |      |  '--'.'|  '--' ||  | .---. ", 3);
	SetPosition(Width, Height + 4, (char*)"|  '-'  /'  '-'  '.-'    |'  '-'  '|  | `   |,----.|  |\  \ |  | --' '  '--'  | ", 4);
	SetPosition(Width, Height + 5, (char*)" `-----'  `-----' `-----'  `-----' `--'  `--''----'`--' '--'`--'      `------'  ", 5);

	Sleep(3000);

	SceneState++;
}

void move(Object* obj,Vector2 direction)
{
	obj->TransInfo.Position.x += direction.x * obj->Speed;
	obj->TransInfo.Position.y += direction.y * obj->Speed;
}

void Stage_ONE()
{
	GameTime += 0.08;
	// 계산 하는 부분

	for (int i = 0; i < 128; i++) //총알 이동
	{
		if (bullets[i] && bullets[i]->obj.Info.Color == 5)
		{
			if (bullets[i]->obj.TransInfo.Position.x + 3 > maxWidth ||
				bullets[i]->obj.TransInfo.Position.y - 2 < 0 ||
				bullets[i]->obj.TransInfo.Position.y + 2 > maxHight ||
				bullets[i]->obj.TransInfo.Position.x - 2 <0 )
			{
				delete  bullets[i];
				bullets[i] = nullptr;
			}
			else         //유도미사일
			{
				if(enemies[bullets[i]->tagetIndex])
				move(&bullets[i]->obj, GetDirection(&enemies[bullets[i]->tagetIndex]->obj,&bullets[i]->obj));
				else
				{
					float dis = 0;
					float Min = 0;
					int index = 0;
					for (size_t j = 0; j < 32; j++)
					{
						if (enemies[j])
						{
							dis = GetDistance(&enemies[j]->obj, &bullets[i]->obj);
							if (Min == 0)
								Min = dis;
							if (dis < Min)
							{
								Min = dis;
								index = j;
							}
						}
					}
					bullets[i]->tagetIndex = index;
				}
			}
			
		}
		else if (bullets[i])
		{
			if (bullets[i]->obj.TransInfo.Position.x + 3 > maxWidth ||
				bullets[i]->obj.TransInfo.Position.y-2<0 ||
				bullets[i]->obj.TransInfo.Position.y+2>maxHight)
			{
				delete  bullets[i];
				bullets[i] = nullptr;
			}
			else
			{
				move(&bullets[i]->obj, bullets[i]->obj.TransInfo.Rotation);
			}
		}
	}

	for (int i = 0; i < 128; i++) //적 총알 이동
	{

		if (eBullets[i])
		{
			if (eBullets[i]->obj.TransInfo.Position.x -3 < 0 ||
				eBullets[i]->obj.TransInfo.Position.y - 2 < 0 ||
				eBullets[i]->obj.TransInfo.Position.y+2>maxHight)
			{
				delete  eBullets[i];
				eBullets[i] = nullptr;
			}
			else
			{
				move(&eBullets[i]->obj,eBullets[i]->obj.TransInfo.Rotation);
			}
		}
	}


	for (size_t i = 0; i < 32; i++) //에너미 이동
	{
		if (enemies[i])
		{
			if (enemies[i]->obj.TransInfo.Position.x < 5)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
			else
			{
				move(&enemies[i]->obj,enemies[i]->obj.TransInfo.Rotation);
			}
		}
	}

	for (size_t i = 0; i < 32; i++) //이펙트 계산
	{
		
		if (hitEffect[i])
		{
			if (hitEffect[i]->time + 300 < GetTickCount())
			{
				delete hitEffect[i];
				hitEffect[i] = nullptr;
			}
		}
	}

	if (appearItem)
	{
		if (appearItem->TransInfo.Position.x < 2)
		{
			delete appearItem;
			appearItem = nullptr;
		}
		else if (Collision(&player.obj,appearItem))
		{
			invokeTem(appearItem);
			delete appearItem;
			appearItem = nullptr;
		}
		else
		{
			move(appearItem, Vector2(-1, 0));
		}
	}

	EnemyHit();
	Enemydied();

	if (itemTimer == 0)
		itemTimer = GetTickCount();


	if (appearItem == nullptr && itemTimer+10000<GetTickCount())
	{
		itemTimer = GetTickCount();
		appearItem = CreateItem(ItemData[0], 140, 15);
	}

	if (GameTime > 15)
	{
		AppearEnemy(enemy2);
	}
	else
	{
		AppearEnemy(enemy1);
	}
	
	for (int i = 0; i < 32; i++)
	{
		if (enemies[i])
		{
			EnemyShoot(enemies[i]);
		}
	}

	// 입력 받는 부분
	UpdateInput();

	
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		PlayerShoot(&player.obj);
	}

	 //*****************콘솔 화면에 표시되는 부분*********

	OnDrawText(&player.obj);

	for (int i = 0; i < 128; i++)
	{
		if (bullets[i])
		{
			OnDrawText(&bullets[i]->obj);
		}
	}
			
	for (size_t i = 0; i < 32; i++)
	{
		if (enemies[i])
		{
			OnDrawText(&enemies[i]->obj);
		}
	}

	for (int i = 0; i < 128; i++)
	{
		if (eBullets[i])
		{
			OnDrawText(&eBullets[i]->obj);
		}
	}

	for (int i = 0; i < 32; i++)
	{
		if (hitEffect[i])
		{
			OnDrawText(&hitEffect[i]->obj);
		}
	}

	if (appearItem)
	{
		OnDrawText(appearItem);
	}
	
	//**********      UI 부분
	SetTextColor(15); SetCursorPosition(maxWidth/2 - strlen("Score:"), 2); cout << "Score:" << Score;
}


