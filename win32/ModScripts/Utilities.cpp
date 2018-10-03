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

// Memory Locations:
const uint32 SamusHealthSBA = 0x7e09C2;
const uint32 SamusMaxHealthSBA = 0x7e09C4;

const uint32 SamusMissilesSBA = 0x7e09C6;
const uint32 SamusMaxMissilesSBA = 0x7e09C8;

const uint32 SamusSuperMissilesSBA = 0x7e09CA;
const uint32 SamusMaxSuperMissilesSBA = 0x7e09CC;

const uint32 SamusPowerBombsSBA = 0x7e09CE;
const uint32 SamusMaxPowerBombsSBA = 0x7e09D0;

const uint32 SamusReserveTanksSBA = 0x7e09D6;
const uint32 SamusMaxReserveTanksSBA = 0x7e09D4;


bool checkBit(uint8 val, int pos) {
	//printf("ID 0x%08x\n", (val & (0x01 << pos) == (0x01 << pos)));
	return 0x00000000 != (val & (0x01 << pos));
}

// Game Data
//Health
int GetSamusHealth() {
	return AlexGet2BytesFree(SamusHealthSBA);
}

int GetSamusMaxHealth() {
	return AlexGet2BytesFree(SamusMaxHealthSBA);
}


void SetSamusHealth(uint16 val) {
	AlexSetByteFree(val & 0b0000000011111111, SamusHealthSBA);
	AlexSetByteFree(val >> 8, SamusHealthSBA + 1);
}

void SetSamusFullHealth() {
	AlexSetByteFree(AlexGetByteFree(SamusMaxHealthSBA), SamusHealthSBA);
	AlexSetByteFree(AlexGetByteFree(SamusMaxHealthSBA + 1), SamusHealthSBA + 1);
}

//Missiles
int GetSamusMissiles() {
	return AlexGetByteFree(SamusMissilesSBA);
	//return AlexGet2BytesFree(SamusMissilesSBA);
}

int GetSamusMaxMissiles() {
	return AlexGetByteFree(SamusMaxMissilesSBA);
	//return AlexGet2BytesFree(SamusMaxMissilesSBA);
}

void SetSamusMissiles(unsigned val) {
	AlexSetByteFree(val, SamusMissilesSBA);
	//return AlexGet2BytesFree(SamusMissilesSBA);
}

void SetSamusMaxMissiles(unsigned val) {
	AlexSetByteFree(val, SamusMaxMissilesSBA);
	//return AlexGet2BytesFree(SamusMaxMissilesSBA);
}


//Super Missiles
int GetSamusSuperMissiles() {
	return AlexGetByteFree(SamusSuperMissilesSBA);
	//return AlexGet2BytesFree(SamusSuperMissilesSBA);
}

int GetSamusMaxSuperMissiles() {
	return AlexGetByteFree(SamusMaxSuperMissilesSBA);
	//return AlexGet2BytesFree(SamusMaxSuperMissilesSBA);
}

void SetSamusSuperMissiles(unsigned val) {
	AlexSetByteFree(val, SamusSuperMissilesSBA);
	//return AlexGet2BytesFree(SamusMissilesSBA);
}

void SetSamusMaxSuperMissiles(unsigned val) {
	AlexSetByteFree(val, SamusMaxSuperMissilesSBA);
	//return AlexGet2BytesFree(SamusMaxMissilesSBA);
}



// Power Bombs
int GetSamusPowerBombs() {
	return AlexGetByteFree(SamusPowerBombsSBA);
	//return AlexGet2BytesFree(SamusPowerBombsSBA);
}

int GetSamusMaxPowerBombs() {
	return AlexGetByteFree(SamusMaxPowerBombsSBA);
	//return AlexGet2BytesFree(SamusMaxPowerBombsSBA);
}

void SetSamusPowerBombs(unsigned val) {
	AlexSetByteFree(val, SamusPowerBombsSBA);
	//return AlexGet2BytesFree(SamusMissilesSBA);
}

void SetSamusMaxPowerBombs(unsigned val) {
	AlexSetByteFree(val, SamusMaxPowerBombsSBA);
	//return AlexGet2BytesFree(SamusMaxMissilesSBA);
}

//Reserve Tanks
int GetSamusReserveTanks() {
	return AlexGet2BytesFree(SamusReserveTanksSBA);
}

int GetSamusMaxReserveTanks() {
	return AlexGet2BytesFree(SamusMaxReserveTanksSBA);
}

void SetSamusFullReserveTanks() {
	//AlexSetByteFree(AlexGetByteFree(SamusReserveTanksSBA), SamusReserveTanksSBA);
	//AlexSetByteFree(AlexGetByteFree(SamusMaxReserveTanksSBA + 1), SamusMaxReserveTanksSBA + 1);
}

void SetSamusReserveTanks(uint16 val) {
	AlexSetByteFree(val & 0b0000000011111111, SamusReserveTanksSBA);
	AlexSetByteFree(val >> 8, SamusReserveTanksSBA + 1);
}

// Main Gameplay Code: **********************************************************************

unsigned CheckGameMode() {
	return AlexGetByteFree(0x7e0998);
}


unsigned GetCurrentPlayTimeSeconds() {
	//Seconds + Minutes + Hours:
	return AlexGet2BytesFree(0x7E09DA) + AlexGet2BytesFree(0x7E09DC) * 60 + AlexGet2BytesFree(0x7E09DE) * 3600;
}

unsigned GetCurrentSaveFile() {
	return AlexGet2BytesFree(0x7E0952);
		//7E:0952 - 7E:0953
}



// Save 1 Data:
unsigned GetP1SavedPlayTimeSeconds() {
	//Seconds + Minutes + Hours:
	return AlexGet2BytesFree(0xFF004A) + AlexGet2BytesFree(0x7E094C) * 60 + AlexGet2BytesFree(0x7E094E) * 3600;
}


unsigned GetP1SavedMissiles() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF0034);
}

unsigned GetP1SavedMaxMissiles() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF0036);
}

unsigned GetP1SavedSuperMissiles() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF0038);
}

unsigned GetP1SavedMaxSuperMissiles() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF003a);
}


unsigned GetP1SavedPowerBombs() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF003c);
}

unsigned GetP1SavedMaxPowerBombs() {
	//Seconds + Minutes + Hours:
	return AlexGetByteFree(0xFF003e);
}



//*******************************************************
// Misc - Not In Use:
void ArmWaveBeam(bool on) {

}

bool GetIceBeamCollected() {
	return checkBit(AlexGetByteFree(0x7e09A8), 1);
}

bool GetIceBeamEquipped() {
	return checkBit(AlexGetByteFree(0x7e09A6), 1) && checkBit(AlexGetByteFree(0x7e09A8), 1);
}