require /home/ubuntu/pi_bsp/rootfs/yocto/poky/meta/recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL += "openssh openssl openssh-sftp-server " 
IMAGE_INSTALL +=  " gcc"

IMAGE_FEATURES += "dev-pkgs"
