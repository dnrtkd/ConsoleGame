#pragma once

static int SceneState = 0;

static Player player;

static Bullet* BulletData[4];
static Enemy* EnemyData[4];
static Effect* EffectData[2];
static Item* ItemData[3];

static int Score=0;

static Bullet* bullets[128] = { nullptr };
static Bullet* eBullets[128] = { nullptr };
static Effect* hitEffect[32] = { nullptr };
static Enemy* enemies[32] = { nullptr };
static Item* appearItem = nullptr;
static Effect* hit;

static Vector2 ScreenPosition;

static Enemy* Boss=nullptr;

static int maxWidth = 150;
static int maxHight = 30;

//������ ����Ҷ� ���� �Լ�
static long delayTime = 0;
static long enemyResporn = 0;
static long itemTimer = 0;

static long TitleTimer = 0; //Ÿ��Ʋ ������ ���̴� Ÿ�̸�

static long titleTimer = 0;

static int ClearUi_Score = 0;

static double GameTime = 0;

static int Life = 3;

static Event* Even[20] = { nullptr };
static LargeText* LevelUp = nullptr;

static bool LevelUpSwitch = false;

static Object* Wall[4] = { nullptr };

static Object* Walls[16] = { nullptr };

static long WallCreatTimer = 0;

static Object* Moon = nullptr;

static LargeText* pressStart = nullptr;



// ** �ʱ�ȭ �Լ� (����Ʈ �Ű����� : int _Value = 0)
void Initialize(Object* _Object, char* _Texture, int _PosX = 0, int _PosY = 0);

// ** �̸��� �����ϴ� �Լ�
char* SetName();

// ** Ŀ���� ��ġ�� ����

void SetCursorPosition(const int _x, const int _y);

// ** Text�� ���� ������.
void SetTextColor(const int _Color);

// ** ����� Text�� ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const char* _str, const int _x, const int _y, const int _Color = 15);

// ** ����� ������ ��ġ�� ������ �������ش�. [Color ���� �⺻�� : ���(15)]
void OnDrawText(const int _Value, const int _x, const int _y, const int _Color = 15);

// ** Ŀ���� ���̰ų�(true) / �Ⱥ��̰�(false) �������.
void HideCursor(const bool _Visible);

// ** �浹ó���� ��.
bool Collision(const Object* _ObjectA, const Object* _ObjectB);

// ** Bullet�� ������.
Bullet* CreateBullet(Bullet *bul, float _x, float _Y);

void PlayerShoot(Object* obj);

// ** Ű�Է� 
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

Bullet* CreateGBullet(Bullet* src, float _x, float _y);//����ź

Bullet* CreateBullet(Bullet* src, float _x, float _y, Vector2 dir);

void move(Object* obj, Vector2 direction);

void invokeTem(const Item* item);

Item* CreateItem(Item* src, int x, int y);

void EventAppearEnemy(Event* even, float _delay, int _Index_E, int creationWay, float posiY = 0);

Event* Initi_Even(int _count);
void EventUi(LargeText* text, int delay, int _x, int _y, bool* _switch);

Object* CreateWall(const Object* src, int posiX, int posiY);
// ** �Լ� ���Ǻ�
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
	item->Info.Option = src->Info.Option;
	return item;
}

void SetPosition(int _x, int _y, char* _str, int _Color)
{
	COORD Pos = { (SHORT)_x,(SHORT)_y }; // �ܼ� ������

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);//Ŀ�� ��ġ �̵�
	SetTextColor(_Color);

	printf_s("%s", _str);
}


void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY)
{
	// ** 3�� ������. 
	// ** _Name �� ���� nullptr �̶��  SetName() �Լ��� �����ϰ� �ƴ϶��,
	// ** _Name�� ���� �״�� �����Ѵ�.
	_Object->Info.Texture [0]= (_Texture == nullptr) ? SetName() : _Texture;

	// ** �̵��ӵ� 
	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector2(_PosX, _PosY);

	// ** ȸ���� (���� ������ ����.)
	_Object->TransInfo.Rotation = Vector2(0, 0);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector2(
		strlen(_Object->Info.Texture[0]), 1);

	_Object->Info.Color = 15;
	_Object->TransInfo.Scale.y = 1;
}

