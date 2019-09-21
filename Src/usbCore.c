#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"
#include "fsmc.h"
#include "usbd_cdc_if.h"

uint8_t InitMAPFunc(void)
{
    uint8_t status;
    return status;
}

uint8_t MyInfo(void)
{
    uint8_t array[128];

    array[0] = 0x01;
    array[1] = 0x00;
    CDC_Transmit_HS(array,128);

    return pdTRUE;
}