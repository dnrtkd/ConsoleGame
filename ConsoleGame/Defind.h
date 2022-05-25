#pragma once

static int SceneState = 0;

static Player player;

const char* bulletTexture = "*";

static Object* bullets[128] = { nullptr };

static int maxWidth = 150;
static int maxHight = 50;

static long delayTime = 0;

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
Object* CreateBullet(const int _x, const int _y);

Object* Shoot(Object* obj);

// ** 키입력 
void UpdateInput();

void SceneManaer();

void SetPosition(int _x, int _y, char* _str, int _Color);

void Stage_ONE();

void TitleScene();

Object* PlayerShoot(Object* obj);


// ** 함수 정의부

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
	// ** (_Object->TransInfo.Position.x + _Object->TransInfo.Scale.x)   : 우측
	// ** _Object->TransInfo.Position.x   : 좌측
	// ** Rect 충돌시 우측선은 항상 크다.
	if ((_ObjectA->TransInfo.Position.x + _ObjectA->TransInfo.Scale.x) > _ObjectB->TransInfo.Position.x &&
		(_ObjectB->TransInfo.Position.x + _ObjectB->TransInfo.Scale.x) > _ObjectA->TransInfo.Position.x &&
		_ObjectA->TransInfo.Position.y == _ObjectB->TransInfo.Position.y)
	{
		OnDrawText((char*)"충돌 입니다.", 55, 0, 14);
		return true;
	}
	else return false;
		
}

Object* CreateBullet(const int _x, const int _y)
{
	// ** Bullet를 생성 및 동적할당.
	Object* _Object = new Object;

	// ** 초기화 시 _x 와 _y 는 const 값으로 받아오면, 함수 내부에서 다른 값으로 변경 되지 않기때문에 안전하다.
	Initialize(_Object, (char*)"장풍!", _x + 2, _y);

	return _Object;
}

void UpdateInput()
{
	// ** [상] 키를 입력받음.
	if (GetAsyncKeyState(VK_UP))
		player.obj.TransInfo.Position.y -= 1;

	// ** [하] 키를 입력받음.
	if (GetAsyncKeyState(VK_DOWN))
		player.obj.TransInfo.Position.y += 1;

	// ** [좌] 키를 입력받음.
	if (GetAsyncKeyState(VK_LEFT))
		player.obj.TransInfo.Position.x -= 1;

	// ** [우] 키를 입력받음.
	if (GetAsyncKeyState(VK_RIGHT))
		player.obj.TransInfo.Position.x += 1;
}
//에너미나 플레이어를 인수로 받고 불렛을 반환
Object* PlayerShoot(Object* obj)
{
	Object* bullet = new Object;


	// ** 초기화 시 _x 와 _y 는 const 값으로 받아오면, 함수 내부에서 다른 값으로 변경 되지 않기때문에 안전하다.
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
	
	// 계산 하는 부분

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

	

	// 입력 받는 부분
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
	// 콘솔 화면에 표시되는 부분

	OnDrawText(&player.obj);

	for (int i = 0; i < 128; i++)
	{
		if (bullets[i])
		{
			OnDrawText(bullets[i]);
		}
	}
			
	
	

}
