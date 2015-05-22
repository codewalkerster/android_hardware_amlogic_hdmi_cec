/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 *     Amlogic HDMITX CEC HAL
 *       Copyright (C) 2014
 *
 * This implements a hdmitx cec hardware library for the Android emulator.
 * the following code should be built as a shared library that will be
 * placed into /system/lib/hw/hdmitx_cec.so
 *
 * It will be loaded by the code in hardware/libhardware/hardware.c
 * which is itself called from
 * frameworks/base/services/core/jni/com_android_server_hdmi_HdmiCecController.cpp
 */

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "hdmi_cec"
#endif
#include <cutils/log.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <hardware/hdmi_cec.h>
#include <hardware/hardware.h>

/* Set to 1 to enable debug messages to the log */
#define DEBUG 0
#if DEBUG
# define D(...) ALOGD(__VA_ARGS__)
#else
# define D(...) do{}while(0)
#endif

#define  E(...)  ALOGE(__VA_ARGS__)

static int dev_fd = -1;

#define HDMITX_CEC_SYSFS "/sys/class/amhdmitx/amhdmitx0/cec"
#define HDMITX_CEC_CONFIG_SYSFS "/sys/class/amhdmitx/amhdmitx0/cec_config"
#define HDMITX_PHY_ADDR_SYSFS "/sys/class/amhdmitx/amhdmitx0/phy_addr"
#define HDMITX_HPD_STATE_SYSFS "/sys/class/amhdmitx/amhdmitx0/hpd_state"

/*
 * (*add_logical_address)() passes the logical address that will be used
 * in this system.
 *
 * HAL may use it to configure the hardware so that the CEC commands addressed
 * the given logical address can be filtered in. This method can be called
 * as many times as necessary in order to support multiple logical devices.
 * addr should be in the range of valid logical addresses for the call
 * to succeed.
 *
 * Returns 0 on success or -errno on error.
 */
static int hdmitx_cec_add_logical_address(const struct hdmi_cec_device* dev, cec_logical_address_t addr)
{
    ALOGE("%s[%d] dev = %p addr = %d\n", __func__, __LINE__, dev, (unsigned int)addr);
    return 0;
}

/*
 * (*clear_logical_address)() tells HAL to reset all the logical addresses.
 *
 * It is used when the system doesn't need to process CEC command any more,
 * hence to tell HAL to stop receiving commands from the CEC bus, and change
 * the state back to the beginning.
 */
static void hdmitx_cec_clear_logical_address(const struct hdmi_cec_device* dev)
{
    ALOGE("%s[%d] dev = %p\n", __func__, __LINE__, dev);
}

/*
 * (*get_physical_address)() returns the CEC physical address. The
 * address is written to addr.
 *
 * The physical address depends on the topology of the network formed
 * by connected HDMI devices. It is therefore likely to change if the cable
 * is plugged off and on again. It is advised to call get_physical_address
 * to get the updated address when hot plug event takes place.
 *
 * Returns 0 on success or -errno on error.
 */
static int hdmitx_cec_get_physical_address(const struct hdmi_cec_device* dev, uint16_t* addr)
{
    int fd = 0;
    char paddr[4] = {0};

    dev = dev;
    fd = open(HDMITX_PHY_ADDR_SYSFS, O_RDONLY);
    if (fd < 0) {
        ALOGE("%s[%d] cat get physical address\n", __func__, __LINE__);
        return -1;
    }
    read(fd, paddr, 4);
    close(fd);
    *addr = (uint16_t)strtoul(paddr, NULL, 16);
    return 0;
}

/*
 * (*send_message)() transmits HDMI-CEC message to other HDMI device.
 *
 * The method should be designed to return in a certain amount of time not
 * hanging forever, which can happen if CEC signal line is pulled low for
 * some reason. HAL implementation should take the situation into account
 * so as not to wait forever for the message to get sent out.
 *
 * It should try retransmission at least once as specified in the standard.
 *
 * Returns error code. See HDMI_RESULT_SUCCESS, HDMI_RESULT_NACK, and
 * HDMI_RESULT_BUSY.
 */
