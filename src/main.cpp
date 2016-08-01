#include "Arduino.h"

enum CONSTANTS {
    SWITCH_1 = 2
  , SWITCH_2 = 4
  , LED = 6
};

int g_StateSW1 = HIGH;
int g_StateSW2 = HIGH;
int g_NrTrains = 0;
bool g_LED = LOW;


unsigned long g_nextLEDTimer = 0;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_1,INPUT_PULLUP);
  pinMode(SWITCH_2,INPUT_PULLUP);
  digitalWrite(6, HIGH);
  Serial.begin(9600);
  g_nextLEDTimer = millis () + 500;
}

void BlinkLED ()
{
    if (millis () > g_nextLEDTimer)
    {
        if (HIGH == g_LED)
        {
            g_LED = LOW;
        }
        else if ((0 != g_NrTrains) && (LOW == g_LED))
        {
            g_LED = HIGH;
        }
        digitalWrite(LED, g_LED);
        g_nextLEDTimer = millis () + 500;
    }
}
void loop()
{
    BlinkLED ();
    int l_State = digitalRead(SWITCH_1);
    if (l_State != g_StateSW1)
    {
        g_StateSW1 = l_State;
        if (LOW == l_State)
        {
            --g_NrTrains;
            char buffer[20];
            sprintf (buffer, "Train - %d", g_NrTrains);
            Serial.println (buffer);
        }
    }
    l_State = digitalRead(SWITCH_2);
    if (l_State != g_StateSW2)
    {
        g_StateSW2 = l_State;
        if (LOW == l_State)
        {
            ++g_NrTrains;
            char buffer[20];
            sprintf (buffer, "Train - %d", g_NrTrains);
            Serial.println (buffer);
        }
    }
  // // turn the LED on (HIGH is the voltage level)
  // digitalWrite(6, HIGH);
  // // wait for a second
  // char l_Msg [] = "00";
  // l_Msg[0] = '0' + digitalRead(4);
  // l_Msg[1] = '0' + digitalRead(2);
  // Serial.println(l_Msg);
  //
  // delay(500);
  // // turn the LED off by making the voltage LOW
  // digitalWrite(6, LOW);
  //  // wait for a second
  //  Serial.println(digitalRead(4));
  // delay(500);
}
