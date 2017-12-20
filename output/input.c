#include <wiringPi.h>

#include "gpioPin.h"
#include "cli.h"

void captureInput(void)
{
    wiringPiSetup();
    pinMode(BUTTON, INPUT);
    int count = 0;

    do
    {
        sleep(1000);
        if (digitalRead(BUTTON) == 1)
            count++;
        else
            count = 0;

        if(count >= 5)
        {
            sendToSrv("BTN-IP");
            count = 0;
        }
    } while (1);
}
