void print_fibonacci() {
  int n1 = 0;
  int n2 = 1;
  int term = 0;
  char print_buf[300];
  sprintf(print_buf, "Term %d: %d\n", term, n1);
  Serial.print(print_buf);
  term = term + 1;
  sprintf(print_buf, "Term %d: %d\n", term, n1);
  Serial.print(print_buf);
  for (;;) {
    term = term + 1;
    int n3 = n1 + n2;
    if(term%5 == 0){
      sprintf(print_buf, "Term %d: %d\n", term, n3);
      Serial.println(print_buf);
    }
    n1 = n2;
    n2 = n3;

    if (term >= 25) break;
  }
}


void sum_numbers() {
  int n1 = 1;
  int sum = 1;
  char print_buf[300];
  for (;;) {
    if(n1 %5 == 0){
      sprintf(print_buf, "                                                            Term %d: %d\n", n1, sum);
      Serial.println(print_buf);
    }
    n1 = n1 + 1;
    sum = sum+n1;
    if (n1 >= 100) break;
  }
}

void codeForTask1( void * parameter ) {
  for (;;) {
    Serial.print("Code is running on Core: ");Serial.println( xPortGetCoreID());
    print_fibonacci();
  }
}

void codeForTask2( void * parameter ) {
  for (;;) {
    Serial.print("                                                            Code is running on Core: ");Serial.println( xPortGetCoreID());
    sum_numbers();
  }
}

TaskHandle_t Task1, Task2;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  /*Syntax for assigning task to a core:
  xTaskCreatePinnedToCore(
                    TaskFunc,     // Function to implement the task
                    "TaskLabel",  // Name of the task 
                    10000,        // Stack size in bytes
                    NULL,         // Task input parameter 
                    0,            // Priority of the task 
                    &TaskHandle,  // Task handle. 
                    TaskCore);    // Core where the task should run 
 */
  xTaskCreatePinnedToCore(    codeForTask1,    "FibonacciTask",    5000,    NULL,    2,    &Task1,    0);
  //delay(500);  // needed to start-up task1
  xTaskCreatePinnedToCore(    codeForTask2,    "SumTask",    5000,    NULL,    2,    &Task2,    1);
}

void loop() {
}
