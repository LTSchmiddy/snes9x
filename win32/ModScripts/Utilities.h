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



// Memory Locations:
extern const uint32 SamusHealthSBA;
extern const uint32 SamusMaxHealthSBA;

extern const uint32 SamusMissilesSBA;
extern const uint32 SamusMaxMissilesSBA;

extern const uint32 SamusSuperMissilesSBA;
extern const uint32 SamusMaxSuperMissilesSBA;

extern const uint32 SamusPowerBombsSBA;
extern const uint32 SamusMaxPowerBombsSBA;

extern const uint32 SamusReserveTanksSBA;
extern const uint32 SamusMaxReserveTanksSBA;

bool checkBit(uint8, int);

// Game Data
//Health
int GetSamusHealth(void);

int GetSamusMaxHealth(void);

void SetSamusFullHealth(void);

void SetSamusHealth(uint16);


//Missiles
int GetSamusMissiles(void);

int GetSamusMaxMissiles(void);

void SetSamusMissiles(unsigned);

void SetSamusMaxMissiles(unsigned);




//Super Missiles
int GetSamusSuperMissiles(void);

int GetSamusMaxSuperMissiles(void);

void SetSamusSuperMissiles(unsigned);

void SetSamusMaxSuperMissiles(unsigned);




// Power Bombs
int GetSamusPowerBombs(void);

int GetSamusMaxPowerBombs(void);

void SetSamusPowerBombs(unsigned);

void SetSamusMaxPowerBombs(unsigned);



//Reserve Tanks
int GetSamusReserveTanks(void);

int GetSamusMaxReserveTanks(void);

void SetSamusFullReserveTanks(void);

void SetSamusReserveTanks(uint16);


// Main Gameplay Code: **********************************************************************

unsigned GetCurrentPlayTimeSeconds(void);

unsigned GetP1SavedPlayTimeSeconds(void);


bool GetWaveBeamCollected(void);

bool GetIceBeamCollected(void);

bool GetSpazerBeamCollected(void);

bool GetPlasmaBeamCollected(void);



bool GetIceBeamEquipped(void);


unsigned CheckGameMode(void);

unsigned CheckWhichPauseScreen(void);

unsigned GetCurrentSaveFile(void);

// P1 Save Data:
unsigned GetP1SavedMissiles(void);

unsigned GetP1SavedMaxMissiles(void);

unsigned GetP1SavedSuperMissiles(void);

unsigned GetP1SavedMaxSuperMissiles(void);

unsigned GetP1SavedPowerBombs(void);

unsigned GetP1SavedMaxPowerBombs(void);
