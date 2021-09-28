#define WATCHDOG_TIMEOUT_S 3

hw_timer_t * watchDogTimer = NULL;

void IRAM_ATTR watchDogInterrupt() {
  Serial.println("reboot");
  ESP.restart();
}


void watchDogRefresh()
{
  timerWrite(watchDogTimer, 0);                    //reset timer (feed watchdog)
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Watchdog sketch start");

  watchDogTimer = timerBegin(2, 80, true);
  timerAttachInterrupt(watchDogTimer, &watchDogInterrupt, true);
  timerAlarmWrite(watchDogTimer, WATCHDOG_TIMEOUT_S * 1000000, false);
  timerAlarmEnable(watchDogTimer);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.println("Watchdog not triggered in 1 second. Feeding it...");
  watchDogRefresh();

  delay(2000);
  Serial.println("Watchdog not triggered in 2 seconds. Feeding it...");
  watchDogRefresh();

  delay(4000);
  Serial.println("Watchdog not triggered in 4 second. Feeding it..."); //This shouldn't get printed
  watchDogRefresh();


}
