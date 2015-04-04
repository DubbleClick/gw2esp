#define HIDE_APP 999

#define HELP 0
#define LOOP_LIMITER 1
#define AUTOCLICKER 2
#define SELF_HEALTH_PERCENT 3
#define DUNGEONTIMER 4

#define SETMAPPOS 89
#define SETCURSORPOS 90
#define DOUBLECLICK 91
#define EQOFFHAND 94
#define ENABLERADAR 92
#define RADARTYPE 93

#define CHANGEZERO 500
#define CHANGEONE 501
#define CHANGETWO 502
#define CHANGETHREE 503
#define RESETPARTYORDER 504

#define target_health 10
#define TARGET_DIST 11
#define TARGET_INFO_T 12
#define TARGET_LOCK 13
#define DPS_ALLOW_NEGATIVE 14

#define LOG_DPS 20
#define LOG_DPS_DETAILS 21

#define LOG_KILL_TIMER 30
#define LOG_KILL_TIMER_DETAILS 31
#define LOG_KILL_TIMER_TO_FILE 32

#define LOG_HITS 40
#define LOG_HITS_DETAILS 41
#define LOG_HITS_TO_FILE 42

#define LOG_ATTACK_RATE 50
#define LOG_ATTACK_RATE_DETAILS 51
#define LOG_ATTACK_RATE_TO_FILE 52
#define ATTACKRATE_CHAIN_HITS_MORE 53
#define ATTACKRATE_CHAIN_HITS_LESS 54

#define ALLIES_LIST 60
#define WVW_BONUS_MORE 61
#define WVW_BONUS_LESS 62

#define FLOAT_CIRCLES 70
#define FLOAT_TYPE 71
#define FLOAT_RADIUS_MORE 72
#define FLOAT_RADIUS_LESS 73
#define FLOAT_ALLY_NPC 74
#define FLOAT_ENEMY_NPC 75
#define FLOAT_ALLY_PLAYER 76
#define FLOAT_ALLY_PLAYER_PROF 77
#define FLOAT_ENEMY_PLAYER 78
#define FLOAT_SIEGE 79

#define LOG_SPEEDOMETER 80
#define LOG_SPEEDOMETER_ENEMY 81
#define LOG_DISPLACEMENT 82
#define LOG_DISPLACEMENT_ENEMY 83

#define LONGDIST 122
#define PARTYHP 123
#define SHOWPARTYNAMES 124

#define LEFTANDRIGHT 988
#define SETLEFTRIGHT 989
#define SHOWROTPOS 991
#define MOVETOAGENT 992


bool ctrlAlt = false;

