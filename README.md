# Super Metroid - PC Edition
*A port of the Snes9x emulator*

DISCLAIMER: 'Super Metroid' and the entire 'Metroid' franchise are the intellectual property of Nintendo Co., Ltd. I have no affiliation with them, nor do I have any legal rights or ownership over the aforementioned properties. I'm just a fan.

Then again, you probably new that.


DISCLAIMER 2: Super Metroid ROM not included. Google it. 

DISCLAIMER 3: This README is designed for someone not TOO familiar with emulation and ROM-Hacking. Sorry if this is too dumbed down for you. Please read the whole thing anyway.

********************************************************

<a href="https://github.com/LTSchmiddy/super-metroid-pc-edition-snex9x-public/releases">Download Latest Stable Build</a>


<a href="https://github.com/LTSchmiddy/super-metroid-pc-edition-snex9x-public/tree/master/Binary%20Archives" >All/Previous Versions</a>
<br/>


=====================================================================================================
Date of Readme: 10/8/2018

Table of Contents:

1) Introduction

2) Features

3) How To Configure

4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here)

5) Links

6) Conclusion

=====================================================================================================

===== 1) Introduction ===============================================================================
(TBH, you've probably already read this part whereever you downloaded this project.)

As Super Metroid is one of my favorite games of all time, and it makes me bit sad sad that this genre-defining classic hasn't seen a remake since... ever. Seriously, it's one of the handful of retro games who's mechanics haven't aged almost at all, and yet the only official version of the game that exists is the original from 24 years ago. Having a fair bit of experience with the Unity Game Engine (in which I am developing my own game), I've considered attempting a fan remake myself, perhaps something along the lines of the fantastic AM2R (which you you can still find with a brief google search, BTW). But I'd rather my work not suffer the same DCMA-based fate as the aforementioned love-letter to the franchise.

Well, within the last few months, I've discovered the wonderful world of ROM-hacking, Super Metroid in particular, and I've been dripping with excitement ever since. I've played through a handful of hacks and even applied a few tweaks for my own enjoyment.

For the record, I'm not new to the world of emulation for retro-games, having a moderate library of classic titles and others from my own childhood. I use LaunchBox to manage this library, along with my games from Steam and other places. Because I'm rather OCD, I like my emulated games to feel as native to my PC as I can make them. I had a seperate copy of Snes9X with the controls/setting configured for an ideal Super Metroid experience, and had I started writing a python script to allow me to select what ROM/ROM-hack to play when I launched the game from my library, when the idea for this project struck me: Instead of modding the ROM, mod the emulator.

Ok, enough with the background info. 

************************************

"Super Metroid - PC Edition" is a modified version of the Snex9X emulator (link to their site in section 6) specifically designed for playing Super Metroid and any ROM Hacks based on it. Unlike the vanilla version of the emulator, it makes a handful of improvements and adds some new controls to the game by means of memory manipulation (and the occasional input spoof) during runtime. And since all of this is handled by the emulator's own execution code (no changes, soft or hard, are made to the ROM itself), these improvements can be applied to ANY Super Metroid ROM hack. On top of that, Snes9X already has a number of featured to improve the visuals and sound of the game, and this copy of the emulator is optimized for Super Metroid by default.

=====================================================================================================

===== 2) Features ===================================================================================

So, exactly what does "Super Metroid - PC Edition" have to offer?

Each major feature listed below can be enabled or disabled in a special config file. More on that later.


a) ADDITIONAL CONTROLS:

I've added a number of additional controls to the game. This system works by hijacking joypads 2, 3, and 4 in the emulator, so they do work with hardware controllers. The programs's input configuration screen reflects these new controls. 

Most notably, I've added quick-fire buttons for the Missiles, Super Missiles, Power Bombs, Grapple Beam, and X-Ray Scope. Seriously, you have no idea what a difference it makes to have the missiles and super missiles on quick-fire buttons. The combat in the game is SO much more fun and fluid when you don't have to stop what your doing and switch weapon modes constantly. Not to mention that having the super missiles on a hot button makes them a much more tactical option for combat, instead of them being the "OH CRAP! BAIL ME OUT!" weapon they tend to be otherwise. The grapple beam benefits even more so, since using the grapple beam prevents you from using your other weapons, and the grapple beam is not the best in a combat situation. On a quick-fire button, you can now flip between shooting and grappling seamlessly. All of this opens up a lot more options for daring manuveres and badass moments in your gameplay.

