#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <softTone.h>
#include <lcd.h>

#include "gpioPin.h"
#include "output.h"
#include "myip.h"

// Global lcd handle:
static int lcdHandle;
int is = 4;
int scale[5] = {1637,0,1637,0};

void succeed()
{
  if (init() != 0)
    return;

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);

  lcdPosition(lcdHandle, 0, 0);
  lcdPuts(lcdHandle, "ID ACCEPTED     ");
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Welcome!        ");

  int i;
  int stat = HIGH;
  for (i = 0; i < is; i++)
  {
    if (stat == HIGH)
      stat = LOW;
    else
      stat = HIGH;
    digitalWrite(LED_GREEN, stat);
    softToneWrite(BEEPER, scale[i]);
    delay(500);
  }
}

void fail()
{
  if (init() != 0)
    return;

  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);

  lcdPosition(lcdHandle, 0, 0);
  lcdPuts(lcdHandle, "ID REJECTED     ");
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Not authorized! ");

  int i;
  int stat = HIGH;
  for (i = 0; i < is; i++)
  {
    if (stat == HIGH)
      stat = LOW;
    else
      stat = HIGH;
    digitalWrite(LED_RED, stat);
    softToneWrite(BEEPER, scale[i]);
    delay(500);
  }
}

void idle()
{
  if (init() != 0)
    return;
  
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);

  lcdPosition(lcdHandle, 0, 0);
  lcdPuts(lcdHandle, "NO ID DETECTED  ");
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Waiting input...");
}

void checking()
{
  if (init() != 0)
    return;

  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);

  lcdPosition(lcdHandle, 0, 0);
  lcdPuts(lcdHandle, "CHECKING ID     ");
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, "Validating...   ");

  int i;
  int stat = HIGH;
  for (i = 0; i < is; i++)
  {
    digitalWrite(LED_RED, stat);
    if (stat == HIGH)
      stat = LOW;
    else
      stat = HIGH;
    digitalWrite(LED_GREEN, stat);
    softToneWrite(BEEPER, scale[i]);
    delay(500);
  }
}

void showip()
{
  char *addrEth;
  char *addrEn;
  char addrEth0[32] = "eth0: ";
  char addrEn0[32] = "en0: ";

  if (init() != 0)
    return;

  IPv4(&addrEth, "eth0");
  IPv4(&addrEn, "en0");

  strcat(addrEth0, addrEth);
  strcat(addrEn0, addrEn);

  lcdPosition(lcdHandle, 0, 0);
  lcdPuts(lcdHandle, addrEth0);
  lcdPosition(lcdHandle, 0, 1);
  lcdPuts(lcdHandle, addrEn0);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

int init()
{
  wiringPiSetup();
  lcdHandle = lcdInit(2, 16, 4, DRS, DE, D4, D5, D6, D7,0, 0, 0, 0);  
  if (lcdHandle < 0)
  {
    fprintf (stderr, "lcdInit failed\n") ;
    return -1;
  }
  softToneCreate(BEEPER);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  return 0;
}
