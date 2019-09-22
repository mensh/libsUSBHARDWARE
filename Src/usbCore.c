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
#include "../nanopb/simple.pb.h"
#include <stdio.h>
#include <../nanopb/pb_encode.h>
#include <../nanopb/pb_decode.h>

uint8_t TestSendProto(void)
{
    uint8_t buffer[128];
    size_t message_length;
    bool status;

    SimpleMessage message = SimpleMessage_init_zero;

    /* Create a stream that will write to our buffer. */
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));

    /* Fill in the lucky number */
    message.lucky_number = 13;

    /* Now we are ready to encode the message! */
    status = pb_encode(&stream, SimpleMessage_fields, &message);
    message_length = stream.bytes_written;
    
    /* Then just check for any errors.. */
    if (!status)
    {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }
    CDC_Transmit_HS(buffer, message_length);
    
    return status;
}

uint8_t MyInfo(void)
{
    uint8_t array[128];

    array[0] = 0x01;
    array[1] = 0x00;
    CDC_Transmit_HS(array, 128);

    return pdTRUE;
}