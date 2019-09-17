LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE     := addLib
LOCAL_SRC_FILES  := com_model_classes_MsgMod.c
include $(BUILD_SHARED_LIBRARY)