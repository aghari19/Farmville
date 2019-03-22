#include <ti/devices/msp432p4xx/driverlib/driverlib.h>


//typedef enum {baud19200, baud57600} UARTBaudRate_t;



void InitUART(uint32_t moduleInstance,
              const eUSCI_UART_Config *uartConfig_p,
              uint_fast8_t selectedPort, uint_fast16_t selectedPins);

void UpdateUART(uint32_t moduleInstance, const eUSCI_UART_Config *uartConfig_p);

bool UARTHasChar(uint32_t moduleInstance);

uint8_t UARTGetChar(uint32_t moduleInstance);

bool UARTCanSend(uint32_t moduleInstance);

void UARTPutChar(uint32_t moduleInstance, uint8_t tChar);

void UARTSetBaud(uint32_t moduleInstance, eUSCI_UART_Config *uartConfig_p, int newBaud);

void InitializeUART(eUSCI_UART_Config *uartConfig);
