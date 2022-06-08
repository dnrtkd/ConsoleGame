#pragma once

static int SceneState = 0;

static Player player;

static Bullet* BulletData[4];
static Enemy* EnemyData[3];
static Effect* EffectData[2];
static Item* ItemData[3];

static int Score=0;

static Bullet* bullets[128] = { nullptr };
static Bullet* eBullets[128] = { nullptr };
static Effect* hitEffect[32] = { nullptr };
static Enemy* enemies[32] = { nullptr };
static Item* appearItem = nullptr;
static Effect* hit;


static int maxWidth = 150;
static int maxHight = 30;

//������ ����Ҷ� ���� �Լ�
static long delayTime = 0;
static long enemyResporn = 0;
static long itemTimer = 0;

static double GameTime = 0;

static int Life = 3;

static Event* Even[20] = { nullptr };
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

void EventAppearEnemy(Event* even, int _delay, int _Index_E, int creationWay = 0, float posiY=0);

Event* Initi_Even(int _count);
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
		player.obj.TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN) && player.obj.TransInfo.Position.y < 26)
		player.obj.TransInfo.Position.y += 1;

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
	des->time = 0;
	des->obj.Info.Option = src->obj.Info.Option;
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
		else if (enemy->obj.Info.Option == 1) //2�� �� ��ü
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
				delete enemies[i];
				enemies[i] = nullptr;
				Score += 50;
			}
		}
	}
}

void invokeTem(const Item* item)
{
	if (item->Info.Option == 0 && player.level < 4) //����
		player.level++;
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

//�����ϰ����ϴ� ���� ���� , ���� ������ ,���� ���� , ������
//������ �Ű������� ���͵��� ��������� ���� 
void EventAppearEnemy(Event* even, int _delay, int _Index_E, int creationWay, float posiY )
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
		srand(time(0));

		posiY = rand() % 27 + 2;
	}

	float posiX = 135;//maxWidth - EnemyData[_Index_E]->obj.TransInfo.Scale.x;

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
	// ��� �ϴ� �κ�

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

	EnemyHit();
	Enemydied();

	if (itemTimer == 0)
		itemTimer = GetTickCount();


	if (appearItem == nullptr && itemTimer+10000<GetTickCount())
	{
		itemTimer = GetTickCount();
		appearItem = CreateItem(ItemData[0], 140, 15);
	}

	if (GameTime > 5)
	{
		if (Even[0] == nullptr)
			Even[0] = new Event(9);
		if(Even[0]->use == false)
		EventAppearEnemy(Even[0],1,0,1,2);
	}
	if(GameTime > 10)
	{
		if (Even[1] == nullptr)
			Even[1] = new Event(4);
		if (Even[1]->use == false)
			EventAppearEnemy(Even[1], 2, 1, 3);
	}
	if (GameTime > 20)
	{
		if (Even[2] == nullptr)
			Even[2] = new Event(6);
		if (Even[2]->use == false)
			EventAppearEnemy(Even[2], 2, 2, 2,25);
	}
	if (GameTime > 30)
	{
		if (Even[3] == nullptr)
			Even[3] = new Event(9);
		if (Even[3]->use == false)
			EventAppearEnemy(Even[3], 1, 2, 3);
	}

	if (GameTime > 55)
	{
		//AppearEnemy(EnemyData[2]);
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
	SetTextColor(15); SetCursorPosition(5, 28); cout << "LIFE:"; for (size_t i = 0; i < player.chance; i++) { cout << " ��"; }

}


