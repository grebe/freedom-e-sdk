#ifndef ASSEMBLY

#ifndef ______BSP__BASEBAND__METAL_H
#define ______BSP__BASEBAND__METAL_H

#ifdef __METAL_MACHINE_MACROS

#define __METAL_PLIC_SUBINTERRUPTS 4

#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#else /* ! __METAL_MACHINE_MACROS */

#define __METAL_CLINT_2000000_INTERRUPTS 2

#define METAL_MAX_CLINT_INTERRUPTS 2

#define __METAL_INTERRUPT_CONTROLLER_C000000_INTERRUPTS 2

#define __METAL_PLIC_SUBINTERRUPTS 4

#define METAL_MAX_PLIC_INTERRUPTS 2

#define __METAL_CLIC_SUBINTERRUPTS 0
#define METAL_MAX_CLIC_INTERRUPTS 0

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 0

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_UART_INTERRUPTS 1


#include <metal/drivers/fixed-clock.h>
#include <metal/drivers/motion.h>
#include <metal/drivers/riscv,clint0.h>
#include <metal/drivers/riscv,cpu.h>
#include <metal/drivers/riscv,plic0.h>
#include <metal/drivers/tohost.h>
#include <metal/pmp.h>
#include <metal/shutdown.h>

asm (".weak __tohost_shutdown");
#define TOHOST_SHUTDOWN
struct __metal_shutdown __tohost_shutdown;

/* From clint@2000000 */
asm (".weak __metal_dt_clint_2000000");
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000;

/* From cpu@0 */
asm (".weak __metal_dt_cpu_0");
struct __metal_driver_cpu __metal_dt_cpu_0;

/* From interrupt_controller */
asm (".weak __metal_dt_interrupt_controller");
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller;

/* From interrupt_controller@c000000 */
asm (".weak __metal_dt_interrupt_controller_c000000");
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000;

// shutdown
extern const struct __metal_shutdown_vtable __tohost_shutdown_vtable;

struct __metal_shutdown __tohost_shutdown = {
  .vtable = &__tohost_shutdown_vtable,
};

/* From clint@2000000 */
struct __metal_driver_riscv_clint0 __metal_dt_clint_2000000 = {
    .vtable = &__metal_driver_vtable_riscv_clint0,
    .controller.vtable = &__metal_driver_vtable_riscv_clint0.clint_vtable,
    .control_base = 33554432UL,
    .control_size = 65536UL,
    .init_done = 0,
    .num_interrupts = METAL_MAX_CLINT_INTERRUPTS,
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_lines[0] = 3,
    .interrupt_lines[1] = 7,
};

/* From cpu@0 */
struct __metal_driver_cpu __metal_dt_cpu_0 = {
    .vtable = &__metal_driver_vtable_cpu,
    .cpu.vtable = &__metal_driver_vtable_cpu.cpu_vtable,
    .timebase = 1000000UL,
    .interrupt_controller = &__metal_dt_interrupt_controller.controller,
};

/* From interrupt_controller */
struct __metal_driver_riscv_cpu_intc __metal_dt_interrupt_controller = {
    .vtable = &__metal_driver_vtable_riscv_cpu_intc,
    .controller.vtable = &__metal_driver_vtable_riscv_cpu_intc.controller_vtable,
    .init_done = 0,
    .interrupt_controller = 1,
};

/* From interrupt_controller@c000000 */
struct __metal_driver_riscv_plic0 __metal_dt_interrupt_controller_c000000 = {
    .vtable = &__metal_driver_vtable_riscv_plic0,
    .controller.vtable = &__metal_driver_vtable_riscv_plic0.plic_vtable,
    .init_done = 0,
/* From interrupt_controller */
    .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    .interrupt_line = 11UL,
/* From interrupt_controller */
    // .interrupt_parent = &__metal_dt_interrupt_controller.controller,
    // .interrupt_line = 9UL,
    .control_base = 201326592UL,
    .control_size = 67108864UL,
    .max_priority = 3UL,
    .num_interrupts = 4UL,
    .interrupt_controller = 1,
};

/* From motion@4000 */
asm(".weak __metal_dt_motion0");
struct __metal_driver_motion __metal_dt_motion0 = {
  .motion = {
    .vtable = &__metal_driver_vtable_motion.motion,
    .actuator = {
      .acceleration = 0,
    },
    .sensor = {
      .frontDistance = 0,
      .backDistance = 0,
      .velocity = 0,
    },
  },
  .vtable = &__metal_driver_vtable_motion,
  .control_base = 0x4000L,
  .control_size = 0x1000L,
  .interrupt_parent = &__metal_dt_interrupt_controller_c000000.controller,
  .num_interrupts = 1,
  .interrupt_line = 3,
};

asm(".weak __metal_uart_tohost");
struct metal_uart __metal_uart_tohost = {
  .vtable = &tohost_uart_vtable,
};

#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_uart_tohost)

/* From clint@2000000 */
#define __METAL_DT_RISCV_CLINT0_HANDLE (&__metal_dt_clint_2000000.controller)

#define __METAL_DT_CLINT_2000000_HANDLE (&__metal_dt_clint_2000000.controller)

/* From cpu@0 */
#define __METAL_DT_RISCV_CPU_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_CPU_0_HANDLE (&__metal_dt_cpu_0.cpu)

#define __METAL_DT_MAX_HARTS 1

asm (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

/* From interrupt_controller */
#define __METAL_DT_RISCV_CPU_INTC_HANDLE (&__metal_dt_interrupt_controller.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_HANDLE (&__metal_dt_interrupt_controller.controller)

/* From interrupt_controller@c000000 */
#define __METAL_DT_RISCV_PLIC0_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_C000000_HANDLE (&__metal_dt_interrupt_controller_c000000.controller)

#define __MEE_DT_MAX_GPIOS 0

asm (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					NULL };
#define __METAL_DT_MAX_BUTTONS 0

asm (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					NULL };
#define __METAL_DT_MAX_LEDS 0

asm (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					NULL };
#define __METAL_DT_MAX_SWITCHES 0

asm (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 0

asm (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					NULL };

#define __METAL_DT_MAX_MOTIONS 1

asm(".weak __metal_motion_table");
struct __metal_driver_motion *__metal_motion_table[] = {
                    &__metal_dt_motion0 };

#define __METAL_DT_SHUTDOWN_HANDLE (&__tohost_shutdown)

#endif /* ! __METAL_MACHINE_MACROS */
#endif /* ______BSP__BASEBAND__METAL_H*/
#endif /* ! ASSEMBLY */
