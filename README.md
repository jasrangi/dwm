# dwm
dwm is a lightweight tiling window manager for X. This repository contains my
ease of use customizations to dwm, which can be found in the config.h file.
The official web page for dwm can be found [here](https://dwm.suckless.org/).

## Dependencies
This version of dwm requires the following packages: \
libx11 \
ttf-font-awesome \
ttf-ubuntu-font-family \
xorg-server \
xorg-xinit

## Installation
Clone this repository. Then run make clean install (may need root privileges).
Then add "exec dwm" to your .xinitrc file.
```sh
git clone https://github.com/jasrangi/dwm.git
cd dwm
make clean install
echo "exec dwm" >> ~/.xinitrc
```
Then start the X display server from a console.
```sh
startx
```

## Summary of customizations
Use of Ubuntu fonts and [Font Awesome](https://fontawesome.com/). \
The color and thickness of window borders has been adjusted for easier
visibility of the active window. \
The default terminal is Alacritty instead of st. \
Custom key binds for various system functions (see below).

### Custom key bind usage
The Super key refers to the key between ctrl and alt on most keyboards. \
Key bind dependencies: Alacritty, Firefox, Brave, Galculator, Playerctl,
Scrot, Slock, Systemd \

**Super + Q** = close window \
**Super + Shift + F** = open Firefox \
**Super + Shift + B** = open Brave browser \
**Calculator key** = open the Galculator calculator app \
**Mute key** functionality has been added \
**Volume-** functionality has been added and it lowers volume by 5% on a single
press \
**Volume+** functionality has been added and it raises volume by 5% on a single
press \
**Play/pause** key functionality has been added using playerctl \
**Previous** media key functionality has been added playerctl \
**Next** media key functionality has been added playerctl \
**Print screen** key = take screenshot with slock and save it to /home/jas/Pictures/screenshots, modify the path to a valid directory of your choice before use \
**Super + shift + L** = lock screen with slock \
**Super + Shift + S** = Enter sleep mode using systemd \
**Super + Shift + P** = Power down the host device (shutdown privileges may be
required) \
**Super + Shift + A** = initialize ALSA, used to instantly resolve sounds issues
