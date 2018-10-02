# Super Metroid - PC Edition
*A port of the Snes9x emulator*

DISCLAIMER: Super Metroid ROM not included. Google it.

"Super Metroid - PC Edition" is a modified version of the Snex9X emulator (link to their site in section 6) specifically designed for playing Super Metroid and any ROM Hacks based on it. Unlike the vanilla version of the emulator, it makes a handful of improvements and adds some new controls to the game by means of memory manipulation (and the occasional input spoof) during runtime. And since all of this is handled by the emulator's own execution code (no changes, soft or hard, are made to the ROM itself), these improvements can be applied to ANY Super Metroid ROM hack. On top of that, Snes9X already has a number of featured to improve the visuals and sound of the game, and this copy of the emulator is optimized for Super Metroid by default.



=====================================================================================================

Table of Contents:

1) Introduction

2) Features

3) How To Configure

4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here)

5) Links

6) Conclusion

=====================================================================================================

===== 1) Introduction ===============================================================================

As Super Metroid is one of my favorite games of all time, and it makes me bit sad sad that this genre-defining classic hasn't seen a remake since... ever. Seriously, it's one of the handful of retro games who's mechanics haven't aged almost at all, and yet the only official version of the game that exists is the original from 24 years ago. Having a fair bit of experience with the Unity Game Engine (in which I am developing my own game), I've considered attempting a fan remake myself, perhaps something along the lines of the fantastic AM2R (which you you can still find with a brief google search, BTW). But I'd rather my work not suffer the same DCMA-based fate as the aforementioned love-letter to the franchise.

Well, within the last few months, I've discovered the wonderful world of ROM-hacking, Super Metroid in particular, and I've been dripping with excitement ever since. I've played through a handful of hacks and even applied a few tweaks for my own enjoyment.

For the record, I'm not new to the world of emulation for retro-games, having a moderate library of classic titles and others from my own childhood. I use LaunchBox to manage this library, along with my games from Steam and other places. Because I'm rather OCD, I like my emulated games to feel as native to my PC as I can make them. I had a seperate copy of Snes9X with the controls/setting configured for an ideal Super Metroid experience, and had I started writing a python script to allow me to select what ROM/ROM-hack to play when I launched the game from my library, when the idea for this project struck me: Instead of modding the ROM, mod the emulator.

Ok, enough with the background info. 

=====================================================================================================

===== 2) Features ===================================================================================
So, exactly what does "Super Metroid - PC Edition" have to offer?

Each major feature listed below can be enabled or disabled in a special config file. More on that later.


a) ADDITIONAL CONTROLS:
(This is probably the biggest feature I have so far.)

I've added a number of additional controls to the game. This system works by hi-jacking joypads 2, 3, and 4 in the emulator, so they should work with your hardware controllers. 

Most notably, I've added quick-fire buttons for the Missiles, Super Missiles, Power Bombs, Grapple Beam, and X-Ray Scope. Seriously, you have no idea what a difference it makes to have the missiles and super missiles on quick-fire buttons. The combat in the game is SO much more fun and fluid when you don't have to stop what your doing and switch weapon modes constantly. Not to mention that having the super missiles on a hot button makes them a much more tactical option for combat, instead of them being the "OH CRAP! BAIL ME OUT!" weapon they tend to be otherwise. The grapple beam benefits even more so, since using the grapple beam prevents you from using your other weapons, and the grapple beam is not the best in a combat situation. On a quick-fire button, you can now flip between shooting and grappling seamlessly. All of this opens up a lot more options for daring manuveres and badass moments in your gameplay.

While they don't provide as much of an improvement to the game, the additional quick buttons for the power bombs and the x-ray scope are a wonderful convienence, especially since the x-ray normally takes the place of the sprint button. Note that the quick powerbomb button does not put you into morphball. If you use it while standing, you'll simply fire your beam. 

Additionally, I've added quick-fire buttons for each beam's power-bomb+charge combo. I know they're supposed to be 'secret moves', but considering how inconvienent they are to use, I figured they're better off this way. There is a minor visual glitch where they use the sprites from the currently equipped set of beams, but the functionality remains the same (and I kinda like how they look, tbh), so I'm keeping it.

