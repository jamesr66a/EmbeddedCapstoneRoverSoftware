#include <stdint.h>

uint32_t getCpuCycles() {
  uint32_t ticks;
  __asm__ __volatile__("mfc0 %0, $9\r\n" : "=r"(ticks));
  return ticks;
}

int32_t positive_modulo(int32_t i, int32_t n) { return (i % n + n) % n; }

uint32_t positive_modulo_u(uint32_t i, uint32_t n) {
  return (i % n + n) % n;
}

int32_t constrain(int val, int max, int min) {
  if (val > max) {
    val = max;
  } else if (val < min) {
    val = min;
  }
  return val;
}