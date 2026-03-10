#include <stdio.h>
#include "driver_api.h"

// 外部引用的具体驱动 ops 结构体
extern struct driver_ops usb_ops;

int main() {
    printf("System Booting...\n");

    // 陷阱 1：这里发生了一次隐性跳转，没有直接调用 usb_init()
    // 测试 Researcher 能否顺藤摸瓜找到 usb_driver.c 中的真身
    int ret = usb_ops.init();

    if (ret == 0) {
        printf("Boot successful.\n");
    } else {
        printf("Boot failed.\n");
    }

    return 0;
}
