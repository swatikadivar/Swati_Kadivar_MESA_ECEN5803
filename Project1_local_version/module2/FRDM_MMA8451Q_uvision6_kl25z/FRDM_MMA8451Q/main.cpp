#include "mbed.h"
#include "MMA8451Q.h"
#include "TSISensor.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)

Timer tick;

int main(void) {
    tick.start();
		MMA8451Q acc(PTE25, PTE24, MMA8451_I2C_ADDRESS);
    PwmOut rled(LED_RED);
    PwmOut gled(LED_GREEN);
    PwmOut bled(LED_BLUE);
    TSISensor tsi;

    while (true) {
				rled = 1.0 - abs(acc.getAccX());
        gled = 1.0 - abs(acc.getAccY());
        bled = 1.0 - abs(acc.getAccZ());
        wait(0.1);
				
				rled = 1.0 - tsi.readPercentage();
        gled = 1.0 - tsi.readPercentage();
        bled = 1.0 - tsi.readPercentage();
        wait(0.1);
				
				tick.stop();
        printf("The time taken was %f seconds\n\r", tick.read());
    }
}
