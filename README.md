# Lighthouse


## Installing PlatformIO

PlatformIO can be installed as a plugin for many IDEs. You can find a complete list here: https://docs.platformio.org/en/latest/ide.html#desktop-ide

My recommendation is to use VSCode, you can find installation guides here:  https://docs.platformio.org/en/latest/ide/vscode.html

### Open the project in VSCode

Once you have cloned this project to a local directory, you can open it on Visual Studio code in ```File``` > ```Add``` folder to workspace.

Then select the Lighthouse folder of the repository and click open, make sure it is the root folder and that it has the platformio.ino inside.

After that, the project should be loaded in Visual Studio Code and ready to configure and build. 

### Build and upload the project

Connect your CWB directly using the USB C port or via a PPU.

Connect the board to the computer and click on the upload button from the PlatformIO toolbar, or go to ```Terminal``` -> ```Run Task``` -> ```Upload```.

All the dependencies will be configured and built automatically.

> Note that if you are a Linux user and it is your first time using PlatformIO, you will have to install the udev rules to grant permissions to PlatformIO to upload the program to the board. You can follow the instructions here: https://docs.platformio.org/en/latest/faq.html#platformio-udev-rules
