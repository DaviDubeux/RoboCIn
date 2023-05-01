#include <mbed.h>
#include <iostream>

using namespace std::chrono;

//pins
PwmOut enable (PB_5);
DigitalOut phase (PB_6);
InterruptIn ChA(PA_8);
DigitalIn ChB(PA_9);

//globals
long prevT = 0;
int prevPos = 0;
volatile int pos_i = 0;

float v1Filt = 0;
float prevV1 = 0;
float v2Filt = 0;
float prevV2 = 0;

float eIntegral = 0;
volatile float velocity_i = 0;
volatile long prevT_i = 0;

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

    //compute velocity with method 2
    Timer t;
    long currT = duration_cast<microseconds>(t.elapsed_time()).count(); //********
    float deltaT = ((float) (currT - prevT_i))/1e6;
    velocity_i = increment/deltaT;
    prevT_i = currT;
  }

int main() {
  ChA.rise(&readEncoder);
  Timer t;
  t.start();

  while(1) {
    enable = 100/3.0*duration_cast<microseconds>(t.elapsed_time()).count(); //********
    phase = 1;
    
    //Read the position in an atomic block to avoid potential misreads
    int pos = 0;
    float velocity2 = 0;
    //ATOMIC_BLOCKS?? *********
    pos = pos_i;
    velocity2 = velocity_i;

    //compute velocity method 1
    long currT = duration_cast<microseconds>(t.elapsed_time()).count(); //********
    float deltaT = ((float)(currT - prevT))/1e6;
    float velocity1 = (pos - prevPos)/deltaT;
    prevPos = pos;
    prevT = currT;

    //convert to rpm
    float v1 = velocity1/4096.0*60.0;
    float v2 = velocity2/4096.0*60.0;

    //Low-pass filter ***********
    v1Filt = 1*v1Filt + 2*v1 + 2*prevV1;
    prevV1 = v1;
    v2Filt = 1*v2Filt + 2*v2 + 2*prevV2;
    prevV2 = v2;
    
    ThisThread::sleep_for(1ms);

    /*
    // Set a target
    float vT = 100*(sin(currT/1e6)>0);

    //PID
    float kp = 1;
    float ki = 0;
    float e = vT - v1;
    eIntegral = eIntegral + e*deltaT;

    float u = kp*e + ki*eIntegral;

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
    cout<<v1<<endl;
    cout<<v1Filt<<endl;
    cout<<v2<<endl;
    cout<<v2Filt<<endl;
  }
}