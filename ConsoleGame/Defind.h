#pragma once

static int SceneState = 0;

static Player player;

const char* bulletTexture = "*";

static Object* bullets[128] = { nullptr };

static int maxWidth = 150;
static int maxHight = 50;

static long delayTime = 0;

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
Object* CreateBullet(const int _x, const int _y);

Object* Shoot(Object* obj);

// ** Ű�Է� 
void UpdateInput();

void SceneManaer();

void SetPosition(int _x, int _y, char* _str, int _Color);

void Stage_ONE();

void TitleScene();

Object* PlayerShoot(Object* obj);


// ** �Լ� ���Ǻ�

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
		cout << obj->Info.Texture[i];
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
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
	{
		OnDrawText((char*)"�浹 �Դϴ�.", 55, 0, 14);
		return true;
	}
	else return false;
		
}

Object* CreateBullet(const int _x, const int _y)
{
	// ** Bullet�� ���� �� �����Ҵ�.
	Object* _Object = new Object;

	// ** �ʱ�ȭ �� _x �� _y �� const ������ �޾ƿ���, �Լ� ���ο��� �ٸ� ������ ���� ���� �ʱ⶧���� �����ϴ�.
	Initialize(_Object, (char*)"��ǳ!", _x + 2, _y);

	return _Object;
}

void UpdateInput()
{
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP))
		player.obj.TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN))
		player.obj.TransInfo.Position.y += 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT))
		player.obj.TransInfo.Position.x -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_RIGHT))
		player.obj.TransInfo.Position.x += 1;
}
//���ʹ̳� �÷��̾ �μ��� �ް� �ҷ��� ��ȯ
Object* PlayerShoot(Object* obj)
{
	Object* bullet = new Object;


	// ** �ʱ�ȭ �� _x �� _y �� const ������ �޾ƿ���, �Լ� ���ο��� �ٸ� ������ ���� ���� �ʱ⶧���� �����ϴ�.
	Initialize(bullet, (char*)"*", obj->TransInfo.Position.x+ 8, obj->TransInfo.Position.y);

	return bullet;
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
	int Width = (120 / 2) - (strlen("     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ") / 2);
	int Height = 10;

	SetPosition(Width, Height + 1, (char*)"     ,--. ,-----.  ,---.  ,--. ,--.,--.  ,--.      ,------. ,------.  ,----.    ", 1);
	SetPosition(Width, Height + 2, (char*)"     |  |'  .-.  ''   .-' |  | |  ||  ,'.|  |      |  .--. '|  .--. ''  .-./    ", 2);
	SetPosition(Width, Height + 3, (char*)",--. |  ||  | |  |`.  `-. |  | |  ||  |' '  |      |  '--'.'|  '--' ||  | .---. ", 3);
	SetPosition(Width, Height + 4, (char*)"|  '-'  /'  '-'  '.-'    |'  '-'  '|  | `   |,----.|  |\  \ |  | --' '  '--'  | ", 4);
	SetPosition(Width, Height + 5, (char*)" `-----'  `-----' `-----'  `-----' `--'  `--''----'`--' '--'`--'      `------'  ", 5);

	Sleep(3000);

	SceneState++;
}

void Stage_ONE()
{
	
	// ��� �ϴ� �κ�

	for (int i = 0; i < 128; i++)
	{

		if (bullets[i])
		{
			if (bullets[i]->TransInfo.Position.x + 3 > maxWidth)
			{
				delete  bullets[i];
				bullets[i] = nullptr;
			}
			else
			{
				bullets[i]->TransInfo.Position.x += 2;
			}
		}
	}

	

	// �Է� �޴� �κ�
	UpdateInput();

	
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (delayTime + player.delay < GetTickCount())
		{
			delayTime = GetTickCount();
			for (int i = 0; i < 128; i++)
			{
				if (bullets[i] == nullptr)
				{
					bullets[i] = Shoot(&player.obj);
					break;
				}
			}
		}
	}
	// �ܼ� ȭ�鿡 ǥ�õǴ� �κ�

	OnDrawText(&player.obj);

	for (int i = 0; i < 128; i++)
	{
		if (bullets[i])
		{
			OnDrawText(bullets[i]);
		}
	}
			
	
	

}
