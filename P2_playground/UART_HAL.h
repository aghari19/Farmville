#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

//This UART module is to initialize the UART
void InitUART(uint32_t moduleInstance,
              const eUSCI_UART_Config *uartConfig_p,
              uint_fast8_t selectedPort, uint_fast16_t selectedPins);

//This method updates the UART
void UpdateUART(uint32_t moduleInstance, const eUSCI_UART_Config *uartConfig_p);

//This UART module checks if there is a value that has been entered or not
bool UARTHasChar(uint32_t moduleInstance);

/*
 * This UART Module is executed when a character is entered.
 * If the entered value is a character this modules gets the character, then checks of the conditions which it falls under
 * and then returns the result that satisfy the condition.
 */
uint8_t UARTGetChar(uint32_t moduleInstance);

//In this module we check if the UART is ready to transmit the received data
bool UARTCanSend(uint32_t moduleInstance);

//In this module if the UART is ready to transmit then it goes ahead and transmits
void UARTPutChar(uint32_t moduleInstance, uint8_t tChar);

//This Module sets the clock prescalar and the registers to the right value depending on the
//the baudrate sent in through the parameter
void UARTSetBaud(uint32_t moduleInstance, eUSCI_UART_Config *uartConfig_p, int newBaud);

//This method declares the sets the first state of the UART
void InitializeUART(eUSCI_UART_Config *uartConfig);
