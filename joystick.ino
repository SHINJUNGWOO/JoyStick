#include <SoftwareSerial.h>
SoftwareSerial BTSerial(11,12);
const int L_x= A0;
const int L_y= A1;
const int R_x= A2;
const int R_y= A3;
const int L_switch=2;
const int R_switch=3;
int X_val=0;
int Y_val=1;

char data;

int mode =0;
// 0-> R_switch go ,L_switch turn
// 1-> L_switch go ,R_swtich turn 


unsigned long previous_time=0;
unsigned long Y_interval =3000;
unsigned long X_interval =1100;


void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(L_switch,INPUT_PULLUP);
  pinMode(R_switch,INPUT_PULLUP);
  

}

void loop() {
  int R_switch_val=digitalRead(R_switch);
  int L_switch_val=digitalRead(L_switch); 
  if(mode==0)
  {
    X_val=analogRead(R_x);;
    Y_val=analogRead(L_y);
    if(digitalRead(R_switch)==0)
    {
      mode=1;
    }
  }
  else if(mode==1)
  {
    X_val=1024-analogRead(L_x);
    Y_val=1024-analogRead(R_y);
    if(digitalRead(L_switch)==0)
    {
      mode=0;
    }
  }
  else
  {
    return 0;
  }


  if(X_val<384)
  {
        if((millis()-previous_time)>=X_interval || previous_time==millis())
        {
          data='L';
          previous_time=millis();
        }
        else
        {
          data=NULL;
        }
  }
  else if(X_val>640)
  {
        if((millis()-previous_time)>=X_interval || previous_time==millis())
        {
          data='R';
          previous_time=millis();
        }
        else
        {
          data=NULL;
        }
  }
  else
  {
    if(Y_val>640)
    {
        if((millis()-previous_time)>=Y_interval || previous_time==millis())
        {
          data='+';
          previous_time=millis();
        }
        else
        {
          data=NULL;
        }

    }
    else if(Y_val<384)
    {
        if((millis()-previous_time)>=Y_interval || previous_time==millis())
        {
          data='-';
          previous_time=millis();
        }
        else
        {
          data=NULL;
        }
    }
    else
    {
      data=NULL;
      previous_time=millis();
    }
  }
  if(data!=NULL)
  {
  Serial.println(data);
   BTSerial.write(data);
  
  }
  if (BTSerial.available())
    Serial.write(BTSerial.read());
  if (Serial.available())
    BTSerial.write(Serial.read());
  //LEFT,RIGHT,+,- check code
  
}