While they don't provide as much of an improvement to the game, the additional quick buttons for the power bombs and the x-ray scope are a wonderful convienence, especially since the x-ray normally takes the place of the sprint button. Note that the quick powerbomb button does not put you into morphball. If you use it while standing, you'll simply fire your beam. 

Additionally, I've added quick-fire buttons for each beam's power-bomb+charge combo. I know they're supposed to be 'secret moves', but considering how inconvienent they are to use, I figured they're better off this way. There is a minor visual glitch where they use the sprites from the currently equipped set of beams, but the functionality remains the same (and I kinda like how they look, tbh), so I'm keeping it.

There are also selection buttons for each weapon, just in case. However, if you switch to a weapon, the quick fire button for that weapon will cease to work (currently a bug. Working on it. Besides, You'll use the Quick-Fire buttons mostly, anyway).

Optionally, there is also now a Self-Destruct function. While the Charge Beam is equipped and Power-Bombs are selected, hold the 'Movement Up' Button ('W' on the keyboard by default), and begin charging a shot (holding 'Movement Up' and 'Quick-Fire Power-Bomb' together will also work. Aiming up by holding the two aiming buttons will not work in place of the 'Movement Up' button.). After 2 seconds, Samus's health will start decreasing for as long as you hold this button combination, or until samus has only 10 hitpoints between her health and Reserve Tanks. I've added this to make the Crystal Flash ability more tactical, as it can only be activated when Samus has less than 50 health. Previously, if you were low on health but not quite low enough, you could stand around and wait for enemies to chip down your health, then use the Crystal Flash to heal yourself. This accomplishes the samw goal, but faster. Of course, in doing this, you are taking a rist and and temporarily leaving yourself more vulnerable thn you (probably) already are, so use wisely. If you don't like this function, it can disabled.


Also, in addition to the original controls, the arrow keys, enter, and backspace can now be used to navigate menus and Right Shift can be used to switch between the Map and Status screens of the pause menu.

The Escape key is now the pause/resume emulation button. The window's menu bar will (normally) only display while emulation is paused, making the menu bar function more like a pause menu in a normal PC Game. (If you really need to see the menu bar while playing the game, the actual play/pause emulation button in the Hotkeys menu will pause/resume emulation while leaving the menu bar in its current state.)


******

Below is a list of all of the default controls for the game, including the new ones I've added:

(Note, This table assumes that you haven't changed the in-game controls. If you have, you'll need to set them back to default for any of this to work.)
(I plan on making a fix for that in a later version)


**** Vanilla Controls ****<br/>
Movement: WASD <br/>
Jump: Space Bar<br/>
Fire: J<br/>
Dash: Left Shift<br/>
Aim Up: K<br/>
Aim Down: L<br/>
Item Switch: , [Comma]<br/>
Item Cancel: . [Period]<br/>
Map/Status Screen: Tab<br/>


**** New Controls ****<br/>
Quick-Fire Missiles: M<br/>
Quick-Fire Super Missiles: N<br/>
Quick-Fire Power-Bombs: E<br/>
Quick-Fire Grapple Beam: H<br/>
Quick-Fire X-Ray Scope: Q<br/>
Quick Morph Ball: Left Control<br/>

Quick-Fire Wave Beam Combo: U [Hold] <br/>
Quick-Fire Ice Beam Combo: I [Hold] <br/>
Quick-Fire Spazer Beam Combo: O [Hold] <br/>
Quick-Fire Plasma Beam Combo: P [Hold] <br/>

Select Beam: 1 <br/>
Select Missiles: 2 <br/>
Select Super Missiles: 3 <br/>
Select Power-Bombs: 4 <br/>
Select Grapple Beam: R <br/>
Select X-Ray Scope: F <br/>


Menu - Navigate: Arrow Keys<br/>
Menu - Select/Confirm: Enter<br/>
Menu - Back/Cancel: Backspace<br/>
Menu - Switch Between Map and Status Screens: Right Shift<br/>


Pause Game: Escape (Not in menus)

***********************

I've played through Super Metroid (vanilla) a number of ROM hacks, and AM2R (albeit, slightly tweaked and w/o my additions in that instance) with these controls, and I have no complaints with the layout.

You don't need to use/enable all of these controls, however. They're just there to give you options. Play around with them and find a setup you like!


B) SAVE STATIONS HEAL YOU:

