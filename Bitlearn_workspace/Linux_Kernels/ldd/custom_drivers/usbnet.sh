#!/bin/bash
##chmod +x usbnet.sh
sudo ip addr add 192.168.7.1/24 dev enx3ce4b0c3f689

sudo ip link set enx3ce4b0c3f689 up

ip addr show enx3ce4b0c3f689

