#ifndef I2C_H
#define I2C_H

#define MASK 0xF8
#define START 0x08
#define REPEATED_START 0x10
#define SLA+W_ACK 0x18
#define SLA+W_NACK 0x20
#define SLA+R_ACK 0x40
#define SLA+R_ACK 0x48
#define DATA_SENT_ACK 0x28
#define DATA_SENT_NACK 0x30
#define DATA_REC_ACK 0x50
#define DATA_REC_NACK 0x58
#define ARBITRATION_LOST 0x38


void i2cInit(void);
void i2cStart(void);
void eepromWr(void);
void address(uint8_t addrs);
void eepromWrite(unsigned char data);
unsigned char eepromRandomRead(void);
void i2cStop(void);
 

#endif
