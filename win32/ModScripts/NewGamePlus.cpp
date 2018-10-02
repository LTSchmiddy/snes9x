#include "ModScripts\NewGamePlus.h"

#include "ModScripts\Utilities.h"

#include "SMMods.h"
#include "wsnes9x.h"
#include "win32_sound.h"
#include "win32_display.h"
#include "CCGShader.h"
#include "../shaders/glsl.h"
#include "CShaderParamDlg.h"
#include "../snes9x.h"
#include "../memmap.h"
#include "../cpuexec.h"
#include "../display.h"
#include "../cheats.h"
#include "../controls.h"
#include "../conffile.h"
#include "../statemanager.h"
#include "InputCustom.h"

#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

using namespace std;

#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

#include <commctrl.h>
#include <io.h>
#include <time.h>
#include <direct.h>

//#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

unsigned RAMEquipmentStart = 0x7E09A2;
unsigned P1SaveEquipmentStart = 0xFF0010;

bool InNewGamePlusMode() {
	if (GetCurrentSaveFile() == 1) {
		return true;
	}
	return false;
}

void NewGamePlus_MainLoop() {

	if (!InNewGamePlusMode) {
		return;
	}

	// Starting a New Game Plus Save:
	if (GetCurrentPlayTimeSeconds() < 1) {
		SetSamusMissiles(GetP1SavedMaxMissiles());
		SetSamusMaxMissiles(GetP1SavedMaxMissiles());

		SetSamusSuperMissiles(GetP1SavedMaxSuperMissiles());
		SetSamusMaxSuperMissiles(GetP1SavedMaxSuperMissiles());

		SetSamusPowerBombs(GetP1SavedMaxPowerBombs());
		SetSamusMaxPowerBombs(GetP1SavedMaxPowerBombs());

		for (unsigned i = 0; i < 8; i++) {
			AlexSetByteFree(AlexGetByteFree(P1SaveEquipmentStart + i), RAMEquipmentStart + i);
		}

	}




}