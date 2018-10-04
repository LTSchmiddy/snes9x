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

//SMMod_PopupMessage * FirstMessage = nullptr;
SMMod_PopupMessage * LatestMessage = nullptr;

// Execution Variables:
SMMod_PopupMessage * CurrentMessage = nullptr;
int countToNext = 0;
// Class Methods:
void SMMod_PopupMessage::InitMessage(const char * newMessage, int newDelay) {
	MessageText = newMessage;
	delay = newDelay;


}


// Event Functions:
void ShowMessage(const char * newMessageText, int newDelay) { 
	SMMod_PopupMessage* newMessage = new SMMod_PopupMessage;

	newMessage->InitMessage(newMessageText, newDelay);

	if ((LatestMessage == nullptr) || (CurrentMessage == nullptr)) {
		//FirstMessage = newMessage;
		LatestMessage = newMessage;
		CurrentMessage = newMessage;
	}
	else {
		LatestMessage->NextMessage = newMessage;
		LatestMessage->HasNext = true;
		newMessage->PrevMessage = LatestMessage;
		LatestMessage = newMessage;
	}
}


bool ReadyMoveToNext() {
	if (countToNext >= LatestMessage->delay) {
		return true;
	}
	else {
		countToNext++;
	}

	return false;
}

void PopupHandler_MainLoop() {

	if ((LatestMessage == nullptr) || (CurrentMessage == nullptr)) {
		return;
	}
	else {
		if (!(CurrentMessage->Shown)) {
			CurrentMessage->Shown = true;
			S9xMessage(S9X_INFO, S9X_NETPLAY_NOT_SERVER, CurrentMessage->MessageText);
		}
		
		if (ReadyMoveToNext()) {

			if (CurrentMessage->HasNext == false) {
				return;
			}
			else {
				CurrentMessage = CurrentMessage->NextMessage;
				countToNext = 0;

				SMMod_PopupMessage * lastMessage = CurrentMessage->PrevMessage;
				delete lastMessage;
			}


		}
	}



}