There are also selection buttons for each weapon, just in case. However, if you switch to a weapon, the quick fire button for that weapon will cease to work (currently a bug. Working on it. Besides, You'll use the Quick-Fire buttons mostly, anyway).


Below is a list of all of the default controls for the game, including the new ones I've added:
The formatting for this table is: 'Command: Keyboard Control (SNES Control - Optional)'

(Note, This table assumes that you haven't changed the in-game controls. If you have, you'll need to set them back to default for any of this to work.)
(I plan on making a fix for this in a later version)


**** Vanilla Controls ****
Movement: WASD
Jump: Space Bar
Fire: J
Dash: Left Shift
Aim Up: K
Aim Down: L
Item Switch: , [Comma]
Item Cancel: . [Period]
Map/Status Screen: Tab


**** New Controls ****
Quick-Fire Missiles: M (Joypad 2 - B)
Quick-Fire Super Missiles: N (Joypad 2 - Y)
Quick-Fire Power-Bombs: E (Joypad 2 - L)
Quick-Fire Grapple Beam: H (Joypad 2 - A)
Quick-Fire X-Ray Scope: Q (Joypad 2 - X)
Quick Morph Ball: Q (Joypad 2 - R)

Quick-Fire Wave Beam Combo: U [Hold] (Joypad 2 - Dpad Up)
Quick-Fire Ice Beam Combo: I [Hold] (Joypad 2 - Dpad Down)
Quick-Fire Spazer Beam Combo: O [Hold] (Joypad 2 - Dpad Left)
Quick-Fire Plasma Beam Combo: P [Hold] (Joypad 2 - Dpad Right)

Select Beam: 1 (Joypad 3 - X)
Select Missiles: 2 (Joypad 3 - A)
Select Super Missiles: 3 (Joypad 3 - B)
Select Power-Bombs: 4 (Joypad 3 - Y)
Select Grapple Beam: R (Joypad 3 - R)
Select X-Ray Scope: F (Joypad 3 - F)

***********************
The emulator's input configuration screen reflects these new controls. Also, the arrow keys, enter, and backspace work in the menus.

I've played through Super Metroid (vanilla) a number of ROM hacks, and AM2R (albeit, slightly tweaked and w/o my additions in that instance) with these controls, and I have no complaints with the layout.

You don't need to use/enable all of these controls, however. They're just there to give you options. Play around with them and find a setup you like!


Additionally, the escape key is now the pause/resume emulation button. The window's menu bar will only display while emulation is paused. 



B) SAVE STATIONS HEAL YOU:
Something of a gripe with vanilla Super Metroid was how you could save with little to zero health, and be stuck in a perpetual cycle of dying in a difficult area outside (not to mention, state saves give me very little reason to use the vanilla save stations). I've added the ability for save stations to heal you to 100% health. However, this does not trump the vanilla energy stations, as save stations will not fill your reserve tanks. This feature works by monitoring the SRAM for certain changes (specifically, the total play time for your file), so it should work with any ROM Hack.

Currently, this only works for save file 1. I'll make it work for the others in a future update.



C) MISC. STUFF:

The emulator now has Samus' helmet as it's icon. Nice, Huh?

The menu bar will now only display while emulation is paused with the Escape button, making the menu bar function more like a pause menu in a normal PC Game. The actual play/pause emulation button (F2 by default) will pause/resume emulation while leaving the menu bar as is.

See that folder labeled ROMs? If you name a file 'main.smc' and put it in there, the emulator will load that ROM by default. You could use a vanilla copy of Super Metroid, or just your favorite ROM hack (personal recommendation for Super Metroid newcomers: 'Project Base 0.7.2 Gameplay Only'. It's vanilla Super Metroid, with some of the mechanics given a nice polish. Download link below). This is also the default directory for the game's Open ROM dialog option. Additionally the 'Select ROM.exe' program will let you launch directly into a specific ROM. ('Select ROM.py' is just the source code for that program.) 

(DO NOT CHANGE THE ROMS DIRECTORY IN THE EMULATION SETTINGS!! I'm going to disallow that in a later version.)

In the display settings, "Super Metroid - PC Edition" currently is set to apply the 4xBRZ upscaling algorithm to the game. Seriously, the game looks SO much better. Be sure to adjust the display settings to your liking, and experiment with the other algorithms to find the one that gives you the best speed and quality.


I hope to add more features down the line: a New Game Plus mode, better compatability with the in-game controls menu (mentioned above), maybe storing the charge-beam's charge for later (a possibility I discovered thanks to a bug I encountered), unique settings for individual ROMs, improving the reserve tank's functionality, some changes to the emulator's UI, etc. But for the moment, I think this is a good first version.

=====================================================================================================

===== 3) How To Configure ===========================================================================

See that file named "SuperMetroid_GameConfig.txt"? Open it.

This file controls which major features are enabled. When a ROM is loaded, the emulator reads through this file, line by line, looking for a handful of flags. If a flag is found, it checks the next line for either 'true' or 'false', which determines whether the feature is on or off. If the line contains the '#' character, it is ignored.

There are only 3 flags atm, but I as I add more features, I imagine there will be more:

'UseNewControls' - This enables the new controls I discussed above.

'SaveStationsHeal' - This enables the save station healing feature I discussed above.

'XrayMetroidRedesignMode' - This is a compatability feature I added to allow the 'Quick-Fire X-Ray Scope' button to work with Super Metroid: Redesigned. Keep this disabled unless you're actually playing the aforementioned ROM Hack.

Additionally, you can have unique settings for ROMs by creating a file with your ROM name + '_GameConfig.txt' in the Patches folder (example: if your ROM is named 'MyHack', then you need to make a file named 'MyHack_GameConfig.txt' in the patches folder. If you're still confused, the stdout.txt file will show you the name of the GameConfig file it's looking for when you open a ROM). Setting found in this file will override the defaults.

Note, these files are COMPLETELY CASE SENSITIVE!!!

Everything else works the same way it does in normal Snes9X.


=====================================================================================================

===== 4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here) ====

