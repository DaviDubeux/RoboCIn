#include <mbed.h>

  DigitalOut modo(PA_0);  // Mode = 1 - PH/EN Control Mode
  DigitalOut enable(PA_1); //Enable - ligado ou n
  DigitalOut phase(PA_2); //Phase - horário ou anti-horário

  PwmOut potencia(PB_0);

int main() {

  modo = 1;
  enable = 1;
  phase = 0;

  potencia = 0.5;

  while(1) {
    
    phase = 1;
    ThisThread::sleep_for(1);
    phase = 0;
    ThisThread::sleep_for(1);

  }
}