# 01 - Boot Init Flow Analysis

## Overview
System boot entry point that initializes the USB subsystem via an ops struct dispatch pattern.

## Call Chain
```
main()                              # main.c:7
  └─ usb_ops.init()                 # main.c:13 [DYNAMIC DISPATCH]
      └─ usb_init_internal()        # usb_driver.c:12 (bound at usb_driver.c:28)
```

## Key Data Structures

### struct driver_ops (driver_api.h:8-11)
```c
struct driver_ops {
    int (*init)(void);       // Initialization function pointer
    void (*shutdown)(void);  // Shutdown function pointer
};
```
- Used as a global contract between main.c and driver implementations
- Single instance: `usb_ops` (usb_driver.c:28)

## Key Logic

- `main()` prints boot message, calls `usb_ops.init()`, checks return value [main.c:7-21]
- Return value 0 = success, non-zero = failure [main.c:15-19]
- No error recovery beyond printing "Boot failed" [main.c:18]

## Dynamic Dispatch / Implicit Jumps

| Variable | Type | Assignment Location | Actual Target |
|----------|------|-------------------|---------------|
| `usb_ops.init` | `int (*)(void)` | usb_driver.c:29 | `usb_init_internal()` (usb_driver.c:12) |
| `usb_ops.shutdown` | `void (*)(void)` | usb_driver.c:30 | `NULL` (no handler) |

## Dead Code

- `legacy_init_do_not_use()` - declared in driver_api.h:14, defined in usb_driver.c:18
  - **Never called** from any code path in the project
  - Grep verification: `grep -rn 'legacy_init' *.c *.h` shows only declaration and definition, zero call sites

## Open Questions
- [ ] What hardware register does `usb_init_internal()` actually access? (deferred to 02-usb-driver)
- [ ] Why is shutdown handler NULL? Design choice or incomplete implementation?
