#include <LiquidCrystal.h>


#define speed_left 10  
#define speed_right 11          
#define rot_left_1 8  
#define rot_left_2 9  
#define rot_right_1 12  
#define rot_right_2 13  

#define trigPin_front A0
#define echoPin_front A1

#define trigPin_right A2
#define echoPin_right A3

#define trigPin_left A4
#define echoPin_left A5

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int flag=0,sec_chance=0,G_flag=0;

void setup()
{
    Serial.begin(9600);
    
    lcd.begin(16, 2);

    pinMode(speed_left,OUTPUT);
    pinMode(speed_right,OUTPUT);
    
    pinMode(rot_left_1,OUTPUT);
    pinMode(rot_left_2,OUTPUT);
    
    pinMode(rot_right_1,OUTPUT);
    pinMode(rot_right_2,OUTPUT);
    
    pinMode(trigPin_front,OUTPUT);
    pinMode(echoPin_front, INPUT);
    
    pinMode(trigPin_right,OUTPUT);
    pinMode(echoPin_right, INPUT);
    
    pinMode(trigPin_left,OUTPUT);
    pinMode(echoPin_left, INPUT);
    
    
    delay(5000);
    
}

void loop()
{
//    stop_now();
    
    long dis_front,dis_left,dis_right;
  
    dis_front= obstacle_front();
    dis_right= obstacle_right();
    dis_left= obstacle_left();
    
    if(flag)
      stop_now(0);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(dis_front);
    lcd.print("  ");
    lcd.print(dis_left);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print(dis_right);
    
    flag=1;
    
 /*   if(dis_left<12 || dis_left>3000)
        turn_right(30);
    if(dis_right<12 || dis_right>3000)
        turn_left(30);
    
    */
    
        
    if(dis_left>12){      
      lcd.print(" GL");   
      turn_left(30);
   //   go_straight(20);
         
    }
    else if(dis_left<10){
         lcd.print(" GR");
         turn_right(30);
     //    go_straight(20);
    }
    
    
    
    //go_straight();
    if(dis_left>50 && dis_left<3000 && dis_right>12){
        lcd.print("   L");
        stop_now(2000);
        G_flag=1; 
         go_straight(700); 
        turn_left(300);
        G_flag=0;
        go_straight(500);
        stop_now(2000);  
        
    }
    else if(dis_front>20 && dis_front<3000){
         lcd.print("   S");
         go_straight(200);
    }
    else if(dis_right>50 && dis_right<3000 && dis_left>12){
          lcd.print("   R");
          stop_now(2000);
          go_straight(700);
         turn_right(300);
         stop_now(2000);
    }
    else if (dis_left<15 && dis_right<15 && dis_front<21 && dis_left>8){
      
      lcd.print("   U");  
       stop_now(2000);
       u_turn(600); 
       stop_now(2000);
        
    }
    else {
      lcd.print("   B");
      go_back(200);
    }
}

void go_straight(int d)
{
  
        long dis_front,dis_left,dis_right;
        int i;
       
        for(i=0;i<d;i+=100){
          
   //       dis_front= obstacle_front();
          dis_right= obstacle_right();
          dis_left= obstacle_left();
          
          analogWrite(speed_left,145);
          analogWrite(speed_right,150);
    
          analogWrite(rot_left_1,0);
          analogWrite(rot_left_2,255);
    
          analogWrite(rot_right_1,0);
          analogWrite(rot_right_2,255);
    
          my_delay(100);
          
          if(!G_flag){
    
            if(dis_left>12){      
              lcd.print(" GL");   
              turn_left(10);
         
            }
            else if(dis_left<10){
             lcd.print(" GR");
             turn_right(10);;
            }
          }else{
            if(dis_right>12){      
              lcd.print(" GL");   
              turn_right(10);
         
            }
            else if(dis_right<10){
             lcd.print(" GR");
             turn_left(10);
            }
            
          }    
        }
}

