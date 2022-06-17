//#include <PWFusion_TCA9548A.h>
#include <Wire.h>
#include <Keypad.h>
#include <SoftPWM.h>
//#include <ezButton.h>
//#include <EEPROM.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
////////////////////////////////////////////////////////////
/////////////////Display Settings///////////////////////////
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
///
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


////////////////////////////////////////////////////////////
////////////////////Address of EEPROM///////////////////////

//int EEFridge = 0; //Address of EEPROM
//int EEComputer = 1;
//int EETv = 2;
//int EEPhoneCharger = 3;
//int EETableFan = 4;
//int EECommon = 5;
//int EEChangeOver = 6;


////////////////////////////////////////////////////////////
/////////Current senser Globel Variables////////////////////
unsigned int x=0;
float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;
float current();
//TCA9548A i2cMux;
const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};
////////////////////////////////////////////////////////////////
//////////////////////days//////////////////////////////////////
// Initializes all values: 
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

////////////////////////////////////////////////////////////////
/////////////////////////Key Pad Settings///////////////////////
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 3; //three columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {14, 15, 16, 17}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {18, 19, 20}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

bool buttonState = 0;
bool lastButtonState = 0;
////////////////////////////////////////////////////////////////
//////////////////////Reallays////////////////////////////////

int Common = 35;
int ChangeOver = 36;//red wire
int Fridge = 30; //blue wire
int Computer = 31;
int Tv = 33;
int PhoneCharger = 32;
int TableFan = 34;
//////////////////////////////////////////////
long count =0;
long count1 =0;
long count2 =0;
////////////////////////////////////////////////////////////////
////////////////Output Status Identifiers///////////////////////
int  CEB = 1;
bool CEBFridge = 1; // CEB power Fridge Status 1=OFF 0=ON
bool CEBComputer = 1;
bool CEBTv = 1;
bool CEBPhoneCharger = 1;
bool CEBTableFan = 1;
///
//bool ACommon = 1;
//bool AChangeOver = 1;
///
bool BPFridge = 1; // Battery Power Fridge Status
bool BPComputer = 1;
bool BPTv = 1;
bool BPPhoneCharger = 1;
bool BPTableFan = 1;

