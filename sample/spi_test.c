#include <stdio.h>
#include <string.h>
#include <core.h>
#include "SPI.h"

int ReadSpiflashID(void) {
    char CMD_RDID = 0x9f;
    char id[3];
    int flashid = 0;

    memset(id, 0x0, sizeof(id));
    SPI.transfer(CMD_RDID, SPI_CONTINUE);
    id[0] = SPI.transfer(0x00, SPI_CONTINUE);
    id[1] = SPI.transfer(0x00, SPI_CONTINUE);
    id[2] = SPI.transfer(0x00, SPI_LAST);
    //MSB first 
    flashid = id[0] << 8;
    flashid |= id[1];
    flashid = flashid << 8;
    flashid |= id[2];

    return flashid;
}

void setup() {

    // initialize SPI:
    SPI.begin(); 
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop() {
    //MSB first 
    printf("spi flash id = 0x%x\n", ReadSpiflashID());
    delay(2000);
}

