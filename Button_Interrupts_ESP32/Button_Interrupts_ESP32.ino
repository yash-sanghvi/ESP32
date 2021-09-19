const int interruptPin = 5;
volatile int interruptOccurrences = 0;
int nInterrupts = 0;
 
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
 
void IRAM_ATTR handleButtonInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  interruptOccurrences++;
  portEXIT_CRITICAL_ISR(&mux);
}
 
void setup() {
 
  Serial.begin(115200);
  Serial.println("Button interrupts sketch begins");
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleButtonInterrupt, FALLING);
 
}
 
void loop() {
  if(interruptOccurrences>0){
 
      portENTER_CRITICAL(&mux);
      interruptOccurrences = 0;
      portEXIT_CRITICAL(&mux);
 
      nInterrupts++;
      Serial.print("Another interrupt recorded. Total count: ");
      Serial.println(nInterrupts);
  }
}
