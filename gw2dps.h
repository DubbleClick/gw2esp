#ifndef GW2DPS_H
#define GW2DPS_H

// Boost v1.56 library
#include <boost/thread.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/timer/timer.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/math/constants/constants.hpp>

#include <sstream> // stringstream
#include <algorithm> // min/max_element()
#include <fstream> // ofstream / file
#include <locale> // locale
#include <algorithm> // count()
#include <Windows.h>
#pragma comment (lib, "winmm.lib")

using namespace GW2LIB;
using namespace boost;
using namespace std;

float const pi = boost::math::constants::pi<float>();
HKL currentKBL = GetKeyboardLayout(0);

// Font Settings
Font font;
int lineHeight = 13; //16 normal
int padX = 5;
int padY = 2;
static const DWORD fontColor = 0xffffffff;
static const DWORD backColor = 0xff000000;
static const DWORD borderColor = 0xff444444;
HWND gw2hwnd = FindWindow(0, L"Guild Wars 2");

Texture icons[9];

// THREADS //
int targetLockID;
struct Target {
	Target() : valid(false), alive(true), id(0), type(0), cHealth(0), mHealth(0), pHealth(0), lvl(0), lvlActual(0), pos(Vector3(0, 0, 0)) {}

	bool valid;
	bool alive;
	int id;
	int type; // 0 char, 9 struct, 10 wboss
	int cHealth;
	int mHealth;
	int pHealth;
	int lvl;
	int lvlActual;

	Vector3 pos;
};
Target selected;
Target locked;
Target self;
struct Ally {
	Ally() : id(0), profession(0), lvl(0), lvlActual(0), cHealth(0), mHealth(0), pHealth(0), vitality(0), traits(0), name("") {}

	int id;
	int profession;
	int lvl;
	int lvlActual;
	int cHealth; // current health
	int mHealth; // max health
	int pHealth; // current health in percent

	int vitality;
	float traits;
	string name;
	int partyPos;
};
struct Allies {
	vector<Ally> war;
	vector<Ally> necro;

	vector<Ally> mes;
	vector<Ally> ranger;
	vector<Ally> engi;

	vector<Ally> guard;
	vector<Ally> ele;
	vector<Ally> thief;
};
struct Float {
	//Float() : cHealth(0), mHealth(0), prof(0), time(0), id(0) {}

	bool operator < (const Float& fl) const {
		return (id < fl.id);
	}
	bool operator == (const Float& fl) const {
		return (id == fl.id);
	}

	Vector3 pos;
	int cHealth;
	int mHealth;
	int prof;
	DWORD time;
	int id;
};
struct Siege {
	int type;
	Vector3 pos;
	int mHealth;
	int cHealth;
};
struct Floaters {
	vector<Float> allyNpc;
	vector<Float> enemyNpc;
	vector<Float> allyPlayer;
	vector<Float> enemyPlayer;
	vector<Siege> siege;
};
struct Killtimer {
	Killtimer() : dmg(0), dps(0), time(0), samplesKnown(0), samplesUnknown(0) {}

	int dmg;
	double dps;
	double time; // seconds
	int samplesKnown;
	int samplesUnknown;
};
Killtimer bufferKillTimer;
struct Displacement {
	Displacement() : id(0), start(Vector3(0, 0, 0)), dist(0) {}

	int id;
	Vector3 start;
	int dist;
};
Displacement bufferDisplacement;
deque<Float> dpsDeque;
boost::circular_buffer<int> bufferDps(2400); // 5s of 250ms samples
boost::circular_buffer<int> bufferHits(50);
boost::circular_buffer<double> bufferAttackRate(50); // seconds
boost::circular_buffer<int> bufferSpeedometer(30); // inches/sec, 100ms sampleRate,3s worth

// Layout Anchors
struct Anchor {
	Anchor() : x(0), y(0) {}

	float x;
	float y;
};