Something of a gripe with vanilla Super Metroid was how you could save with little to zero health, and be stuck in a perpetual cycle of dying in a difficult area outside (not to mention, state saves give me very little reason to use the vanilla save stations). I've added the ability for save stations to heal you to 100% health. However, this does not trump the vanilla energy stations, as save stations will not fill your reserve tanks. This feature works by monitoring the SRAM for certain changes (specifically, the total play time for your file).

Due to compatability issues with ROM hacks that alter how much space each save slot needs, this feature only works for save file 1. That being said, it should work with any ROM Hack.



C) NEW GAME PLUS / NEW GAME ULTRA MODE:

This feature is still a work in progress. See the end of this heading for details.

******

Starting the game on Save Slot B will begin New Game Plus mode.

Samus starts New Game Plus with all the power-ups and ammo tanks from the last playthrough (save slot 1), but not the energy and reserve tanks.

Since you have all the non-optional upgrades, you can explore the map and tackle the bosses in any order you want. You could go fight the bosses straight away if you're skilled enough, or (since you now have way less max health) you can hunt down the health/reserve tanks (so that you don't die in one hit) and re-collect ammo tanks (since you might need the fire-power) in order make the boss fights more... doable. Seriously, this could open up a whole new world for speedrunners. Of course, you still need to defeat them all to get into Tourian and beat the game.

Speaking of recollecting ammo tanks: You can do that. Meaning you can have a much higher ammo capacity then you would in normal mode. For example, if you managed to collect every single missile tank in your first playthrough, giving you a 230 missile storage capacity, you can collect them all again for a maximum of 460 missiles. This applies to super missiles and power bombs as well.*

Defeating each miniboss (Bomb Torizo, Spore Spawn, Crocomire, Botwoon, and Golden Torizo) gives Samus a small amount of health regeneration. You will regenerate 1 point per number of minibosses defeated per second, with a 10 second pause if you take damage or, if allowed (see below), a save state is used.  I'm doing this for a number of reasons: 1) There isn't much reason to fight any of the minibosses otherwise. You start with all of the power-ups that they guard, and thus have the abilities needed to detour around them. This way, there's some incentive to face them. 2) I want to make up for the fact that you can't re-collect the health tanks for a greater max health. 3) This way, there is a little more upgrading you can do. When you load up your save file or defeat a miniboss, an on-screen messsage will inform you of your current health regen rate.

Enemies just do more damage in general. You now take 3x the amount of damage you normally would (I may adjust this value in later versions).

The "Save Stations Heal You" feature that I've added will not work in New Game Plus.

If Save State Integration is enabled (see below), the emulator's Save State functions will be disabled in New Game Plus (and New Game Ultra). 

If you wish, Save States can be re-enabled in New Game Plus / New Game Ultra for experiemental/development purposes. However, this causes an issue with the damage multiplier thinking you've taken a hit when you load a save state with less health, and dropping your health accordingly. Loading the state twice seems undo the effect, but until I fix this bug, I highly recommend leaving Save States disabled for actual in New Game Plus / New Game Ultra gameplay.

******

Starting the game on Save Slot C will begin New Game Ultra mode. It's the same as New Game Plus, with the following addition:

At first, you only take 2x the damage you do in normal play. Every major boss you defeat (Kraid, Phantoon, Draygon, and Ridley) increases that multiplier by 2, until you have a damage multiplier of 10x by the time you head off to Tourian. This means you need to be strategic about when you fight each boss, and in what order you conquer them. Otherwise, you may find yourself struggling against a tougher boss while the damage multiplier is too high. When you load up your save file or defeat a boss, an on-screen messsage will inform you of your current damage multiplier.

******

This feature is still in progress. As my knowledge of the Super Metroid ROM increases, I plan to make this feature more nuanced. I want to adjust the health and attack strength of the bosses and minibosses individually, the power of Samus's weapons, how much health/ammo that pickups restore, and other little things to adjust the difficulty.

BUG WARNING: In New Game Plus (and New Game Ultra), the first time you pass through a door on planet Zebes, the game (within the emulation) will freeze. Don't panic. Simply reset the game (in the menu bar, File -> Reset Game) and load up Save Slot B (Slot C for New Game Ultra). The game will now work normally. I'm still working on a fix for this, but for now, just know that this is what to do.


