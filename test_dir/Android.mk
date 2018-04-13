LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := spectre_custom
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ./libspectre_custom.so
else
LOCAL_SRC_FILES := ./libspectre_custom.so
endif
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := video
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ../libs/arm64-v8a/libvideo.so
#NDK_APP_DST_DIR := ../libs/arm64-v8a/
else
LOCAL_SRC_FILES := ../libs/arm64-v8a/libvideo.so
#NDK_APP_DST_DIR := ../libs/armeabi-v7a/
endif
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    main.cpp
	
LOCAL_MODULE_PATH := $(LOCAL_PATH)
	
LOCAL_SHARED_LIBRARIES := \
	video \
	spectre_custom	
	
#LOCAL_STATIC_LIBRARIES := \
#	libjpeg_static
	
LOCAL_C_INCLUDES += $(LOCAL_PATH)/
		
LOCAL_CFLAGS += -fPIC -Wno-multichar -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -w

#LOCAL_LDFLAGS := -w
#LOCAL_LDFLAGS := -Wl,-v,--fatal-warnings
LOCAL_LDFLAGS := -fPIE -pie
#LOCAL_LDFLAGS += -L$(LOCAL_PATH) -lusb1.0 -lTof


APP_STL := gnustl_static
LOCAL_LDLIBS     := -llog
LOCAL_LDLIBS     += -lz

LOCAL_MODULE:= mars_test
LOCAL_MODULE_TAGS := debug

include $(BUILD_EXECUTABLE)
