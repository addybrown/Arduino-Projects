
/*

Takes a hall sensor input from a motor and is able to convert to the rpm, plan to add multi-input for less noise and better tracking

*/

volatile int count = 0;//if the interrupt will change this value, it must be volatile

float fRevolutions=0;
float countConvert;
int hall_sensor_pin=2;

float rpm;
unsigned long timeold;


void setup() {
 pinMode(hall_sensor_pin, INPUT); //set as input
 digitalWrite(hall_sensor_pin, HIGH);//enable internal pullup resistor
 attachInterrupt(digitalPinToInterrupt(2), interruptName, RISING);//Interrupt initialization
 
  timeold = 0;
  rpm=0;
 
 Serial.begin(9600);
}//end setup

void loop() {

  
  countConvert=float(count);
   fRevolutions=countConvert/22.0;

if (fRevolutions>0)
{
     detachInterrupt(0);
     rpm = 60000.0/(1000*(millis() - timeold))*fRevolutions;
     Serial.println(rpm,DEC);
     fRevolutions=0;
     count=0;
     timeold = millis();
     attachInterrupt(digitalPinToInterrupt(2), interruptName, RISING);
}
   Serial.println(rpm,DEC);

 // Serial.println(fRevolutions);//see the counts advance
  delay(100);//Delays usually can't be interfered with, here we will see the interrupt work
}//end loop

void interruptName()
{
  count = count+1;
  
}//end Interrupt Service Routine (ISR)void setup() {
  // put your setup code here, to run once:


