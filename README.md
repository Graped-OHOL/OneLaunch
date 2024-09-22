
![Logo](http://ohol.isbad.gg/img/logo.png)
# A launcher for [One Hour One Life](https://github.com/jasonrohrer/OneLife).
This project aims to provide an intuitive interface for users to launch multiple OHOL accounts effortlessly. Many users (griefers and legitimate players) have more than one account due to the willy-nilly use of the Curse System in OHOL. The issue they face is having multiple installs of the game or swapping out some files every time they switch accounts. This project provides an automated way of performing that latter option with a beautiful UI! Without all the hassle!

### Our [Support Discord](https://discord.gg/grieflife)

## Contents
- ### [Features](#features)
    - #### [Launcher Tab](#launchertab)
    - #### [Account Manager Tab](#accmngrtab)
    - #### [Settings Tab](#settingstab)
- ### [Installation](#installation)
- ### [Building](#building)

<a name="features"/></a>
## Features
The main window features three tabs :

<a name="launchertab"/></a>
### Launcher Tab
![Launcher Tab](http://ohol.isbad.gg/img/launchertab.png)
The *Launcher Tab* is home to the *Account Selector*, *Launcher Controls*, and *Debug Console*.
- The *Account Selector* is a multi-selection array that allows users to select one or more accounts to launch.
- The *Launch* button launches the game for the account(s) selected in the *Account Selector*.
- The *Launch All* button launches an instance of the game for every configured account, regardless of selection.
- The *Debug Console* outputs a lot of information when debug mode is enabled, but only some general messages if not.

<a name="accmngrtab"/></a>
### Account Manager Tab
![Account Manager Tab](http://ohol.isbad.gg/img/accountmanagertab.png)
The *Account Manager Tab* is home to the *Account Manager List*, and *Account Editor*.
- The *Account Manager List* is a single selection array that gives a detailed list of the accounts, with each of their data columns.
    - If Yumhack is enabled/disabled, the CName and YHKey columns are shown/hidden. Like in the screenshot. (Turning Yumhack off requires restarting OneLaunch to hide them)
- The *Account Editor* features several elements :
- The title of the editor indicates if the *Account Editor* is in edit or create mode.
- The *Edit* button will populate the below fields with the selected account.
- The *Delete* button will delete a selected account. A confirmation window will pop up first.
- The *Account Editor* has 6 fields :
    - The *Account ID* field is a value OneLaunch uses to identify accounts. This value must be unique for every account.
    - The *Account Email* field is the account's email for logging into OHOL.
    - The *Account Key* field is the account's key for logging into OHOL.
    - The *Notes* field is for your convenience. Users may log whatver data they would like here.
    - The *Client Name* and *Yumhack Key* fields are only shown if Yumhack is enabled.
    - The *Client Name* field is used by Yumhack to add a string to the title of the game client.
    - The *Yumhack Key* field is used by Yumhack for the Yumhack Chat.
- The *Save/Create* button will say "Save" if the editor is in edit mode, or "Create" if in create mode. It will save whatever data is in the fields, and clear the fields when pressed.

<a name="settingstab"/></a>
### Settings Tab
![Settings Tab](http://ohol.isbad.gg/img/settingstab.png)
The *Settings Tab* is home to the *Client Settings*, *Launcher Settings*, a *Notice*, and a *Defaults* button.
- The *Client Settings* are all settings related to the OHOL client. I have avoided Yumlife specific settings, but they may come in the future. The settings are as follows :

    - - **Radio Buttons**
    - Auto Login `autoLogin.ini`
    - Hard Quit Mode `hardToQuitMode.ini`
    - Skip FPS Check `skipFPSMeasure.ini`
    - FullScreen `fullscreen.ini`
    - Borderless `borderless.ini`
    - VSync `countOnVsync.ini`
    - Hide UI `hideGameUI.ini`
    - Mouse Highlights `showMouseOverHighlights.ini`
    - E Key for RMB `eKeyForRightClick.ini`
    - Mute Music `musicOff.ini`
    - Mute Effects `soundEffectsOff.ini`
    - Use Custom Server `useCustomServer.ini`
    - Pause on Minimize `pauseOnMinimize.ini`
    - VOG Mode `vogModeOn.ini`
    - - **Text Fields**
    - Screen Height `screenHeight.ini`
    - Screen Width `screenWidth.ini`
    - Cursor Scale `emulatedCursorScale.ini`
    - Mouse Speed `mouseSpeed.ini`
    - Music Volume `musicLoudness.ini`
    - Effects Volume `soundEffectsLoudness.ini`
    - Buffer Size `soundBufferSize.ini`
    - Sample Rate `soundSampleRate.ini`
    - Emote Duration `emotDuration.ini`
    - Tutorial Done `tutorialDone.ini`
    - Server Address `customServerAddress.ini`
    - Server Port `customServerPort.ini`
    - Server Password `serverPassword.ini`
    - - **Drop List**
    - Cursor Mode `cursorMode.ini`
    
- The *Launcher Settings* are all settings related to OneLaunch. These are stored in `/onelaunch/config.json`.

    - The *Using Yumhack* setting will enable Yumhack related features in OneLaunch, and swap Yumhack related data when launching accounts.
        - If OneLaunch is started with this of and then turned off OneLaunch will hide most things Yumhack related. The two extra columns in the *Accounts Manager List* will not dissapear until OneLaunch has been restarted. If you modify or add an account after disabling it (Without restarting) the list will refresh with emtpy data for those two extra columns. (Worry not, the data is not wiped, OneLaunch just displays nothing, enable Yumhack again to see the data)
    - The *Debug Mode* setting enables extra (a stupid amount of extra) messages to be printed in the *Debug Console* if enabled.
    - The *Executable* setting defines which executable to use. Don't try adding a path, your executable and OneLaunch should both be in the main OHOL directory. Just type the name of the executable here, with the .exe extension.
    - The *Launch Delay* setting defines how long a period (in seconds) OneLaunch will wait between launching accounts.
    -The *Selector Data* setting defines what data is shown in the *Account Selector* when OneLaunch loads. You can strill toggle between the three options ("IDs", "Emails", "Names") in the *Launcher Tab*.
    
- The *Notice* is a notice message. Read it.
- The *Defaults* button will restore both the OHOL Client Settings (Based of default settings in the OneLife Repository) and the OneLaunch settings to their defaults.

<a name="installation"/></a>
## Installation
Installing OneLaunch couldn't be easier. To download you will find two options: the executable, and a zip with the executable and two folders with files. The zip is for advanced users, it is recommended you just download the executable. Once you have the executable just place it in your main OHOL directory. IF you're going with the zip file, just extract the contents of the zip into your main OHOL directory.

When OneLaunch is properly installed the `OneLaunch.exe` and `OneLife.exe` should be right next to eachother. OneLaunch depends ont his location to path to the settings folder and find your executable. IF you're using Yumlife or some other mod, you can configure OneLaunch to work with it by changing the setting in the *Settings Tab*

Notes about Zip file : I supplied this to show anyone who cares which files OneLaunch will generate if they don't exist, and what data it will populate them with. IF you're looking to install OneLaunch into an OHOL installtion that you've used you should just install the executable.

<a name="building"/></a>
##  Building
Compiling is pretty straight forward. The GUI was built with [Ultimate++](https://www.ultimatepp.org/). I kept the project structure readable by TheIDE. The U++ library includes TheIDE. Load it, open the project, modify the UI if you wish, and built it using TheIDE.
    
