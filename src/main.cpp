#include <mbed.h>
#include <iostream>

using namespace std::chrono;

//pins
PwmOut enable (PB_5);
DigitalOut phase (PB_6);
InterruptIn ChA(PA_8);
DigitalIn ChB(PA_9);

//globals
int pos = 0;
float deltaPos = 0;
float velocity = 0;

float vFilt = 0;
float prevV = 0;

float eIntegral = 0;

//Ticker
Ticker timer;

//Monitor serial ******
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd) {
  return &serial_port;
}

void readEncoder() {
  int b = ChB;
  if (b>0) {
    pos++;
  }
  else {
    pos--;
  }
}

void update(){
  velocity = pos/10; //deltaT float
  pos = 0;
}

int main() {
  ChA.rise(&readEncoder);
  timer.attach(&update, 10ms);

  while(1) {

    //convert to rpm
    float v = velocity/4096.0*1000.0*60.0;

    //Low-pass filter
    /*
    vFilt = 1*vFilt + 2*v + 2*preV
    prevV = v;
    */

    // Set a target
    float vT = 1500;

    //PID
    float kp = 0.001;
    float ki = 0.01;
    float e = vT - v;
    eIntegral = eIntegral + e*0.01;

    float u = kp*e + ki*eIntegral;

    //Set enable and phase
    int dir = 1;
    if (u<0){
      dir = -1;
    }
    int pwr = (int) fabs(u);
    if (pwr > 1){
      pwr = 1;
    }
    phase = dir;
    enable = pwr;

    printf("%f\n", v);
  }
}