# young_makers_academy


sudo dnf install kernel-modules-extra
sudo modprobe cp210x
sudo modprobe ch341
sudo usermod -aG dialout $USER
reboot