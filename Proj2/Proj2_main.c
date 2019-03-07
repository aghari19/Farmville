
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>


#include "graphics_HAL.h"
#include "UART_HAL.h"
#include "Farm.h"
// include all other .h files


void initialize();

int main(void) {


    Graphics_Context g_sContext;

    initialize();
    InitGraphics(&g_sContext);

    farm_t farm;
    Farm_init(&farm);

    while (1) {


    }

}

void initialize() {
    // stop the watchdog timer
    WDT_A_hold(WDT_A_BASE);

    // call your intialization functions
}