char key='0';
//////////////////////statusPin////////////////////////////////
int Availability = 53;  
///////////////////////////////////////////////////////////////
////////////////////Ad Sensors/////////////////////////////////
const int voltageSensor = A9;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;
////////////////////////////////////////////////////////////
//////////////////Functions/////////////////////////////////
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);///Display
void displayInit();
void displayUpdate();
//void setDisplayBrightness(uint8_t x);/// brighness controller
float current();
float voltage();
bool avilibility();
void readTime();
void printTime();
//need add memory card fuction HERE
byte decToBcd(byte val);
byte bcdToDec(byte val);
void sensors();
void BTTF(char key);
void CEBF(char key);
////////////////////////////////////////////////////////////
void setup()
{
pinMode(45,OUTPUT);//PWM pin For Display  
delay(3000);
digitalWrite(45,LOW);
//SoftPWMBegin();
//SoftPWMSet(45, 0);
//SoftPWMSetFadeTime(13, 20, 20);// for display
//delay(3000);
//SoftPWMSet(13, 255);/// set Intencity
//delay(3000);
//SoftPWMSet(13, 125);/// set Intencity
//delay(3000);
//SoftPWMSet(13, 75);/// set Intencity
//delay(3000);
//SoftPWMSet(13, 25);/// set Intencity
//delay(3000);
//SoftPWMSet(13, 0);/// set Intencity

float volt = voltage();
if ( volt < 10.8){
  error();
  while (volt<10.8){
    volt = voltage();
    tft.fillRect(50,175, 100,100,BLUE);
    tft.setCursor(60, 180);
    tft.setTextSize(1);
    tft.println(volt);
  }
  tft.fillScreen(BLUE);///Clean Screen
}

Serial.begin(9600);

//////////////////////////////
/////Error List///////////////
//1. No Battery Connected
//2. 
/////////////////////////////////////////////////////////////
//EEPROM.write(EEFridge, '1');
//EEPROM.write(EEComputer, '1');
//EEPROM.write(EETv, '1');
//EEPROM.write(EEPhoneCharger, '1');
//EEPROM.write(EETableFan, '1');
//EEPROM.write(EECommon, '1');
//EEPROM.write(EEChangeOver, '1');
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////  
pinMode(Availability,INPUT);
pinMode(LED_BUILTIN, OUTPUT);
///////////////////////////////////////////////
pinMode(Fridge,OUTPUT);// Fridge
pinMode(Computer,OUTPUT);// Computer
pinMode(Tv,OUTPUT);// Television
pinMode(PhoneCharger,OUTPUT);// Phone Charger
pinMode(TableFan,OUTPUT);// Table Fan
///////////////////////////////////////////////
pinMode(Common,OUTPUT);
pinMode(ChangeOver,OUTPUT);
///////////////////////////////////////////////

///////Output Safty State//////////////////////
digitalWrite(Fridge, HIGH);// HIGH=OFF, LOW=ON
digitalWrite(Computer, HIGH);
digitalWrite(Tv, HIGH);
digitalWrite(PhoneCharger, HIGH);
digitalWrite(TableFan, HIGH);
digitalWrite(Common, HIGH); 
digitalWrite(ChangeOver, HIGH);
///////////////////////////////////////////////
Serial.println("System Booting....!");
delay(500);
Serial.println("Initiating Display.....");
//// Display Init Here
delay(500);
Serial.println("Initiating Communication.....");
//Wire.begin();
delay(500);
/////// channel select
//i2cMux.begin();
//i2cMux.setChannel(CHAN0); 
//Serial.println("Channel 0 selected");

//Serial.print("CEB AC Availability check:");
//bool a = digitalRead(Availability);
//digitalWrite(LED_BUILTIN,a);
//Serial.print(a);
//Serial.print(" Measure > 25V  ");
//delay(2000);
//tft.setDisplayBrightness(0);/// set Brightness
displayInit();
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOOOP/////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void loop()
{
 key = keypad.getKey();// do the key pad scanner
 if (key=='*'){
  key=' ';
    count1=0;
    count=0;
    digitalWrite(45,LOW);// turn on display
    count1=0;
    count=0;
 }
  
 count = count + 1;
 if (count == 40){
  count =0;
  sensors();
  count1 = count1 + 1;
  if (count1 == 10){
    count1=0;
    digitalWrite(45,HIGH);// turn of display
  }
 }

 
////////////////////////////////////////////////////////////////////
displayUpdate();// need check tested okay
////////////////////////////////////////////////////////////////////
///Program Codes here///////////////////////////////////////////////
bool aa= avilibility();
//key = keypad.getKey();// do the key pad scanner
  if (aa == 0){ // CEB Power availble
    BTTF();// function
  }  
  else if(aa == 1) { // no CEB Power
    
    CEBF();// function
  } 
    
////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
bool avilibility(){
  bool a = digitalRead(Availability);

  digitalWrite(LED_BUILTIN,a);
  //Serial.println("CEB AC Availability check:");
  //Serial.println(a);
  return a;
} 
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
float voltage(){
  //value = analogRead(voltageSensor);
  //vOUT = (value * 5.0) / 1024.0;
  //////////////////////////////////////
  float Sample=0.0;
  for (int x = 0; x < 50; x++){
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0; 
  Sample = Sample +  vOUT;
  //delay (3);
  }
  vOUT = Sample/50;
  //////////////////////////////////////
  //vIN = vOUT / (R2/(R1+R2));
  vIN = (vOUT * 4.7826); /////5.02 
  Serial.print("  Input Volt = ");
  Serial.println(vIN);
  return vIN;
}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
float current(){
  for (int x = 0; x < 150; x++){ //Get 150 samples
  AcsValue = analogRead(A10);     //Read current sensor values   
  Samples = Samples + AcsValue;  //Add samples together
  delay (3); // let ADC settle before next sample 3ms
  }
  AvgAcs=Samples/150.0;//Taking Average of Samples

//((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
//2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
//out to be 2.5 which is out offset. If your arduino is working on different voltage than 
//you must change the offset according to the input voltage)
//0.185v(185mV) is rise in output voltage when 1A current flows at input
  AcsValueF = (2.6118 - (AvgAcs * (5.0 / 1024.0)) )/0.185;
  Serial.print( AcsValueF);//Print the read current on Serial monitor
  return AcsValueF;
}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void display(){
  
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void printTime() {
  char buffer[3];
  const char* AMPM = 0;
  readTime();
  Serial.print(days[weekday-1]);
  Serial.print(" ");
  Serial.print(months[month-1]);
  Serial.print(" ");
  Serial.print(monthday);
  Serial.print(", 20");
  Serial.print(year);
  Serial.print(" ");
  if (hour > 12) {
    hour -= 12;
    AMPM = " PM";
  }
  else AMPM = " AM";
  Serial.print(hour);
  Serial.print(":");
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  Serial.println(AMPM);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
