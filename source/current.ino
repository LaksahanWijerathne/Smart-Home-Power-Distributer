void sensors(){
  float volt = voltage();
////////////////////////////////////////////////////////////////////
  tft.setTextColor(YELLOW);
  tft.drawRect(265,64, 50,17,WHITE);
  tft.fillRect(266,66, 47,13,BLACK);
  tft.setCursor(269, 69); 
  tft.setTextSize(1);
  tft.println(volt); //// This is variable that need Update Display
  tft.setCursor(305, 69); 
  tft.println("v");
//////////////////////////////////////////////////////////////////// 
  float ans =0.0;
  if (volt >= 11){  
   ans = volt-11; //
   ans = ans * 10;//
   ans = 5*ans; // this answer is the Precentage level of battery
  }
  tft.drawRect(265,90, 50,17,WHITE);
  tft.fillRect(266,92, 47,13,BLACK);
  tft.setCursor(269, 95); 
  tft.setTextSize(1);
  tft.println(ans); //// This is variable that need Update Display
  tft.setCursor(305, 95); 
  tft.println("%");
//////////////////////////////////////////////////////////////////
float ChargeTime = (13.2-volt)*10;
  tft.drawRect(265,116, 50,17,WHITE);
  tft.fillRect(266,118, 47,13,BLACK);
  tft.setCursor(269, 121); 
  tft.setTextSize(1);
  tft.println(ChargeTime); //// This is variable that need Update Display
  tft.setCursor(300, 121); 
  tft.println("hr");
}
//////////////////////////////////////////////////////////////////////////////////////
void error(){
//Serial.println(F("TFT LCD Starting.."));
//Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier==0x0101)
      identifier=0x9341;
  
  tft.begin(identifier);
  tft.fillScreen(BLUE);
  unsigned long start = micros();
  tft.setRotation(1);
  tft.setCursor(0, 0);
  tft.setTextSize(4);
  tft.setCursor(60, 60);
  tft.setTextColor(RED);
  tft.println("NO Battery ");
  tft.setCursor(60, 100);
  tft.println("Connected");
  /////////////////////////////////////
  tft.setCursor(60, 180);
  tft.setTextSize(1);  
  float volt = voltage();
  tft.println(volt);
}
//////////////////////////////////////////////////////////////////////////////////
void displayUpdate(){
  //////////////////////////////////
  
  if (digitalRead(Fridge)==1) {
    tft.fillCircle(15, 74, 5, BLACK);//  This is Fridge Update Display
  }
  else  {
    tft.fillCircle(15, 74, 5, GREEN);//  This is Fridge Update Display
  }
  /////////////////////////////////
  if (digitalRead(Computer)==1) {
    tft.fillCircle(15, 104, 5, BLACK);// This is Computer Display
  }
  else  {
    tft.fillCircle(15, 104, 5, GREEN);// This is Computer Display
  }
  /////////////////////////////////
  if (digitalRead(Tv)==1) {
    tft.fillCircle(15, 134, 5, BLACK);//  This is TV Update Display
  }
  else  {
    tft.fillCircle(15, 134, 5, GREEN);//  This is Tv Display
  }
  /////////////////////////////////
  if (digitalRead(PhoneCharger)==1) {
    tft.fillCircle(15, 165, 5, BLACK);//  This is PhoneCharger Update Display
  }
  else  {
    tft.fillCircle(15, 165, 5, GREEN);//  This is PhoneCharger Update Display
  }
  /////////////////////////////////
  if (digitalRead(TableFan)==1) {
    tft.fillCircle(15, 194, 5, BLACK);//  This is TableFan Update Display
  }
  else  {
    tft.fillCircle(15, 194, 5, GREEN);//  This is TableFan Update Display
  }
  
}
////////////////////////////////////////////////////////////////////////////////
void displayInit(){
Serial.println(F("TFT LCD Starting.."));
Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.reset();

  uint16_t identifier = tft.readID();
  if(identifier==0x0101)
      identifier=0x9341;
  tft.begin(identifier);
  tft.fillScreen(BLUE);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setRotation(1);
  tft.println();
  tft.println();
  tft.println();
  tft.setTextColor(YELLOW);  
  tft.setTextSize(2.5);
  tft.setCursor(60, 10);
  bool aa= avilibility();
  if (aa == 1){
  tft.println("Status - CEB Power"); // Add Variable -CEB change to Batt.
  }
  else {
  tft.println("Status - BTT Power"); // Add Variable -CEB change to Batt.  
  }
  /////////////////////Element of GUI////////////
  tft.drawCircle(15, 74, 8, WHITE);
  tft.drawCircle(15, 74, 7, WHITE);
  tft.fillCircle(15, 74, 5, BLACK);//  This is Fridge variable Display
  tft.setCursor(31, 68);  
  tft.setTextSize(2);
  tft.println("Fridge");
  ///////////////////////////////////////////////
  /////////////////////Element of GUI////////////
  tft.drawCircle(15, 104, 8, WHITE);
  tft.drawCircle(15, 104, 7, WHITE);
  tft.fillCircle(15, 104, 5, BLACK);// This is Computer Display
  tft.setCursor(31, 98);  
  tft.setTextSize(2);
  tft.println("Computer");
  ///////////////////////////////////////////////
  /////////////////////Element of GUI////////////
  tft.drawCircle(15, 134, 8, WHITE);
  tft.drawCircle(15, 134, 7, WHITE);
  tft.fillCircle(15, 134, 5, BLACK);// This is TV Display
  tft.setCursor(31, 128);  
  tft.setTextSize(2);
  tft.println("Television");
  ///////////////////////////////////////////////
  /////////////////////Element of GUI////////////
  tft.drawCircle(15, 165, 8, WHITE);
  tft.drawCircle(15, 165, 7, WHITE);
  tft.fillCircle(15, 165, 5, BLACK);// This is PhoneCharger Display
  tft.setCursor(31, 159);  
  tft.setTextSize(2);
  tft.println("PhoneCharger");
  ///////////////////////////////////////////////
  /////////////////////Element of GUI////////////
  tft.drawCircle(15, 194, 8, WHITE);
  tft.drawCircle(15, 194, 7, WHITE);
  tft.fillCircle(15, 194, 5, BLACK);// This is TableFan Display
  tft.setCursor(31, 188);  
  tft.setTextSize(2);
  tft.println("TableFan");
  ///////////////////////////////////////////////
  ///////////////////////////////////////////////
  tft.setTextColor(YELLOW);
  tft.setCursor(205, 70); 
  tft.setTextSize(1);
  tft.println("Batt.Volt:");
  ///////////////////////////////////////////////
  ///////////////////////////////////////////////
  tft.setTextColor(YELLOW);
  tft.setCursor(205, 97); 
  tft.setTextSize(1);
  tft.println("Batt.(%):");
 //////////////////////////////////////
 ///////////////////////////////////////////////
  tft.setTextColor(YELLOW);
  tft.setCursor(205, 124); 
  tft.setTextSize(1);
  tft.println("Char.In:");
  //////////////////////////////////////////////
  sensors();
  //tft.drawRect(265,64, 50,17,WHITE);
  //tft.fillRect(266,66, 47,13,BLACK);
  //tft.setCursor(269, 69); 
  //tft.setTextSize(1);
  //tft.println("00.00"); //// This is variable that need Update Display
  //tft.setCursor(305, 69); 
  //tft.println("v");
  ///////////////////////////////////////////////

  //////////////////////////////////////////////
  //tft.drawRect(265,90, 50,17,WHITE);
  //tft.fillRect(266,92, 47,13,BLACK);
  //tft.setCursor(269, 95); 
  //tft.setTextSize(1);
  //tft.println("00.00"); //// This is variable that need Update Display
  //tft.setCursor(305, 95); 
  //tft.println("%");
/////////////////////////////////////////////////////////////

  //tft.drawRect(265,116, 50,17,WHITE);
  //tft.fillRect(266,118, 47,13,BLACK);
  //tft.setCursor(269, 121); 
  //tft.setTextSize(1);
  //tft.println("0"); //// This is variable that need Update Display
  //tft.setCursor(300, 121); 
  //tft.println("hr");
/////////////////////////////////////////////////////////////  
}
//void Adafruit_TFTLCD::setDisplayBrightness(uint8_t x) {
  // Try with 0x28 (Display Off) to see if display reacts
//  writeRegister8(0x28, 0);
//  writeRegister8(0x51, 0);
//  return;
//}
