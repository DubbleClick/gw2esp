#include "gw2lib.h"
#include "gw2dps.h"


bool showMapId = false;
bool initFailed = false;
bool logTime = false;
timer::cpu_timer dungeonTimer;

bool autoClick = false;
bool follow = false;
Agent followAgent;

bool leftAndRight = false;
bool leftOrRight = false;
bool showRotAndPos = false;

// Settings //
bool hideApp = false;
bool longDist = true;
bool partyHp = true;
bool showPartyNames = true;

bool enableRadar = true;
bool radarType = false;
bool radarSet = true;

//retarded way to change lol, artifact of older version, disregard this
int changeZero = 0;
int changeOne = 1;
int changeTwo = 2;
int changeThree = 3;

bool help = false;
bool selfHealthPercent = true;
bool loopLimiter = true;

bool targetHealth = true;
bool targetDist = true;
bool targetInfoT = false;
bool targetLock = false;

bool dpsAllowNegative = true;

bool logDpsArray = true;
float diff;

bool logDps = false;
bool logDpsDetails = false;
string logDpsFile = "gw2dpsLog-Dps.txt";

bool logKillTimer = false;
bool logKillTimerDetails = false;
bool logKillTimerToFile = false;

bool logHits = false;
bool logHitsDetails = false;
bool logHitsToFile = false;
string logHitsFile = "gw2dpsLog-Hits.txt";
int threadHitsCounter = 0;

bool logAttackRate = false;
bool logAttackRateDetails = false;
bool logAttackRateToFile = false;
int AttackRateChainHits = 1;
int AttackRateChainTime = 0; // not used atm
string logAttackRateFile = "gw2dpsLog-AttackRate.txt";
int threadAttackRateCounter = 0;

bool alliesList = false;
int wvwBonus = 0;

bool floatAllyNpc = false;
bool floatEnemyNpc = false;
bool floatAllyPlayer = false;
bool floatAllyPlayerProf = false;
bool floatEnemyPlayer = false;
bool floatSiege = false;
int floatRadius = 7000;
bool floatCircles = true;
bool floatType = false; // false = circles (+ profession icon); true = hp + distance;

bool logSpeedometer = false;
bool logSpeedometerEnemy = false;
int logDisplacementValue = 0;
bool logDisplacement = false;
bool logDisplacementEnemy = false;
Vector3 logDisplacementStart = Vector3(0, 0, 0);

int resX = GetSystemMetrics(SM_CXSCREEN);
int resY = GetSystemMetrics(SM_CYSCREEN);
int lowResY = 0;
int lowResX = 0;


// Threads //
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.Hotkeys.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.Dps.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.KillTimer.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.Hits.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.AttackRate.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.Speedometer.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.Follower.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.DpsArray.cpp"
#include "C:\Users\M\Documents\Visual Studio 2013\Projects\gw2esp\src\hacklib_gw2\thread.AutoClicker.cpp"

// Self
Character me;

