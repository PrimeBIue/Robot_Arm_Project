
//Libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
//Pins
#define OLED_RESET 4


//Define Visuals
#define FONT_SIZE 2
#define SCREEN_WIDTH 127  //real size minus 1, because coordinate system starts with 0
#define SCREEN_HEIGHT 63  //real size minus 1, because coordinate system starts with 0

Adafruit_SSD1306 display(OLED_RESET);

//Variables
int sel=0;
int sel2=0;
Servo rot;
Servo arm1;
Servo grab;
int rotmove;
int armmove1;
int armclose=90;
int armopen=180;
int pot1=A0;
int pot2=A1;
int hold=0;

void setup()   {  

   rot.attach(13);
   arm1.attach(12);
   grab.attach(11);
   
   pinMode(5,INPUT_PULLUP);
   pinMode(6,INPUT_PULLUP);
   pinMode(7,INPUT_PULLUP);


                
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);  // initialize with the I2C addr 0x3D (for the 128x64)
  display.clearDisplay();   // clears the screen and buffer
  display.display();   
  display.setTextWrap(false);

  splash();

  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE);
  display.clearDisplay();
  
}

//Splash Screen
void splash(){

  
  
  display.clearDisplay();

  display.setTextColor(WHITE);
  centerPrint("R-BOT",0,3);
  centerPrint("V4.0-beta",24,1);

  display.display();

  delay(3000);

  display.clearDisplay();

  display. setTextColor(WHITE);
  centerPrint("Created by:",0,1);
  centerPrint("Jorge Cabiedes",8,1);
  centerPrint("Miguel Frias",16,1);
  centerPrint("Alejandro Pascal",24,1);
  centerPrint("Miguel Medina",32,1);
  centerPrint("Santiago Guzman",40,1);
  
  display.display();

  delay(3000);

  menu();
}

void menu(){
  do{
    display.clearDisplay();
    if(sel2>2){
      sel2=2;
    }
    else if (sel2<0){
      sel2=0;
    }
    if(digitalRead(6)==LOW){
      sel2++;
      delay(200);
    }
    else if(digitalRead(5)==LOW){
      sel2--;  
      delay(200);
     }
    if(sel2==0){
      display.setTextColor(WHITE);
      centerPrint("Auto-1",25,1);
      centerPrint("Auto-2",45,1);

      display.fillRect(0,4,SCREEN_WIDTH,10,WHITE);
      display.setTextColor(BLACK);
      centerPrint("Manual",5,1);
      display.display();
}
else if(sel2==1){
display.setTextColor(WHITE);
centerPrint("Auto-2",45,1);
centerPrint("Manual",5,1);

display.fillRect(0,24,SCREEN_WIDTH,10,WHITE);
display.setTextColor(BLACK);
centerPrint("Auto-1",25,1);
display.display();
}
else if(sel2==2){
display.setTextColor(WHITE);
centerPrint("Auto-1",25,1);
centerPrint("Manual",5,1);

display.fillRect(0,44,SCREEN_WIDTH,10,WHITE);
display.setTextColor(BLACK);
centerPrint("Auto-2",45,1);
display.display();
}
if(digitalRead(7)==LOW&&sel2==0&&sel==0){
  sel=1;
  manual();
}
if(digitalRead(7)==LOW&&sel2==1&&sel==0){
  sel=2;
  auto1();
}
if(digitalRead(7)==LOW&&sel2==2&&sel==0){
  sel=3;
  auto2();
}

    
  }while(sel==0);
}

void loop() {
  if(sel==1){
  manual();
}
else if(sel==2){
  auto1();     
}
else if(sel==3){
  auto2();     
}
}

void manual(){
  delay(200);
  do{
    
    display.clearDisplay();
    display.fillRect(0,2,SCREEN_WIDTH,14,WHITE);
    display.setTextColor(BLACK);
    centerPrint("MANUAL",2,2);
    display.setTextColor(WHITE);
    centerPrint("1. ****",19,1);
    centerPrint("2. ****",27,1);
    centerPrint("3. Open/Close",35,1);
    centerPrint("4. Back to menu",43,1);

    display.display();


    
  armmove1 = analogRead(pot1);           
  armmove1 = map(armmove1, 0, 1023, 15, 179);
  arm1.write(armmove1);
  rotmove = analogRead(pot2);
  rotmove = map(rotmove, 0, 1023, 15, 179);
  rot.write(rotmove);

  if(digitalRead(7)==LOW&&hold==0){
    grab.write(armclose);
    hold++;
    delay(250);  
  }
  else if(digitalRead(7)==LOW&&hold==1){
    grab.write(armopen);
    hold--;  
    delay(250);
  }
  Serial.print(hold);
  delay(5);             
  }while(sel==1);
}

void auto1(){
  display.clearDisplay();
    display.fillRect(0,2,SCREEN_WIDTH,14,WHITE);
    display.setTextColor(BLACK);
    centerPrint("Auto-1",2,2);
    display.setTextColor(WHITE);
    centerPrint("1. ****",19,1);
    centerPrint("2. ****",27,1);
    centerPrint("3. ****",35,1);
    centerPrint("4. Back to menu",43,1);

    display.display();
  exit(0);
}

void auto2(){
  display.clearDisplay();
    display.fillRect(0,2,SCREEN_WIDTH,14,WHITE);
    display.setTextColor(BLACK);
    centerPrint("Auto-2",2,2);
    display.setTextColor(WHITE);
    centerPrint("1. ****",19,1);
    centerPrint("2. ****",27,1);
    centerPrint("3. ****",35,1);
    centerPrint("4. Back to menu",43,1);

    display.display();
  exit(0);
}

void centerPrint(char *text, int y, int size)
{
  display.setTextSize(size);
  display.setCursor(SCREEN_WIDTH/2 - ((strlen(text))*6*size)/2,y);
  display.print(text);
}
