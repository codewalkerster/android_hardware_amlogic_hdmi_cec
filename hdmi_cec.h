#ifndef __HDMI_CEC_H__
#define __HDMI_CEC_H__

#define CEC_IOC_MAGIC                   'C'
#define CEC_IOC_GET_PHYSICAL_ADDR       _IOR(CEC_IOC_MAGIC, 0x00, uint16_t)
#define CEC_IOC_GET_VERSION             _IOR(CEC_IOC_MAGIC, 0x01, int)
#define CEC_IOC_GET_VENDOR_ID           _IOR(CEC_IOC_MAGIC, 0x02, uint32_t)
#define CEC_IOC_GET_PORT_INFO           _IOR(CEC_IOC_MAGIC, 0x03, int)
#define CEC_IOC_GET_PORT_NUM            _IOR(CEC_IOC_MAGIC, 0x04, int)
#define CEC_IOC_GET_SEND_FAIL_REASON    _IOR(CEC_IOC_MAGIC, 0x05, uint32_t)
#define CEC_IOC_SET_OPTION_WAKEUP       _IOW(CEC_IOC_MAGIC, 0x06, uint32_t)
#define CEC_IOC_SET_OPTION_ENALBE_CEC   _IOW(CEC_IOC_MAGIC, 0x07, uint32_t)
#define CEC_IOC_SET_OPTION_SYS_CTRL     _IOW(CEC_IOC_MAGIC, 0x08, uint32_t)
#define CEC_IOC_SET_OPTION_SET_LANG     _IOW(CEC_IOC_MAGIC, 0x09, uint32_t)
#define CEC_IOC_GET_CONNECT_STATUS      _IOR(CEC_IOC_MAGIC, 0x0A, uint32_t)
#define CEC_IOC_ADD_LOGICAL_ADDR        _IOW(CEC_IOC_MAGIC, 0x0B, uint32_t)
#define CEC_IOC_CLR_LOGICAL_ADDR        _IOW(CEC_IOC_MAGIC, 0x0C, uint32_t)

#define CEC_FAIL_NONE                   0
#define CEC_FAIL_NACK                   1
#define CEC_FAIL_BUSY                   2
#define CEC_FAIL_OTHER                  3

#endif /* __HDMI_CEC_H__ */
