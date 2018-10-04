//#pragma once


//#include <map>
//#include <set>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <assert.h>
//#include <ctype.h>


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

//Config Variables:
//extern bool SaveStationsHeal;
//extern bool XraySMRedesignMode;
//extern bool UseNewControls;
//extern bool AllowChargeBeamToggling;
//extern bool QuitOnExit;


extern bool SaveStationsHeal;
extern bool BetterReserveTanks;
extern bool XraySMRedesignMode;
extern bool UseNewControls;
extern bool SaveStateIntegration;
extern bool AllowChargeBeamToggling;
extern bool QuitOnExit;
extern bool Save2IsNewGamePlus;
extern bool SSI_AllowSaveStatesInNewGamePlus;
extern bool SSI_SaveStatesDisabled;

//Methods:
void HideMenu(void);
int SaveStatesAllowed(void);
//bool SaveStatesAllowed(void);

void SMOnLoadState(void);


void SMOnLoadRom(void);

bool SMInputUpdate(uint32 id, bool pressed);

void SMGameplayControl(uint32 id, bool pressed);


void SMMainLoop(void);


void SMMainLoop_Late(void);

void SMOnEndRom(void);