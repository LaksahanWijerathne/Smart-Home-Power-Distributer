void BTTF(){    
    digitalWrite(ChangeOver, LOW); // ON the ChangeOver
    /// Add a Delay here
    digitalWrite(Common, LOW); // Turning on the Common switch
    /// Add a Delay
    if (CEB==0){
      CEB=1;
      digitalWrite(45,LOW);// turn on display
      tft.setTextColor(YELLOW);  
      tft.setTextSize(2);
      tft.fillRect(60,10, 200,13,BLUE);
      tft.setCursor(60, 10);
      tft.println("Status - BTT Power"); // Add Variable -CEB change to Batt.
      digitalWrite(Fridge, BPFridge);
      digitalWrite(Computer, BPComputer);
      digitalWrite(Tv, BPTv);
      digitalWrite(PhoneCharger, BPPhoneCharger);
      digitalWrite(TableFan, BPTableFan);
      displayUpdate();
    }
    // Calculate current status for power use and update Display
    //////////////////////////////////////////////////////////////
    ////////////////////Key Scanner with power Calculator Here////
    //scan eken key number eka aragnnawa

    //on karanawa
float CurrentVolt = voltage();

if  ( CurrentVolt > 12.00)  {  
  tft.fillRect(180,160, 135,75,BLUE); /// error Massage clean

  key = keypad.getKey();// do the key pad scanner 
 if (key=='*'){
  key=' ';
    count1=0;
    count=0;
    digitalWrite(45,LOW);// turn on display
    count1=0;
    count=0;
 }
 else if (key > 48){  
  if (key == '1'){
    key=' ';
    digitalWrite(45,LOW);//display on
    count1=0;// timer reset
    //delay(20);
    //Serial.println(key);
    //Serial.println("pressed");
    if (digitalRead(Fridge)==1) {
      digitalWrite(Fridge, LOW);//toggel switch // HIGH=OFF, LOW=ON
      CEBFridge = 0;// HIGH=OFF, LOW=ON
      tft.fillCircle(15, 74, 5, GREEN);//  This is Fridge Display
    }
    else {
      digitalWrite(Fridge, HIGH);//toggel switch
      CEBFridge = 1;// HIGH=OFF, LOW=ON
      tft.fillCircle(15, 74, 5, BLACK);//  This is Fridge Display
    }
  }//
  if (key == '2'){
    key=' ';
    digitalWrite(45,LOW);//display on
    count1=0;// timer reset
    //delay(20);
    //Serial.println(key);
    //Serial.println("pressed");
    if (digitalRead(Computer)==1) {
      digitalWrite(Computer, LOW);//toggel switch
      CEBComputer=0;
      tft.fillCircle(15, 104, 5, GREEN);// This is Computer Display
    }
    else {
      digitalWrite(Computer, HIGH);//toggel switch
      CEBComputer=1;
      tft.fillCircle(15, 104, 5, BLACK);// This is Computer Display
    }
  }//
  if (key == '3'){
    key=' ';
    digitalWrite(45,LOW);//display on
    count1=0;// timer reset
    //delay(20);
    //Serial.println(key);
    //Serial.println("pressed");
    if (digitalRead(Tv)==1) {
      digitalWrite(Tv, LOW);//toggel switch
      CEBTv=0;
      tft.fillCircle(15, 134, 5, GREEN);// This is TV Display
    }
    else {
      digitalWrite(Tv, HIGH);//toggel switch
      CEBTv=1;
      tft.fillCircle(15, 134, 5, BLACK);// This is TV Display
    }
  }//
  if (key == '4'){
    key=' ';
    digitalWrite(45,LOW);//display on
    count1=0;// timer reset
    //delay(20);
    //Serial.println(key);
    //Serial.println("pressed");
    if (digitalRead(PhoneCharger)==1) {
      digitalWrite(PhoneCharger, LOW);//toggel switch
      CEBPhoneCharger=0;
      tft.fillCircle(15, 165, 5, GREEN);// This is PhoneCharger Display
    }
    else {
      digitalWrite(PhoneCharger, HIGH);//toggel switch
      CEBPhoneCharger=1;
      tft.fillCircle(15, 165, 5, BLACK);// This is PhoneCharger Display
    }
  }//
  if (key == '5'){
    key=' ';
    digitalWrite(45,LOW);//display on
    count1=0;// timer reset
    //delay(20);
    //Serial.println(key);
    //Serial.println("pressed");
    if (digitalRead(TableFan)==1) {
      digitalWrite(TableFan, LOW);//toggel switch
      CEBTableFan=0;
      tft.fillCircle(15, 194, 5, GREEN);// This is TableFan Display
    }
    
    else {
      digitalWrite(TableFan, HIGH);//toggel switch
      CEBTableFan=1;
      tft.fillCircle(15, 194, 5, BLACK);// This is TableFan Display
         }
    }//key '5'
   }// if key > 48 
  }// current volt bigger that 12.00
  else if(CurrentVolt < 12.00){
    digitalWrite(Fridge, HIGH);
    digitalWrite(Computer, HIGH);
    digitalWrite(Tv, HIGH);
    digitalWrite(PhoneCharger, HIGH);
    digitalWrite(TableFan, HIGH);
    tft.fillRect(180,160, 135,75,BLACK); /// error Massage
    tft.setCursor(185, 165);
    tft.setTextColor(RED); 
    tft.setTextSize(2);
    tft.println("LOW Batery");
    tft.setCursor(185, 185);
    tft.println("POWER");
    delay(1000);
    tft.fillRect(180,160, 135,75,BLACK); /// error Massage
  }//CurrentVolt < 12.00
}// function ends
