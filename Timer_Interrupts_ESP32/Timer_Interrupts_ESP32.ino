int t1 = 0;
int t2 = 0;
int adc_read_counter = 0;
int SamplingRate = 1000; //Read 1000 values in one second.

hw_timer_t * timer = NULL; 
volatile bool interruptbool1 = false;

/*Interrupt routine for Timer overflow event*/
void IRAM_ATTR onTimer() {
   interruptbool1 = true; //Indicates that the interrupt has been entered since the last time its value was changed to false 
}


void setup() {
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);                //Begin timer with 1 MHz frequency (80MHz/80)
  timerAttachInterrupt(timer, &onTimer, true);   //Attach the interrupt to Timer1
  unsigned int timerFactor = 1000000/SamplingRate; //Calculate the time interval between two readings, or more accurately, the number of cycles between two readings
  timerAlarmWrite(timer, timerFactor, true);      //Initialize the timer
  timerAlarmEnable(timer); 

}

void loop() {
  // put your main code here, to run repeatedly:
  if(interruptbool1){
      analogRead(36);
      interruptbool1 = false;
      if(adc_read_counter == 1){
          t1 = millis();
        }
      if(adc_read_counter == 1001){
          t2 = millis();
          Serial.println();
          Serial.print("Time taken to read 1000 readings is "); Serial.print(t2-t1);Serial.println(" milliseconds");
          Serial.println();
          adc_read_counter = 0;
        }
      adc_read_counter++;
    }

}