void threadHotKeys() {
	if (ctrlAlt == false) {
		RegisterHotKey(NULL, DUNGEONTIMER, MOD_ALT | MOD_NOREPEAT, 0x54); //T key
		RegisterHotKey(NULL, AUTOCLICKER, MOD_ALT | MOD_NOREPEAT, 0x43); //C Key
		RegisterHotKey(NULL, EQOFFHAND, MOD_ALT | MOD_NOREPEAT, 0x41); //A key

		//RegisterHotKey(NULL, LEFTANDRIGHT, MOD_ALT | MOD_NOREPEAT, 0x57); //W key
		//RegisterHotKey(NULL, SETLEFTRIGHT, MOD_ALT | MOD_NOREPEAT, 0x36); //6 key
		//RegisterHotKey(NULL, SHOWROTPOS, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x36); //shift + 6 key
		//RegisterHotKey(NULL, MOVETOAGENT, MOD_ALT | MOD_NOREPEAT, 0x37); //7 key

		RegisterHotKey(NULL, ENABLERADAR, MOD_ALT | MOD_NOREPEAT, 0x52); //R key
		RegisterHotKey(NULL, RADARTYPE, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x52); //R key

		RegisterHotKey(NULL, HIDE_APP, MOD_ALT | MOD_NOREPEAT, 0x42); // killApp| B key
		RegisterHotKey(NULL, LONGDIST, MOD_ALT | MOD_NOREPEAT, 0x4A); //J key
		RegisterHotKey(NULL, PARTYHP, MOD_ALT | MOD_NOREPEAT, 0x4E); //N key
		RegisterHotKey(NULL, SHOWPARTYNAMES, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x4E); //N key

		RegisterHotKey(NULL, SETCURSORPOS, MOD_ALT | MOD_NOREPEAT, VK_HOME); //home/pos1 key
		RegisterHotKey(NULL, SETMAPPOS, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, VK_HOME); //home/pos1 key
		RegisterHotKey(NULL, DOUBLECLICK, MOD_NOREPEAT, VK_END); //U key

		RegisterHotKey(NULL, CHANGEZERO, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x31); //1 key
		RegisterHotKey(NULL, CHANGEONE, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x32); //2 key
		RegisterHotKey(NULL, CHANGETWO, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x33); //3 key
		RegisterHotKey(NULL, CHANGETHREE, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x34); //4 key
		RegisterHotKey(NULL, RESETPARTYORDER, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x35); //5 key

		RegisterHotKey(NULL, HELP, MOD_ALT | MOD_NOREPEAT, 0x48); // help| H key
		RegisterHotKey(NULL, LOOP_LIMITER, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x4C); // loopLimiter | shift + L key
		RegisterHotKey(NULL, SELF_HEALTH_PERCENT, MOD_ALT | MOD_NOREPEAT, 0x50); // selfHealthPercent| P key

		RegisterHotKey(NULL, target_health, MOD_ALT | MOD_NOREPEAT, 0x53); // targetHealth| S key
		RegisterHotKey(NULL, TARGET_DIST, MOD_ALT | MOD_NOREPEAT, 0x49); // targetDist| I key
		RegisterHotKey(NULL, TARGET_INFO_T, MOD_ALT | MOD_NOREPEAT, 0x54); //T key
		RegisterHotKey(NULL, TARGET_LOCK, MOD_ALT | MOD_NOREPEAT, 0x4C); // targetLock | L key
		//RegisterHotKey(NULL, DPS_ALLOW_NEGATIVE, MOD_ALT | MOD_NOREPEAT | MOD_SHIFT, 0x4E); // dpsAllowNegative| N key

		RegisterHotKey(NULL, LOG_DPS, MOD_ALT | MOD_NOREPEAT, 0x44); // logDps| D key
		RegisterHotKey(NULL, LOG_DPS_DETAILS, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x44); // logDpsDetails

		RegisterHotKey(NULL, LOG_KILL_TIMER, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD1); // logKillTimer| T key
		RegisterHotKey(NULL, LOG_KILL_TIMER_DETAILS, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD2); // logKillTimerDetails
		RegisterHotKey(NULL, LOG_KILL_TIMER_TO_FILE, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD3); // logKillTimerToFile

		RegisterHotKey(NULL, LOG_HITS, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD7); // logHits
		RegisterHotKey(NULL, LOG_HITS_DETAILS, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD8); // logHitsDetails
		RegisterHotKey(NULL, LOG_HITS_TO_FILE, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD9); // logHitsToFile
		RegisterHotKey(NULL, LOG_ATTACK_RATE, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD4); // logAttackRate
		RegisterHotKey(NULL, LOG_ATTACK_RATE_DETAILS, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD5); // logAttackRateDetails
		RegisterHotKey(NULL, LOG_ATTACK_RATE_TO_FILE, MOD_ALT | MOD_NOREPEAT, VK_NUMPAD6); // logAttackRateToFile
		RegisterHotKey(NULL, ATTACKRATE_CHAIN_HITS_MORE, MOD_ALT, VK_PRIOR); // AttackRateChainHits +
		RegisterHotKey(NULL, ATTACKRATE_CHAIN_HITS_LESS, MOD_ALT, VK_NEXT); // AttackRateChainHits -

		RegisterHotKey(NULL, ALLIES_LIST, MOD_ALT | MOD_NOREPEAT, 0x56); // alliesList| V key
		//RegisterHotKey(NULL, WVW_BONUS_MORE, MOD_ALT, VK_HOME); // wvwBonus +
		//RegisterHotKey(NULL, WVW_BONUS_LESS, MOD_ALT, VK_END); // wvwBonus -

		RegisterHotKey(NULL, FLOAT_CIRCLES, MOD_ALT | MOD_NOREPEAT, 0x46); // floatCircles
		RegisterHotKey(NULL, FLOAT_TYPE, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, 0x46); // floatType
		RegisterHotKey(NULL, FLOAT_RADIUS_MORE, MOD_ALT, VK_ADD); // floatRadius +
		RegisterHotKey(NULL, FLOAT_RADIUS_LESS, MOD_ALT, VK_SUBTRACT); // floatRadius -
		RegisterHotKey(NULL, FLOAT_ALLY_NPC, MOD_ALT, 0x31); // floatAllyNpc
		RegisterHotKey(NULL, FLOAT_ENEMY_NPC, MOD_ALT, 0x32); // floatEnemyNpc
		RegisterHotKey(NULL, FLOAT_ALLY_PLAYER, MOD_ALT, 0x33); // floatAllyPlayer
		RegisterHotKey(NULL, FLOAT_ALLY_PLAYER_PROF, MOD_ALT | MOD_SHIFT, 0x33); // floatAllyPlayerProf
		RegisterHotKey(NULL, FLOAT_ENEMY_PLAYER, MOD_ALT, 0x34); // floatEnemyPlayer
		RegisterHotKey(NULL, FLOAT_SIEGE, MOD_ALT, 0x35); // floatSiege

		RegisterHotKey(NULL, LOG_SPEEDOMETER, MOD_ALT, 0x39); // logSpeedometer| 9 key
		RegisterHotKey(NULL, LOG_SPEEDOMETER_ENEMY, MOD_ALT | MOD_SHIFT, 0x39); // logSpeedometerEnemy
		RegisterHotKey(NULL, LOG_DISPLACEMENT, MOD_ALT, 0x30); // logDisplacement| 0 key
		RegisterHotKey(NULL, LOG_DISPLACEMENT_ENEMY, MOD_ALT | MOD_SHIFT, 0x30); // logDisplacementEnemy
	}
	else {
		RegisterHotKey(NULL, DUNGEONTIMER, MOD_CONTROL | MOD_NOREPEAT, 0x54); //T key
		RegisterHotKey(NULL, AUTOCLICKER, MOD_CONTROL | MOD_NOREPEAT, 0x43); //C Key
		RegisterHotKey(NULL, EQOFFHAND, MOD_CONTROL | MOD_NOREPEAT, 0x41); //A key
		/*
		RegisterHotKey(NULL, LEFTANDRIGHT, MOD_CONTROL | MOD_NOREPEAT, 0x57); //W key
		RegisterHotKey(NULL, SETLEFTRIGHT, MOD_CONTROL | MOD_NOREPEAT, 0x36); //6 key
		RegisterHotKey(NULL, SHOWROTPOS, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x36); //shift + 6 key
		RegisterHotKey(NULL, MOVETOAGENT, MOD_CONTROL | MOD_NOREPEAT, 0x37); //7 key
		*/
		RegisterHotKey(NULL, ENABLERADAR, MOD_CONTROL | MOD_NOREPEAT, 0x52); //R key
		RegisterHotKey(NULL, RADARTYPE, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x52); //R key

		RegisterHotKey(NULL, HIDE_APP, MOD_CONTROL | MOD_NOREPEAT, 0x42); // killApp| B key
		RegisterHotKey(NULL, LONGDIST, MOD_CONTROL | MOD_NOREPEAT, 0x4A); //J key
		RegisterHotKey(NULL, PARTYHP, MOD_CONTROL | MOD_NOREPEAT, 0x4E); //N key
		RegisterHotKey(NULL, SHOWPARTYNAMES, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x4E); //N key

		RegisterHotKey(NULL, SETCURSORPOS, MOD_CONTROL | MOD_NOREPEAT, VK_HOME); //home/pos1 key
		RegisterHotKey(NULL, SETMAPPOS, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, VK_HOME); //home/pos1 key
		RegisterHotKey(NULL, DOUBLECLICK, MOD_NOREPEAT, VK_END); //U key

		RegisterHotKey(NULL, CHANGEZERO, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x31); //1 key
		RegisterHotKey(NULL, CHANGEONE, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x32); //2 key
		RegisterHotKey(NULL, CHANGETWO, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x33); //3 key
		RegisterHotKey(NULL, CHANGETHREE, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x34); //4 key
		RegisterHotKey(NULL, RESETPARTYORDER, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x35); //5 key

		RegisterHotKey(NULL, HELP, MOD_CONTROL | MOD_NOREPEAT, 0x48); // help| H key
		RegisterHotKey(NULL, LOOP_LIMITER, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x4C); // loopLimiter | shift + L key
		RegisterHotKey(NULL, SELF_HEALTH_PERCENT, MOD_CONTROL | MOD_NOREPEAT, 0x50); // selfHealthPercent| P key

		RegisterHotKey(NULL, target_health, MOD_CONTROL | MOD_NOREPEAT, 0x53); // targetHealth| S key
		RegisterHotKey(NULL, TARGET_DIST, MOD_CONTROL | MOD_NOREPEAT, 0x49); // targetInfo| I key
		RegisterHotKey(NULL, TARGET_INFO_T, MOD_CONTROL | MOD_NOREPEAT, 0x54); //T key
		RegisterHotKey(NULL, TARGET_LOCK, MOD_CONTROL | MOD_NOREPEAT, 0x4C); // targetLock | L key
		//RegisterHotKey(NULL, DPS_ALLOW_NEGATIVE, MOD_CONTROL | MOD_NOREPEAT | MOD_SHIFT, 0x4E); // dpsAllowNegative| N key

		RegisterHotKey(NULL, LOG_DPS, MOD_CONTROL | MOD_NOREPEAT, 0x44); // logDps| D key
		RegisterHotKey(NULL, LOG_DPS_DETAILS, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x44); // logDpsDetails

		RegisterHotKey(NULL, LOG_KILL_TIMER, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD1); // logKillTimer| T key
		RegisterHotKey(NULL, LOG_KILL_TIMER_DETAILS, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD2); // logKillTimerDetails
		RegisterHotKey(NULL, LOG_KILL_TIMER_TO_FILE, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD3); // logKillTimerToFile

		RegisterHotKey(NULL, LOG_HITS, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD7); // logHits
		RegisterHotKey(NULL, LOG_HITS_DETAILS, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD8); // logHitsDetails
		RegisterHotKey(NULL, LOG_HITS_TO_FILE, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD9); // logHitsToFile
		RegisterHotKey(NULL, LOG_ATTACK_RATE, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD4); // logAttackRate
		RegisterHotKey(NULL, LOG_ATTACK_RATE_DETAILS, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD5); // logAttackRateDetails
		RegisterHotKey(NULL, LOG_ATTACK_RATE_TO_FILE, MOD_CONTROL | MOD_NOREPEAT, VK_NUMPAD6); // logAttackRateToFile
		RegisterHotKey(NULL, ATTACKRATE_CHAIN_HITS_MORE, MOD_CONTROL, VK_PRIOR); // AttackRateChainHits +
		RegisterHotKey(NULL, ATTACKRATE_CHAIN_HITS_LESS, MOD_CONTROL, VK_NEXT); // AttackRateChainHits -

		RegisterHotKey(NULL, ALLIES_LIST, MOD_CONTROL | MOD_NOREPEAT, 0x56); // alliesList| V key
		//RegisterHotKey(NULL, WVW_BONUS_MORE, MOD_CONTROL, VK_HOME); // wvwBonus +
		//RegisterHotKey(NULL, WVW_BONUS_LESS, MOD_CONTROL, VK_END); // wvwBonus -

		RegisterHotKey(NULL, FLOAT_CIRCLES, MOD_CONTROL | MOD_NOREPEAT, 0x46); // floatCircles
		RegisterHotKey(NULL, FLOAT_TYPE, MOD_CONTROL | MOD_SHIFT | MOD_NOREPEAT, 0x46); // floatType
		RegisterHotKey(NULL, FLOAT_RADIUS_MORE, MOD_CONTROL, VK_ADD); // floatRadius +
		RegisterHotKey(NULL, FLOAT_RADIUS_LESS, MOD_CONTROL, VK_SUBTRACT); // floatRadius -
		RegisterHotKey(NULL, FLOAT_ALLY_NPC, MOD_CONTROL, 0x31); // floatAllyNpc
		RegisterHotKey(NULL, FLOAT_ENEMY_NPC, MOD_CONTROL, 0x32); // floatEnemyNpc
		RegisterHotKey(NULL, FLOAT_ALLY_PLAYER, MOD_CONTROL, 0x33); // floatAllyPlayer
		RegisterHotKey(NULL, FLOAT_ALLY_PLAYER_PROF, MOD_CONTROL | MOD_SHIFT, 0x33); // floatAllyPlayerProf
		RegisterHotKey(NULL, FLOAT_ENEMY_PLAYER, MOD_CONTROL, 0x34); // floatEnemyPlayer
		RegisterHotKey(NULL, FLOAT_SIEGE, MOD_CONTROL, 0x35); // floatSiege

		RegisterHotKey(NULL, LOG_SPEEDOMETER, MOD_CONTROL, 0x39); // logSpeedometer| 9 key
		RegisterHotKey(NULL, LOG_SPEEDOMETER_ENEMY, MOD_CONTROL | MOD_SHIFT, 0x39); // logSpeedometerEnemy
		RegisterHotKey(NULL, LOG_DISPLACEMENT, MOD_CONTROL, 0x30); // logDisplacement| 0 key
		RegisterHotKey(NULL, LOG_DISPLACEMENT_ENEMY, MOD_CONTROL | MOD_SHIFT, 0x30); // logDisplacementEnemy
	}

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) && !this_thread::interruption_requested()) {
		try {
			PeekMessage(&msg, 0, 0, 0, 0x0001);
			switch (msg.message) {
				case WM_HOTKEY:
					if (msg.wParam == LEFTANDRIGHT) {
						leftAndRight = !leftAndRight;
						int iMappedKey = MapVirtualKey(0x51, 0); //Q key
						LPARAM lparam = (iMappedKey << 16) | 1;
						LPARAM lparamup = lparam | 0xc0000000;
						PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
						iMappedKey = MapVirtualKey(0x45, 0); //E key
						lparam = (iMappedKey << 16) | 1;
						lparamup = lparam | 0xc0000000;
						PostMessage(gw2hwnd, WM_KEYUP, iMappedKey, lparamup);
					}
					if (msg.wParam == DUNGEONTIMER) {
						if (!logTime) dungeonTimer.start();
						else dungeonTimer.stop();
						logTime = !logTime;
					}
					if (msg.wParam == AUTOCLICKER) autoClick = !autoClick;
					if (msg.wParam == SETLEFTRIGHT) SetPosLeftPosRight(40);
					if (msg.wParam == SHOWROTPOS) showRotAndPos = !showRotAndPos;
					if (msg.wParam == MOVETOAGENT) {
						if (follow) {
							ReleaseButton('w');
							ReleaseButton('d');
							ReleaseButton('a');
						}
						follow = !follow;
					}
					if (msg.wParam == HIDE_APP) hideApp = !hideApp;
					if (msg.wParam == LONGDIST) longDist = !longDist;
					if (msg.wParam == PARTYHP) partyHp = !partyHp;
					if (msg.wParam == SHOWPARTYNAMES) showPartyNames = !showPartyNames;

					if (msg.wParam == SETCURSORPOS) SetClickPosToCurrent();
					if (msg.wParam == EQOFFHAND) EqOffhand();
					if (msg.wParam == SETMAPPOS) {
						SetMapPosToCurrent(); radarSet = !radarSet;
					}
					if (msg.wParam == DOUBLECLICK) ClickAtPos(ClickPos);
					if (msg.wParam == ENABLERADAR) enableRadar = !enableRadar;
					if (msg.wParam == RADARTYPE) radarType = !radarType;

					if (msg.wParam == CHANGEZERO) changeZero = (changeZero == 3 ? 0 : changeZero + 1);
					if (msg.wParam == CHANGEONE) changeOne = (changeOne == 3 ? 0 : changeOne + 1);
					if (msg.wParam == CHANGETWO) changeTwo = (changeTwo == 3 ? 0 : changeTwo + 1);
					if (msg.wParam == CHANGETHREE) changeThree = (changeThree == 3 ? 0 : changeThree + 1);
					if (msg.wParam == RESETPARTYORDER) {
						changeZero = 0; changeOne = 1; changeTwo = 2; changeThree = 3;
					}
					if (msg.wParam == HELP) help = !help;
					if (msg.wParam == LOOP_LIMITER) loopLimiter = !loopLimiter;
					if (msg.wParam == SELF_HEALTH_PERCENT) selfHealthPercent = !selfHealthPercent;

					if (msg.wParam == target_health) targetHealth = !targetHealth;
					if (msg.wParam == TARGET_DIST) targetDist = !targetDist;
					if (msg.wParam == TARGET_INFO_T) targetInfoT = !targetInfoT;
					if (msg.wParam == TARGET_LOCK) targetLock = !targetLock;
					if (msg.wParam == DPS_ALLOW_NEGATIVE) dpsAllowNegative = !dpsAllowNegative;

					if (msg.wParam == LOG_DPS) logDpsArray = !logDpsArray;
					if (msg.wParam == LOG_DPS_DETAILS) {
						logDpsDetails = !logDpsDetails;
						dpsDeque.clear();
					}
					if (msg.wParam == LOG_KILL_TIMER) logKillTimer = !logKillTimer;
					if (msg.wParam == LOG_KILL_TIMER_DETAILS) logKillTimerDetails = !logKillTimerDetails;
					if (msg.wParam == LOG_KILL_TIMER_TO_FILE) logKillTimerToFile = !logKillTimerToFile;

					if (msg.wParam == LOG_HITS) logHits = !logHits;
					if (msg.wParam == LOG_HITS_DETAILS) logHitsDetails = !logHitsDetails;
					if (msg.wParam == LOG_HITS_TO_FILE) logHitsToFile = !logHitsToFile;

					if (msg.wParam == LOG_ATTACK_RATE) logAttackRate = !logAttackRate;
					if (msg.wParam == LOG_ATTACK_RATE_DETAILS) logAttackRateDetails = !logAttackRateDetails;
					if (msg.wParam == LOG_ATTACK_RATE_TO_FILE) logAttackRateToFile = !logAttackRateToFile;
					if (msg.wParam == ATTACKRATE_CHAIN_HITS_MORE) if (AttackRateChainHits < 50) AttackRateChainHits += 1;
					if (msg.wParam == ATTACKRATE_CHAIN_HITS_LESS) if (AttackRateChainHits > 1) AttackRateChainHits -= 1;

					if (msg.wParam == ALLIES_LIST) alliesList = !alliesList;
					if (msg.wParam == WVW_BONUS_MORE) if (wvwBonus < 10) wvwBonus += 1;
					if (msg.wParam == WVW_BONUS_LESS) if (wvwBonus > 0) wvwBonus -= 1;

					if (msg.wParam == FLOAT_CIRCLES) floatCircles = !floatCircles;
					if (msg.wParam == FLOAT_TYPE) floatType = !floatType;
					//if (msg.wParam == FLOAT_RADIUS_MORE) if (floatRadius < 10000) floatRadius += 100;
					//if (msg.wParam == FLOAT_RADIUS_LESS) if (floatRadius > 100) floatRadius -= 100;
					if (msg.wParam == FLOAT_ALLY_NPC) floatAllyNpc = !floatAllyNpc;
					if (msg.wParam == FLOAT_ENEMY_NPC) floatEnemyNpc = !floatEnemyNpc;
					if (msg.wParam == FLOAT_ALLY_PLAYER) floatAllyPlayer = !floatAllyPlayer;
					if (msg.wParam == FLOAT_ALLY_PLAYER_PROF) floatAllyPlayerProf = !floatAllyPlayerProf;
					if (msg.wParam == FLOAT_ENEMY_PLAYER) floatEnemyPlayer = !floatEnemyPlayer;
					if (msg.wParam == FLOAT_SIEGE) floatSiege = !floatSiege;

					if (msg.wParam == LOG_SPEEDOMETER) logSpeedometer = !logSpeedometer;
					if (msg.wParam == LOG_SPEEDOMETER_ENEMY) logSpeedometerEnemy = !logSpeedometerEnemy;
					if (msg.wParam == LOG_DISPLACEMENT) logDisplacement = !logDisplacement;
					if (msg.wParam == LOG_DISPLACEMENT_ENEMY) logDisplacementEnemy = !logDisplacementEnemy;
			}

			//boost::this_thread::interruption_point();
		}
		catch (boost::thread_interrupted&) {
			return;
		}
	}
}
