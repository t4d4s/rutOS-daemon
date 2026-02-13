include $(TOPDIR)/rules.mk

PKG_NAME := libtuyad
PKG_RELEASE := 1
PKG_VERSION := 1.0.1
PKG_SOURCE_PROTO := git
PKG_SOURCE_URL := https://github.com/tuya/tuya-iot-core-sdk.git
PKG_SOURCE_VERSION := 0208badefb2003d30e70b5b875395e3187c850d9

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_BINARY_SUBDIR := build

define Package/libtuyad
	CATEGORY := Tuya-RutOS
	TITLE := Tuya-SDK LIB
endef

define Package/libtuyad/description
	This is a library for communication with devices using Tuya IoT Cloud.
endef

define Build/Install
	@echo "PLACEHOLDER: SDK does not have <MAKE INSTALL>"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib $(1)/usr/include
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/liblink_core.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libmiddleware_implementation.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libplatform_port.so $(1)/usr/lib/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libutils_modules.so $(1)/usr/lib/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/interface/system_interface.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/interface/mqtt_client_interface.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/include/tuyalink_core.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/utils/cJSON.h $(1)/usr/include/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/utils/tuya_error_code.h $(1)/usr/include/
endef

define Package/libtuyad/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/liblink_core.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libmiddleware_implementation.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libplatform_port.so $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(CMAKE_BINARY_SUBDIR)/lib/libutils_modules.so $(1)/usr/lib
endef

$(eval $(call BuildPackage,libtuyad))
