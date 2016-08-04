#include "Arduino.h"

enum CONSTANTS {
    SWITCH_1 = 2
  , SWITCH_2 = 4
  , SWITCH_B1 = 10
  , SWITCH_B2 = 5
  , LED = 6
  , DIR_B = 13
  , VEL_B = 11
};

int g_StateSW1 = HIGH;
int g_StateSW2 = HIGH;
int g_StateSWB1 = HIGH;
int g_StateSWB2 = HIGH;
int g_NrTrains = 0;
int g_NrTrainsB = 0;
bool g_LED = LOW;


unsigned long g_nextLEDONTimer = 0;
unsigned long g_nextLEDOFFTimer = 0;
unsigned long g_motorOffTimer = 0;
bool g_gateOpen = true;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(DIR_B, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SWITCH_1,INPUT_PULLUP);
  pinMode(SWITCH_2,INPUT_PULLUP);
  pinMode(SWITCH_B1,INPUT_PULLUP);
  pinMode(SWITCH_B2,INPUT_PULLUP);
  digitalWrite(6, HIGH);
  Serial.begin(9600);
  g_nextLEDONTimer = millis () + 500;
  g_nextLEDOFFTimer = millis () + 1000;

  digitalWrite (LED, LOW);

  // open gates
  digitalWrite (DIR_B, HIGH);
  analogWrite (VEL_B, 200);
  delay (500);
  analogWrite (VEL_B, 0);
}

void BlinkLED ()
{
    if (millis () > g_nextLEDONTimer)
    {
        digitalWrite(LED, g_LED);
        g_nextLEDONTimer = millis () + 1000;
    }
    if (millis () > g_nextLEDOFFTimer)
    {
        digitalWrite(LED, LOW);
        g_nextLEDOFFTimer = millis () + 1000;
    }
}

void loop()
{
    BlinkLED ();
    if (0 != g_motorOffTimer)
    {
        if (millis () > g_motorOffTimer)
        {
            analogWrite (VEL_B, 0);
            g_motorOffTimer = 0;
        }
    }
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
    l_State = digitalRead(SWITCH_B1);
    if (l_State != g_StateSWB1)
    {
        g_StateSWB1 = l_State;
        if (LOW == l_State)
        {
            --g_NrTrainsB;
            char buffer[20];
            sprintf (buffer, "TrainB - %d", g_NrTrainsB);
            Serial.println (buffer);
        }
    }
    l_State = digitalRead(SWITCH_B2);
    if (l_State != g_StateSWB2)
    {
        g_StateSWB2 = l_State;
        if (LOW == l_State)
        {
            ++g_NrTrainsB;
            char buffer[20];
            sprintf (buffer, "TrainB - %d", g_NrTrainsB);
            Serial.println (buffer);
        }
    }
    if ((0 == g_NrTrains) && (0 == g_NrTrainsB))
    {
        g_LED = LOW;
        if (!g_gateOpen)
        {
            g_gateOpen = true;
            digitalWrite (DIR_B, HIGH);
            analogWrite (VEL_B, 255);
            g_motorOffTimer = millis () + 500;
        }
    }
    else
    {
        g_LED = HIGH;
        if (g_gateOpen)
        {
            g_gateOpen = false;
            digitalWrite (DIR_B, LOW);
            analogWrite (VEL_B, 255);
            g_motorOffTimer = millis () + 500;
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