char* SetName()
{
	// ** ���ڿ��� �Է� ���� �ӽ� ������ �迭�� �����Ѵ�. (������ �������� �ٷ� �Է¹����� ����.)
	char Buffer[128] = "";

	// ** �̸� �Է�
	cout << "�Է� : "; cin >> Buffer;

	// ** ������ ������ �����Ͽ� �Է¹��� ���ڿ��� ���̸�ŭ ũ�⸦ �Ҵ���.
	//char* pName = (char*)malloc(strlen(Buffer) + 1);
	char* pName = new char[strlen(Buffer) + 1];

	// ** �Է¹��� ���ڿ��� ������ ������.
	strcpy(pName, Buffer);

	// ** ��ȯ
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

void OnDrawText(const Object* obj)
{
	Vector2 Posi = { obj->TransInfo.Position.x-ScreenPosition.x ,
		obj->TransInfo.Position.y- ScreenPosition.y};

	if (Posi.x > maxWidth-1 ||
		Posi.x + obj->TransInfo.Scale.x<0 ||
		Posi.y>maxHight ||
		Posi.y + obj->TransInfo.Scale.y < 0) return;

	int sizeY = (int)obj->TransInfo.Scale.y;
	int sizeX = (int)obj->TransInfo.Scale.x;

	

	SetTextColor(obj->Info.Color);

	for (size_t i = 0; i < sizeY; i++)
	{
		char temp[128];

		int x = (int)Posi.x;
		int y = (int)Posi.y;

		if (x < 0)
		{
			int start = -x;
			for (size_t j = start; j < sizeX; j++)
			{
				temp[j - start] = obj->Info.Texture[i][j];
			}
			temp[sizeX - start] = '\0';
			x = 0;
		}
		else if (x + sizeX > maxWidth && x < maxWidth )
		{
			for (size_t j = 0; j < maxWidth - x; j++)
			{
				temp[j] = obj->Info.Texture[i][j];
			}
			temp[maxWidth - x] = '\0';
		}
		else
			strcpy(temp, obj->Info.Texture[i]);

		if (y + i < 30 && y + i >= 0)
		{
			SetCursorPosition(x, y + i);
			cout << temp;
		}
	}
}

void ClearUi(int _x, int _y);

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
	// ** (_Object->TransInfo.Position.x + _Object->TransInfo.Scale.x)   : ����
	// ** _Object->TransInfo.Position.x   : ����
	// ** Rect �浹�� �������� �׻� ũ��.
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
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP) && player.obj.TransInfo.Position.y > 2)
	{
		player.obj.TransInfo.Position.y -= 1;
		//ScreenPosition.y -= 1;
	}
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN) && player.obj.TransInfo.Position.y < 28)
	{
		player.obj.TransInfo.Position.y += 1;
		//ScreenPosition.y+=1;
	}

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT) && player.obj.TransInfo.Position.x > 1)
		player.obj.TransInfo.Position.x -= player.obj.Speed;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_RIGHT) && player.obj.TransInfo.Position.x < 148)
		player.obj.TransInfo.Position.x += player.obj.Speed;

	
}
//���ʹ̳� �÷��̾ �μ��� �ް� �ҷ��� ��ȯ
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
					bullets[i] = CreateGBullet(BulletData[3],
						obj->TransInfo.Position.x + obj->TransInfo.Scale.x + 3,
						obj->TransInfo.Position.y -2);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = CreateGBullet(BulletData[3],
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
	des->timer = 0;
	des->obj.Info.Option = src->obj.Info.Option;
	des->count = src->count;
	des->lateTime = src->lateTime;
	des->lateTimer = 0;
	return des;
}

