LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := video
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ../libs/arm64-v8a/libvideo.so
#NDK_APP_DST_DIR := ../libs/arm64-v8a/
else
LOCAL_SRC_FILES := ../libs/armeabi-v7a/libvideo.so
#NDK_APP_DST_DIR := ../libs/armeabi-v7a/
endif
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := spectre4neolix
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ../libs/arm64-v8a/libspectre4neolix.so
#NDK_APP_DST_DIR := ../libs/arm64-v8a/
else
LOCAL_SRC_FILES := ../libs/armeabi-v7a/libspectre4neolix.so
#NDK_APP_DST_DIR := ../libs/armeabi-v7a/
endif
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
DEBUG_X9_TOF_HAL_ID=3
LOCAL_SRC_FILES:= \
	Sunny_Spectre_Wrapper.cpp
	
LOCAL_MODULE_PATH := $(LOCAL_PATH)
	
LOCAL_SHARED_LIBRARIES := \
	spectre4neolix\
	video 
	
	
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ \
					$(LOCAL_PATH)/../include \
					$(LOCAL_PATH)/../include/inc \
					$(LOCAL_PATH)/../include/inc2 \
LOCAL_CFLAGS += -fPIC -Wno-multichar  -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -w
LOCAL_CPPFLAGS += -DX9_TOF_HAL_ID=$(DEBUG_X9_TOF_HAL_ID)
#LOCAL_LDFLAGS := -w
#LOCAL_LDFLAGS := -Wl,-v,--fatal-warnings
LOCAL_LDFLAGS := -fPIE -pie


APP_STL := gnustl_static
LOCAL_LDLIBS     := -llog
LOCAL_LDLIBS     += -lz

LOCAL_MODULE:= sunnySpectreWrapper
LOCAL_MODULE_TAGS := debug

include $(BUILD_SHARED_LIBRARY)
