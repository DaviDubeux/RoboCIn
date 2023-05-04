#include <mbed.h>
#include <iostream>

using namespace std::chrono;

//pins
PwmOut enable (PB_5);
DigitalOut phase (PB_6);
InterruptIn ChA(PA_8);
InterruptIn ChB(PA_9);

//Monitor serial
static BufferedSerial serial_port(USBTX, USBRX, 115200);
FileHandle *mbed::mbed_override_console(int fd) {
  return &serial_port;
}

//globals
int pos = 0;
int posA = 0;
int posB = 0;
float deltaPos = 0;
float velocity = 0;
int i = 100;
float vFilt = 0;
float prevV = 0;
float eIntegral = 0;
float ePrev = 0;

//define uma RPM target
float vT = 300.0;

//Tickers 
Ticker timer;
Ticker pwm;

void readPosA(){
  posA++;
}
// void readPosB(){
//   posB++;
// }

void readPos() {
  pos = posA;
  posA = 0;
  // posB = 0;
;
  }

void update(){
  readPos();
  velocity = pos/1; //1: deltaT float
  pos = 0;
}

void vTupdate(){
  i = (-1)*i;
  vT = 200 + i;
}

int main() {  
  enable.period(1.0/1000);

  ChA.rise(&readPosA);
  // ChB.rise(&readPosB);
  timer.attach(&update, 1ms); //deltaT chrono
  pwm.attach(&vTupdate, 1000ms); 

  while(1) {

  //converter para RPM
  long double v = velocity/4096.0*1000.0*60.0/5.0;

  //constantes PID
  float kp = 0.005;
  float ki = 0.001;

  //define variáveis de erro
  float e = vT - v;
  eIntegral = eIntegral + e*0.001;

  //calcula o ajuste (u)
  float u = kp*e + ki*eIntegral;

  //problemas devido a mudança de sentido do motor
  // int dir = 0;
  // if (u<0){
  //   dir = 1;
  // }
  // int pwr = (int) fabs(u);
  // if (pwr > 1){
  //   pwr = 1;
  // }
  // phase = dir;
  // enable = pwr;

  //define direção e sentido do motor
  phase = 0;
  enable = u;

  //printa as velocidades target e medidas no plotter
  printf("%f ", vT);
  printf("%Lf\n", v);
  }
}