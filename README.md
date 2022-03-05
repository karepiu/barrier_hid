# Barrier HID ( Synergy )

This is a fork of the open source core component of Synergy, a keyboard
and mouse sharing tool.
For compilation and configuration, check
[the main repo](https://github.com/debauchee/barrier).

In certain cases - for example where installing the client on the system
is not possible, this project helps to remediate that.

It does that by using raspberry pi as a proxy ( hid device )
that emulates usb keyboard and mouse ( and touch ). 

## Required hardware

Raspberry Pi Zero W connected to same network as Barrier server 
BUSTER Rpi OS ( Legacy ) 

## Building the solution

You can build the solution by executing:

git clone https://github.com/karepiu/barrier_hid.git
cd barrier_hid
./build.sh

or manually:

git clone https://github.com/karepiu/barrier_hid.git
cd barrier_hid
sudo apt update && sudo apt upgrade
sudo apt install git cmake make xorg-dev g++ libcurl4-openssl-dev \
                 libavahi-compat-libdnssd-dev libssl-dev libx11-dev \
                 libqt4-dev qtbase5-dev
./clean_build.sh

## Hardware setup 

Raspberry Pi Zero W needs to be setup as OTG device. 

1. Connect RPiZw to the PC using OTG cable and port. 
2. Set correct OTG mode
   - by executing script 
        ./otg_mode_setup.sh
   - manually 
        echo "dtoverlay=dwc2" | sudo tee -a /boot/config.txt
        echo "dwc2" | sudo tee -a /etc/modules
3. Set RPiZw as HID device
   - by executing script 
        ./hid_setup.sh
        
## Usage

barrierc --client --name <your client name> -f --hid /dev/hidg0 /dev/hidg1 /dev/hidg2 1920 1080 <ip of server>

or

modify the client name and port in start.sh and execute - ./start.sh

start.sh starts barrierc in forground and uses nohup and & to run it in backround - reason for that is performance. 
The standrd deamon option in barrier does not work great on RPiZw.

* SSL works but for performance sake I suggest to disable it

## Limitations/Issues

- No clipboard - as Pi Zero is proxy clipboard functionality would require supporting app or mass storage to make it work


