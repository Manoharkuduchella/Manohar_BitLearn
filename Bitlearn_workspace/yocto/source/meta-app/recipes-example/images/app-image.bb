require recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL:append = " usbutils"

IMAGE_FEATURES = "ssh-server-dropbear debug-tweaks splash tools-debug"

IMAGE_NAME = "appimage_splash"