void ESP() {

	//MapPos.x = 1743; MapPos.y = 940;
	if (resY < 1000) {
		lowResY = 1;
	}
	if (resY < 800) {
		lowResY = 2;
	}
	if (resX < 1900) {
		lowResX = 1;
	}
	if (resX < 1500) {
		lowResX = 2;
	}
	if (resX < 1300) {
		lowResX = 3;
	}
	if (resX < 1200) {
		lowResX = 4;
	}
	// Element Anchors
	Anchor aLeft, aTopLeft, aTop, aTopRight, aRight, aCenter, aBottom, aHealthBar;

	aLeft.x = 100;
	aLeft.y = 75;

	aTopLeft.x = round((GetWindowWidth() / 2 - 316 - 179) / 2 + 316);
	aTopLeft.y = 8;

	aTop.x = round(GetWindowWidth() * float(0.5)); //eig. winheight/2
	aTop.y = 1;

	aTopRight.x = round((GetWindowWidth() / 2 - 294 - 179) / 2 + GetWindowWidth() / 2 + 179);
	aTopRight.y = 8;

	aRight.x = GetWindowWidth() - 10;
	aRight.y = 8;

	aCenter.x = round(GetWindowWidth() * float(0.5));
	aCenter.y = round(GetWindowHeight() * float(0.5));

	aBottom.x = round(GetWindowWidth() * float(0.5));
	aBottom.y = round(GetWindowHeight() - float(85));

	aHealthBar.y = round((aCenter.y + aTop.y) / 7);

	if (lowResY == 1) {
		aLeft.y = 40;
		aTopLeft.y = 5;
		aTop.y = 1;
		aTopRight.y = 5;
		aRight.y = 5;
		aCenter.y = round(GetWindowHeight() * float(0.6));
		aBottom.y = round(GetWindowHeight() - float(55));
	}
	else if (lowResY == 2) {
		aLeft.y = 40;
		aTopLeft.y = 5;
		aTop.y = 1;
		aTopRight.y = 5;
		aRight.y = 5;
		aCenter.y = round(GetWindowHeight() * float(0.6));
		aBottom.y = round(GetWindowHeight() - float(55));

		aHealthBar.y = round((aCenter.y + aTop.y) / 6.5f);
	}

	if (hideApp) {
		return;
		stringstream ss;
		ss << format("[%i]");
		font.Draw(100, 100, fontColor - (!loopLimiter ? 0x00aa0000 : 0), ss.str());
	}

	if (help) {
		stringstream ss;
		ss << format("Hide App with (Alt + B)\n");
		ss << format("[%i] Show Party Member HP (Alt N)\n") % partyHp;
		ss << format("[%i] Show Detailed Party List (Alt + Shift + N)\n") % showPartyNames;
		ss << format("\n");
		ss << format("[%i] Show Radar (Alt + R)\n") % enableRadar;
		ss << format("[%i] Radartype (0=stickied, 1=moves by camera)\n") % radarType;
		ss << format("[%i] Show Radar Circle & Move to Mouse Pos (Alt + Shift + Home)\n") % radarSet;
		ss << format("\n");
		ss << format("(%i, %i) Set Click Position (Alt + Home) & Dubble Click (Alt + End) \n") % ClickPos.x % ClickPos.y;
		ss << format("\n");
		ss << format("[%i] Self Health Percent (Alt P)\n") % selfHealthPercent;
		ss << format("[%i] Selected/Locked Target HP (Alt S)\n") % targetHealth;
		ss << format("[%i] Selected Target Details/Range (Alt I)\n") % targetDist;
		ss << format("[%i] Lock On Target (Alt L)\n") % targetLock;
		//ss << format("[%i] Allow Negative DPS (Alt + Shift + N)\n") % dpsAllowNegative;
		ss << format("\n");
		ss << format("[%i] DPS Meter (Alt D)\n") % logDps;
		//ss << format("[%i] DPS Meter History (Alt Shift D)\n") % logDpsDetails;
		ss << format("[%i] DPS 1s/5s/60s (Alt Shift D)\n") % logDpsDetails;
		ss << format("\n");
		ss << format("[%i] Kill Timer (Alt Num1)\n") % logKillTimer;
		ss << format("[%i] Kill Timer Details (Alt Num2)\n") % logKillTimerDetails;
		//ss << format("[%i] Kill Timer Writes to a File (Alt Num3)\n") % logKillTimerToFile;
		ss << format("\n");
		ss << format("[%i] Monitor Hits (Alt Num7)\n") % logHits;
		ss << format("[%i] Show Hits History (Alt Num8)\n") % logHitsDetails;
		ss << format("[%i] Record Hits to File (Alt Num9)\n") % logHitsToFile;
		ss << format("\n");
		ss << format("[%i] Monitor Attack Rate (Alt Num4)\n") % logAttackRate;
		ss << format("[%i] Show Attack Rate History (Alt Num5)\n") % logAttackRateDetails;
		ss << format("[%i] Record Attack Rate to File (Alt Num6)\n") % logAttackRateToFile;
		ss << format("[%i] Adjust Attack Rate Threshold (Alt PgUp/PgDown)\n") % AttackRateChainHits;
		ss << format("\n");
		ss << format("[%i] Nearby Ally Players List (Alt V)\n") % alliesList;
		ss << format("[%i] Adjust WvW HP Bonus (Alt Home/End)\n") % wvwBonus;
		ss << format("\n");
		ss << format("[%i] Count Ally NPCs (Alt 1)\n") % floatAllyNpc;
		ss << format("[%i] Count Enemy NPCs (Alt 2)\n") % floatEnemyNpc;
		ss << format("[%i] Count Ally Players (Alt 3)\n") % floatAllyPlayer;
		ss << format("[%i] Count Enemy Players (Alt 4)\n") % floatEnemyPlayer;
		//ss << format("[%i] Count Siege (Alt 5)\n") % floatSiege;
		ss << format("[%i] Show/Hide Floaters below counted (Alt F)\n") % floatCircles;
		ss << format("[%i] Floaters show Max HP / Distance (Alt Shift F)\n") % floatType;
		ss << format("\n");
		ss << format("[%i] Speedometer (Alt 9)\n") % logSpeedometer;
		ss << format("[%i] Speedometer for Self/Enemy (Alt Shift 9)\n") % logSpeedometerEnemy;
		ss << format("[%i] Measure Distance (Alt 0)\n") % logDisplacement;
		ss << format("[%i] Distance for Self/Enemy (Alt Shift 0)\n") % logDisplacementEnemy;
		ss << format("\n");
		ss << format("[%i] Position for 1st who joined dungeon (Alt + Shift + 1)\n") % changeZero;
		ss << format("[%i] Position for 2nd who joined dungeon (Alt + Shift + 2)\n") % changeOne;
		ss << format("[%i] Position for 3rd who joined dungeon (Alt + Shift + 3)\n") % changeTwo;
		ss << format("[%i] Position for 4th who joined dungeon (Alt + Shift + 4)\n") % changeThree;
		ss << format("Reset all positions (Alt + Shift + 5)\n");

		StrInfo strInfo;
		strInfo = StringInfo(ss.str());
		float x = round(aCenter.x - strInfo.x / 2);
		float y = round(aCenter.y - strInfo.y / 2);

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (!loopLimiter ? 0x00aa0000 : 0), ss.str());
	}

	// Font Draw Debug
	if (0) {
		stringstream ss;
		ss << format("Selected: 18,140 / 18,140 [100%s]") % "%%";
		ss << format("Locked: 18,140 / 18,140 [100%s]") % "%%";

		StrInfo strInfo;
		strInfo = StringInfo(ss.str());
		float x = 0;
		float y = float(strInfo.lineCount * lineHeight + 1);
		padX = 0;
		padY = 0;

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, 0xffffffff);
		font.Draw(x, y, 0xff000000, ss.str());

		return;
	}

	// Targets & Agents //
	me = GetOwnCharacter();

	if (me.IsValid()) {
		self.id = GetOwnAgent().GetAgentId();
		self.pos = GetOwnAgent().GetPos();

		self.cHealth = int(me.GetCurrentHealth());
		self.mHealth = int(me.GetMaxHealth());
		if (self.mHealth > 0)
			self.pHealth = int(100.f * float(self.cHealth) / float(self.mHealth));
		else
			self.pHealth = 0;

		self.lvl = me.GetScaledLevel();
		self.lvlActual = me.GetLevel();
		self.alive = me.IsAlive();
	}
	Agent agLocked = GetLockedSelection();
	if (agLocked.IsValid()) {
		if (agLocked.GetAgentId() != selected.id)
			selected = {};

		int agType = agLocked.GetType();
		if (agType == GW2::AGENT_CATEGORY_CHAR) // char
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			Character chLocked = agLocked.GetCharacter();
			selected.cHealth = int(chLocked.GetCurrentHealth());
			selected.mHealth = int(chLocked.GetMaxHealth());
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;
			selected.lvl = chLocked.GetScaledLevel();
			selected.lvlActual = chLocked.GetLevel();
		}
		else if (agType == GW2::AGENT_TYPE_GADGET) // structure
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			unsigned long shift = *(unsigned long*) agLocked.m_ptr;
			shift = *(unsigned long*) (shift + 0x30);
			shift = *(unsigned long*) (shift + 0x168);
			if (shift) {
				selected.cHealth = int(*(float*) (shift + 0x8));
				selected.mHealth = int(*(float*) (shift + 0xC));
			}
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;
			//selected.lvl = chLocked.GetScaledLevel();
			//selected.lvlActual = chLocked.GetLevel();
		}
		else if (agType == GW2::AGENT_TYPE_GADGET_ATTACK_TARGET) // world boss
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			unsigned long shift = *(unsigned long*) agLocked.m_ptr;
			shift = *(unsigned long*) (shift + 0x30);
			shift = *(unsigned long*) (shift + 0x28);
			shift = *(unsigned long*) (shift + 0x17c);
			if (shift) {
				selected.cHealth = int(*(float*) (shift + 0x8));
				selected.mHealth = int(*(float*) (shift + 0xC));
			}
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;

			//selected.lvl = chLocked.GetScaledLevel();
			//selected.lvlActual = chLocked.GetLevel();
		}
		else
			selected = {};

		if (selected.mHealth == 0)
			selected = {};
	}
	else
		selected = {};

	// Locked Target (ID)
	if (targetLock) {
		//if (ReadCtrlLMouse()) { //ctrl + left mouse
			if (!selected.valid && targetLockID == 0) {
				locked = {};
				locked.id = 0;
				targetLock = false;
			}
			if (selected.valid && locked.valid) {
				locked.id = targetLockID = selected.id;
			}
		//}
		if (!locked.valid && selected.valid)
			targetLockID = selected.id;
		else if (!locked.valid && !selected.valid)
			targetLock = false;
	}
	else {
		//if (ReadCtrlLMouse()) { //ctrl + left mouse
		//	if (selected.valid)
		//		targetLock = true;
		//}
		if (!selected.valid) {
			locked = {};
			targetLockID = 0;
		}
		else
			locked.id = targetLockID = selected.id;
	}

	// compile all agent data
	Floaters floaters;
	Allies allies;
	vector<Ally> partymembers;
	Agent ag;
	Vector3 mypos = me.GetAgent().GetPos();
	float WinX, WinY;
	if (MapPos.x != NULL && MapPos.y != NULL) {
		WinX = (float) MapPos.x;
		WinY = (float) MapPos.y;
	}
	else {
		WinX = GetWindowWidth() - 125;
		WinY = GetWindowHeight() / 2;
	}
	bool mapSet = !(MapPos.x == NULL || MapPos.y == NULL);
	float myRot = me.GetAgent().GetRot();
	if (enableRadar && !radarSet) {
		DrawCircleFilled(WinX, WinY, 100, 0x44000000); //44->BB normal
		DrawCircle(WinX, WinY, 8, 0x99FFFFFF);
		DrawLine(WinX - 100, WinY, WinX + 100, WinY, 0x99FFFFFF);
		DrawLine(WinX, WinY - 100, WinX, WinY + 100, 0x99FFFFFF);
	}
	while (ag.BeNext()) {
		// Locked Target (Data)
		if (targetLockID == ag.GetAgentId()) {
			int agType = ag.GetType();
			if (agType == GW2::AGENT_CATEGORY_CHAR) // char
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				Character ch = ag.GetCharacter();
				locked.cHealth = int(ch.GetCurrentHealth());
				locked.mHealth = int(ch.GetMaxHealth());
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				locked.lvl = ch.GetScaledLevel();
				locked.lvlActual = ch.GetLevel();
			}
			else if (agType == GW2::AGENT_TYPE_GADGET) // structure
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				unsigned long shift = *(unsigned long*) ag.m_ptr;
				shift = *(unsigned long*) (shift + 0x30);
				shift = *(unsigned long*) (shift + 0x168);
				if (shift) {
					locked.cHealth = int(*(float*) (shift + 0x8));
					locked.mHealth = int(*(float*) (shift + 0xC));
				}
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				//locked.lvl = ch.GetScaledLevel();
				//locked.lvlActual = ch.GetLevel();
			}
			else if (agType == GW2::AGENT_TYPE_GADGET_ATTACK_TARGET) // world boss
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				unsigned long shift = *(unsigned long*) ag.m_ptr;
				shift = *(unsigned long*) (shift + 0x30);
				shift = *(unsigned long*) (shift + 0x28);
				shift = *(unsigned long*) (shift + 0x17c);
				if (shift) {
					locked.cHealth = int(*(float*) (shift + 0x8));
					locked.mHealth = int(*(float*) (shift + 0xC));
				}
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				//locked.lvl = ch.GetScaledLevel();
				//locked.lvlActual = ch.GetLevel();
			}

			if (locked.cHealth == 0 && locked.mHealth != 78870) // don't clear if 78870 (indestructible golem) or targetLocked
			{
				if (targetLock)
					locked.alive = false;
				else
					locked = {};
			}
		}


		// Floaters
		if (floatAllyNpc || floatEnemyNpc || floatAllyPlayer || floatEnemyPlayer || floatSiege) {
			int agType = ag.GetType();

			// NPC & Player
			if (agType == GW2::AGENT_TYPE_CHAR) {
				Character ch = ag.GetCharacter();

				// gather data
				Vector3 pos = ag.GetPos();
				int cHealth = int(ch.GetCurrentHealth());
				int mHealth = int(ch.GetMaxHealth());
				int attitude = ch.GetAttitude();
				int prof = ch.GetProfession();

				// Filter the dead
				if (cHealth > 0 && mHealth > 1) {
					// Filter those out of range
					int radiuS = (longDist ? floatRadius : 3000);
					if (Dist(self.pos, pos) <= radiuS) {
						Float floater;
						floater.pos = pos;
						floater.mHealth = mHealth;
						floater.cHealth = cHealth;
						floater.prof = prof;

						// player vs npc
						if (ch.IsPlayer() && !ch.IsControlled()) // (ignore self)
						{
							// allyPlayer
							if (floatAllyPlayer && attitude == GW2::ATTITUDE_FRIENDLY)
								floaters.allyPlayer.push_back(floater);

							// enemyPlayer
							if (floatEnemyPlayer && attitude == GW2::ATTITUDE_HOSTILE)
								floaters.enemyPlayer.push_back(floater);
						}

						if (!ch.IsPlayer()) {
							// allyNpc
							if (floatAllyNpc && (attitude == GW2::ATTITUDE_FRIENDLY || attitude == GW2::ATTITUDE_NEUTRAL))
								floaters.allyNpc.push_back(floater);

							// enemyNpc
							if (floatEnemyNpc && (attitude == GW2::ATTITUDE_HOSTILE || attitude == GW2::ATTITUDE_INDIFFERENT))
								floaters.enemyNpc.push_back(floater);
						}
					}
				}
			}
		}

		// Allies list
		if (alliesList) {
			Character ch = ag.GetCharacter();

			// collect only valid allies (and yourself)
			bool chValid = true;

			if (!ch.IsValid())
				chValid = false;

			//if (ch.IsControlled())
			//chValid = false;

			if (!ch.IsPlayer() || ch.GetAttitude() != GW2::ATTITUDE_FRIENDLY)
				chValid = false;

			// gather char data
			if (chValid) {
				Ally ally;
				ally.id = ag.GetAgentId();

				ally.profession = ch.GetProfession();
				ally.mHealth = int(round(ch.GetMaxHealth() / (100 + wvwBonus) * 100));
				//ally.cHealth = int(ch.GetCurrentHealth());
				//if (ally.mHealth > 0)
				//ally.pHealth = int(100.f * float(ally.cHealth) / float(ally.mHealth));
				//else
				//ally.pHealth = 0;
				ally.lvl = ch.GetScaledLevel();
				ally.lvlActual = ch.GetLevel();
				ally.name = ch.GetName();

				baseHpReturn base = baseHp(ally.lvl, ally.profession);
				ally.vitality = int(round((ally.mHealth - base.health) / 10));
				ally.traits = (926.f / base.vitality) * ((ally.mHealth - base.health) / 100.f / 5.f);
				ally.traits = round(ally.traits * 10) / 10; // round to 0.0

				switch (ally.profession) {
				case GW2::PROFESSION_WARRIOR:
					allies.war.push_back(ally);
					break;
				case GW2::PROFESSION_NECROMANCER:
					allies.necro.push_back(ally);
					break;

				case GW2::PROFESSION_ENGINEER:
					allies.engi.push_back(ally);
					break;
				case GW2::PROFESSION_RANGER:
					allies.ranger.push_back(ally);
					break;
				case GW2::PROFESSION_MESMER:
					allies.mes.push_back(ally);
					break;

				case GW2::PROFESSION_GUARDIAN:
					allies.guard.push_back(ally);
					break;
				case GW2::PROFESSION_THIEF:
					allies.thief.push_back(ally);
					break;
				case GW2::PROFESSION_ELEMENTALIST:
					allies.ele.push_back(ally);
					break;
				}
			}
		}
		// Party member for hp
		if (partyHp) {
			Character ch = ag.GetCharacter();

			// collect only valid allies
			bool chValid = true;

			if (!ch.IsValid())
				chValid = false;

			//if (ch.IsControlled())
			//chValid = false;

			if (!ch.IsPlayer() || ch.GetAttitude() != GW2::ATTITUDE_FRIENDLY)
				chValid = false;
			if (ch.IsPlayer() && ch.IsControlled())
				chValid = false;

			// gather char data
			if (chValid) {
				Ally ally;
				ally.id = ag.GetAgentId();

				ally.profession = ch.GetProfession();
				ally.mHealth = int(round(ch.GetMaxHealth() / (100 + wvwBonus) * 100));
				ally.cHealth = int(ch.GetCurrentHealth());
				if (ally.mHealth > 0)
					ally.pHealth = int(100.f * float(ally.cHealth) / float(ally.mHealth));
				else
					ally.pHealth = 0;
				ally.lvlActual = ch.GetLevel();
				ally.name = ch.GetName();
				ally.partyPos = partymembers.size();
				//TODO: if in party:
				partymembers.push_back(ally);
			}
		}

		// Displacement
		if (logDisplacement) {
			if (logDisplacementEnemy) {
				if (locked.valid) {
					if (locked.id != bufferDisplacement.id ||
						(bufferDisplacement.start.x == 0 && bufferDisplacement.start.y == 0 && bufferDisplacement.start.z == 0)) {
						bufferDisplacement.start = locked.pos;
						bufferDisplacement.id = locked.id;
					}
					else {
						float displacement = Dist(bufferDisplacement.start, locked.pos);
						bufferDisplacement.dist = int(displacement);
					}
				}
				else {
					// reset
					bufferDisplacement = {};
				}
			}
			else {
				if (bufferDisplacement.start.x == 0 && bufferDisplacement.start.y == 0 && bufferDisplacement.start.z == 0) {
					bufferDisplacement.start = self.pos;
				}
				else {
					float displacement = Dist(bufferDisplacement.start, self.pos);
					bufferDisplacement.dist = int(displacement);
				}
			}
		}
		else {
			// reset
			bufferDisplacement = {};
		}

		if (enableRadar) {
			Character chr = ag.GetCharacter();
			Vector3 pos = ag.GetPos();
			float agdist = Dist(mypos, pos);
			if (agdist > (mapSet ? 7000 : 5000))
				goto skip;
			float CoordRot;

			if (radarType) {
				CoordRot = (atan2(pos.y - mypos.y, pos.x - mypos.x) - myRot) + (pi / 2); //rotating
			}
			else {
				CoordRot = atan2(pos.y - mypos.y, pos.x - mypos.x);
			}
			float CoordX = ((agdist * cos(CoordRot)) / (48));
			float CoordY = ((agdist * sin(CoordRot)) / (48));

			DWORD color = 0xee000000;
			// assign colors


			if (chr == me) {
				color = 0x00000000;
			}
			else {
				switch (chr.GetAttitude()) {
				case GW2::ATTITUDE_FRIENDLY:
					if (ag.GetCharacter().IsPlayer())
						color |= 0x0000ffCC;
					else
						color |= 0x0033FF00;
					break;
				case GW2::ATTITUDE_HOSTILE:
					if (ag.GetCharacter().IsPlayer())
						color |= 0x00ff3300;
					else
						color |= 0x11ff6600;
					break;
				case GW2::ATTITUDE_INDIFFERENT:
					color |= 0x00dddd00;
					break;
				case GW2::ATTITUDE_NEUTRAL:
					color = 0xbbdddddd;
					break;
				}
			}
			if (!chr.IsAlive()) {
				color = 0x22000000;

				DrawCircleFilled(WinX + CoordX, WinY - CoordY, 1, color);
			}
			else
				DrawCircleFilled(WinX + CoordX, WinY - CoordY, 2, color);
		skip:
			if (ag.GetAgentId() == GetLockedSelection().GetAgentId())
				DrawCircle(WinX + CoordX, WinY - CoordY, 3, 0xEEFFFF00);
		}
	}

	// Bottom Element //

	if (selfHealthPercent && self.alive) {
		stringstream ss;
		ss << format("%i") % self.pHealth;

		float x = round(aBottom.x - 11.75f);
		float y = round(aBottom.y - lineHeight);

		if (self.pHealth < 100)
			x += 4.25f;
		if (self.pHealth < 10)
			x += 4;
		font.Draw(x, y, fontColor, ss.str());
	}


	// Left Element //

	if (alliesList) {
		stringstream ss;
		stringstream sp;
		stringstream sn;
		stringstream sh;
		stringstream sv;
		stringstream st;


		ss << format("Nearby Ally Players (WvW HP Bonus: %i%s)") % wvwBonus % "%%";
		sp << format("Class");
		sn << format("Name");
		sh << format("Health");
		sv << format("Vitality");
		st << format("Traits");

		bool listEmpty = true;
		if (!allies.war.empty()) {
			for (auto & ally : allies.war) {
				sp << format("\nWar:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (!allies.guard.empty()) {
			for (auto & ally : allies.guard) {
				sp << format("\nGuard:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}

		if (!allies.ele.empty()) {
			for (auto & ally : allies.ele) {
				sp << format("\nEle:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (!allies.mes.empty()) {
			for (auto & ally : allies.mes) {
				sp << format("\nMes:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}

		if (!allies.thief.empty()) {
			for (auto & ally : allies.thief) {
				sp << format("\nThief:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (!allies.ranger.empty()) {
			for (auto & ally : allies.ranger) {
				sp << format("\nRanger:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (!allies.engi.empty()) {
			for (auto & ally : allies.engi) {
				sp << format("\nEngi:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (!allies.necro.empty()) {
			for (auto & ally : allies.necro) {
				sp << format("\nNecro:");
				sn << format("\n%s") % ally.name;
				sh << format("\n%i hp") % ally.mHealth;
				sv << format("\n%+i") % ally.vitality;
				st << format("\n%+.1f") % ally.traits;
			}
			listEmpty = false;
		}
		if (listEmpty) {
			sp << format("\n...");
			sn << format("\n...");
			sh << format("\n...");
			sv << format("\n...");
			st << format("\n...");
		}


		// CharName max width
		stringstream sx;
		sx << "WWWWWWWWWWWWWWWWWWW";
		StrInfo strInfo;
		strInfo = StringInfo(sx.str());

		float spOffset = 0;
		float snOffset = spOffset + 65;
		float shOffset = snOffset + strInfo.x;
		float svOffset = shOffset + 85;
		float stOffset = svOffset + 70;
		float sxOffset = stOffset + 60;

		float x = round(aLeft.x);
		float y = round(aLeft.y);

		strInfo = StringInfo(sp.str());
		int lineCount = int(strInfo.lineCount) + 2;

		// render the list
		DrawRectFilled(x - padX, y - padY, sxOffset + padX * 2, float(lineCount * lineHeight) + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, sxOffset + padX * 2, float(lineCount * lineHeight) + padY * 2, borderColor);

		int lineShiftY = 2;
		for (int i = 3; i < lineCount; i++) {
			DrawLine(x - padX, y - padY + i * lineHeight + lineShiftY, x + sxOffset + padX, y - padY + i * lineHeight + lineShiftY, borderColor);
		}
		font.Draw(x + spOffset, y, fontColor, ss.str()); y += 2 * lineHeight;
		font.Draw(x + spOffset, y, fontColor, sp.str());
		font.Draw(x + snOffset, y, fontColor, sn.str());
		font.Draw(x + shOffset, y, fontColor, sh.str());
		font.Draw(x + svOffset, y, fontColor, sv.str());
		font.Draw(x + stOffset, y, fontColor, st.str());
	}
	int mapId = GetCurrentMapId();
	bool mapOk = (mapId == 36 || mapId == 33 || mapId == 111 || mapId == 112 || mapId == 75 || mapId == 76 || mapId == 68 || mapId == 67
		|| mapId == 70 || mapId == 71 || mapId == 66 || mapId == 69 || mapId == 63 || mapId == 64 || mapId == 81 || mapId == 82
		|| mapId == 872 || mapId == 947 || mapId == 948 || mapId == 949 || mapId == 950 || mapId == 951 || mapId == 952 || mapId == 953 || mapId == 954
		|| mapId == 955 || mapId == 956 || mapId == 957 || mapId == 958 || mapId == 959);
	if (partyHp && mapOk) {
		stringstream ss0, ss1, ss2, ss3;
		if (!partymembers.empty())
			for (auto & ally : partymembers) {
				if (showPartyNames) {
					if (ally.partyPos == 0)
						ss0 << format("%s: %i / %i [%i%s]\n") % ally.name % ally.cHealth % ally.mHealth % ally.pHealth % "%%";
					else if (ally.partyPos == 1)
						ss1 << format("%s: %i / %i [%i%s]\n") % ally.name % ally.cHealth % ally.mHealth % ally.pHealth % "%%";
					else if (ally.partyPos == 2)
						ss2 << format("%s: %i / %i [%i%s]\n") % ally.name % ally.cHealth % ally.mHealth % ally.pHealth % "%%";
					else if (ally.partyPos == 3)
						ss3 << format("%s: %i / %i [%i%s]\n") % ally.name % ally.cHealth % ally.mHealth % ally.pHealth % "%%";
				}
				else {
					if (ally.partyPos == 0)
						ss0 << format("[%i%s]\n") % ally.pHealth % "%%";
					else if (ally.partyPos == 1)
						ss1 << format("[%i%s]\n") % ally.pHealth % "%%";
					else if (ally.partyPos == 2)
						ss2 << format("[%i%s]\n") % ally.pHealth % "%%";
					else if (ally.partyPos == 3)
						ss3 << format("[%i%s]\n") % ally.pHealth % "%%";
				}
			}
		float x = showPartyNames ? aLeft.x*0.9f : aLeft.x*0.25f;
		float y0, y1, y2, y3, y4;
		y0 = aBottom.y / 6 * 0.8975f;
		y1 = y0 + y0 / 2;
		y2 = y1 + y0 / 2;
		y3 = y2 + y0 / 2;
		y4 = y3 + y0 / 2;

		DWORD colorToUse = (showPartyNames || targetLock) ? fontColor : 0xffb0b0b0;

		if (changeZero == 0)
			font.Draw(x, y0, colorToUse, ss0.str());
		else if (changeZero == 1)
			font.Draw(x, y1, colorToUse, ss0.str());
		else if (changeZero == 2)
			font.Draw(x, y2, colorToUse, ss0.str());
		else if (changeZero == 3)
			font.Draw(x, y3, colorToUse, ss0.str());

		if (changeOne == 0)
			font.Draw(x, y0, colorToUse, ss1.str());
		else if (changeOne == 1)
			font.Draw(x, y1, colorToUse, ss1.str());
		else if (changeOne == 2)
			font.Draw(x, y2, colorToUse, ss1.str());
		else if (changeOne == 3)
			font.Draw(x, y3, colorToUse, ss1.str());

		if (changeTwo == 0)
			font.Draw(x, y0, colorToUse, ss2.str());
		else if (changeTwo == 1)
			font.Draw(x, y1, colorToUse, ss2.str());
		else if (changeTwo == 2)
			font.Draw(x, y2, colorToUse, ss2.str());
		else if (changeTwo == 3)
			font.Draw(x, y3, colorToUse, ss2.str());

		if (changeThree == 0)
			font.Draw(x, y0, colorToUse, ss3.str());
		else if (changeThree == 1)
			font.Draw(x, y1, colorToUse, ss3.str());
		else if (changeThree == 2)
			font.Draw(x, y2, colorToUse, ss3.str());
		else if (changeThree == 3)
			font.Draw(x, y3, colorToUse, ss3.str());

	}



	// TopLeft Element //

	if (targetHealth) {
		if (targetLock && locked.valid && selected.valid && selected.id == locked.id) {

			stringstream ss, ss2;
			StrInfo strInfo, sI2, sI3;

			ss << format("%i%s") % selected.pHealth % "%%";
			ss2 << format("%i / %i") % selected.cHealth % selected.mHealth;

			strInfo = StringInfo("100%    10,000 / 10,000 ");
			sI2 = StringInfo("100%    ");
			sI3 = StringInfo(ss.str());
			float x, xx;
			float y;
			if (selected.pHealth == 100) x = round(aTop.x*1.03f);
			else x = round(aTop.x*1.03f) + StringInfo("1").x;
			y = aHealthBar.y;
			xx = round(aTop.x*0.835f);

			font.Draw(x, y, fontColor, ss.str());
			font.Draw(xx, y, fontColor, ss2.str());
		}
		else {
			if (targetLock && locked.valid) {
				stringstream ss, ss2;
				StrInfo strInfo, sI2, sI3;

				ss << format("%i%s") % locked.pHealth % "%%";
				ss2 << format("%i / %i") % locked.cHealth % locked.mHealth;

				sI2 = StringInfo("100%    ");
				float x, xx;
				float y;
				if (locked.pHealth == 100) x = round(aTop.x*1.03f);
				else if (locked.pHealth >= 10) x = round(aTop.x*1.03f) + StringInfo("1").x;
				else x = round(aTop.x*1.03f) + StringInfo("10").x;
				y = aHealthBar.y;
				xx = round(aTop.x*0.835f);

				font.Draw(x, y, fontColor, ss.str());
				font.Draw(xx, y, fontColor, ss2.str());
			}
			else if (selected.valid) {
				stringstream ss, ss2;
				StrInfo strInfo, sI2, sI3;

				ss << format("%i%s") % selected.pHealth % "%%";
				ss2 << format("%i / %i") % selected.cHealth % selected.mHealth;

				sI2 = StringInfo("100%    ");
				float x, xx;
				float y;
				if (selected.pHealth == 100) x = round(aTop.x*1.03f);
				else if (selected.pHealth >= 10) x = round(aTop.x*1.03f) + StringInfo("1").x;
				else x = round(aTop.x*1.03f) + StringInfo("10").x;
				y = aHealthBar.y;
				xx = round(aTop.x*0.835f);

				DWORD healthFontColor = 0xFFb0b0b0;

				font.Draw(x, y, healthFontColor, ss.str());
				font.Draw(xx, y, healthFontColor, ss2.str());
			}
		}

		if (targetDist) {
			stringstream ss;

			if (targetLock && locked.valid) {
				if (int(Dist(self.pos, locked.pos)) < 10) ss << format("      %i |") % int(Dist(self.pos, locked.pos));
				else if (int(Dist(self.pos, locked.pos)) < 100) ss << format("    %i |") % int(Dist(self.pos, locked.pos));
				else if (int(Dist(self.pos, locked.pos)) < 1000) ss << format("  %i |") % int(Dist(self.pos, locked.pos));
				else ss << format("%i |") % int(Dist(self.pos, locked.pos));
			}
			else if (!targetLock && selected.valid) {
				if (int(Dist(self.pos, selected.pos)) < 10) ss << format("      %i |") % int(Dist(self.pos, selected.pos));
				else if (int(Dist(self.pos, selected.pos)) < 100) ss << format("    %i |") % int(Dist(self.pos, selected.pos));
				else if (int(Dist(self.pos, selected.pos)) < 1000) ss << format("  %i |") % int(Dist(self.pos, selected.pos));
				else ss << format("%i |") % int(Dist(self.pos, selected.pos));
			}

			float x = round(aTop.x) - 53;
			float y = aHealthBar.y - (lineHeight + 2);

			DWORD colorToUse = (targetLock) ? fontColor : 0xffb0b0b0;

			font.Draw(x, y, colorToUse, ss.str());
		}
	}


	// Top Elements (and floaters) //

	if (floatAllyNpc || floatEnemyNpc || floatAllyPlayer || floatEnemyPlayer || floatSiege) {
		stringstream ss;
		StrInfo strInfo;

		ss << format("R: %i") % (longDist ? floatRadius : 3000);

		if (floatAllyNpc)
			ss << format(" | AllyNPCs: %i") % floaters.allyNpc.size();

		if (floatEnemyNpc)
			ss << format(" | FoeNPCs: %i") % floaters.enemyNpc.size();

		if (floatAllyPlayer)
			ss << format(" | Allies: %i") % floaters.allyPlayer.size();

		if (floatEnemyPlayer)
			ss << format(" | Foes: %i") % floaters.enemyPlayer.size();

		if (floatSiege)
			ss << format(" | Siege: %i") % floaters.siege.size();

		strInfo = StringInfo(ss.str());
		float x = round(aTop.x - strInfo.x / 2);
		float y = round(aTop.y);

		DWORD colorToUse = ((floatCircles&&floatType) ? fontColor : 0xffb0b0b0);

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, colorToUse, ss.str());

		aTop.y += strInfo.y + padY * 2;

		if (floatAllyPlayerProf) {
			int prof[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			for (auto & ally : floaters.allyPlayer) {
				prof[ally.prof]++;
			}

			ss.str("");
			ss << format("War: %i") % prof[2];
			ss << format(" | Guard: %i") % prof[1];
			ss << format(" | Ele: %i") % prof[6];
			ss << format(" | Thief: %i") % prof[5];
			ss << format(" | Mes: %i") % prof[7];
			ss << format(" | Engi: %i") % prof[3];
			ss << format(" | Ranger: %i") % prof[4];
			ss << format(" | Necro: %i") % prof[8];

			strInfo = StringInfo(ss.str());
			float x = round(aTop.x - strInfo.x / 2);
			float y = round(aTop.y);

			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (floatCircles ? 0x00aa0000 : 0), ss.str());

			aTop.y += strInfo.y + padY * 2;
		}


		if (floatCircles) {
			float x, y;
			if (floatAllyNpc && floaters.allyNpc.size() > 0) {
				for (auto & floater : floaters.allyNpc) {
					if (WorldToScreen(floater.pos, &x, &y)) {
						stringstream fs;
						DWORD circlecolor = 0x44ff3300;
						DWORD color = fontColor;
						if (floatType) {
							fs << format("%i") % int(Dist(self.pos, floater.pos));
							if (int(Dist(self.pos, floater.pos)) <= 600)
								color = 0xCC7CFC00;
							//else if (int(Dist(self.pos, floater.pos)) <= 1200)
							//	color = 0xBBFFD700;
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0xCCFF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0xCCFFCC00;
						}
						else {
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0xCCFF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0xCCFFCC00;
						}

						StrInfo fsInfo = StringInfo(fs.str());
						font.Draw(x - fsInfo.x / 2, y - 15, color, fs.str());

						//DWORD color = 0x4433ff00;
						DrawCircleProjected(floater.pos, 20.0f, circlecolor);
						DrawCircleFilledProjected(floater.pos, 20.0f, circlecolor - 0x30000000);
					}
				}
			}

			if (floatEnemyNpc && floaters.enemyNpc.size() > 0) {
				for (auto & floater : floaters.enemyNpc) {
					if (WorldToScreen(floater.pos, &x, &y)) {
						stringstream fs;
						DWORD color = fontColor;
						DWORD circlecolor = 0x44ff3300;
						if (floatType) {
							fs << format("%i") % int(Dist(self.pos, floater.pos));
							if (int(Dist(self.pos, floater.pos)) <= 900)
								color = 0xCC7CFC00;
							else if (int(Dist(self.pos, floater.pos)) <= 1200)
								color = 0xCCFFDD00;
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0x66FF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0x66FFCC00;
						}
						else {
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0x66FF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0x66FFDD00;
						}

						int disT = (int) Dist(self.pos, floater.pos);
						StrInfo fsInfo = StringInfo(fs.str());


						DWORD tColor = color;
						if (disT < 1200) {}
						else if (disT < 1500) {
							tColor -= 0x22000000;
						}
						else if (disT < 2000) {
							tColor -= 0x44000000;
						}
						else if (disT < 2500) {
							tColor -= 0x66000000;
						}
						else if (disT < 3000) {
							tColor -= 0x88000000;
						}
						else {
							tColor -= 0xAA000000;
						}
						font.Draw(x - fsInfo.x / 2, y - 15, tColor, fs.str());
						DrawCircleProjected(floater.pos, 20.0f, circlecolor);
						DrawCircleFilledProjected(floater.pos, 20.0f, circlecolor - 0x30000000);
					}
				}
			}

			if (floatAllyPlayer && floaters.allyPlayer.size() > 0) {
				for (auto & floater : floaters.allyPlayer) {
					if (WorldToScreen(floater.pos, &x, &y)) {
						stringstream fs;
						DWORD circlecolor = 0x44ff3300;
						DWORD color = fontColor;
						if (floatType) {
							fs << format("%i") % int(Dist(self.pos, floater.pos));
							if (int(Dist(self.pos, floater.pos)) <= 600) {
								color = 0xCC7CFC00;
							}
							//else if (int(Dist(self.pos, floater.pos)) <= 1200) {
							//	color = 0xBBFFD700;
						}
						if (floater.cHealth < (int) floater.mHealth / 4)
							circlecolor = 0xCCFF0000;
						else if (floater.cHealth < (int) floater.mHealth / 2)
							circlecolor = 0xCCFFCC00;
						else {
							if (!initFailed && !floatType) {
								int disT = int(Dist(self.pos, floater.pos));
								float sz = (20.0f - (10.0f * ((float) disT / 3000)));
								icons[floater.prof].Draw(x - 7.5f, y - 15, sz, sz);
							}
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0xCCFF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0xCCFFCC00;
						}

						int disT = int(Dist(self.pos, floater.pos));
						DWORD tColor = color;
						if (disT < 1200) {}
						else if (disT < 1500) {
							tColor -= 0x22000000;
						}
						else if (disT < 2000) {
							tColor -= 0x44000000;
						}
						else if (disT < 2500) {
							tColor -= 0x66000000;
						}
						else if (disT < 3000) {
							tColor -= 0x88000000;
						}
						else {
							tColor -= 0xAA000000;
						}

						StrInfo fsInfo = StringInfo(fs.str());
						font.Draw(x - fsInfo.x / 2, y - 15, tColor, fs.str());

						//DWORD color = 0x4433ff00;
						DrawCircleProjected(floater.pos, 20.0f, circlecolor);
						DrawCircleFilledProjected(floater.pos, 20.0f, circlecolor - 0x30000000);
					}
				}
			}


			if (floatEnemyPlayer && floaters.enemyPlayer.size() > 0) {
				for (auto & floater : floaters.enemyPlayer) {
					if (WorldToScreen(floater.pos, &x, &y)) {
						stringstream fs;
						DWORD circlecolor = 0x44ff3300;
						DWORD color = fontColor;
						if (floatType) {
							fs << format("%i") % int(Dist(self.pos, floater.pos));
							if (int(Dist(self.pos, floater.pos)) <= 900)
								color = 0xCC7CFC00;
							else if (int(Dist(self.pos, floater.pos)) <= 1200)
								color = 0xCCFFDD00;
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0xCCFF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0xCCFFCC00;
						}
						else {
							if (!initFailed && !floatType) {
								int disT = int(Dist(self.pos, floater.pos));
								float sz = 20.0f - (10.0f * ((float) disT / 3000));
								icons[floater.prof].Draw(x - 7.5f, y - 15, (float) sz, (float) sz);
							}
							if (floater.cHealth < (int) floater.mHealth / 4)
								circlecolor = 0xCCFF0000;
							else if (floater.cHealth < (int) floater.mHealth / 2)
								circlecolor = 0xCCFFCC00;
						}
						int disT = int(Dist(self.pos, floater.pos));
						DWORD tColor = color;
						if (disT < 1200) {}
						else if (disT < 1500) {
							tColor -= 0x22000000;
						}
						else if (disT < 2000) {
							tColor -= 0x44000000;
						}
						else if (disT < 2500) {
							tColor -= 0x66000000;
						}
						else if (disT < 3000) {
							tColor -= 0x88000000;
						}
						else {
							tColor -= 0xAA000000;
						}
						StrInfo fsInfo = StringInfo(fs.str());
						font.Draw(x - fsInfo.x / 2, y - 15, tColor, fs.str());

						//DWORD color = 0x44ff3300; 
						DrawCircleProjected(floater.pos, 20.0f, circlecolor);
						DrawCircleFilledProjected(floater.pos, 20.0f, circlecolor - 0x30000000);
					}
				}
			}
		}

		if (floatSiege && floaters.siege.size() > 0) {
			for (auto & floater : floaters.siege) {
				//DWORD color = 0x44ff3300;
				//DrawCircleProjected(floater.pos, 20.0f, color);
				//DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
			}
		}
	}


	if (logSpeedometer) {
		stringstream ss;
		StrInfo strInfo;

		ss << format("Speed: ");

		if (!bufferSpeedometer.empty()) {
			double average[2] {};
			size_t samples = 0;

			// Speed ~ .5s
			samples = 5;
			if (samples > bufferSpeedometer.size())
				samples = bufferSpeedometer.size();
			average[0] = 0;
			for (size_t i = 0; i < samples; i++)
				average[0] += bufferSpeedometer[i];
			average[0] = average[0] / samples * (1000 / 100);

			// Speed ~ 3s
			samples = 30;
			if (samples > bufferSpeedometer.size())
				samples = bufferSpeedometer.size();
			average[1] = 0;
			for (size_t i = 0; i < samples; i++)
				average[1] += bufferSpeedometer[i];
			average[1] = average[1] / samples * (1000 / 100);

			// Prepare String
			ss << format("%i in/s, %i in/s") % int(average[0]) % int(average[1]);
		}
		else {
			ss << format("0 in/s, 0 in/s");
		}

		strInfo = StringInfo(ss.str());
		float x = round(aTop.x - strInfo.x / 2);
		float y = round(aTop.y);

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (logSpeedometerEnemy ? 0x00aa0000 : 0), ss.str());

		aTop.y += strInfo.y + padY * 2;
	}

	if (logDisplacement) {
		stringstream ss;
		StrInfo strInfo;

		ss << format("Distance: %i") % bufferDisplacement.dist;

		strInfo = StringInfo(ss.str());
		float x = round(aTop.x - strInfo.x / 2);
		float y = round(aTop.y);

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (logDisplacementEnemy ? 0x00aa0000 : 0), ss.str());

		aTop.y += strInfo.y + padY * 2;

	}
	else {
		if (logDisplacementStart.x != 0 || logDisplacementStart.y != 0 || logDisplacementStart.z != 0)
			logDisplacementStart = Vector3(0, 0, 0);
	}


	// TopRight Elements //

	if (logDpsArray) {
		stringstream sd;
		Float temp;
		DWORD colorToUse = targetLock ? fontColor : 0xFFb0b0b0;
		float x, y;
		x = round(aTop.x) - 7; //(StrInfo(8))
		y = aHealthBar.y - ((2 * lineHeight) + 2);

		if (targetLock && locked.valid) {
			temp.id = targetLockID;
			auto e = lower_bound(dpsDeque.begin(), dpsDeque.end(), temp);
			if (e != dpsDeque.end())
				temp = *e;
			DWORD now = timeGetTime();
			if (locked.cHealth != 0) //stop time measuring when enemy is dead
				diff = (float) (now - temp.time) / CLOCKS_PER_SEC;
			float dps = (temp.mHealth - temp.cHealth) / diff; //dps
			if (dps) {//temp.mHealth != temp.cHealth)
				sd << format("DPS: %0.0f\n") % dps;
				sd << format("%s") % SecondsToString(diff);
			}
			else {
				sd << format("DPS: ...\n");
				sd << format("00:00.00");
			}
		}
		else if (selected.valid) {
			temp.id = selected.id;
			auto e = lower_bound(dpsDeque.begin(), dpsDeque.end(), temp);
			if (e != dpsDeque.end())
				temp = *e;
			DWORD now = timeGetTime();
			if (locked.cHealth != 0) //stop time measuring when enemy is dead
				diff = (float) (now - temp.time) / CLOCKS_PER_SEC;
			float dps = (float) (temp.mHealth - temp.cHealth) / diff; //dps
			if (dps) {//temp.mHealth != temp.cHealth)
				sd << format("DPS: %0.0f\n") % dps;
				sd << format("%s") % SecondsToString(diff);
			}
			else {
				sd << format("DPS: ...\n");
				sd << format("00:00.00");
			}
		}
		font.Draw(x, y, colorToUse, sd.str());
	}


	if (logDps) {
		// separate ss vars
		stringstream ss;
		stringstream ffs;
		StrInfo strInfo;

		float aAdjustX = 120; // adjust anchor -120

		if (!bufferDps.empty()) {
			double average[601] {}; // for 1s & 5s
			size_t samples = 0;

			if (logDpsDetails) {
				// DP1s
				samples = 4; // 1s/250ms=4
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[1] = 0;
				for (size_t i = 0; i < samples; i++)
					average[1] += bufferDps[i];
				average[1] = average[1] / samples * (1000 / 250);

				// DP5s
				samples = 20; // 5s/250ms=20
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[5] = 0;
				for (size_t i = 0; i < samples; i++)
					average[5] += bufferDps[i];
				average[5] = average[5] / samples * (1000 / 250);

				// DP60s
				samples = 240;
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[60] = 0;
				for (size_t i = 0; i < samples; i++)
					average[60] += bufferDps[i];
				average[60] = average[60] / samples * (1000 / 250);


				ffs << format("DP1: %0.0f\n") % average[1];
				ffs << format("DP5: %0.0f\n") % average[5];
				ffs << format("D60: %0.0f\n") % average[60];
			}

			if (!logDpsArray) {
				samples = 2400;
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[600] = 0;
				for (size_t i = 0; i < samples; i++)
					average[600] += bufferDps[i];
				average[600] = average[600] / samples * (1000 / 250);

				// Prepare String
				ss << format("DPS: %0.0f\n") % average[600];
			}

			/*
			if (logDpsDetails) {
			ss << format("\n\n");
			for (size_t i = 0; i < bufferDps.size(); i++)
			ss << format("\nDP250ms: %i") % bufferDps[i];
			}
			*/
		}
		else {
			//ss << format("1s: ...\n");
			ss << format("DPS: ...");
		}

		strInfo = StringInfo(ss.str());
		if (logDpsDetails && !bufferDps.empty() && strInfo.x < aAdjustX)
			strInfo.x = aAdjustX; // box min-width with history stream
		float x;
		float y;
		x = x = round(aTop.x) - StringInfo("8").x;
		y = aHealthBar.y - 2 * (lineHeight + 2);
		DWORD colorToUse = targetLock ? fontColor : 0xFFb0b0b0;

		if (selected.valid || targetLock) {
			if (!logDpsArray)
				font.Draw(x, y, colorToUse, ss.str());
			if (logDpsDetails)
				font.Draw(x, y - StringInfo("dps\ndps\ndps").y, colorToUse, ffs.str());
		}
	}

	if (targetInfoT && selected.valid) {
		//aTopLeft.y += lineHeight;
		stringstream ss;
		StrInfo strInfo;
		if (agLocked.GetType() == GW2::AGENT_TYPE_CHAR) {
			int stats[7] {};
			stats[0] = 0; // power
			stats[1] = 0; // precision
			stats[2] = 0; // toughness
			stats[3] = 0; // vitality
			stats[4] = 0; // ferocity
			stats[5] = 0; // healing
			stats[6] = 0; // condition
			unsigned long shift;
			shift = *(unsigned long*) agLocked.m_ptr;
			shift = *(unsigned long*) (shift + 0x30);
			shift = *(unsigned long*) (shift + 0x138);
			stats[0] = *(unsigned long*) (shift + 0x18c + 0x4 * 0);
			stats[1] = *(unsigned long*) (shift + 0x18c + 0x4 * 1);
			stats[2] = *(unsigned long*) (shift + 0x18c + 0x4 * 2);
			stats[3] = *(unsigned long*) (shift + 0x18c + 0x4 * 3);
			stats[4] = *(unsigned long*) (shift + 0x18c + 0x4 * 4);
			stats[5] = *(unsigned long*) (shift + 0x18c + 0x4 * 5);
			stats[6] = *(unsigned long*) (shift + 0x18c + 0x4 * 6);
			ss << format("Power - %i") % stats[0];
			ss << format("\nPrecision - %i") % stats[1];
			ss << format("\nToughness - %i") % stats[2];
			ss << format("\nVitality - %i") % stats[3];
			ss << format("\nFerocity - %i") % stats[4];
			ss << format("\nHealing - %i") % stats[5];
			ss << format("\nCondition - %i") % stats[6];
			ss << format("\n");
			ss << format("\n(Agent: %p)") % (void**) agLocked.m_ptr;
		}
		else {
			ss << format("Distance: %i") % int(Dist(self.pos, selected.pos));
		}
		strInfo = StringInfo(ss.str());
		float x = round(aTopLeft.x - strInfo.x / 2);
		float y = round(aTopLeft.y);
		font.Draw(x, y, fontColor, ss.str());
	}

	if (logKillTimer) {
		stringstream ss;
		StrInfo strInfo;

		// Prepare String
		if (bufferKillTimer.time > 0) {
			ss << format("%s") % SecondsToString(bufferKillTimer.time);
			//if (logKillTimerDetails)
			//	ss << format("\nDPS: %0.2f") % bufferKillTimer.dps;
		}
		else {
			ss << format("00:00.00");
			//if (logKillTimerDetails)
			//	ss << format("\nDPS: 0.0");
		}

		strInfo = StringInfo("00:00.00");
		float x;
		float y;
		x = round(aTop.x) - StringInfo("8").x;
		y = aHealthBar.y - (lineHeight + 2);

		DWORD colorToUse = targetLock ? fontColor : 0xFFb0b0b0;

		if ((selected.valid || targetLock) && !logDpsArray)
			font.Draw(x, y, colorToUse, ss.str());

	}



	// Right Elements //

	if (logAttackRate) {
		stringstream ss;
		StrInfo strInfo;

		if (logAttackRateToFile)
			ss << format(L'\uFFFD' + " Recording " + L'\uFFFD' + '\n');
		else
			ss << format(L'\uFFFD' + " Monitoring " + L'\uFFFD' + '\n');
		ss << format(L'\uFFFD' + " Attack Rate " + L'\uFFFD' + '\n');
		ss << format("\n");

		if (!bufferAttackRate.empty()) {
			//double min = *min_element(bufferAttackRate.begin(), bufferAttackRate.end());
			//double max = *max_element(bufferAttackRate.begin(), bufferAttackRate.end());
			double average = 0;
			for (size_t i = 0; i < bufferAttackRate.size(); i++)
				average += bufferAttackRate[i];
			average = average / bufferAttackRate.size();

			ss << format("Counter: %i\n") % threadAttackRateCounter;
			//ss << format("Min: %0.3fs\n") % min;
			ss << format("Average: %0.3fs\n") % average;
			//ss << format("Max: %0.3fs\n") % max;

			if (logAttackRateDetails) {
				ss << format("\n");
				ss << format("History\n");
				for (size_t i = 0; i < bufferAttackRate.size(); i++)
					ss << format(L'\uFFFD' + " %0.3fs\n") % bufferAttackRate[i];
			}
		}
		else {
			ss << format("Counter: ...\n");
			//ss << format("Minimum: ...\n");
			ss << format("Average: ...\n");
			//ss << format("Maximum: ...\n");

			if (logAttackRateDetails) {
				ss << format("\n");
				ss << format("History\n");
				ss << format(L'\uFFFD' + " ...\n");
			}
		}
		ss << format("\n");
		ss << format("Threshold: %i Hits\n") % AttackRateChainHits;

		strInfo = StringInfo(ss.str());

		float aAdjustX = 120; // adjust anchor -120
		if (strInfo.x < aAdjustX)
			strInfo.x = aAdjustX; // perma box min-width
		float x = round(aRight.x - strInfo.x);
		float y = round(aRight.y);

		// Draw
		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (logAttackRateToFile ? 0x00aa0000 : 0), ss.str());

		// Prepare for Next Element
		ss.str("");
		aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
		aRight.x = x - padX * 2 - 5;
	}

	if (logHits) {
		stringstream ss;
		StrInfo strInfo;

		if (logHitsToFile)
			ss << format(L'\uFFFD' + " Recording " + L'\uFFFD' + '\n');
		else
			ss << format(L'\uFFFD' + " Monitoring " + L'\uFFFD' + '\n');

		ss << format(L'\uFFFD' + " Damage Hits " + L'\uFFFD' + '\n');
		ss << format("\n");

		if (!bufferHits.empty()) {
			//double min = *min_element(bufferHits.begin(), bufferHits.end());
			//double max = *max_element(bufferHits.begin(), bufferHits.end());
			double average = 0;
			for (size_t i = 0; i < bufferHits.size(); i++)
				average += bufferHits[i];
			average = average / bufferHits.size();

			ss << format("Counter: %i\n") % threadHitsCounter;
			ss << format("Average: %0.1f\n") % average;

			if (logHitsDetails) {
				ss << format("\n");
				ss << format("History\n");
				for (size_t i = 0; i < bufferHits.size(); i++)
					ss << format(L'\uFFFD' + " %i\n") % bufferHits[i];
			}
		}
		else {
			ss << format("Counter: ...\n");
			ss << format("Average: ...\n");

			if (logHitsDetails) {
				ss << format("\n");
				ss << format("History\n");
				ss << format(L'\uFFFD' + " ...\n");
			}
		}

		strInfo = StringInfo(ss.str());


		float aAdjustX = 120; // adjust anchor -120
		if (strInfo.x < aAdjustX)
			strInfo.x = aAdjustX; // perma box min-width
		float x = round(aRight.x - strInfo.x);
		float y = round(aRight.y);

		// Draw
		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (logHitsToFile ? 0x00aa0000 : 0), ss.str());

		// Prepare for Next Element
		ss.str("");
		aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
		aRight.x = x - padX * 2 - 5;
	}

	if (showMapId) {
		stringstream ss;
		ss << format("%i") % GetCurrentMapId();

		font.Draw(aCenter.x, aCenter.y, fontColor, ss.str());
	}

	if (showRotAndPos) {
		stringstream stronkkk;
		stronkkk << "Rotation: " << GetOwnAgent().GetRot();
		stronkkk << "\nSelf:   x: " << self.pos.x << " y: " << self.pos.y;// << " z: " << self.pos.z;
		stronkkk << "\nLeft:   x: " << posLeft.x << " y: " << posLeft.y;// << " z: " << posLeft.z;
		stronkkk << "\nRight: x: " << posRight.x << " y: " << posRight.y;// << " z: " << posRight.z;
		font.Draw(700, 500, fontColor, stronkkk.str());
	}

	if (leftAndRight) {
		if (gw2hwnd == NULL)
			font.Draw(700, 500, fontColor, "gw2 not found");
		else {
			if (!leftOrRight) { //left
				int iMappedKey = MapVirtualKey(0x51, 0); //Q key
				LPARAM lparam = (iMappedKey << 16) | 1;
				LPARAM lparamup = lparam | 0xc0000000;

				posLeft.z = self.pos.z;
				posRight.z = self.pos.z;
				if (Dist2D(self.pos, posLeft) > 20) {
					PostMessage(gw2hwnd, WM_KEYDOWN, iMappedKey, lparam);
				}
				else {
					UseSkill(1);
					Sleep(20);
					PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
					leftOrRight = true;
				}
			}
			else { //right
				int iMappedKey = MapVirtualKey(0x45, 0); //E key
				LPARAM lparam = (iMappedKey << 16) | 1;
				LPARAM lparamup = lparam | 0xc0000000;

				if (Dist2D(self.pos, posRight) > 20) {
					PostMessage(gw2hwnd, WM_KEYDOWN, iMappedKey, lparam);
				}
				else {
					PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
					leftOrRight = false;
				}
			}
		}
	}


	if (follow) {
		stringstream st;
		float curAngle = GetOwnAgent().GetRot();
		float resAngle = CalcAngleToTarget(self.pos, selected.pos);
		int dir = GetTurnDirection(curAngle, resAngle);
		st << "x: " << selected.pos.x << " y: " << selected.pos.y
			<< "\n" << resAngle << "\n" << dir;
		font.Draw(800, 800, fontColor, st.str());
	}

	if (logTime) {
		stringstream ss;
		DWORD colorToUse = targetLock ? fontColor : 0xffb0b0b0;
		timer::cpu_times elapsed = dungeonTimer.elapsed();
		double elapsedTime = elapsed.wall / 1e6;
		ss << SecondsToString(elapsedTime/CLOCKS_PER_SEC);
		font.Draw(3, 45, colorToUse, ss.str());
	}
} //end ESP


void GW2LIB::gw2lib_main() {
	//locale::global(locale("en-US"));
	/*
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	*/

	EnableEsp(ESP);

	boost::thread t1(&threadHotKeys);
	//boost::thread t2(&threadDps);
	//boost::thread t3(&threadKillTimer);
	boost::thread t4(&threadHits);
	boost::thread t5(&threadAttackRate);
	boost::thread t6(&threadSpeedometer);
	boost::thread t7(&threadFollower);
	boost::thread t8(&threadDpsArray);
	boost::thread t9(&threadAutoClicker);

	if (!icons[GW2::PROFESSION_REVENANT].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\revenant.png")
		|| !icons[GW2::PROFESSION_WARRIOR].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\war.png")
		|| !icons[GW2::PROFESSION_GUARDIAN].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\guard.png")
		|| !icons[GW2::PROFESSION_ELEMENTALIST].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\ele.png")
		|| !icons[GW2::PROFESSION_ENGINEER].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\engi.png")
		|| !icons[GW2::PROFESSION_NECROMANCER].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\necro.png")
		|| !icons[GW2::PROFESSION_MESMER].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\mes.png")
		|| !icons[GW2::PROFESSION_RANGER].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\ranger.png")
		|| !icons[GW2::PROFESSION_THIEF].Init("C:\\Users\\M\\Documents\\Visual Studio 2013\\Projects\\gw2esp\\src\\hacklib_gw2\\thief.png"))
		initFailed = true;

	if (!font.Init(lineHeight, "Verdana")) {
		//DbgOut("could not create font");
		return;
	}

	while (!GetAsyncKeyState(VK_PAUSE));

	t1.interrupt();
	t1.join();
	//t2.interrupt();
	//t2.join();
	//t3.interrupt();
	//t3.join();
	t4.interrupt();
	t4.join();
	t5.interrupt();
	t5.join();
	t6.interrupt();
	t6.join();
	t7.interrupt();
	t7.join();
	t8.interrupt();
	t8.join();
	t9.interrupt();
	t9.join();
	return;
}