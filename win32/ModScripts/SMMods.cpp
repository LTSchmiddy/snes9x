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
#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "ModScripts\NewGamePlus.h"
#include "ModScripts\PopupHandler.h"

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




// Constant Variables: ===============================================


string TrueString = "true";
string FalseString = "false";

// Active Variables:====================================================
bool LeftTitleScreen = false;



//Better Save Stations:
int SMLastSaveTime = 0;

//File Config:

bool SaveStationsHeal = false;
bool BetterReserveTanks = false;
bool XraySMRedesignMode = false;
bool UseNewControls = false;
bool SaveStateIntegration = false;
bool AllowChargeBeamToggling = false;
bool QuitOnExit = false;
bool Save2IsNewGamePlus = false;
bool SSI_AllowSaveStatesInNewGamePlus = false;
bool SSI_SaveStatesDisabled = false;


//const char * DefaultConfigPath = "SuperMetroid_GameConfig.txt";
const char * DefaultConfigPathBase = "SuperMetroid_GameConfig.txt";
//const string ConfigPath = "SuperMetroidConfig.conf";
const string SaveStationsHealStr = "SaveStationsHeal";
const string BetterReserveTanksStr = "BetterReserveTanks";
const string XraySMRedesignModeStr = "XrayMetroidRedesignMode";
const string UseNewControlsStr = "UseNewControls";
const string SaveStateIntegrationStr = "SaveStateIntegration";
const string AllowChargeBeamTogglingStr = "AllowChargeBeamToggling";
const string QuitOnExitStr = "QuitOnExit";
const string Save2IsNewGamePlusStr = "Save2IsNewGamePlus";
const string SSI_AllowSaveStatesInNewGamePlusStr = "SSI_AllowSaveStatesInNewGamePlus";
const string SSI_SaveStatesDisabledStr = "SSI_SaveStatesDisabled";


unsigned LastReserveTanks = 0;
const unsigned RT_HitDelay = 3600;
unsigned RT_HitDelayCounter = 0;
const unsigned RT_FillDelay = 20;
unsigned RT_FillDelayCounter = 0;

//Function Declairations: ================================================================================================
void SMGameplayControl(uint32, bool);
void LoadSMGameConfig();



// Function Methods: ================================================================================================
//Tools:

void PrintByte(uint32 addr) {
	printf("Address 0x%08x = 0x%08x\n", addr, AlexGet2BytesFree(addr));
}



//Utilities: **********************************************************************


//External Calls:
void HideMenu() {
	SetMenu(GUI.hWnd, NULL);
}

int SaveStatesAllowed() {
//bool SaveStatesAllowed() {
	if (!SaveStateIntegration) {
		return 1;
	}

	if (Save2IsNewGamePlus) {
		if (InNewGamePlusMode() && !SSI_AllowSaveStatesInNewGamePlus) {
			ShowMessage("Save States are not allowed in New Game Plus.");
			return 0;
		}
	}


	if (CheckGameMode() == 0x1A) {
		
		return 2;
	}

	if (CheckGameMode() != 0x08) {
		ShowMessage("Save States are only available during gameplay.");
		return 0;
	}

	return 1;
}

// Main Loop Function:

void SMOnLoadRom() {
	LeftTitleScreen = false;
	LoadSMGameConfig();
	SMLastSaveTime = GetP1SavedPlayTimeSeconds();

	if (Save2IsNewGamePlus) {
		NewGamePlus_OnLoadRom();
	}

	if (BetterReserveTanks) {
		RT_HitDelayCounter = RT_HitDelay;
		RT_FillDelayCounter = 0;
	}

}

