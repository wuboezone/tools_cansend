LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := \
liblog \
libcutils \
libutils
LOCAL_MODULE:=can_send
LOCAL_MODULE_TAGS:=optional
LOCAL_SRC_FILES:= \
can_send.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

include $(BUILD_EXECUTABLE)
include $(call all-makefiles-under,$(LOCAL_PATH))
