
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "system_config/default/framework/driver/usart/drv_usart_static.h"

#define PRINT(buf)                                                             \
  do {                                                                         \
    size_t i;                                                                  \
    for (i = 0; i < strlen((buf)); i++) {                                      \
      DRV_USART0_WriteByte((buf)[i]);                                          \
    }                                                                          \
  } while (0);

#define EXPECT_EQ(a, b)                                                        \
  if (a != b) {                                                                \
    char buf[150];                                                             \
    sprintf(buf, "Test Failed: %s %i", __FILE__, __LINE__);                    \
    PRINT(buf);                                                                \
  }

#if (!BIG_ENDIAN)
static uint32_t swap_32(uint32_t op) {
  return ((op >> 24) & 0xff) | ((op << 8) & 0xff0000) | ((op >> 8) & 0xff00) |
         ((op << 24) & 0xff000000);
}
#endif

static uint32_t ntohl(uint32_t netlong) {
#ifdef NETWORK_BIG_ENDIAN
#if BIG_ENDIAN
  return netlong;
#else
  return swap_32(netlong);
#endif
#else
  return netlong;
#endif
}

static uint32_t htonl(uint32_t hostlong) {
#ifdef NETWORK_BIG_ENDIAN
#if BIG_ENDIAN
  return hostlong;
#else
  return swap_32(hostlong);
#endif
#else
  return hostlong;
#endif
}

#if (!BIG_ENDIAN)
static uint16_t swap_16(uint16_t op) { return (op >> 8) | (op << 8); }
#endif

static uint16_t ntohs(uint16_t netshort) {
#ifdef NETWORK_BIG_ENDIAN
#if BIG_ENDIAN
  return netshort;
#else
  return swap_16(netshort);
#endif
#else
  return netshort;
#endif
}

static uint16_t htons(uint16_t hostshort) {
#ifdef NETWORK_BIG_ENDIAN
#if BIG_ENDIAN
  return hostshort;
#else
  return swap_16(hostshort);
#endif
#else
  return hostshort;
#endif
}

#include "MotorCommand.pbo.h"
void MotorCommand_direction_test() {
  MotorCommand my_message;
  MotorCommand_init(&my_message);
  EXPECT_EQ(0xDEADBEEF, my_message.magic);
  EXPECT_EQ(false, MotorCommand_has_direction(&my_message));
  EXPECT_EQ(0x00, my_message.direction);
  MotorCommand_set_direction(&my_message, 0x12);
  EXPECT_EQ(true, MotorCommand_has_direction(&my_message));
  EXPECT_EQ((0x12), my_message.direction);
  EXPECT_EQ(0x12, MotorCommand_direction(&my_message));
  MotorCommand_clear_direction(&my_message);
  EXPECT_EQ(false, MotorCommand_has_direction(&my_message));
  EXPECT_EQ(0x00, my_message.direction);
}
void MotorCommand_dutyCycle_test() {
  MotorCommand my_message;
  MotorCommand_init(&my_message);
  EXPECT_EQ(0xDEADBEEF, my_message.magic);
  EXPECT_EQ(false, MotorCommand_has_dutyCycle(&my_message));
  EXPECT_EQ(0x00, my_message.dutyCycle);
  MotorCommand_set_dutyCycle(&my_message, 0x12);
  EXPECT_EQ(true, MotorCommand_has_dutyCycle(&my_message));
  EXPECT_EQ((0x12), my_message.dutyCycle);
  EXPECT_EQ(0x12, MotorCommand_dutyCycle(&my_message));
  MotorCommand_clear_dutyCycle(&my_message);
  EXPECT_EQ(false, MotorCommand_has_dutyCycle(&my_message));
  EXPECT_EQ(0x00, my_message.dutyCycle);
}
void MotorCommand_mode_test() {
  MotorCommand my_message;
  MotorCommand_init(&my_message);
  EXPECT_EQ(0xDEADBEEF, my_message.magic);
  EXPECT_EQ(false, MotorCommand_has_mode(&my_message));
  EXPECT_EQ(0x00, my_message.mode);
  MotorCommand_set_mode(&my_message, 0x12);
  EXPECT_EQ(true, MotorCommand_has_mode(&my_message));
  EXPECT_EQ((0x12), my_message.mode);
  EXPECT_EQ(0x12, MotorCommand_mode(&my_message));
  MotorCommand_clear_mode(&my_message);
  EXPECT_EQ(false, MotorCommand_has_mode(&my_message));
  EXPECT_EQ(0x00, my_message.mode);
}
int main() {
  DRV_USART0_Initialize();
  MotorCommand_direction_test();
  MotorCommand_dutyCycle_test();
  MotorCommand_mode_test();
  PRINT("Tests completed")
}