void go_back(int d)
{
        analogWrite(speed_left,145);
        analogWrite(speed_right,150);
    
        analogWrite(rot_left_1,255);
        analogWrite(rot_left_2,0);
    
        analogWrite(rot_right_1,255);
        analogWrite(rot_right_2,0);
    
        my_delay(d);    
    
}


void turn_right(int d)
{

    analogWrite(speed_left,255);
    analogWrite(speed_right,255);
    
    analogWrite(rot_left_1,0);
    analogWrite(rot_left_2,255);
    
    analogWrite(rot_right_1,255);
    analogWrite(rot_right_2,0);
    
    my_delay(d);
}

void turn_left(int d)
{

    analogWrite(speed_left,255);
    analogWrite(speed_right,255);
    
    analogWrite(rot_left_1,255);
    analogWrite(rot_left_2,0);
    
    analogWrite(rot_right_1,0);
    analogWrite(rot_right_2,255);
    
    my_delay(d);
}

void stop_now(int d)
{

    analogWrite(speed_left,0);
    analogWrite(speed_right,0);
    
    analogWrite(rot_left_1,0);
    analogWrite(rot_left_2,0);
    
    analogWrite(rot_right_1,0);
    analogWrite(rot_right_2,0);
    
    my_delay(d);
}

void u_turn(int d)
{
    long frnt=0,lft=10,rht=20;
    
  //  while(frnt<50){
    
      analogWrite(speed_left,220);
    
      analogWrite(speed_right,220);
    
      analogWrite(rot_left_1,255);
      analogWrite(rot_left_2,0);
    
      analogWrite(rot_right_1,0);
      analogWrite(rot_right_2,255);
      
     my_delay(d);
      
    //  frnt= obstacle_front();
   //   lft= obstacle_left();
    //  rht= obstacle_right();
      
  //  }
    //my_delay(d);

    
}


long obstacle_front(){
    
    long duration,distance;
    
    digitalWrite(trigPin_front,LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin_front,HIGH);
    delayMicroseconds(10);
  
    digitalWrite(trigPin_front,LOW);
  
    duration= pulseIn(echoPin_front,HIGH);
    distance= (duration/2)/29.1;
    
    Serial.print("front ");
    Serial.print(distance);
    Serial.print("\n");
    
    return distance;
}

long obstacle_right(){
    
    long duration,distance;
    
    digitalWrite(trigPin_right,LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin_right,HIGH);
    delayMicroseconds(10);
  
    digitalWrite(trigPin_right,LOW);
  
    duration= pulseIn(echoPin_right,HIGH);
    distance= (duration/2)/29.1;
    
    Serial.print("right ");
    Serial.print(distance);
    Serial.print("\n");
    
    return distance;
}

long obstacle_left(){
    
    long duration,distance;
    
    digitalWrite(trigPin_left,LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigPin_left,HIGH);
    delayMicroseconds(10);
  
    digitalWrite(trigPin_left,LOW);
  
    duration= pulseIn(echoPin_left,HIGH);
    distance= (duration/2)/29.1;
    
    Serial.print("left ");
    Serial.print(distance);
    Serial.print("\n");
    
    
    return distance;
}


void my_delay(int d){
    
    /*long dis_front,dis_left,dis_right;
    
    int i;
    
    for(i=0;i<d;i+=100){
    
    dis_front= obstacle_front();
    dis_right= obstacle_right();
    dis_left= obstacle_left();
    
    if(dis_left<9)
        turn_right(0);
    if(dis_right<9)
        turn_left(0);
    }
    */
    delay(d);
}

void G_right(int d)
{

    analogWrite(speed_left,0);
    analogWrite(speed_right,255);
    
    analogWrite(rot_left_1,0);
    analogWrite(rot_left_2,0);
    
    analogWrite(rot_right_1,255);
    analogWrite(rot_right_2,0);
    
    my_delay(d);
}

void G_left(int d)
{

    analogWrite(speed_left,255);
    analogWrite(speed_right,0);
    
    analogWrite(rot_left_1,255);
    analogWrite(rot_left_2,0);
    
    analogWrite(rot_right_1,0);
    analogWrite(rot_right_2,0);
    
    my_delay(d);
}


