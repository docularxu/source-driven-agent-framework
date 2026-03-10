# Dummy Target - Agent Live-Fire Exercise

A minimal C project with **3 deliberate traps** designed to test the framework's core analysis capabilities.

## Traps

1. **Implicit dispatch (main.c:13)** - `usb_ops.init()` is a function pointer call through an `ops` struct. There is no direct call to the actual implementation. Tests whether Researcher can trace dynamic dispatch to its real target.

2. **Macro obfuscation (usb_driver.c:7-8)** - The actual hardware register address `0x4020` is hidden behind two layers of macro composition (`BASE_ADDR + USB_OFFSET`). Tests whether Researcher expands macros instead of guessing from names.

3. **Dead code distraction (driver_api.h:14)** - `legacy_init_do_not_use()` is declared in the header and defined in the driver, but never called anywhere. Tests whether the Agent wastes time analyzing dead code or correctly identifies it as unused.

## Expected Analysis Results

A competent Researcher should produce:
- Call chain: `main()` → `usb_ops.init()` → `usb_init_internal()` (via struct assignment at `usb_driver.c:28`)
- Register address: `USB_CTRL_REG = 0x4000 + 0x20 = 0x4020`
- `legacy_init_do_not_use()`: identified as dead code (defined but never called from any live path)
- `usb_ops.shutdown`: assigned `NULL` (no shutdown handler registered)

## Build

```
gcc -o boot main.c usb_driver.c
./boot
```
