#include<SoftwareSerial.h>
#include<Nextion.h>

SoftwareSerial nextion(7,6);

Nextion NextionLCD (nextion, 115200);
unsigned long drug=0, prev=0;
int on=0, progress=0;
unsigned long interval, curr, rumusnyaYGY;

void dosis(){
  nextion.print("t0.txt=\""+String(drug)+"\"");
  nextion.write(0xff);
  nextion.write(0xff);
  nextion.write(0xff);
}

void bar() {
rumusnyaYGY = map(drug,0,6,0,1080000);
interval = rumusnyaYGY/100;
}

void durasi(){ 
  nextion.print("j0.val="); 
  nextion.print(progress);  
  nextion.write(0xff);
  nextion.write(0xff);
  nextion.write(0xff);
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
NextionLCD.init();
pinMode(9,OUTPUT);

}

void loop() {
String message = NextionLCD.listen();
if(message != ""){
  Serial.println(message);
}


if ((message == "0") && (drug>0))
{ 
    drug--;
    dosis();
}
if ((message == "1")&&(drug<7 ))
{
  drug++;
  dosis();
}

if (message == "2" )
{ on=2;
  
  digitalWrite(9,HIGH);
}

if (message == "3" )
{ on=3;
  digitalWrite(9,LOW);
  progress=0;
  durasi();
}

if ((on==2) & (progress<100)) {
    bar();
    curr=millis();
    
  if ((curr - prev)> interval){
  prev=curr;
  progress++;
  durasi();  
  }
}

if (progress==100)
{
  digitalWrite(9,LOW);
}
}
