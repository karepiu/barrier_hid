#!/bin/bash
# Snippet from https://github.com/girst/hardpass-sendHID/blob/master/README.md . In which, the following notice was left:

# this is a stripped down version of https://github.com/ckuethe/usbarmory/wiki/USB-Gadgets - I don't claim any rights
SRC="$(cd "$(dirname "$0")" ; pwd)"

modprobe libcomposite
cd /sys/kernel/config/usb_gadget/
mkdir -p g1
cd g1
echo 0x1d6b > idVendor # Linux Foundation
echo 0x0104 > idProduct # Multifunction Composite Gadget
echo 0x0100 > bcdDevice # v1.0.0
echo 0x0200 > bcdUSB # USB2
mkdir -p strings/0x409
echo "314159" > strings/0x409/serialnumber
echo "karepiu" > strings/0x409/manufacturer
echo "Raspbery Pi Zero W HID" > strings/0x409/product

A_N="mouse"
mkdir -p functions/hid.$A_N
echo 2 > functions/hid.$A_N/protocol
echo 1 > functions/hid.$A_N/subclass
echo 3 > functions/hid.$A_N/report_length
cat "$SRC/mouse.desc" > functions/hid.$A_N/report_desc

B_N="keyboard"
mkdir -p functions/hid.$B_N
echo 1 > functions/hid.$B_N/protocol
echo 1 > functions/hid.$B_N/subclass
echo 8 > functions/hid.$B_N/report_length
cat "$SRC/keyboard.desc" > functions/hid.$B_N/report_desc

C_N="touch"
mkdir -p functions/hid.$C_N
echo 0 > functions/hid.$C_N/protocol
echo 0 > functions/hid.$C_N/subclass
echo 5 > functions/hid.$C_N/report_length
cat "$SRC/touch.desc" > functions/hid.$C_N/report_desc

D=1
mkdir -p configs/c.$D/strings/0x409
echo "Config $D: ECM network" > configs/c.$D/strings/0x409/configuration 
echo 250 > configs/c.$D/MaxPower 
ln -s functions/hid.$A_N configs/c.$D/
ln -s functions/hid.$B_N configs/c.$D/
ln -s functions/hid.$C_N configs/c.$D/
ls /sys/class/udc > UDC

sudo chmod 777 /dev/hidg*
