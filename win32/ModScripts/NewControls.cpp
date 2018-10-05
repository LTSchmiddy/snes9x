#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
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


//New Controls:
const uint32 selectBeamButton = 0x81100400;
const uint32 selectMissilesButton = 0x81100401;
const uint32 selectSuperMissilesButton = 0x81100402;
const uint32 selectPowerBombsButton = 0x81100403;
const uint32 selectGrappleButton = 0x81100405;
const uint32 selectXrayButton = 0x81100404;

const uint32 toggleChargeBeam = 0x81100407;
const uint32 toggleIceBeam = 0x81100408;
const uint32 toggleWaveBeam = 0x81100409;
const uint32 toggleSpazerBeam = 0x8110040a;
const uint32 togglePlasmaBeam = 0x8110040b;

const uint32 quickXRayButton = 0x81100200;
const uint32 quickGrappleButton = 0x81100201;
const uint32 quickMissileButton = 0x81100202;
const uint32 quickSuperMissileButton = 0x81100203;
const uint32 quickPowerBombButton = 0x81100204;
const uint32 quickMorphBallButton = 0x81100205;

const uint32 quickPowerBombSpecial1Button = 0x81100208;
const uint32 quickPowerBombSpecial2Button = 0x81100209;
const uint32 quickPowerBombSpecial3Button = 0x8110020a;
const uint32 quickPowerBombSpecial4Button = 0x8110020b;

const uint32 ForceSRAMSave = 0x81100800;

const uint32 Menu_Up = 0x81100808;
const uint32 Menu_Down = 0x81100809;
const uint32 Menu_Left = 0x8110080a;
const uint32 Menu_Right = 0x8110080b;
const uint32 Menu_A = 0x81100801;
const uint32 Menu_B = 0x81100802;
const uint32 Menu_PauseSwitch = 0x81100805;

const uint32 Control_Up = 0x81100108;
const uint32 Control_Down = 0x81100109;
const uint32 Control_Left = 0x8110010a;
const uint32 Control_Right = 0x8110010b;
const uint32 Control_A = 0x81100101;
const uint32 Control_B = 0x81100102;
const uint32 Control_L = 0x81100104;
const uint32 Control_R = 0x81100105;

bool MainPowerBombButtonWasPressed = false;
bool Special1ButtonWasPressed = false;
bool Special2ButtonWasPressed = false;
bool Special3ButtonWasPressed = false;
bool Special4ButtonWasPressed = false;


bool MenuPressed_Up = false;
bool MenuPressed_Down = false;
bool MenuPressed_Left = false;
bool MenuPressed_Right = false;
bool MenuPressed_A = false;
bool MenuPressed_B = false;
bool MenuPressed_PauseSwitch = false;

// Active Variables:====================================================
uint32 WeaponMode = 0x7e09d2;
//uint32 AutoCancelWeaponMode = 0x7e09d2;

uint8 oldBeamSet = 0xff;


bool doXray = false;
uint8 preXray = 0xff;


bool doGrapple = false;
bool killGrapple = false;
uint8 preGrapple = 0xff;

bool doQuickMissile = false;
bool didQuickMissile = false;
uint8 preQuickMissile = 0xff;


bool doQuickSuperMissile = false;
bool didQuickSuperMissile = false;
uint8 preQuickSuperMissile = 0xff;

bool doQuickPowerBomb = false;
bool didQuickPowerBomb = false;
uint8 preQuickPowerBomb = 0xff;


bool doQuickMorphball = false;
bool doQuickMorphballSwitcher = false;


int lastPress = -1;

bool sramsaveLastLoop = false;


bool toggleChargeBeamPressed = false;


bool FirePressed = false;
bool UpPressed = false;

unsigned SDHoldTimer = 0;
unsigned SDHoldTimerMax = 120;

unsigned SDCoolDownTimer = 0;
unsigned SDCoolDownTimerMax = 600;


//Methods:

