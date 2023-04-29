#include <mbed.h>
#include <iostream>

using namespace std::chrono;

//pins
PwmOut enable (PB_5);
DigitalOut phase (PB_6);
InterruptIn ChA(PA_8);
DigitalIn ChB(PA_9);

//globals
Timer t;
long prevT = 0;
int prevPos = 0;
volatile int pos_i = 0;
float vFilt = 0;
float prevV = 0;
float eIntegral = 0;

/*
//Monitor serial ******
static BufferredSerial serial_port(USBTX, USBRX, 115200);

FileHandle *mbed::mbed_override_console(int fd) {
  return &serial_port;
}
*/

void readEncoder() {
  int b = ChB;
  int increment = 0;
  if (b>0) {
    increment++;
  }
  else {
    increment--;
  }
  pos_i = pos_i + increment;
  }


int main() {
  ChA.rise(&readEncoder);
  t.start();

  while(1) {
   int pos = 0;

   //ATOMIC_BLOCKS?? *********
   pos = pos_i;

   //compute velocity
   long currT = duration_cast<microseconds>(t.elapsed_time()).count(); //********
   float deltaT = ((float)(currT - prevT))/1e6;
   float velocity = (pos - prevPos)/deltaT;
   prevPos = pos;
   prevT = currT;
   
   //convert to rpm
   float v = velocity/4096.0*60.0;
   
   /*
  //Low-pass filter ***********
  vFilt = a*vFilt + b*v + b*prevV;
  prevV = v;
  */

  // Set a target
  float vT = 100*(sin(currT/1e6)>0);

  /*
  //PID
  float kp = 1;
  float ki = 0;
  float e = vT - v;
  eIntegral = eIntegral + e*deltaT;

  float u = kp*e + ki*eIntegral;
  */

  /*
  //Set enable and phase
  int dir = 1;
  if (u<0){
    dir = -1;
  }
  int pwr = (int) fabs(u);
  if (pwr > 255){
    pwr = 255;
  }
  phase = dir;
  enable = pwr;
  */


  /*
  cout<<vFilt<<endl;
  ThisThread::sleep_for(1);
  */
  }
}