D) SAVE STATE INTEGRATION:

I've integrated Save States more seamlessly integrated into the game. Save Slots A, B, and C of the vanilla game now each have own set of save states, denoted by the hundred's place in the Save State file extension (assuming you CAN use save states in slots B and C, as explained above). States can now only be saved during gameplay, and only loaded either during gameplay or on the Game Over screen after you die. While I'm not here to encourage save scumming, I personally think that the ability to save whenever/whereever is an inprovement to any open-world/open-map game. If you disgree, you can also completely disable Save States if you want.

Currently, on-screen messages will appear to explain this when you try to use Save States when not allowed. 

Of course, Save State Integration can be completely disabled, if you like.



E) BETTER RESERVE TANKS:

I never liked how Reserve Tanks worked in the vanilla game. I mean, they're basically just energy tanks that aren't as good. I would much rather just have an actual Energy Tank. Maybe I'm nitpicky, but when I'm on the trail of a hidden power-up and get kinda dissappointed when I realize it's a just Reserve Tank, that's a problem. So... I improved them. 

Reserve Tanks now refill over time, in addition to how you normally fill them. The reserve tanks will fill at a rate of 3 points per second (technically, it adds 1 point every 1/3 of a second). Thus, one Tank will reach full capactiy after 33 seconds, and all 4 will refill after 133 seconds (2 minutes and 13 seconds). The Reserve Tanks will pause regeneration for 60 second delay whenever energy is drained from them or a save state is used. This way, Reserve Tanks can now be used as a sort-of indirect health regeneration.

This regen may seem fast, but considering the pacing of the game (combat especially), it's longer than you think. I may adjust these values for balance purposes down the line, however, and (as you can guess by now) this feature can be disabled completely if you wish.



... Z) MISC. STUFF:

The emulator now has Samus' helmet as it's icon. Nice, Huh?

