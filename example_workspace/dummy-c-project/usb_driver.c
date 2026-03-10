#include <stdio.h>
#include "driver_api.h"

// 陷阱 2：宏定义混淆
// 测试 Researcher 能否算出这里的基址是 0x4000 + 0x20 = 0x4020
#define BASE_ADDR   0x4000
#define USB_OFFSET  0x20
#define USB_CTRL_REG (BASE_ADDR + USB_OFFSET)

// 真正的初始化逻辑
static int usb_init_internal(void) {
    printf("Initializing USB at Register: 0x%X\n", USB_CTRL_REG);
    return 0; // Success
}

// 供外部调用的空壳
void legacy_init_do_not_use(void) {
    printf("This should never be called!\n");
}

/*
 * 陷阱 3：静态注册
 * Researcher 必须识别出，当 main.c 调用 usb_ops.init 时，
 * 实际上执行的是本文件中的 usb_init_internal 函数。
 */
struct driver_ops usb_ops = {
    .init = usb_init_internal,
    .shutdown = NULL
};
