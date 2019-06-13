#include <stdio.h>
#include <stdlib.h>

#include <metal/cpu.h>
#include <metal/motion.h>

static struct metal_motion *motion;
static struct metal_interrupt *motion_intr;
static int motion_intr_id;

extern struct metal_cpu *__metal_dt_cpu_0;

void motion_handler (int id, void *data)
{
  struct metal_motion *m = data;
  metal_motion_sense(m);

  if (m->sensor.frontDistance < 320) {
    m->actuator.acceleration = -50;
  } else {
    m->actuator.acceleration = 50;
  }

  metal_motion_actuate(m);
}

int main (void)
{
  struct metal_cpu *cpu0;
  struct metal_interrupt *cpu_intr;
  int rc;

  printf("Ok, let's go.\n");

  // Lets get the CPU and and its interrupt
  cpu0 = metal_cpu_get(0);
  if (cpu0 == NULL) {
    printf("CPU null.\n");
    return 2;
  } else {
    printf("Got CPU.\n");
  }
  cpu_intr = metal_cpu_interrupt_controller(cpu0);
  if (cpu_intr == NULL) {
      printf("CPU interrupt controller is null.\n");
      return 3;
  } else {
    printf("Got CPU interrupt controller.\n");
  }
  metal_interrupt_init(cpu_intr);
  printf("Initialized interrupt controller.\n");

  // Enable CPU interrupt
  if (metal_interrupt_enable(cpu_intr, 0) == -1) {
    printf("CPU interrupt enable failed.\n");
    return 6;
  } else {
    printf("CPU interrupt enabled.\n");
  }

  motion = metal_motion_get_device(0);
  if (motion == NULL) {
    printf("Motion is null.\n");
    return 4;
  } else {
    printf("Got motion.\n");
  }
  metal_motion_init(motion);

  motion_intr = metal_motion_interrupt(motion);
  if (motion == NULL) {
    printf("Motion interrupt is null.\n");
    return 5;
  }

  metal_interrupt_init(motion_intr);

  motion_intr_id = metal_motion_get_interrupt_id(motion);
  motion_intr_id = 3;
  rc = metal_interrupt_register_handler(motion_intr, motion_intr_id, motion_handler, motion);
  if (rc < 0) {
    return rc;
  } else

  printf("About to init.\n");
  metal_motion_init(motion);
  if (metal_interrupt_enable(motion_intr, motion_intr_id) == -1) {
    return 6;
  } else {
    printf("Enabled interrupt.\n");
  }

  while (1)
    ;

  return 0;
}
