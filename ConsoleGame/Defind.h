#pragma once

static int SceneState = 0;

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

// ** Ű�Է� 
void UpdateInput(Object* _Object);

void SceneManaer();







// ** �Լ� ���Ǻ�


void Initialize(Object* _Object, char* _Texture, int _PosX, int _PosY)
{
	// ** 3�� ������. 
	// ** _Name �� ���� nullptr �̶��  SetName() �Լ��� �����ϰ� �ƴ϶��,
	// ** _Name�� ���� �״�� �����Ѵ�.
	_Object->Info.Texture = (_Texture == nullptr) ? SetName() : _Texture;

	// ** �̵��ӵ� 
	_Object->Speed = 0;

	// ** ��ǥ��
	_Object->TransInfo.Position = Vector2(_PosX, _PosY);

	// ** ȸ���� (���� ������ ����.)
	_Object->TransInfo.Rotation = Vector2(0, 0);

	// ** ũ�Ⱚ
	_Object->TransInfo.Scale = Vector2(
		strlen(_Object->Info.Texture), 1);
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

void UpdateInput(Object* _Object)
{
	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_UP))
		_Object->TransInfo.Position.y -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_DOWN))
		_Object->TransInfo.Position.y += 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_LEFT))
		_Object->TransInfo.Position.x -= 1;

	// ** [��] Ű�� �Է¹���.
	if (GetAsyncKeyState(VK_RIGHT))
		_Object->TransInfo.Position.x += 1;
}

void SceneManaer()
{
	switch (SceneState)
	{
	case Scene::Title:
		break;
	case Scene::Menu:
		break;
	case Scene::Battle:
		break;
	case Scene::GameClear:
		break;
	}
}

void TitleScene()
{

}