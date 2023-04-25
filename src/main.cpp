#include <mbed.h>
#include <iostream>

  DigitalOut enable(PA_1); //Enable - PWM
  DigitalOut phase(PA_2); //Phase - horário ou anti-horário
  DigitalIn ChA(PC_0);
  DigitalIn ChB(PC_1);

  int pos = 0;

  void readEncoder() {
    int b = ChA;
    if (b>0) {
      pos++;
    }
    else{
      pos--;
    }
    }


int main() {

  while(1) {
    
    enable = 0.4;
    phase = 1;
    cout<<pos;
    ThisThread::sleep_for(1);
    phase = 0;
    cout<<pos;
    ThisThread::sleep_for(1);

    enable = 0.8;
    phase = 1;
    cout<<pos;
    ThisThread::sleep_for(1);
    phase = 0;
    cout<<pos;
    ThisThread::sleep_for(1);

  }
}