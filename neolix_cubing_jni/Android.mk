LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := neolixCubingAlgrthm
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ./neolixAlgorithm/lib/arm64-v8a/libneolixCubingAlgrthm.so
else
LOCAL_SRC_FILES := ./neolixAlgorithm/lib/armeabi-v7a/libneolixCubingAlgrthm.so
endif
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := sunnySpectreWrapper
ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES := ./pmd_sdk/arm64-v8a/libsunnySpectreWrapper.so
#NDK_APP_DST_DIR := ./pmd_sdk/arm64-v8a/
else
LOCAL_SRC_FILES := ./pmd_sdk/armeabi-v7a/libsunnySpectreWrapper.so
#NDK_APP_DST_DIR := ./pmd_sdk/armeabi-v7a/
endif
include $(PREBUILT_SHARED_LIBRARY)
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
LOCAL_MODULE           := neolixCubingJNI

LOCAL_C_INCLUDES := \
	./neolixAlgorithm/include \
	./opencv/native/jni/include

LOCAL_C_INCLUDES += $(LOCAL_PATH)/ \
					$(LOCAL_PATH)/../include \
					$(LOCAL_PATH)/../include/inc \
					$(LOCAL_PATH)/../include/inc2 

LOCAL_SRC_FILES := \
    NeolixCubing.cpp

LOCAL_CFLAGS := -DTARGET_PLATFORM_ANDROID

LOCAL_SHARED_LIBRARIES := \
	spectre4neolix\
	video \
	sunnySpectreWrapper \
	neolixCubingAlgrthm
LOCAL_LDLIBS :=  -llog -ldl -ljnigraphics

include $(BUILD_SHARED_LIBRARY)
