#ifndef SPI_H
#define SPI_H

#define SS 0
#define SCK 1
#define MOSI 2
#define MISO 3

void spiInit(void);
uint8_t spiTrans(uint8_t data);

#endif