bool NewControlsInputUpdate(uint32 id, bool pressed) {

	//if (id == ForceSRAMSave) {
	//	if (pressed) {

	//		printf("\nSRAM Check\n");
	//		if (!sramsaveLastLoop) {
	//			Memory.SaveSRAM(S9xGetFilename(".srm", SRAM_DIR));
	//			printf("Forced SRAM Save\n");

	//			printf("Health: %d\n", GetSamusHealth());
	//			printf("Max Health: %d\n", GetSamusMaxHealth());

	//			printf("Missiles: %d\n", GetSamusMissiles());
	//			printf("Max Missiles: %d\n", GetSamusMaxMissiles());

	//			printf("Super Missiles: %d\n", GetSamusSuperMissiles());
	//			printf("Max Super Missiles: %d\n", GetSamusMaxSuperMissiles());

	//			printf("Power Bombs: %d\n", GetSamusPowerBombs());
	//			printf("Max Health: %d\n", GetSamusMaxPowerBombs());

	//			printf("Reserve Tanks: %d\n", GetSamusReserveTanks());
	//			printf("Max Reserve Tanks: %d\n", GetSamusMaxReserveTanks());

	//			//health
	//			PrintByte(0xff0030);
	//			PrintByte(0xff0032);

	//			//missiles
	//			PrintByte(0xff0034);
	//			PrintByte(0xff0036);

	//			//S missiles
	//			PrintByte(0xff0038);
	//			PrintByte(0xff003a);


	//		}
	//		sramsaveLastLoop = true;

	//		//printf("SRAM: %d\n", (char *)Memory.SRAM);

	//	}
	//	else {
	//		sramsaveLastLoop = false;
	//}
	//}

	// Menu Controls:
	if (id == Menu_Up) {
		//printf("\nPressing Up\n");
		MenuPressed_Up = pressed;
	}

	else if (id == Menu_Down) {
		MenuPressed_Down = pressed;
	}

	else if (id == Menu_Left) {
		MenuPressed_Left = pressed;
	}

	else if (id == Menu_Right) {
		MenuPressed_Right = pressed;
	}

	else if (id == Menu_A) {
		MenuPressed_A = pressed;
	}

	else if (id == Menu_B) {
		MenuPressed_B = pressed;
	}

	else if (id == Menu_PauseSwitch) {
		MenuPressed_PauseSwitch = pressed;
	}

	if (AlexGetByteFree(0x7e0998) != 0x08) {

		if (id == Control_Up && MenuPressed_Up) {
			//printf("Spoofing Up");
			pressed = true;
		}

		if (id == Control_Down && MenuPressed_Down) {
			pressed = true;
		}

		if (id == Control_Left && MenuPressed_Left) {
			pressed = true;
		}

		if (id == Control_Right && MenuPressed_Right) {
			pressed = true;
		}

		if (id == Control_A && MenuPressed_A) {
			pressed = true;
		}

		if (id == Control_B && MenuPressed_B) {
			pressed = true;
		}

		//if (id == Control_R && MenuPressed_PauseSwitch) {
		//	pressed = true;
		//}
		
		if ((MenuPressed_PauseSwitch) && (CheckGameMode() == 0x0F)) {
			if ((CheckWhichPauseScreen() == 0x00) && (id == Control_R)) {
				pressed = true;
			}
			else if ((CheckWhichPauseScreen() == 0x01) && (id == Control_L)) {
				pressed = true;
			}

		}

	}

	if (AlexGetByteFree(0x7e0998) == 0x08) {


		if (id == 0x81100102 && doXray && !XraySMRedesignMode) {
			pressed = true;
			AlexSetByteFree(0x05, WeaponMode);
			//printf("%d\n", GetSamusHealth());
		}

		if (id == 0x81100100 && doXray && XraySMRedesignMode) {
			pressed = true;
			AlexSetByteFree(0x05, WeaponMode);
			//printf("%d\n", GetSamusHealth());
		}

		if (id == 0x81100100 && doGrapple && !killGrapple) {
			pressed = true;
			AlexSetByteFree(0x04, WeaponMode);
		}


		else if (id == 0x81100100 && doGrapple && killGrapple) {
			pressed = false;

			doGrapple = false;
			if (preGrapple != 0xff) {
				AlexSetByteFree(preGrapple, WeaponMode);
				preGrapple = 0xff;
			}

			killGrapple = false;
		}

		if (id == 0x81100100 && doQuickMissile) {
			if (!didQuickMissile) {
				pressed = true;
				didQuickMissile = true;
			}

			AlexSetByteFree(0x01, WeaponMode);
		}


		if (id == 0x81100100 && doQuickSuperMissile) {
			if (!didQuickSuperMissile) {
				pressed = true;
				didQuickSuperMissile = true;
			}
			AlexSetByteFree(0x02, WeaponMode);
		}

		if (id == 0x81100100 && doQuickPowerBomb) {
			//if (!didQuickPowerBomb) {
			pressed = true;
			didQuickPowerBomb = true;
			//}
			AlexSetByteFree(0x03, WeaponMode);
		}

		if (doQuickMorphball) {
			if (id == 0x81100108) {
				pressed = false;
			}


			if (id == 0x81100109) {

				doQuickMorphballSwitcher = !doQuickMorphballSwitcher;

				pressed = doQuickMorphballSwitcher;

			}



		}
		else {
			doQuickMorphballSwitcher = false;
		}


		//if (id = 0x81100100 && pressed){
		//	allowBeamToggling = false;
		//} else if (id = 0x81100100 && !pressed) {
		//	allowBeamToggling = true;
		//}

		if (AllowChargeBeamToggling) {
			if (id == toggleChargeBeam && AlexGetByteFree(0x7E09A9) != 0 && AlexGetByteFree(0x7E09A7) != 0) {
				if ((!toggleChargeBeamPressed) && pressed) {
					AlexSetByteFree(0x00, 0x7E09A7);
				}
				toggleChargeBeamPressed == pressed;
			}

			else if (id == toggleChargeBeam && AlexGetByteFree(0x7E09A9) != 0 && AlexGetByteFree(0x7E09A7) == 0) {
				
				if ((!toggleChargeBeamPressed) && pressed) {
					AlexSetByteFree(0x10, 0x7E09A7);
					//AlexSetByteFree(0x00, 0x7E09A7);
				}
				toggleChargeBeamPressed == pressed;

			}
		}
	}
	else {
		doQuickMorphball = false;
		//AllowChargeBeamToggling = false;
	}

	return pressed;


}


