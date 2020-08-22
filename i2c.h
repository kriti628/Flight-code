#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define MASK 0xF8
#define START 0x08
#define REPEATED_START 0x10
#define SLA_W_ACK 0x18
#define SLA_W_NACK 0x20
#define SLA_R_ACK 0x40
#define SLA_R_NACK 0x48
#define DATA_SENT_ACK 0x28
#define DATA_SENT_NACK 0x30
#define DATA_REC_ACK 0x50
#define DATA_REC_NACK 0x58
#define ARBITRATION_LOST 0x38
#define kill 0b00000011
#define emergency 0b00000110
#define restart 0b00001100
#define deploy 0b00011000
#define send_data 0b00110000
#define hm_data 0b01100000


void i2cInit(volatile uint8_t *add2);
void i2cStart(void);
void eepromWr(void);
void address(uint8_t addrs);
void eepromWrite(unsigned char data,volatile uint8_t *add3);
unsigned char eepromRandomRead(void);
void i2cStop(void);


#endif