void AppearEnemy(Enemy* src)
{
	srand(time(0));
	int _x = rand() % 5 + 140;
	int _y = rand() % 28+1;
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
	if (enemy->count == 0)
	{
		enemy->obj.Info.Color = 14;
		enemy->lateTimer+= + 0.08; // ������ ��ŭ ������
		if (enemy->lateTimer > enemy->lateTime)
		{
			if (enemy->obj.Info.Option == 1)
				enemy->count = 5;
			else if (enemy->obj.Info.Option == 0)
				enemy->count = 3;
			else if (enemy->obj.Info.Option == 2)
				enemy->count = 3;
			else if (enemy->obj.Info.Option == 3)
				enemy->count = EnemyData[3]->count;

			enemy->lateTimer = 0;
		}
	}
	if (enemy->timer+ enemy->delay < GetTickCount() && enemy->count != 0)
	{
		enemy->obj.Info.Color = 15;
		enemy->timer = GetTickCount();
		if (enemy->obj.Info.Option == 0)
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr  )
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y);
					eBullets[i]->obj.TransInfo.Rotation = GetDirection(&player.obj, &eBullets[i]->obj);

					break;
				}
			}
		}
		else if (enemy->obj.Info.Option == 1) //2�� �� ��ü
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr )
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, -0.25+enemy->count* 0.05);
					

					break;
				}
			}
		}

		else if (enemy->obj.Info.Option == 2) //2�� �� ��ü
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[2], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, 0);
					break;
				}
			}
		}
		else if (enemy->obj.Info.Option == 3) //2�� �� ��ü
		{
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y+1);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, 0.25 - enemy->count * 0.05);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y + 2);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, 0);
					break;
				}
			}
			for (int i = 0; i < 128; i++)
			{
				if (eBullets[i] == nullptr)
				{
					eBullets[i] = CreateBullet(BulletData[1], enemy->obj.TransInfo.Position.x - 2,
						enemy->obj.TransInfo.Position.y + 3);
					eBullets[i]->obj.TransInfo.Rotation = Vector2(-1, -0.25 + enemy->count * 0.05);
					break;
				}
			}

			if (enemy->count % 10 == 0)
			{
				if (enemy->obj.TransInfo.Rotation.y == 0)
					enemy->obj.TransInfo.Rotation.y == 1;

				enemy->obj.TransInfo.Rotation.y *= -1;

			}
				
		}

		enemy->count--;
		
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
			hitEffect[i] = createEffect(EffectData[0], _x, _y);
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
				if (enemies[i]->obj.Info.Option == 3)
				{
					ClearUi(69,12);
				}
				else
				{
					delete enemies[i];
					enemies[i] = nullptr;
					Score += 50;
				}
			}
		}
	}
}