static int hdmitx_cec_send_message(const struct hdmi_cec_device* dev, const cec_message_t* msg)
{
    ALOGE("%s[%d] dev = %p  msg = %p\n", __func__, __LINE__, dev, msg);
    return HDMI_RESULT_SUCCESS;
}

/*
 * (*register_event_callback)() registers a callback that HDMI-CEC HAL
 * can later use for incoming CEC messages or internal HDMI events.
 * When calling from C++, use the argument arg to pass the calling object.
 * It will be passed back when the callback is invoked so that the context
 * can be retrieved.
 */
static void hdmitx_cec_register_event_callback(const struct hdmi_cec_device* dev,
        event_callback_t callback, void* arg)
{
    dev = dev;
    callback = callback;
    arg = arg;
    ALOGE("%s[%d]TODO\n", __func__, __LINE__);
    //callback(, arg);
}

/*
 * (*get_version)() returns the CEC version supported by underlying hardware.
 */
static void hdmitx_cec_get_version(const struct hdmi_cec_device* dev, int* version)
{
    ALOGE("%s[%d] dev = %p  version = %p\n", __func__, __LINE__, dev, version);
    *version = 0x14;
}

/*
 * (*get_vendor_id)() returns the identifier of the vendor. It is
 * the 24-bit unique company ID obtained from the IEEE Registration
 * Authority Committee (RAC).
 */
static void hdmitx_cec_get_vendor_id(const struct hdmi_cec_device* dev, uint32_t* vendor_id)
{
    ALOGE("%s[%d] dev = %p  vendor_id = %p\n", __func__, __LINE__, dev, vendor_id);
    *vendor_id = 0x4321;
}

static struct hdmi_port_info hdmitx_port0 = {
    .type = HDMI_OUTPUT,
    // Port ID should start from 1 which corresponds to HDMI "port 1".
    .port_id = 1,
    .cec_supported = 1,
    .arc_supported = 0,
    .physical_address = 0x1000,
};

/*
 * (*get_port_info)() returns the hdmi port information of underlying hardware.
 * info is the list of HDMI port information, and 'total' is the number of
 * HDMI ports in the system.
 */
// FIXED 1 port for MBox
static void hdmitx_cec_get_port_info(const struct hdmi_cec_device* dev,
        struct hdmi_port_info* list[], int* total)
{
    ALOGE("%s[%d] dev = %p  list = %p  total = %p\n", __func__, __LINE__, dev, list, total);
    *total = 1;
    list[0] = &hdmitx_port0;
}

/*
 * (*set_option)() passes flags controlling the way HDMI-CEC service works down
 * to HAL implementation. Those flags will be used in case the feature needs
 * update in HAL itself, firmware or microcontroller.
 */
static void hdmitx_cec_set_option(const struct hdmi_cec_device* dev, int flag, int value)
{
    int fd = 0;

    ALOGE("%s[%d] dev = %p  flag = %p  value = %p\n", __func__, __LINE__, dev, flag, value);
    fd = open(HDMITX_CEC_CONFIG_SYSFS, O_WRONLY);
    if (fd < 0) {
        ALOGE("%s[%d][FILE]%s open failed\n", __func__, __LINE__, HDMITX_CEC_CONFIG_SYSFS);
        return ;
    }
    switch (flag) {
    case HDMI_OPTION_ENABLE_CEC:
        if (value == 1)
            write(fd, "0xf", 3);
        if (value == 0)
            write(fd, "0x0", 3);
        break;
    case HDMI_OPTION_WAKEUP:
        //Function: Automatic wake-up
        //write(fd, "0xf", 3);
        break;
    case HDMI_OPTION_SYSTEM_CEC_CONTROL:
        ALOGE("%s[%d]HDMI_OPTION_SYSTEM_CEC_CONTROL TODO\n", __func__, __LINE__);
        break;
    default:
        ALOGE("%s[%d] un-recognized flag = %d\n", __func__, __LINE__, flag);
        break;
    }
    close(fd);
}