See that folder labeled ROMs? If you name a file 'main.smc' and put it in there, the emulator will load that ROM by default. You could use a vanilla copy of Super Metroid, or just your favorite ROM hack (personal recommendation for Super Metroid newcomers: 'Project Base 0.7.2 Gameplay Only'. It's vanilla Super Metroid, with some of the mechanics given a much-appreciated polish. Download link below). This is also the default directory for the game's Open ROM dialog option. Additionally the 'Select ROM.exe' program will let you launch directly into a specific ROM. ('Select ROM.py' is just the source code for that program.) 

(I don't recommend changing default ROM directory. I haven't tested it, so I have no idea what will happen if you set this to somewhere else. The 'Select Rom.exe' program will definitely not work, however.)

(I'm working on a way to let you choose the default ROM file. Next version, probably.)

In the display settings, "Super Metroid - PC Edition" currently is set to apply the 4xhq upscaling algorithm to the game. Seriously, the game looks SO much better. Be sure to adjust the display settings to your liking, and experiment with the other algorithms to find the one that gives you the best speed and quality, and that suits your personal taste.

******

I hope to add more features down the line: better compatability with the in-game controls menu (mentioned above), maybe storing the charge-beam's charge for later (a possibility I discovered thanks to a bug I encountered), some changes to the emulator's UI, a proper pause menu to perform the functionality of the menu bar, etc.


=====================================================================================================

===== 3) How To Configure ===========================================================================

See that file named "SuperMetroid_GameConfig.txt"? Open it.

This file controls which major features are enabled. When a ROM is loaded, the emulator reads through this file, line by line, looking for a handful of flags. If a flag is found, it checks the next line for either 'true' or 'false', which determines whether the feature is enabled or disabled. If the line contains the '#' character, it is ignored.

The current flags are:

'UseNewControls' - This enables the new controls I discussed above.

'NC_SelfDestruct' - This enables the Self Destruct function I discussed above. In order for this to work, UseNewControls MUST be enabled.

'SaveStationsHeal' - This enables the save station healing feature I discussed above.

'BetterReserveTanks' - This enables the Better Reserve Tanks feature, discussed above.

'Save2IsNewGamePlus' - This enables New Game Plus and New Game Ultra, discussed above... I might need to rename this flag.

'SaveStateIntegration' - This enables the Save State Integration feature, and allows the features that depend on it. Discussed above. 

'SSI_SaveStatesDisabled' - If enabled, Save States will be completely disabled. In order for this to work, SaveStateIntegration MUST be enabled.

'XrayMetroidRedesignMode' - This is a compatability feature I added to allow the 'Quick-Fire X-Ray Scope' button to work with Super Metroid: Redesigned, due to a slight tweak to the control scheme that hack makes. Keep this disabled unless you're actually playing the aforementioned ROM Hack.

'SSI_AllowSaveStatesInNewGamePlus' - Currently, only recommended for development purposes. Allows Save States to be used in New Game Plus and New Game Ultra.

******

There mey be some flags for experimental features that I'm still working on. They will be marked properly, and you should really leave these off, as some of them WILL break the game and none of them work properly yet.

If a flag is never found, the associated feature will be disabled.

You can have unique settings for ROMs by creating a file with your ROM name + '_GameConfig.txt' in the Patches folder (example: if your ROM is named 'MyHack.smc', then you need to make a file named 'MyHack_GameConfig.txt' in the patches folder. If you're still confused, the stdout.txt file will show you the name of the GameConfig file it's looking for when you open a ROM). Setting found in this file will override the defaults.

Note, these files are COMPLETELY CASE SENSITIVE!!!


Everything else works the same way it does in normal Snes9X.


=====================================================================================================

===== 4) QIAWBFAIIDATH (Questions I Assume Will Be Frequently Asked If I Don't Answer Them Here) ====

********************************************************************************<br/>
Q: What ROMs is this compatable with?
A: Most any Super Metroid ROM hack should work, so long as it doesn't alter the primary functionality of the SNES controls (sorry, 'Control Freak'), Also the hack shouldn't change the location of samus's health, ammo, play time, and weapon/equipment info in the RAM or SRAM. Because doing any of these would be a horrible idea when making a ROM Hack, most hacks should work in this emulator.

I've tested this with a number of ROM hacks (including several variants of Project Base), and I haven't had any problems yet. If you encounter any, lemme know. I want this emulator to work with as many ROM hacks as possible, so I'll usually be glad to include options and patches for other hacks.

... Oh, also, in case this isn't obvious: don't try to use a non-Super-Metroid-based ROM with this emulator. Most of the time, nothing will happen. The most of these special features don't do anything unless the byte at address 0x7E0998 (the byte that determines Super Metroid's current state) of the SNES's RAM is set to 0x08 (indicating that we're in normal gameplay, and not some menu or something). If a different game sets this byte to that value, I have no idea what will happen.

********************************************************************************<br/>
Q: Where can I get your source code? Where are your changes?
A: Right Here.

The code I've added it mostly contained in the files SMMods.cpp and SMMods.h, and in the directory named ModScripts, along with a slight reworking of the beginning of the program's Main() method, found in wsnes9x.cpp, and some parts of UI-related code also in that file. Everything else is either making certain methods available outside of their origin file, or calls to the methods in SMMods.cpp to make these features work.

If people are interested, I could put in a programmer's API/Documentation at some point.

********************************************************************************<br/>
Q: Does this work on Mac/Linux?
A: It could at some point. But not as of yet. Once I'm confident that the windows version is stable and is fully functional, then I'll consider other platforms.

********************************************************************************


... I'll be adding to this part as people begin to ask questions....



=====================================================================================================

===== 5) Links ======================================================================================

http://www.SNES9x.com/ - Snes9X's official website. If it's not a question related to my changes, look here.

https://github.com/LTSchmiddy/super-metroid-pc-edition-snex9x-public - The source code for this project.

https://github.com/snes9xgit/snes9x - The source code for the official version of Snes9X, on which my version is based.

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



=====================================================================================================
* For whatever reason, Super Metroid uses 2 bytes (4 bytes, since it needs another 2 bytes to remember your storage capacity) in the RAM to store how much ammo you have, PER AMMO TYPE, even though you'll never have enough ammo in the base game to need more than 1 byte to store it. This means the game could handle you having up to 65535 missiles, etc. Now, the missile counter in the UI gets confused on what to draw if you have more than 999 missiles (and I believe 99 for super missiles and power bombs) starts drawing random characters/tiles in hundred's place (ten's place for super missiles and power bombs, I think), but it will still work normally otherwise. Besides, it's unlikely that you'll ever encounter this situation, considering that 999 is more than 4x the max missile capacity in vanilla SM.



