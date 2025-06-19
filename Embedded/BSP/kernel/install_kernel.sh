mkdir /srv/nfs/pi_kernel
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- INSTALL_MOD_PATH=/srv/nfs/pi_kernel modules_install
cp arch/arm/boot/zImage /srv/nfs/pi_kernel/kernel7l.img
mkdir -p /srv/nfs/pi_kernel/dts/overlays
cp arch/arm/boot/dts/broadcom/*.dtb /srv/nfs/pi_kernel/dts/
cp arch/arm/boot/dts/overlays/*.dtb* /srv/nfs/pi_kernel/dts/overlays/
cp arch/arm/boot/dts/overlays/README /srv/nfs/pi_kernel/dts/overlays/
