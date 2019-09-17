LOCAL_PATH := $(call my-dir)
APP_PLATFORM := android-8
include $(CLEAR_VARS)
LOCAL_MODULE     := jnicallbacker
LOCAL_SRC_FILES  := com_jniclass_MsgMod.c
include $(BUILD_SHARED_LIBRARY)