void invokeTem(const Item* item)
{
	if (item->Info.Option == 0 && player.level < 4) //����
	{
		player.level++;
		LevelUpSwitch = true;
	}
	else if (item->Info.Option == 1) //���
		player.chance++;
	else if (item->Info.Option == 2) //��ź
	{

	}
		
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
	if (titleTimer == 0)
	{
		titleTimer = GetTickCount();
	}

	int Width = (150 / 2) - (strlen("     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ", 1);
	SetPosition(Width, Height + 2, (char*)"     |  |'  .-.  ''   .-' |  | |  ||  ,'.|  |      |  .--. '|  .--. ''  .-./    ", 2);
	SetPosition(Width, Height + 3, (char*)",--. |  ||  | |  |`.  `-. |  | |  ||  |' '  |      |  '--'.'|  '--' ||  | .---. ", 3);
	SetPosition(Width, Height + 4, (char*)"|  '-'  /'  '-'  '.-'    |'  '-'  '|  | `   |,----.|  |\  \ |  | --' '  '--'  | ", 4);
	SetPosition(Width, Height + 5, (char*)" `-----'  `-----' `-----'  `-----' `--'  `--''----'`--' '--'`--'      `------'  ", 5);

	SetCursorPosition((150 / 2) - (strlen("PRESS THE START!") / 2), Height + 7);

	if (titleTimer + 3000 > GetTickCount()) return;

	if (pressStart == nullptr) //pressStart �ʱ�ȭ
	{
		pressStart = new LargeText;
		pressStart->texture[0] = (char*)"PRESS THE ENTER!";
		pressStart->lateTimer = GetTickCount();
		pressStart->timer = GetTickCount();
		pressStart->color = 15;
	}

	if (pressStart->timer + 300 > GetTickCount())
	{
		SetTextColor(15);
		SetCursorPosition((150 / 2) - (strlen(pressStart->texture[0]) / 2), Height + 7);
		cout << pressStart->texture[0];
	}
	else if (pressStart->timer + 600 < GetTickCount())
	{
		pressStart->timer = GetTickCount();
	}

	if(GetAsyncKeyState(13))
		SceneState++;

	
}

void move(Object* obj,Vector2 direction)
{
	obj->TransInfo.Position.x += direction.x * obj->Speed;
	obj->TransInfo.Position.y += direction.y * obj->Speed;
}

//�����ϰ����ϴ� ���� ���� , ���� ������ ,���� ���� , ������
//������ �Ű������� ���͵��� ��������� ���� 
void EventAppearEnemy(Event* even, float _delay, int _Index_E, int creationWay, float posiY )
{
	if (even->count == even->max)  //
	{
		even->use = true; //�̹� ���� �̺�Ʈ
	}

	if (creationWay==1) //�Ʒ��� ���ʴ�� ����
	{
		posiY += even->count*2;
	}
	else if (creationWay == 2) // ���� ���ʴ�� ����
	{
		posiY -= even->count * 2;
	}
	else if (creationWay == 3) //���� ����
	{
		srand(GameTime*GameTime);

		posiY = rand() % 22 + 2;
	}

	float posiX = 160;//maxWidth - EnemyData[_Index_E]->obj.TransInfo.Scale.x;

	if (even->time+ _delay*1000 < GetTickCount())
	{
		even->time = GetTickCount();

		for (int i = 0; i < 32; i++)
		{
			if (enemies[i] == nullptr)
			{
				enemies[i] = CreateEnemy(EnemyData[_Index_E], posiX, posiY);
				even->count++;
				break;
			}
		}
	}
}

Event* Initi_Even(int _max)
{
	Event* temp = new Event;
	temp->max = _max;
	temp->time = GetTickCount();
	temp->use = false;
	temp->count = 0;

	return temp;
}


void Stage_ONE()
{
	GameTime += 0.08;

	if (WallCreatTimer == 0)
		WallCreatTimer = GetTickCount();

	for (int i = 0; i < 128; i++) //�Ѿ� �̵�
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
			else         //�����̻���
			{
				if(enemies[bullets[i]->tagetIndex])
				move(&bullets[i]->obj, GetDirection(&enemies[bullets[i]->tagetIndex]->obj,&bullets[i]->obj));
				else
				{
					move(&bullets[i]->obj,Vector2(0.5,0));
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

	for (int i = 0; i < 128; i++) //�� �Ѿ� �̵�
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

	for (size_t i = 0; i < 32; i++) //���ʹ� �̵�
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

	for (size_t i = 0; i < 32; i++) //����Ʈ ���
	{
		
		if (hitEffect[i])
		{
			if (hitEffect[i]->time + 100 < GetTickCount())
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

	for (size_t i = 0; i < 16; i++)
	{
		if (Walls[i])
		{
			if (Walls[i]->TransInfo.Position.x + Walls[i]->TransInfo.Scale.x < 0)
			{
				delete Walls[i];
				Walls[i] = nullptr;
			}
			else 
			{
				move(Walls[i], Vector2(-1, 0));
			}
		}
	}

	if (Moon) //���� �̵�
	{
		if (Moon->TransInfo.Position.x + Moon->TransInfo.Scale.x < 0)
		{
			delete Moon; Moon = nullptr;
		}
		else
		{
			move(Moon,Vector2(-1,0));
		}
	}

	if (WallCreatTimer + 2000 < GetTickCount()) // �� ����
	{
		WallCreatTimer = GetTickCount();
		for (size_t i = 0; i < 16; i++)
		{
			if (Walls[i] == nullptr)
			{
				srand(GetTickCount() * GetTickCount());
				Walls[i] = CreateWall(Wall[rand()%2+1], 154, 26);
				break;
			}
		}
	}

	if (Moon == nullptr)  // ���� ����
	{
		srand(GetTickCount()* GetTickCount());
		int y= rand() % 20 + 2;
		Moon = CreateWall(Wall[3], 152, y);
	}

	
	EnemyHit();
	Enemydied();

	for (size_t i = 0; i < 128; i++)
	{
		if (eBullets[i])
			if (Collision(&player.obj, &eBullets[i]->obj))
			{
				if (player.chance >= 0)
					player.chance--;
				else
					SceneState++;
			}		
	}

	if (itemTimer == 0)
		itemTimer = GetTickCount();


	if (appearItem == nullptr && itemTimer+15000<GetTickCount())
	{
		itemTimer = GetTickCount();
		appearItem = CreateItem(ItemData[0], 160, 15);
	}

	/*if (GameTime > 5)
	{
		if (Even[0] == nullptr)
			Even[0] = new Event(5);
		if(Even[0]->use == false)
		EventAppearEnemy(Even[0], 1, 0, 1, 4);
	}
	if(GameTime > 15)
	{
		if (Even[1] == nullptr)
			Even[1] = new Event(5);
		if (Even[1]->use == false)
			EventAppearEnemy(Even[1], 1, 0, 3);
	}
	if (GameTime > 30)
	{
		if (Even[2] == nullptr)
			Even[2] = new Event(3);
		if (Even[2]->use == false)
			EventAppearEnemy(Even[2], 2, 1, 2,20);
	}
	if (GameTime > 40)
	{
		if (Even[3] == nullptr)
			Even[3] = new Event(6);
		if (Even[3]->use == false)
			EventAppearEnemy(Even[3], 1, 0, 1,4);
	}

	if (GameTime > 55)
	{
		if (Even[4] == nullptr)
			Even[4] = new Event(3);
		if (Even[4]->use == false)
			EventAppearEnemy(Even[4], 1, 1, 1, 4);
	}*/

	if (GameTime > 5)
	{
		if (Boss == nullptr)
		{
			for (size_t i = 0; i < 32; i++)
			{
				if (enemies[i] == nullptr)
				{
					enemies[i] = CreateEnemy(EnemyData[3], 152, 12);
					Boss = enemies[i];
					break;
				}
			}
		}
	}

	if (Boss)
	{
		if (Boss->obj.TransInfo.Position.x + Boss->obj.TransInfo.Scale.x < 147)
		{
			Boss->obj.TransInfo.Rotation.x = 0;
			Boss->obj.TransInfo.Rotation.y = 0;

		}
	}

	

	
	for (int i = 0; i < 32; i++)
	{
		if (enemies[i])
		{
			EnemyShoot(enemies[i]);
		}
	}

	// �Է� �޴� �κ�
	UpdateInput();

	
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		PlayerShoot(&player.obj);
	}

	 //*****************�ܼ� ȭ�鿡 ǥ�õǴ� �κ�*********
	if (GameTime < 3)
	{
		int x = 45;
		int y = 12;
		SetTextColor(12); SetCursorPosition(x, y);
		cout << " _______  _______  _______  _______  _______    _______  ____  ";
		SetCursorPosition(x, y + 1);
		cout << "|       ||       ||   _   ||       ||       |  |  _    ||    | ";
		SetCursorPosition(x, y + 2);
		cout << "|  _____||_     _||  |_|  ||    ___||    ___|  | | |   | |   | ";
		SetCursorPosition(x, y + 3);
		cout << "| |_____   |   |  |       ||   | __ |   |___   | | |   | |   | ";
		SetCursorPosition(x, y + 4);
		cout << "|_____  |  |   |  |       ||   ||  ||    ___|  | |_|   | |   | ";
		SetCursorPosition(x, y + 5);
		cout << " _____| |  |   |  |   _   ||   |_| ||   |___   |       | |   | ";
		SetCursorPosition(x, y + 6);
		cout << "|_______|  |___|  |__| |__||_______||_______|  |_______| |___| ";
	}

	if(LevelUpSwitch)
	EventUi(LevelUp, 3, player.obj.TransInfo.Position.x-5, player.obj.TransInfo.Position.y-6, &LevelUpSwitch);

	for (size_t i = 0; i < 16; i++)
	{
		if (Walls[i])
		OnDrawText(Walls[i]);
	}

	if (Moon)
	{
		OnDrawText(Moon);
	}

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

	
	
	//**********      UI �κ�
	SetTextColor(15); SetCursorPosition(maxWidth/2 - strlen("Score:"), 2); cout << "Score:" << Score;
	SetTextColor(15); SetCursorPosition(5, 29); cout << "LIFE:"; for (size_t i = 0; i < player.chance; i++) { cout << " ��"; }


}

Object* CreateWall(const Object* src,int posiX, int posiY)
{
	Object* temp = new Object;
	temp->TransInfo.Scale.y = src->TransInfo.Scale.y;
	temp->TransInfo.Scale.x = src->TransInfo.Scale.x;
	for (size_t i = 0; i < src->TransInfo.Scale.y; i++)
	{
		temp->Info.Texture[i] = src->Info.Texture[i];
	}
	temp->Info.Option = src->Info.Option;
	temp->TransInfo.Position.x = posiX;
	temp->TransInfo.Position.y = posiY;
	temp->Info.Color = src->Info.Color;
	temp->Speed = src->Speed;

	return temp;
}




void EventUi(LargeText* text,int delay,int _x, int _y,bool* _switch)

{
	if (text->timer == 0)
		text->timer = GetTickCount();
	if (text->timer + delay * 1000 < GetTickCount())
	{
		*_switch = false;
		text->timer = 0;
		return;
	}

	int sizeY = 5;
	int posiX = _x;

	for (size_t i = 0; i < sizeY; i++)
	{
		char temp[128];
		if (_x < 0)
		{
			int start = -_x;
			for (size_t j = start; j < strlen(text->texture[0]); j++)
			{
				temp[j - start] = text->texture[i][j];
			}
			temp[strlen(text->texture[0])-start] = '\0';
			posiX = 0;
		}
		else if(_x+strlen(text->texture[i])>maxWidth && _x<maxWidth)
		{
			for (size_t j = 0; j < maxWidth-_x; j++)
			{
				temp[j] = text->texture[i][j];
			}
			temp[maxWidth - _x] = '\0';
		}
		else
		strcpy(temp, text->texture[i]);
		
		if (_y + i<30 && _y+i>=0)
		{
			SetCursorPosition(posiX, _y + i);
			cout << temp;
		}
	}
}

void ClearUi(int _x, int _y)
{
	int heightSize = 5;

	if (ClearUi_Score != Score)
		ClearUi_Score++;
	else if (GameTime > 0)
	{
		ClearUi_Score -= 50;
		GameTime -= 1;
	}
		
	for (size_t i = 0; i < heightSize; i++)
	{
		SetCursorPosition(_x, _y+i);  cout << "                                  ";
	}

	for (size_t i = 0; i < heightSize; i++)
	{
		SetCursorPosition(_x, _y + i);
		if (i == 0 || i == heightSize-1)
			cout << "-------------------------------";

		else
			cout << "|                             |";
	}
	
	SetCursorPosition(_x + 3, _y+1); cout <<"����     : " << ClearUi_Score;

	SetCursorPosition(_x + 3, _y + 3); cout << "���ӽð� : " << int(GameTime);
	
}