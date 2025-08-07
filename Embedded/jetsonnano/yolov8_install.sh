#!/bin/sh

#This script is made for the Ubuntu 20.04 Image provided by Qenginieering
#https://github.com/Qengineering/Jetson-Nano-Ubuntu-20-image
#
#Before runnin this script, increase the partition size to the max in Disks utility.
#Then delete the swapfile /var/swapfile to make room for a larger swapfile created by the script.

set -e

password='jetson'

# Record the time this script starts
date

# Get the full dir name of this script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Keep updating the existing sudo time stamp
sudo -v
while true; do sudo -n true; sleep 120; kill -0 "$$" || exit; done 2>/dev/null &

#================================================================================
# Make swapfile
echo "\e[46m ================ Make swapfile ================ \e[0m"
cd
if [ ! -f /var/swapfile ]; then
	sudo fallocate -l 8G /var/swapfile
	sudo chmod 600 /var/swapfile
	sudo mkswap /var/swapfile
	sudo swapon /var/swapfile
	sudo bash -c 'echo "/var/swapfile swap swap defaults 0 0" >> /etc/fstab'
else
	echo "Swapfile already exists"
fi


# Get started with updates
echo "\e[46m Update \e[0m"
sudo apt-get update


echo "\e[44m ================ jetson-fan-ctl ================ \e[0m"
cd ~/Documents
git clone https://github.com/Pyrestone/jetson-fan-ctl
cd jetson-fan-ctl
echo $password | sudo -S ./install.sh
echo $password | sudo -S service automagic-fan restart


#https://i7y.org/en/yolov8-on-jetson-nano/
sudo apt update
sudo apt install -y libopenmpi-dev libomp-dev libopenblas-dev libblas-dev libeigen3-dev libcublas-dev

#https://github.com/ultralytics/ultralytics?tab=readme-ov-file
pip3 install ultralytics

#Test run to check correct detection of 4 persons, 1 bus, 1 stop sign on this image
yolo predict model=yolov8n.pt source='https://ultralytics.com/images/bus.jpg'

#Test real-time detection and segmentation from camera input (device 0)
#yolo task=detect mode=predict model=yolov8n.pt source=0 show=True
#yolo task=segment mode=predict model=yolov8n-seg.pt source=0 show=True imgsz=320

#To test real-time detection of the GardenCam model on the video clip.
cd ~/Downloads
wget https://github.com/StefansAI/Custom_Yolov8/raw/main/example/GardenCam640.pt
wget https://github.com/StefansAI/Custom_Yolov8/raw/main/example/GardenCam640.mp4
yolo task=detect mode=predict model=GardenCam640.pt source=GardenCam640.mp4 show=True


