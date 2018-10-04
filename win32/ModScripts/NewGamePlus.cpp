#include "ModScripts\NewGamePlus.h"

#include "ModScripts\Utilities.h"
#include "ModScripts\PopupHandler.h"

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

// HealthRegen Info:
unsigned LastHealth = 0;
unsigned StaticDamageMult = 3;
const unsigned HitDelay = 600;
unsigned HitDelayCounter = 0;
const unsigned FillDelay = 60;
unsigned FillDelayCounter = 0;

bool HideThisRegenChange = false;
bool RecheckHealth = false;

unsigned LastRegen = 0;
unsigned LastDamageMult = 0;

bool OnLoadSlotMessages = false;
bool OnSlotMenuMessages = false;

bool InNewGameUltraMode() {
	if (GetCurrentSaveFile() == 2) {
		return true;
	}
	return false;
}

bool InNewGamePlusMode() {
	if (InNewGameUltraMode()) {
		return true;
	}

	if (GetCurrentSaveFile() == 1) {
		return true;
	}
	return false;
}

unsigned MiniBossesDefeated() {
	unsigned retVal = 0;

	//Bomb Torizo
	if (checkBit(AlexGetByteFree(0x7ED828), 2)) {
		retVal++;
	}

	//Spore Spawn
	if (checkBit(AlexGetByteFree(0x7ED829), 1)) {
		retVal++;
	}

	//Crocomire
	if (checkBit(AlexGetByteFree(0x7ED82A), 1)) {
		retVal++;
	}

	//Golden Torizo
	if (checkBit(AlexGetByteFree(0x7ED82A), 2)) {
		retVal++;
	}

	//Golden Torizo
	if (checkBit(AlexGetByteFree(0x7ED82C), 1)) {
		retVal++;
	}


	return retVal;
}

unsigned BossesDefeated() {
	unsigned retVal = 0;

	//Kraid
	if (checkBit(AlexGetByteFree(0x7ED829), 0)) {
		retVal++;
	}

	//Phantoon
	if (checkBit(AlexGetByteFree(0x7ED82B), 0)) {
		retVal++;
	}

	//Draygon
	if (checkBit(AlexGetByteFree(0x7ED82C), 0)) {
		retVal++;
	}

	//Ridley
	if (checkBit(AlexGetByteFree(0x7ED82A), 0)) {
		retVal++;
	}

	return retVal;
}

unsigned DamageMult() {
	return (BossesDefeated() * 2) + 2;
}

void ShowHealthRegenMessage(unsigned regenVal) {
	//S9X_ROM_INFO,
	//S9X_HEADERS_INFO,
	//S9X_CONFIG_INFO,
	//S9X_TURBO_MODE,
	//S9X_NETPLAY_NOT_SERVER,
	if (!InNewGamePlusMode()) {
		return;
	}

	if (regenVal == 0) {
		ShowMessage("No Health Regen", 60);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Welcome to New Game Plus.");
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "No Health Regen");
	} 
	else if (regenVal == 1) {
		ShowMessage("Health Regen: 1 per Second.", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: 1 per Second.");
	}
	else if (regenVal == 2) {
		ShowMessage("Health Regen: 2 per Second.", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: 2 per Second.");
	}
	else if (regenVal == 3) {
		ShowMessage("Health Regen: 3 per Second.", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: 3 per Second.");
	}
	else if (regenVal == 4) {
		ShowMessage("Health Regen: 4 per Second.", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: 4 per Second.");
	}
	else if (regenVal == 5) {
		ShowMessage("Health Regen: 5 per Second.", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: 5 per Second.");
	}
	else {
		ShowMessage("Health Regen: More than 5 per Second... Somehow...", 180);
		//S9xMessage(S9X_INFO, S9X_TURBO_MODE, "Health Regen: More than 5 per Second... Somehow...");
	}

}

void ShowDamageMultMessage(unsigned damMultVal) {
	//S9X_ROM_INFO,
	//S9X_HEADERS_INFO,
	//S9X_CONFIG_INFO,
	//S9X_TURBO_MODE,
	//S9X_NETPLAY_NOT_SERVER,
	if (!InNewGameUltraMode()) {
		return;
	}

	if (damMultVal <= 2) {
	
		ShowMessage("So, we're doing this again...", 180);
		ShowMessage("You will take 2x damage.", 180);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "Welcome to New Game Ultra.		(You will take 2x damage.)");
	}
	else if (damMultVal <= 4) {
		ShowMessage("The Space Pirates are worried...", 180);
		ShowMessage("You will now take 4x damage.", 180);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "The Space Pirates are getting worried...		(You now take 4x damage.)");
	}
	else if (damMultVal <= 6) {
		ShowMessage("You reflect on the fate of your surrogate home...", 180);
		ShowMessage("You will now take 6x damage.", 180);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "You reflect on the fate of your surrogate home...		(You now take 6x damage.)");
	}
	else if (damMultVal <= 8) {
		ShowMessage("Mother Brain and Tourian are in a panic...", 180);
		ShowMessage("You will now take 8x damage.", 180);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "Mother Brain and Tourian are in a panic...		(You now take 8x damage.)");
	}
	else if (damMultVal <= 10) {
		ShowMessage("Let's finish this...", 180);
		ShowMessage("You will now take 10x damage.", 180);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "Let's finish this...		(You now take 10x damage.)");
	}
	else {
		ShowMessage("... Umm, Something went wrong, and you're screwed.		 (Damage Multiplier > 10x. This isn't supposed to happen.)", 60);
		//S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, "... Umm, Something went wrong, and you're screwed.		 (Damage Multiplier > 10x. This isn't supposed to happen.)");
	}

}




