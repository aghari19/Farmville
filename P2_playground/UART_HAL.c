#include "UART_HAL.h"

void InitUART(uint32_t moduleInstance,
              const eUSCI_UART_Config *uartConfig_p,
              uint_fast8_t selectedPort, uint_fast16_t selectedPins)
{
    UART_initModule(moduleInstance, uartConfig_p);
    UART_enableModule(moduleInstance);
    GPIO_setAsPeripheralModuleFunctionInputPin(selectedPort,
    selectedPins, GPIO_PRIMARY_MODULE_FUNCTION);
}

void UpdateUART(uint32_t moduleInstance, const eUSCI_UART_Config *uartConfig_p)
{
    UART_initModule(moduleInstance,uartConfig_p);
    UART_enableModule(moduleInstance);
}

//This UART module checks if there is a value that has been entered or not
bool UARTHasChar(uint32_t moduleInstance)
{
    if(UART_getInterruptStatus (moduleInstance, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
        return true;
    else
        return false;
}

/*
 * This UART Module is executed when a character is entered.
 * If the entered value is a character this modules gets the character, then checks of the conditions which it falls under
 * and then returns the result that satisfy the condition.
 */
uint8_t UARTGetChar(uint32_t moduleInstance)
{
    return UART_receiveData(moduleInstance);
}

//In this module we check if the UART is ready to transmit the received data
bool UARTCanSend(uint32_t moduleInstance)
{
    if (UART_getInterruptStatus (moduleInstance, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG) == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
        return true;
    else
        return false;
}

//In this module if the UART is ready to transmit then it goes ahead and transmits
void UARTPutChar(uint32_t moduleInstance, uint8_t tChar)
{
    UART_transmitData(moduleInstance, tChar);
}

void UARTSetBaud(uint32_t moduleInstance, eUSCI_UART_Config *uartConfig_p, UARTBaudRate_t newBaud)
{
    if(newBaud == 19200)
    {
        uartConfig_p->clockPrescalar = 156;
        uartConfig_p->firstModReg = 4;
        uartConfig_p->secondModReg = 0x00;
        UpdateUART(moduleInstance, uartConfig_p);
    }
    else if(newBaud == 57600)
    {
        uartConfig_p->clockPrescalar = 52;
        uartConfig_p->firstModReg = 1;
        uartConfig_p->secondModReg = 0x25;
        UpdateUART(moduleInstance, uartConfig_p);
    }
}