void ReadGameConfigFromFile(const char * path) {
	std::ifstream infile;

	infile.open(path, ios::in);

	if (infile.is_open()) {
		printf("Opened GameConfig File '");
		printf(path);
		printf("'\n");
	}
	else {

		printf("GameConfig File '");
		printf(path);
		printf("' not found. Continuing without...\n");

		return;
	}

	printf("Reading Config\n");
	std::string line;

	//while (infile >> line)
	while (std::getline(infile, line))
	{


		if (line.find("#") != std::string::npos) {
			continue;
		}

		if (line.find(SaveStationsHealStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				SaveStationsHeal = true;
				printf("Enabling Save Station Healing\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				SaveStationsHeal = false;
				printf("Disabling Save Station Healing\n");
			}


		}

		if (line.find(BetterReserveTanksStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				BetterReserveTanks = true;
				printf("Enabling Better Reserve Tanks\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				BetterReserveTanks = false;
				printf("Disabling Better Reserve Tanks\n");
			}


		}
				
		if (line.find(AllowChargeBeamTogglingStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				AllowChargeBeamToggling = true;
				printf("Enabling Charge Beam Toggling\n");
			}
			else if (line.find(FalseString) != std::string::npos) {
				AllowChargeBeamToggling = false;
				printf("Disabling Charge Beam Toggling\n");
			}


		}

		if (line.find(XraySMRedesignModeStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("Enabling  X-Ray: Super Metroid Redesigned X-Ray Mode\n");
				XraySMRedesignMode = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("Disabling X-Ray: Super Metroid Redesigned Mode\n");
				XraySMRedesignMode = false;
			}
		}

		if (line.find(UseNewControlsStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("Enabling Additional Controls\n");
				UseNewControls = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("Disabling Additional Controls\n");
				UseNewControls = false;
			}
		}

		if (line.find(SaveStateIntegrationStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("Enabling SaveState Integration\n");
				SaveStateIntegration = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("Disabling SaveState Integration\n");
				SaveStateIntegration = false;
			}
		}

		if (line.find(QuitOnExitStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("Enabling Quit on Exit\n");
				QuitOnExit = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("Disabling Quit on Exit\n");
				QuitOnExit = false;
			}
		}
		if (line.find(Save2IsNewGamePlusStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("Save Slot 2 is New Game Plus\n");
				Save2IsNewGamePlus = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("Save Slot 2 is NOT New Game Plus\n");
				Save2IsNewGamePlus = false;
			}
		}

		if (line.find(SSI_AllowSaveStatesInNewGamePlusStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("SaveStateIntegration: Allowing Save States In New Game Plus\n");
				SSI_AllowSaveStatesInNewGamePlus = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("SaveStateIntegration: Disallowing Save States In New Game Plus\n");
				SSI_AllowSaveStatesInNewGamePlus = false;
			}
		}


		if (line.find(SSI_SaveStatesDisabledStr) != std::string::npos) {

			std::getline(infile, line);
			if (line.find(TrueString) != std::string::npos) {
				printf("SaveStateIntegration: Save States are COMPLETELY disabled\n");
				SSI_SaveStatesDisabled = true;
			}
			else if (line.find(FalseString) != std::string::npos) {
				printf("SaveStateIntegration: Save States are NOT completely disabled\n");
				SSI_SaveStatesDisabled = false;
			}
		}


		//if (line.find(AllowBeamTogglingStr) != std::string::npos) {
		//	printf("Enabling Charge Beam Toggling\n");
		//	AllowChargeBeamToggling = true;
		//}

	}


}

void LoadSMGameConfig() {

	const char * DefaultConfigPath = S9xGetFileInDirectory(DefaultConfigPathBase, HOME_DIR);
	printf("\nDefault GameConfig Path: ");
	//strcat(DefaultConfigPath, DefaultConfigPathBase);
	printf(DefaultConfigPath);
	printf("\n");

	ReadGameConfigFromFile(DefaultConfigPath);

	const char * ROMConfigPath = S9xGetFilename("_GameConfig.txt", PATCH_DIR);
	printf("ROM GameConfig Path: ");
	printf(ROMConfigPath);
	printf("\n");
	ReadGameConfigFromFile(ROMConfigPath);
}

//And this is where the extra controls are applied:
bool SMInputUpdate(uint32 id, bool pressed) {

	if (UseNewControls) {
		pressed = NewControlsInputUpdate(id, pressed);
	}

	return pressed;
}


void SMGameplayControl(uint32 id, bool pressed) {
	if (UseNewControls) {
		NewControlsGameplayInputUpdate(id, pressed);
	}
}


void SMMainLoop() {
	if (Save2IsNewGamePlus) {
		NewGamePlus_MainLoop();
	}

	if (UseNewControls) {
		NewControls_Update();
	}

	PopupHandler_MainLoop();


	if (SaveStationsHeal) {
		if (AlexGetByteFree(0x7e0998) == 0x07) {
			SetSamusFullHealth();
			SetSamusFullReserveTanks();
			SMLastSaveTime = GetP1SavedPlayTimeSeconds();
		}

		else if (AlexGetByteFree(0x7e0998) == 0x08) {

			if (GetP1SavedPlayTimeSeconds() != SMLastSaveTime) {
				SetSamusFullHealth();
				SetSamusFullReserveTanks();
;
			}
			SMLastSaveTime = GetP1SavedPlayTimeSeconds();
		}
	}


	if (BetterReserveTanks) {
		if (CheckGameMode() == 0x08) {


			bool hit = false;


			if ((LastReserveTanks > GetSamusReserveTanks())) {
				hit = true;
			}

			if (hit) {
				RT_HitDelayCounter = RT_HitDelay;
				RT_FillDelayCounter = 0;

			}
			else {
				if (RT_HitDelayCounter > 0) {
					RT_HitDelayCounter--;
				}
				else {
					if (RT_FillDelayCounter > 0) {
						RT_FillDelayCounter--;
					}
					else {
						RT_FillDelayCounter = RT_FillDelay;

						if (GetSamusReserveTanks() < GetSamusMaxReserveTanks()) {
							SetSamusReserveTanks(GetSamusReserveTanks() + 1);
						}

						if (GetSamusReserveTanks() > GetSamusMaxReserveTanks()) {
							SetSamusReserveTanks(GetSamusMaxReserveTanks());
						}
					}
				}
			}
			LastReserveTanks = GetSamusReserveTanks();
		}
	}
}


void SMMainLoop_Late() {
	if (QuitOnExit) {
		if (LeftTitleScreen) {
			if (AlexGetByteFree(0x7e0998) == 0x01) {
				DoQuit();
			}
		}

		else if (AlexGetByteFree(0x7e0998) == 0x04) {
			LeftTitleScreen = true;
		}
	}

}




void SMOnEndRom() {
	LeftTitleScreen = false;


}

void SMOnLoadState() {
 	SMLastSaveTime = GetP1SavedPlayTimeSeconds();
	if (Save2IsNewGamePlus) {
		void NewGamePlus_OnLoadState();
	}

	if (BetterReserveTanks) {
		RT_HitDelayCounter = RT_HitDelay;
		RT_FillDelayCounter = 0;
	}

}