void NewControlsGameplayInputUpdate(uint32 id, bool pressed) {
	int buttonID = id;
	//int buttonID = id % 64;

	if (pressed && lastPress != buttonID) {
		//printf("%s ID 0x%08x\n is pressed\n", maptypename(maptype(keymap[id].type)), buttonID);

		//printf("ID 0x%08x\n", AlexGetByteFree(0x7e09a8));
		//printf("ID 0x%08x\n", (0x01 << 1));
		//printf("ID 0x%08x\n", AlexGetByteFree(0x7e09a8) & (0x01 << 1) == (0x01 << 1));
		//printf("\n\n");

		////if (buttonID == 0) {
		////	printf("Button 0 Pressed\n");
		////}
		//printf("\n");


		// Set Active Weapon:

		//Beam on 2-X
		if (buttonID == selectBeamButton) {
			AlexSetByteFree(0x00, WeaponMode);
		}

		//Missiles on 2-A
		else if (buttonID == selectMissilesButton) {
			AlexSetByteFree(0x01, WeaponMode);
		}

		//Super Missiles on 2-B
		else if (buttonID == selectSuperMissilesButton) {
			AlexSetByteFree(0x02, WeaponMode);
		}

		//Power Bombs on 2-Y
		else if (buttonID == selectPowerBombsButton) {
			AlexSetByteFree(0x03, WeaponMode);
		}

		else if (buttonID == selectGrappleButton && checkBit(AlexGetByteFree(0x7E09A5), 6)) {
			AlexSetByteFree(0x04, WeaponMode);
		}


		else if (buttonID == selectXrayButton && checkBit(AlexGetByteFree(0x7E09A5), 7)) {

			if (AlexGetByteFree(WeaponMode) == 0x05) {
				AlexSetByteFree(0x00, WeaponMode);
			}
			else {
				AlexSetByteFree(0x05, WeaponMode);
			}

		}

		//if (true) {



		lastPress = buttonID;
	}
	else if (lastPress == buttonID && !pressed) {
		lastPress = 0;
	}

	// Quick Morph-Ball:
	if (buttonID == quickMorphBallButton) {
		if (pressed) {
			doQuickMorphball = true;
		}
		else {
			doQuickMorphball = false;
		}
	}

	// Hold 2-L for the X-Ray Scope:
	if (!doGrapple && !doQuickMissile && !doQuickSuperMissile && !doQuickPowerBomb) {

		//if (buttonID == quickXRayButton && pressed) {
		if (buttonID == quickXRayButton && pressed && checkBit(AlexGetByteFree(0x7E09A5), 7)) {
			doXray = true;
			if (AlexGetByteFree(WeaponMode) != 0x05) {
				preXray = AlexGetByteFree(WeaponMode);
				AlexSetByteFree(0x05, WeaponMode);
			}
		}
		else if (buttonID == quickXRayButton && !pressed) {
			doXray = false;
			if (preXray != 0xff) {
				AlexSetByteFree(preXray, WeaponMode);
				preXray = 0xff;
			}
		}
	}


	// Hold 2-R for the Grapple Beam:
	if (!doXray && !doQuickMissile && !doQuickSuperMissile && !doQuickPowerBomb) {

		if (buttonID == quickGrappleButton && pressed && checkBit(AlexGetByteFree(0x7E09A5), 6)) {
			doGrapple = true;
			if (AlexGetByteFree(WeaponMode) != 0x04) {
				preGrapple = AlexGetByteFree(WeaponMode);
				AlexSetByteFree(0x04, WeaponMode);
			}
		}
		else if (buttonID == quickGrappleButton && !pressed) {
			killGrapple = true;
			//doGrapple = false;
			//if (preGrapple != 0xff) {
			//	AlexSetByteFree(preGrapple, WeaponMode);
			//	preGrapple = 0xff;
			//}
		}
	}

	// Press 2-Select for a Quick Missile:
	if (!doXray && !doGrapple && !doQuickSuperMissile && !doQuickPowerBomb) {

		if (buttonID == quickMissileButton && pressed) {
			doQuickMissile = true;
			if (AlexGetByteFree(WeaponMode) != 0x01) {
				preQuickMissile = AlexGetByteFree(WeaponMode);
				AlexSetByteFree(0x01, WeaponMode);

			}
		}
		else if (buttonID == quickMissileButton && !pressed) {
			doQuickMissile = false;
			if (preQuickMissile != 0xff) {
				AlexSetByteFree(preQuickMissile, WeaponMode);
				preQuickMissile = 0xff;
				didQuickMissile = false;
			}
		}
	}

	// Press 2-Start for a Quick Super Missile:
	if (!doXray && !doGrapple && !doQuickMissile && !doQuickPowerBomb) {

		if (buttonID == quickSuperMissileButton && pressed) {
			doQuickSuperMissile = true;
			if (AlexGetByteFree(WeaponMode) != 0x02) {
				//if (AlexGetByteFree(WeaponMode) != 0x02) {
				preQuickSuperMissile = AlexGetByteFree(WeaponMode);
				AlexSetByteFree(0x02, WeaponMode);
			}
		}
		else if (buttonID == quickSuperMissileButton && !pressed) {
			doQuickSuperMissile = false;
			if (preQuickSuperMissile != 0xff) {
				AlexSetByteFree(preQuickSuperMissile, WeaponMode);
				preQuickSuperMissile = 0xff;
				didQuickSuperMissile = false;
			}
		}
	}

	//if ((checkPowerBombButtons(buttonID)) && pressed) {
	//else if ((checkPowerBombButtons(buttonID)) && !pressed) {

	// Quick Power Bomb + Charge Beam Special Handling:
	if (!doXray && !doGrapple && !doQuickMissile && !doQuickSuperMissile) {
		//Standard Power Bomb:
		if (pressed) {
			if (buttonID == quickPowerBombButton) {
				if (!MainPowerBombButtonWasPressed) {
					MainPowerBombButtonWasPressed = true;
				}
				else {
					doQuickPowerBomb = true;
					if (AlexGetByteFree(WeaponMode) != 0x03) {
						//if (AlexGetByteFree(WeaponMode) != 0x02) {
						preQuickPowerBomb = AlexGetByteFree(WeaponMode);
						AlexSetByteFree(0x03, WeaponMode);
					}
				}

			}
			//Special 1 Power Bomb - Wave Beam:
			else if (buttonID == quickPowerBombSpecial1Button && checkBit(AlexGetByteFree(0x7e09a8), 0) && AlexGetByteFree(0x7E09D0) > 0x00 && AlexGetByteFree(0x7E09CE) > 0x00) {
				//else if (buttonID == quickPowerBombSpecial1Button && AlexGetByteFree(0x7e09a8) % 0x02 == 0x01) {
				if (!Special1ButtonWasPressed) {
					Special1ButtonWasPressed = true;
				}
				else {
					doQuickPowerBomb = true;
					if (AlexGetByteFree(WeaponMode) != 0x03) {
						//if (AlexGetByteFree(WeaponMode) != 0x02) {
						preQuickPowerBomb = AlexGetByteFree(WeaponMode);
						AlexSetByteFree(0x03, WeaponMode);
					}

					if (oldBeamSet == 0xff) {
						oldBeamSet = AlexGetByteFree(0x7E09A6);
						AlexSetByteFree(0x01, 0x7E09A6);
					}
				}
			}
			//Special 2 Power Bomb - Ice Beam:
			else if (buttonID == quickPowerBombSpecial2Button && checkBit(AlexGetByteFree(0x7e09a8), 1) && AlexGetByteFree(0x7E09D) > 0x00 && AlexGetByteFree(0x7E09CE) > 0x00) {
				//Special2ButtonWasPressed = true;

				if (!Special2ButtonWasPressed) {
					Special2ButtonWasPressed = true;
				}
				else {
					doQuickPowerBomb = true;
					if (AlexGetByteFree(WeaponMode) != 0x03) {
						//if (AlexGetByteFree(WeaponMode) != 0x02) {
						preQuickPowerBomb = AlexGetByteFree(WeaponMode);
						AlexSetByteFree(0x03, WeaponMode);
					}

					if (oldBeamSet == 0xff) {
						oldBeamSet = AlexGetByteFree(0x7E09A6);
						AlexSetByteFree(0x02, 0x7E09A6);
					}
				}
			}

			//Special 3 Power Bomb - Spazer:
			else if (buttonID == quickPowerBombSpecial3Button && checkBit(AlexGetByteFree(0x7e09a8), 2) && AlexGetByteFree(0x7E09D) > 0x00 && AlexGetByteFree(0x7E09CE) > 0x00) {
				//Special3ButtonWasPressed = true;

				if (!Special3ButtonWasPressed) {
					Special3ButtonWasPressed = true;
				}
				else {
					doQuickPowerBomb = true;
					if (AlexGetByteFree(WeaponMode) != 0x03) {
						//if (AlexGetByteFree(WeaponMode) != 0x02) {
						preQuickPowerBomb = AlexGetByteFree(WeaponMode);
						AlexSetByteFree(0x03, WeaponMode);
					}

					if (oldBeamSet == 0xff) {
						oldBeamSet = AlexGetByteFree(0x7E09A6);
						AlexSetByteFree(0x04, 0x7E09A6);
					}
				}
			}


			//Special 4 Power Bomb - Plasma Beam:
			else if (buttonID == quickPowerBombSpecial4Button && checkBit(AlexGetByteFree(0x7e09a8), 3) && AlexGetByteFree(0x7E09D) > 0x00 && AlexGetByteFree(0x7E09CE) > 0x00) {
				//Special4ButtonWasPressed = true;

				if (!Special4ButtonWasPressed) {
					Special4ButtonWasPressed = true;
				}

				else {
					doQuickPowerBomb = true;
					if (AlexGetByteFree(WeaponMode) != 0x03) {
						//if (AlexGetByteFree(WeaponMode) != 0x02) {
						preQuickPowerBomb = AlexGetByteFree(WeaponMode);
						AlexSetByteFree(0x03, WeaponMode);
					}


					if (oldBeamSet == 0xff) {
						oldBeamSet = AlexGetByteFree(0x7E09A6);
						AlexSetByteFree(0x08, 0x7E09A6);
					}
				}
			}

		}
		else {
			if (buttonID == quickPowerBombButton && MainPowerBombButtonWasPressed) {
				MainPowerBombButtonWasPressed = false;
				doQuickPowerBomb = false;
				if (preQuickPowerBomb != 0xff) {
					AlexSetByteFree(preQuickPowerBomb, WeaponMode);
					preQuickPowerBomb = 0xff;
					didQuickPowerBomb = false;
				}
			}

			else if (buttonID == quickPowerBombSpecial1Button && Special1ButtonWasPressed) {
				Special1ButtonWasPressed = false;
				doQuickPowerBomb = false;
				if (preQuickPowerBomb != 0xff) {
					AlexSetByteFree(preQuickPowerBomb, WeaponMode);
					preQuickPowerBomb = 0xff;
					didQuickPowerBomb = false;
				}


				if (oldBeamSet != 0xff) {
					AlexSetByteFree(oldBeamSet, 0x7E09A6);
					oldBeamSet = 0xff;
				}
			}

			if (buttonID == quickPowerBombSpecial2Button && Special2ButtonWasPressed) {
				Special2ButtonWasPressed = false;
				doQuickPowerBomb = false;
				if (preQuickPowerBomb != 0xff) {
					AlexSetByteFree(preQuickPowerBomb, WeaponMode);
					preQuickPowerBomb = 0xff;
					didQuickPowerBomb = false;
				}

				if (oldBeamSet != 0xff) {
					AlexSetByteFree(oldBeamSet, 0x7E09A6);
					oldBeamSet = 0xff;
				}
			}

			if (buttonID == quickPowerBombSpecial3Button && Special3ButtonWasPressed) {
				Special3ButtonWasPressed = false;
				doQuickPowerBomb = false;
				if (preQuickPowerBomb != 0xff) {
					AlexSetByteFree(preQuickPowerBomb, WeaponMode);
					preQuickPowerBomb = 0xff;
					didQuickPowerBomb = false;
				}

				if (oldBeamSet != 0xff) {
					AlexSetByteFree(oldBeamSet, 0x7E09A6);
					oldBeamSet = 0xff;
				}
			}

			if (buttonID == quickPowerBombSpecial4Button && Special4ButtonWasPressed) {
				Special4ButtonWasPressed = false;
				doQuickPowerBomb = false;
				if (preQuickPowerBomb != 0xff) {
					AlexSetByteFree(preQuickPowerBomb, WeaponMode);
					preQuickPowerBomb = 0xff;
					didQuickPowerBomb = false;
				}

				if (oldBeamSet != 0xff) {
					AlexSetByteFree(oldBeamSet, 0x7E09A6);
					oldBeamSet = 0xff;
				}
			}
		}

	}


	if (id == 0x81100100) {
		FirePressed = pressed;
	}
	if (id == 0x81100108) {
		UpPressed = pressed;
	}
}

void NewControls_Update() {
	if (NC_SelfDestruct) {
		if (CheckGameMode() == 0x08) {
			if (FirePressed && UpPressed && (AlexGetByteFree(0x7E09A7) != 0x00) && (AlexGetByteFree(WeaponMode) == 0x03) && (GetSamusPowerBombs > 0)) {
				if (SDHoldTimer >= SDHoldTimerMax) {
					if ((GetSamusHealth() > 10) || (GetSamusReserveTanks() != 0)) {
						SetSamusHealth(GetSamusHealth() - 1);
					}

				}
				else {
					SDHoldTimer++;
				}

			}
			else {
				SDHoldTimer = 0;
			}
		}
	}
}