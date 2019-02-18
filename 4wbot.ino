                  //1........2\\
 //              ||           ||
 //              ||           ||
 //              \\4.........3//

//Arduino code for 4 wheeled bot, complete working
//--------------------------------------------------------------------------------------------------//

#include "Wire.h"

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

const byte pwm1 = 11;
const byte pwm2 = 10;
const byte pwm3 = 1 ;
const byte pwm4 = 2;

const byte dir1 = 13;
const byte dir2 = 12;
const byte dir3 = 1;
const byte dir4 = 2;


float kp=0.5;
float ki=0.2;
float kd=0.1;

float integrate=0;
float derivative=0;
float error=0;
float prev_error=0;

int pwm=0;
static float val;




//---------------------------------------------------SETUP-----------------------------------------//
void setup(){
    Serial.begin(9600);
    Wire.begin();
   

    Wire.beginTransmission(address);                      //open communication with HMC5883
    Wire.write(0x02);                                     //select mode register
    Wire.write(0x00);                                     //continuous measurement mode
    Wire.endTransmission();
    // Serial.println("Initializing I2C devices...");
    pinMode(dir1,INPUT);
    pinMode(dir2,INPUT);
    pinMode(dir3,INPUT);
    pinMode(dir4,INPUT);
 
    pinMode(pwm1,INPUT);
    pinMode(pwm2,INPUT);
    pinMode(pwm3,INPUT);
    pinMode(pwm4,INPUT);

    
   int x1,y1,z1; //triple axis data

  //......................Tell the HMC5883L where to begin reading data....................................//
      Wire.beginTransmission(address);
      Wire.write(0x03);                                 //select register 3, X MSB register
      Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x1 = Wire.read()<<8;     //X msb
    x1 |= Wire.read();       //X lsb
    y1 = Wire.read()<<8;     //Y msb
    y1 |= Wire.read();       //Y lsb
  }
  float val = atan2(y1, x1);          // val is set point
  
     val*=180/M_PI;
    Serial.println("val");
    Serial.println(val);


}


 
//--------------------------------------------------LOOP-------------------------------------------//

//-------------------------------Rotation-----------------------------------------------------//
void loop(){



   
    int x,y,z; //triple axis data

  //......................Tell the HMC5883L where to begin reading data....................................//
      Wire.beginTransmission(address);
      Wire.write(0x03);                                 //select register 3, X MSB register
      Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8;     //X msb
    x |= Wire.read();       //X lsb
    y = Wire.read()<<8;     //Y msb
    y |= Wire.read();       //Y lsb
  }
  float temp = atan2(y, x);          // val is set point
  //Serial.println(temp);
     temp*=180/M_PI;
     Serial.println("temp");
    Serial.println(temp);

    while(temp != val) {

        error=temp-val;  
        integrate+=error;
              if(error==0){
                integrate=0;
              }
              
              if(abs(error)>10){
                integrate=0;
              }
        derivative=error-prev_error;
        prev_error=error;
        pwm=(int)((kp*error)+(ki*integrate)+(kd*derivative));
              
              if(temp < val){
                
                if (temp < 0){
                    temp = 360 + temp;
                }
                motor(1,pwm);
              }
              
              if(temp > val){

                if (temp > 360){
                    temp = temp - 360;
                }
                motor(0,abs(pwm));
              }

    } 

    stop1();
   
          
        

}


void motor(int dir,int temp_pwm){
      if(dir==1){
          Serial.println("Clockwise");
          analogWrite(pwm1,temp_pwm );
          analogWrite(pwm2,temp_pwm - 30);
          analogWrite(pwm3,temp_pwm );
          analogWrite(pwm4,temp_pwm - 30);
          digitalWrite(dir1,HIGH);
          digitalWrite(dir2,HIGH);
          digitalWrite(dir3,HIGH);
          digitalWrite(dir4,HIGH);
         
      }
      
      if(dir==0){
          Serial.println("Counter Clockwise");
          analogWrite(pwm1,temp_pwm - 30);
          analogWrite(pwm2,temp_pwm);
          analogWrite(pwm3,temp_pwm - 30);
          analogWrite(pwm4,temp_pwm);
          digitalWrite(dir1,LOW);
          digitalWrite(dir2,LOW);
          digitalWrite(dir3,LOW);
          digitalWrite(dir4,LOW);

      }
    
}

/*

//----------------------Forward - Backward-----------------------------------------------//

void loop(){



    mag.getHeading(&mx, &my, &mz);
    float varheading = atan2(my, mx);   //continuous heading angle
    
    int temp=varheading * 180/M_PI;     
    error=temp-val;  
    integrate=integrate+error;
          if(error==0){
            integrate=0;
          }
          
          if(abs(error)>10){
            integrate=0;
          }
    derivative=error-prev_error;
    prev_error=error;
    pwm=(int)((kp*error)+(ki*integrate)+(kd*derivative));
          
          if(pwm>0){
            motor(1,pwm);
          }
          
          if(pwm<0){
            motor(0,abs(pwm));
          }
          
          if(pwm==0){
            stop1();
          }

}


void motor(int dir,int temp_pwm){
      if(dir==1){
          Serial.println('Forward');
          analogWrite(pwm1,temp_pwm);
          analogWrite(pwm2,temp_pwm);
          analogWrite(pwm3,temp_pwm);
          analogWrite(pwm4,temp_pwm);
          digitalWrite(dir1,HIGH);
          digitalWrite(dir2,HIGH);
          digitalWrite(dir3,HIGH);
          digitalWrite(dir4,HIGH);
         
      }
      
      if(dir==0){
          Serial.println('Backward');
          analogWrite(pwm1,temp_pwm);
          analogWrite(pwm2,temp_pwm);
          analogWrite(pwm3,temp_pwm);
          analogWrite(pwm4,temp_pwm);
          digitalWrite(dir1,LOW);
          digitalWrite(dir2,LOW);
          digitalWrite(dir3,LOW);
          digitalWrite(dir4,LOW);

      }
    
}
*/

void stop1(){

      analogWrite(pwm1,0);
      analogWrite(pwm2,0);
      analogWrite(pwm3,0);
      analogWrite(pwm4,0);
}