// FUNCTIONS //
POINT ClickPos;
POINT MapPos = {1753, 940};
void SetClickPosToCurrent() {
	GetCursorPos(&ClickPos);
}
void SetMapPosToCurrent() {
	GetCursorPos(&MapPos);
}
void DoubleClick() {
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(3);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(3);
}
void ClickAtPos(POINT toClick) {
	POINT current;
	//RECT rect;
	//HWND hWindow = GetActiveWindow();
	//GetWindowRect(hWindow, &rect);
	GetCursorPos(&current);
	SetCursorPos((int) toClick.x, (int) toClick.y);
	Sleep(3);
	//double click
	DoubleClick();
	//back to original position
	SetCursorPos((int) current.x, (int) current.y);
}
void EqOffhand() {
	POINT cur;
	GetCursorPos(&cur);
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
	Sleep(5);
	SetCursorPos((int) cur.x + 20, (int) cur.y + 30);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(5);
	SetCursorPos(cur.x, cur.y);
}
Vector3 posLeft;
Vector3 posRight;
void SetPosLeftPosRight(int distance) {
	float d = GetOwnAgent().GetRot();
	float x = self.pos.x;
	float y = self.pos.y;
	float z = self.pos.z;
	float xL, xR, yL, yR;
	if (d > pi / 2) {
		xL = (float) (x + distance * cos((d - (2 / 3) * pi) + pi / 2));
		yL = (float) (y + distance * sin((d - (2 / 3) * pi) + pi / 2));
		xR = (float) (x + distance * cos(d - pi / 2));
		yR = (float) (y + distance * sin(d - pi / 2));
	}
	else if (d < -pi / 2) {
		xL = (float) (x + distance * cos(d + pi / 2));
		yL = (float) (y + distance * sin(d + pi / 2));
		xR = (float) (x + distance * cos((d + (2 / 3) * pi) - pi / 2));
		yR = (float) (y + distance * sin((d + (2 / 3) * pi) - pi / 2));
	}
	else {
		xL = (float) (x + distance * cos(d + pi / 2));
		yL = (float) (y + distance * sin(d + pi / 2));
		xR = (float) (x + distance * cos(d - pi / 2));
		yR = (float) (y + distance * sin(d - pi / 2));
	}
	posLeft = {xL, yL, z};
	posRight = {xR, yR, z};
}
void UseSkill(int i) {
	if (gw2hwnd == NULL)
		return;
	int iMappedKey = MapVirtualKey((0x30 + i), 0); //i key
	LPARAM lparam = (iMappedKey << 16) | 1;
	LPARAM lparamup = lparam | 0xc0000000;
	PostMessage(gw2hwnd, WM_KEYDOWN, iMappedKey, lparam);
	Sleep(5);
	PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
}
float Dist2D(Vector3 p1, Vector3 p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
float CalcAngleToTarget(Vector3 ownPos, Vector3 targetPos) {
	float distance = Dist2D(ownPos, targetPos);
	float angle = acos((targetPos.x - ownPos.x) / distance);
	//if (angle > pi)
	//	return (angle - 2 * pi);
	//else if (angle < -pi)
	//	return (angle + 2 * pi);
	//else
	if (ownPos.y > targetPos.y)
		return -angle;
	else
		return angle;
}
int GetTurnDirection(float curAngle, float resAngle) {
	if ((curAngle >= 0 && resAngle >= 0)) {
		if (curAngle <= resAngle + 0.2f && curAngle >= resAngle - 0.2f)
			return 0; //dont turn
	}
	else if ((curAngle < 0 && resAngle < 0)) {
		if (curAngle <= resAngle + 0.2f && curAngle >= resAngle - 0.2f)
			return 0; //dont turn
	}
	if (resAngle > curAngle) {
		if ((resAngle >= 0 && curAngle >= 0) || (resAngle < 0 && curAngle < 0)) {
			return 1; //left
		}
		else { //resangle +, curAngle -
			if (resAngle < (pi + curAngle)) {
				return 1; //left
			}
			else {
				return 2; //right
			}
		}
	}
	else {//resAngle < curAngle
		if ((resAngle >= 0 && curAngle >= 0) || (resAngle < 0 && curAngle < 0)) {
			return 2; //turn right
		}
		else { //resangle -, curangle +
			if (resAngle > (curAngle - pi)) {
				return 2; //right
			}
			else {
				return 1; //left
			}
		}
	}
}
void PressButton(char ch) {
	int vKey = VkKeyScanEx(ch, currentKBL);
	int iMappedKey = MapVirtualKey(vKey, 0); //W key
	LPARAM lparam = (iMappedKey << 16) | 1;
	LPARAM lparamup = lparam | 0xc0000000;
	PostMessage(gw2hwnd, WM_KEYDOWN, iMappedKey, lparam);
}
void ReleaseButton(char ch) {
	int vKey = VkKeyScanEx(ch, currentKBL);
	int iMappedKey = MapVirtualKey(vKey, 0); //W key
	LPARAM lparam = (iMappedKey << 16) | 1;
	LPARAM lparamup = lparam | 0xc0000000;
	PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
}
void ReadKeyboardState(uint8_t* keys) {
	for (int x = 0x0; x < 256; x++)
		keys[x] = (GetAsyncKeyState(x) & 0x8000) ? 1 : 0;
}
bool ReadCtrlLMouse() {
	uint8_t buf[2];
	buf[0] = (GetAsyncKeyState(VK_CONTROL) & 0x8000) ? 1 : 0;
	buf[1] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0;
	return (buf[0] && buf[1]);
}
bool MoveToPos(Vector3 pos) {
	if (pos.x == 0 && pos.y == 0) {
		ReleaseButton('a');
		ReleaseButton('d');
		ReleaseButton('w');
		return 0;
	}
	if (Dist2D(self.pos, pos) < 50)
		return 0;
	float curAngle = GetOwnAgent().GetRot();
	float resAngle = CalcAngleToTarget(self.pos, pos);

	int dir = GetTurnDirection(curAngle, resAngle);

	if (dir == 0) {
		ReleaseButton('a');
		ReleaseButton('d');
		PressButton('w');
	}
	else if (dir == 1) {
		ReleaseButton('d');
		PressButton('w');
		PressButton('a');
	}
	else if (dir == 2) {
		ReleaseButton('a');
		PressButton('w');
		PressButton('d');
	}
	else {
		ReleaseButton('a');
		ReleaseButton('d');
		ReleaseButton('w');
	}
	return 1;
}
float Dist(Vector3 p1, Vector3 p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}
string SecondsToString(double input) {
	int hours = int(input) / 60 / 60;
	int minutes = (int(input) - hours * 60 * 60) / 60;
	double seconds = (input - hours * 60 * 60 - minutes * 60);

	stringstream ss;
	if (hours > 0) ss << format("%i:") % hours;
	if (minutes >= 0 && minutes < 10) ss << format("0%0.2i:") % minutes;
	else if (minutes > 9) ss << format("%0.2i:") % minutes;
	if (seconds >= 0 && seconds < 10) ss << format("0%0.2f") % seconds;
	else if (seconds > 9) ss << format("%0.2f") % seconds;
	if (input == 0) ss << "00:00.00";

	return ss.str();
}
struct StrInfo {
	StrInfo() : lineCount(0), x(0), y(0) {}

	size_t lineCount;
	float x;
	float y;
};

inline wstring convert(const string& as) {
	wstring ws = wstring(as.begin(), as.end());
	replace_all(ws, "%%", "%");
	replace_all(ws, "&", "&&");
	wstring rval = ws;

	//wchar_t* buf = new wchar_t[as.size() * 2 + 2];
	//swprintf(buf, L"%S", as.c_str());
	//wstring rval = buf;
	//delete[] buf;

	return rval;
}
StrInfo StringInfo(string str) {
	StrInfo strInfo;

	// Line Count
	{
		size_t lineCount = 0;
		regex token("\n");
		sregex_token_iterator i(str.begin(), str.end(), token, -1);
		sregex_token_iterator j;
		while (i != j) {
			//cout << *i++ << endl;
			*i++;
			lineCount++;
		}
		strInfo.lineCount = lineCount;
	}

	// Width
	{
		typedef vector<string> split_vector_type;
		split_vector_type lines; // #2: Search for tokens
		split(lines, str, is_any_of("\n"), token_compress_on);

		HDC hdc = GetDC(gw2hwnd);
		HFONT hFont = CreateFont(lineHeight, 0, 0, 0, 600, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_TT_ALWAYS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH, L"Verdana");
		HFONT hFontOld = (HFONT) SelectObject(hdc, hFont);

		// Sanitize
		//replace_all(str, "%%", "");
		//replace_all(str, "&&", "&");

		// find longest line
		LONG width = 0;
		string longLine;
		for (auto & line : lines) {
			RECT r = {0, 0, 0, 0};
			DrawText(hdc, (LPCTSTR) convert(line.c_str()).c_str(), -1, &r, DT_CALCRECT);
			LONG w = abs(r.right - r.left);

			// refine the width
			size_t i;
			i = count(line.begin(), line.end(), ':'); w -= i * 2;
			i = count(line.begin(), line.end(), ','); w -= i * 1;
			i = count(line.begin(), line.end(), ' '); w -= i * 2;
			i = count(line.begin(), line.end(), '['); w -= i * 1;
			i = count(line.begin(), line.end(), ']'); w -= i * 1;
			i = count(line.begin(), line.end(), 'T'); w -= i * 2;
			i = count(line.begin(), line.end(), 't'); w -= i * 1;
			//i = count(line.begin(), line.end(), '%'); w -= i * 6;

			i = count(line.begin(), line.end(), 'm'); w += i * 1;
			i = count(line.begin(), line.end(), 'o'); w += i * 1;

			if (w > width) {
				width = w;
				longLine = line;
			}
		}
		/*
		if (0) { // Test Draw
		//DbgOut("%s\n", longLine.c_str());

		RECT r = {0, 0, 0, 0};
		DrawText(hdc, convert(longLine.c_str()).c_str(), -1, &r, DT_CALCRECT);
		DrawText(hdc, convert(longLine.c_str()).c_str(), -1, &r, NULL);
		}*/
		DeleteObject(hFont);
		ReleaseDC(gw2hwnd, hdc);

		strInfo.x = float(width);
		strInfo.y = float(strInfo.lineCount * lineHeight);
	}

	return strInfo;
}

struct baseHpReturn {
	float health;
	float vitality;
};
baseHpReturn baseHp(int lvl, int profession) {
	// base stats
	float hp = 0;
	float vit = 0;

	// calc base vit
	if (lvl >= 1) vit += 24;
	if (lvl >= 4) vit += 30;
	if (lvl >= 10) vit += 35;
	if (lvl >= 16) vit += 35;
	if (lvl >= 22) vit += 40;
	if (lvl >= 28) vit += 55;
	if (lvl >= 34) vit += 60;
	if (lvl >= 40) vit += 70;
	if (lvl >= 46) vit += 73;
	if (lvl >= 52) vit += 80;
	if (lvl >= 58) vit += 80;
	if (lvl >= 64) vit += 82;
	if (lvl >= 70) vit += 82;
	if (lvl >= 76) vit += 85;
	if (lvl >= 80) vit += 95;

	// calc base hp
	switch (profession) {
	case GW2::PROFESSION_WARRIOR:
	case GW2::PROFESSION_NECROMANCER:
		hp = lvl * 28.f;
		if (lvl > 19) hp += (lvl - 19) * float(42);
		if (lvl > 39) hp += (lvl - 39) * float(70);
		if (lvl > 59) hp += (lvl - 59) * float(70);
		if (lvl > 79) hp += (lvl - 79) * float(70);
		hp += vit * 10;
		break;
	case GW2::PROFESSION_ENGINEER:
	case GW2::PROFESSION_RANGER:
	case GW2::PROFESSION_MESMER:
		hp = lvl * 18.f;
		if (lvl > 19) hp += (lvl - 19) * float(27);
		if (lvl > 39) hp += (lvl - 39) * float(45);
		if (lvl > 59) hp += (lvl - 59) * float(45);
		if (lvl > 79) hp += (lvl - 79) * float(45);
		hp += vit * 10;
		break;
	case GW2::PROFESSION_GUARDIAN:
	case GW2::PROFESSION_ELEMENTALIST:
	case GW2::PROFESSION_THIEF:
		hp = lvl * 5.f;
		if (lvl > 19) hp += (lvl - 19) * float(7.5);
		if (lvl > 39) hp += (lvl - 39) * float(12.5);
		if (lvl > 59) hp += (lvl - 59) * float(12.5);
		if (lvl > 79) hp += (lvl - 79) * float(12.5);
		hp += vit * 10;
		break;
	}

	baseHpReturn out;
	out.health = hp;
	out.vitality = vit;
	return out;
}

#endif