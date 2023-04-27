#include <mbed.h>
#include <iostream>

PwmOut enable (PB_5);
DigitalOut phase (PB_6);
InterruptIn ChA(PA_8);
DigitalIn ChB(PA_9);

int pos = 0;

void readEncoder() {
  int b = ChB;
  if (b>0) {
    pos++;
  }
  else {
    pos--;
  }
  }

int main() {
  phase = 0;
  ChA.rise(&readEncoder);

  while(1) {
    for (int i = 0; i < 100; i++) {

      enable = i/100.0;
       ThisThread::sleep_for(10ms);
      cout<<pos<<endl;

      if (i == 99){
        i = 0;
        phase = !phase;
      }

    }
  }
}