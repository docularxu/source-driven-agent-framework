#ifndef DRIVER_API_H
#define DRIVER_API_H

/*
 * 全局契约结构体
 * Researcher 必须在 SYMBOL_INDEX 中记录这个结构体
 */
struct driver_ops {
    int (*init)(void);
    void (*shutdown)(void);
};

// 废弃的旧版接口（陷阱：测试 Agent 是否会被这段没用的代码干扰）
void legacy_init_do_not_use(void);

#endif // DRIVER_API_H
