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

   cout<<velocity<<endl;
   
  }
}