#include <mbed.h>

int main() {

  PwmOut potencia(PA_0);
  DigitalOut sentido1(PA_1);
  DigitalOut sentido2(PA_2);


  while(1) {
    
    potencia = 0.5;
    sentido1 = 1;
    sentido2 = 0;
    
  }
}