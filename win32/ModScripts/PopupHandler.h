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



class SMMod_PopupMessage {
	public:
		bool Shown = false;
		bool HasNext = false;
		const char * MessageText;
		int delay;
		SMMod_PopupMessage* NextMessage;
		SMMod_PopupMessage* PrevMessage;
		void InitMessage(const char *, int);
};

void ShowMessage(const char *, int);

void PopupHandler_MainLoop(void);