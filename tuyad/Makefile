include $(TOPDIR)/rules.mk

PKG_NAME := tuyad
PKG_RELEASE := 1
PKG_VERSION := 1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/tuyad
	CATEGORY := Tuya-RutOS
	TITLE := Tuya Daemon SRC
	DEPENDS := +libtuyad +libubus +libubox +libblobmsg-json
endef

define Package/tuyad/description
	This is the Tuya Daemon task SRC code for RutOS task for Tuya Cloud
endef

define Package/tuyad/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tuyad $(1)/usr/bin
	$(INSTALL_BIN) ./files/tuyad.init $(1)/etc/init.d/tuyad
	$(INSTALL_CONF) ./files/tuyad.config $(1)/etc/config/tuyad
endef

$(eval $(call BuildPackage,tuyad))
