#include "mpu9250.h"
#include "mpu9250_registers.h"

static uint8_t mpu9250_reg_read(mpu9250_t *dev, uint8_t reg);

void mpu9250_init(mpu9250_t *dev, SPIDriver *spi_dev)
{
    dev->spi = spi_dev;
}

bool mpu9250_ping(mpu9250_t *dev)
{
    int id = mpu9250_reg_read(dev, MPU9250_REG_WHO_AM_I);
    return id == 0x71;
}

static uint8_t mpu9250_reg_read(mpu9250_t *dev, uint8_t reg)
{
    uint8_t ret = 0;

    /* 7th bit indicates read (1) or write (0). */
    reg |= 0x80;

    spiSelect(dev->spi);
    spiSend(dev->spi, 1, &reg);
    spiReceive(dev->spi, 1, &ret);
    spiUnselect(dev->spi);

    return ret;
}
