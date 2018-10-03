#include "ModScripts\AM2RMusic.h"

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
#include "ModScripts\libZPlay\libzplay.h"
//#include "ModScripts\libZPlay\libZPlayNET.h"

using namespace libZPlay;


ZPlay *player;



void Music_OnAppStart() {
	player = CreateZPlay();
}



void StartMusicExp() {
	const char * SongName = S9xGetFileInDirectory("Serris.mp3", HOME_DIR);


	if (player->OpenFile(SongName, sfAutodetect) == 0)
	{
		printf("Audio File Not Found");
	}

	player->Play();
}

void StopMusicExp() {
	player->Stop();


}

void Music_OnAppEnd() {
	player->Release();
}