********************************************************************************
Q: What ROMs is this compatable with?
A: Most any Super Metroid ROM hack should work, so long as it doesn't alter the primary functionality of the SNES controls (sorry, 'Control Freak'), Also the hack shouldn't change the location of samus's health, ammo, play time, and weapon/equipment info in the RAM or SRAM. Because doing any of these would be a horrible idea when making a ROM Hack, most hacks should work in this emulator.

I've tested this with a number of ROM hacks (including several variants of Project Base), and I haven't had any problems yet. If you encounter any, lemme know. I want this emulator to work with as many ROM hacks as possible, so I'll usually be glad to include options and patches for other hacks.

... Oh, also, in case this isn't obvious: don't try to use a non-Super-Metroid-based ROM with this emulator. Most of the time, nothing will happen. The most of these special features don't do anything unless the byte at SNES memory address 0x7E0998 (the byte that determines Super Metroid's current state) is set to 0x08 (indicating that we're in normal gameplay, and not some menu or something). If a different game sets this byte to that value, I have no idea what will happen.

********************************************************************************
Q: Where can I get your source code? Where are your changes?
A: I haven't put source code up on GitHub yet, but I will. 

The code I've added it mostly contained in the files SMMods.cpp and SMMods.h, and in the directory named ModScripts, along with a slight reworking of the beginning of the program's Main() method, found in wsnes9x.cpp, and some parts of UI-related code also in that file. Everything else is either making certain methods available outside of their origin file, or calls to the methods in SMMods.cpp to make these features work.

If people are interested, I could put in a programmer's API/Documentation at some point. Next release.

********************************************************************************
Q: Does this work on Mac/Linux?
A: It could at some point. But not as of yet. Once I'm confident that the windows version is stable and is fully functional, then I'll consider other platforms.

********************************************************************************


... I'll be adding to this part as people begin to ask questions....



=====================================================================================================

===== 5) Links ======================================================================================

http://www.SNES9x.com/ - Snes9X's official website. If it's not a question related to my changes, look here.

https://github.com/snes9xgit/snes9x - the source code for the official version of Snes9X, on which my version is based.

https://www.begrimed.com/pb/ - Project Base is definitely one of the best Super Metroid hacks out there, and has been the basis for many more. I suggest downloading the '+ Extras' .zip file. It contains the 'Project Base 0.7.2 Gameplay Only' hack I mentioned earlier, along with my personal favorite, 'Project_Base_0.7.2_Nintendit_1.57', which has a slightly remixed campaign.

https://visualstudio.microsoft.com/downloads/ - If you wanna try to work on my code, you're gonna need Microsoft Visual Studio 2017 - Community Edition (which is what I used).

http://metroidconstruction.com//howto.php - Guide to running/playing ROM Hacks.


Resources for finding ROM Hacks to play:
https://www.romhacking.net/games/729/

http://metroidconstruction.com//hacks.php


=====================================================================================================

===== 6) Conclusion =================================================================================

Well, that's all I gotta say about this project. Give it a play, lemme know what ya think!

If you got questions or comments or feedback, hit me up on Twitter (@Lt_ASchmiddy) or Discord (LT_Schmiddy), and I'll be glad to talk / help you out!


LT_Schmiddy, out.


