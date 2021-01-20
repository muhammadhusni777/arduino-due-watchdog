#define WDT_KEY (0xA5)

void watchdogSetup(void) {
  /*** watchdogDisable (); ***/
}

void setup()
{
  // Enable watchdog.
  WDT->WDT_MR = WDT_MR_WDD(0xFFF)
                | WDT_MR_WDRPROC
                | WDT_MR_WDRSTEN
                | WDT_MR_WDV(256 * 2); // Watchdog triggers a reset after 2 seconds if underflow
  // 2 seconds equal 84000000 * 2 = 168000000 clock cycles
  /* Slow clock is running at 32.768 kHz
    watchdog frequency is therefore 32768 / 128 = 256 Hz
    WDV holds the periode in 256 th of seconds  */

  Serial.begin(9600);
  uint32_t status = (RSTC->RSTC_SR & RSTC_SR_RSTTYP_Msk) >> RSTC_SR_RSTTYP_Pos; // Get status from the last Reset
  Serial.print("RSTTYP = 0b"); Serial.println(status, BIN);  // Should be 0b010 after first watchdog reset
}

void loop()
{
  Serial.println("LOOP started ! ");
  for(int i=0; i<=5; i++){
  Serial.print("Loop : ");
  Serial.print(i);
  Serial.println();
  delay(1000);
  //Restart watchdog
  WDT->WDT_CR = WDT_CR_KEY(WDT_KEY)
                | WDT_CR_WDRSTT;
}
//infinity loop to hang MCU
while(1){}
 
}
