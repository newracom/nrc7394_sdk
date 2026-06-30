include $(TOPDIR)/rules.mk

PKG_NAME:=nrc_fota_rootd
PKG_RELEASE:=1
PKG_LICENSE:=Apache-2.0

include $(INCLUDE_DIR)/package.mk

define Package/nrc_fota_rootd
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=nrc standalone FOTA root addition
  MAINTAINER:=newracom
  DEPENDS:=+libjson-c
endef

define Package/nrc_fota_rootd/description
  FOTA support
endef


define Build/Configure
endef

define Build/Compile
	$(TARGET_CC) $(TARGET_CFLAGS) \
		-o $(PKG_BUILD_DIR)/nrc_fota_rootd \
		$(PKG_BUILD_DIR)/nrc_fota_rootd.c \
		-L$(STAGING_DIR)/usr/lib -ljson-c
endef


define Package/nrc_fota_rootd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/nrc_fota_rootd $(1)/usr/bin/nrc_fota_rootd
endef

$(eval $(call BuildPackage,nrc_fota_rootd))
