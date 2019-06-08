define Device/7623n-bananapi-bpi-r2
  DEVICE_TITLE := MTK7623n BananaPi R2
  DEVICE_DTS := mt7623n-bananapi-bpi-r2
  DEVICE_PACKAGES := kmod-usb-core kmod-usb-ohci kmod-usb2 kmod-usb3 \
                     kmod-ata-core kmod-ata-ahci-mtk \
                     mt7623n-preloader
  SUPPORTED_DEVICES := bananapi,bpi-r2
endef

TARGET_DEVICES += 7623n-bananapi-bpi-r2
