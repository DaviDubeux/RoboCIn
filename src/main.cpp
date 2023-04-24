#include <mbed.h>

  DigitalOut enable(PA_1); //Enable - PWM
  DigitalOut phase(PA_2); //Phase - horário ou anti-horário

int main() {

  while(1) {
    
    enable = 0.4;
    phase = 1;
    ThisThread::sleep_for(1);
    phase = 0;
    ThisThread::sleep_for(1);

    enable = 0.8;
    phase = 1;
    ThisThread::sleep_for(1);
    phase = 0;
    ThisThread::sleep_for(1);

  }
}