/*
 * (*set_audio_return_channel)() configures ARC circuit in the hardware logic
 * to start or stop the feature. Flag can be either 1 to start the feature
 * or 0 to stop it.
 *
 * Returns 0 on success or -errno on error.
 */
static void hdmitx_cec_set_audio_return_channel(const struct hdmi_cec_device* dev, int flag)
{
    ALOGE("%s[%d] dev = %p  flag = %p\n", __func__, __LINE__, dev, flag);
}

/*
 * (*is_connected)() returns the connection status of the specified port.
 * Returns HDMI_CONNECTED if a device is connected, otherwise HDMI_NOT_CONNECTED.
 * The HAL should watch for +5V power signal to determine the status.
 */
static int hdmitx_cec_is_connected(const struct hdmi_cec_device* dev, int port_id)
{
    int fd = 0;
    char st = '0';
    dev = dev;      // prevent warning
    fd = open(HDMITX_HPD_STATE_SYSFS, O_RDONLY);
    if (fd < 0) {
        ALOGE("%s[%d][FILE]%s open failed\n", __func__, __LINE__, HDMITX_HPD_STATE_SYSFS);
        return 1;
    }
    read(fd, &st, 1);
    close(fd);
    ALOGE("port_id = %d  cec_is_connected = %c\n", port_id, st);
    return (st == '1') ? HDMI_CONNECTED : HDMI_NOT_CONNECTED;
}

/** Close the hdmitx cec device */
static int hdmitx_cec_close(struct hw_device_t *dev)
{
    ALOGE("%s[%d] dev = %p n", __func__, __LINE__, dev);
    if (dev_fd)
        close(dev_fd);
    free(dev);
    return 0;
}
/**
 * module methods
 */
static int open_hdmitx_cec( const struct hw_module_t* module, char const *name,
        struct hw_device_t **device )
{
    ALOGE("%s[%d] %s\n", __func__, __LINE__, name);
    if (strcmp(name, HDMI_CEC_HARDWARE_INTERFACE) != 0) {
        ALOGE("hdmitx_cec strcmp fail !!!");
        return -EINVAL;
    }
    if (device == NULL) {
        ALOGE("NULL hdmitx_cec device on open");
        return -EINVAL;
    }

    hdmi_cec_device_t *dev = malloc(sizeof(hdmi_cec_device_t));
    memset(dev, 0, sizeof(hdmi_cec_device_t));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t*) module;
    dev->common.close = hdmitx_cec_close;

    dev->add_logical_address = hdmitx_cec_add_logical_address;
    dev->clear_logical_address = hdmitx_cec_clear_logical_address;
    dev->get_physical_address = hdmitx_cec_get_physical_address;
    dev->send_message = hdmitx_cec_send_message;
    dev->register_event_callback = hdmitx_cec_register_event_callback;
    dev->get_version = hdmitx_cec_get_version;
    dev->get_vendor_id = hdmitx_cec_get_vendor_id;
    dev->get_port_info = hdmitx_cec_get_port_info;
    dev->set_option = hdmitx_cec_set_option;
    dev->set_audio_return_channel = hdmitx_cec_set_audio_return_channel;
    dev->is_connected = hdmitx_cec_is_connected;

    *device = (hw_device_t*) dev;

    dev_fd = open(HDMITX_CEC_SYSFS, O_RDWR);
    if (dev_fd < 0) {
        ALOGE("open cec device error\n");
        return -1;
    }

    return 0;
}

static struct hw_module_methods_t hdmitx_cec_module_methods = {
    .open =  open_hdmitx_cec,
};

/*
 * The hdmitx cec Module
 */
struct hdmi_cec_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag                = HARDWARE_MODULE_TAG,
        .module_api_version = HDMI_CEC_MODULE_API_VERSION_1_0,
        .hal_api_version    = HARDWARE_HAL_API_VERSION,
        .id                 = HDMI_CEC_HARDWARE_MODULE_ID,
        .name               = "Amlogic hdmitx cec Module",
        .author             = "Amlogic Corp.",
        .methods            = &hdmitx_cec_module_methods,
    },
};