// *********************************************** Feature Events: ***********************************************

void NewGamePlus_OnLoadRom() {
	//LastRegen = 0;
	//HideThisRegenChange = true;
}


void NewGamePlus_MainLoop() {
	
	if (CheckGameMode() == 0x01) {
		LastRegen = 0;
		LastHealth = GetSamusHealth();
		LastDamageMult = DamageMult();
	}

	if (CheckGameMode() == 0x04) {
		if (!OnSlotMenuMessages) {
			ShowMessage("Save Slot A is Normal Play.", 120);
			ShowMessage("Save Slot B is New Game Plus.", 120);
			ShowMessage("Save Slot C is New Game Ultra.", 120);

			OnSlotMenuMessages = true;
		}

	}
	else {
		OnSlotMenuMessages = false;
	}

	if (!InNewGamePlusMode()) {
		LastRegen = 0;
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
	
	

	if (CheckGameMode() == 0x07) {
		if (!OnLoadSlotMessages) {
			ShowDamageMultMessage(DamageMult());
			ShowHealthRegenMessage(MiniBossesDefeated());
			
			OnLoadSlotMessages = true;
		}

		LastDamageMult = DamageMult();
		LastRegen = MiniBossesDefeated();
		LastHealth = GetSamusHealth();
	}
	else {
		OnLoadSlotMessages = false;
	}



	if (CheckGameMode() == 0x08) {
		//if (LastHealth == GetSamusHealth()) {
			//RecheckHealth = false;
			//LastHealth = GetSamusHealth();
			//SetSamusHealth(LastHealth);

		//}

		bool hit = false;

		//if ((LastHealth > GetSamusHealth()) && !RecheckHealth) {
		if ((LastHealth > GetSamusHealth())) {
			hit = true;
		}

		if (hit) {
			HitDelayCounter = HitDelay;
			FillDelayCounter = 0;

			//if (!RecheckHealth) {

				if (InNewGameUltraMode()) {
					SetSamusHealth(LastHealth - ((LastHealth - GetSamusHealth()) * (DamageMult())));
				}
				else {
					SetSamusHealth(LastHealth - ((LastHealth - GetSamusHealth()) * StaticDamageMult));
				}
			//}
			//else {
			//	RecheckHealth = false;
			//}

		}
		else {
			if (HitDelayCounter > 0) {
				HitDelayCounter--;
			}
			else {
				if (FillDelayCounter > 0) {
					FillDelayCounter--;
				}
				else {
					FillDelayCounter = FillDelay;

					if (GetSamusHealth() < GetSamusMaxHealth()) {
						SetSamusHealth(GetSamusHealth() + MiniBossesDefeated());
					}
					if (GetSamusHealth() > GetSamusMaxHealth()) {
						SetSamusHealth(GetSamusMaxHealth());
					}

				}
			}
		}
		LastHealth = GetSamusHealth();
		//RecheckHealth = false;


		if (MiniBossesDefeated() != LastRegen) {
			//if (HideThisRegenChange) {
			//	HideThisRegenChange = false;
			//}
			//else {
			ShowHealthRegenMessage(MiniBossesDefeated());
			//}

		}
		LastRegen = MiniBossesDefeated();


		if (DamageMult() != LastDamageMult) {
			ShowDamageMultMessage(DamageMult());
		}
		LastDamageMult = DamageMult();


		


	}


	
}

void NewGamePlus_OnLoadState() { 
	if (!InNewGamePlusMode()) {
		return;
	}
	LastHealth = GetSamusHealth();
	//LastDamageMult = DamageMult();
	//RecheckHealth = true;
	//ShowHealthRegenMessage(MiniBossesDefeated());
	HitDelayCounter = HitDelay;
	FillDelayCounter = 0;
}