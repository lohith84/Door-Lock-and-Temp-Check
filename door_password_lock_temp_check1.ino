#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

//initializing variables
Servo servo;

const byte ROWS=4; //four rows
const byte COLS=4; //four columns
char keys[ROWS][COLS]= 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS]={1,2,3,4}; 
byte colPins[COLS]={5,6,7,8}; 

Keypad k=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

LiquidCrystal lcd(10,A1,A2,A3,A4,A5);

char correctPassword[]="1369";
int number=sizeof(correctPassword)-1;
char pass[sizeof(correctPassword)-1];
int i=0,j=0;
int cnt=0;
int dg;
double Rdg;
char key;
bool d=1;

void setup() 
{
  servo.attach(9);
  servo.write(0);
  lcd.begin(16,2);
  lcd.print("     WELCOME");
  delay(2000);
  lcd.clear();
  lcd.print("Enter the Password");
  scroll();
  servo.write(0);
  lcd.setCursor(0,1);
}

void loop()
{
  if(d==0)
  {
    key=k.getKey();
    if(key=='C')
    {
      servo.write(0);
      i=0;
      cnt=0;
      lcd.clear();
      lcd.print("Enter the Password");
      scroll();
      lcd.setCursor(0,1);
      d=1;
    }
  }
  else
  {
    key=k.getKey();
    if(key >= '0' && key <='9')
    {
      lcd.print('*');
      pass[i]=key;
      i++;      
    }
    else if(key=='D')
    {
      if(i==number)
      {
        for(j=0;j<number;j++)
        {
          if(pass[j]==correctPassword[j]) cnt++;   
        }
        if(cnt==number) correct(); 
        else wrong();    
      }
      else wrong();
    }
  }
}

void scroll()
{
  int ps;
  delay(800);
  for(ps=0;ps<13;ps++) 
  {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  for(ps=0;ps<25;ps++)
  {
    lcd.scrollDisplayRight();
    delay(150);
  }
  for(ps=0;ps<12;ps++)
  {
    lcd.scrollDisplayLeft();
    delay(150);
  }
  delay(1000);
}

void wrong()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Wrong Password");
  lcd.setCursor(0,1);
  lcd.print("    Try Again   ");
  delay(2000);
  i=0;
  cnt=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter the Password");     
  scroll();
  lcd.setCursor(0,1);
}

void correct()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Correct Password    ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  delay(1000);
  lcd.begin(16,2);
  dg=0;
  Rdg=0.0;
  lcd.print("Temperature Check");
  scroll();
  delay(5000);
  dg=analogRead(0);
  Rdg=(double)dg/1024;
  Rdg=Rdg*5;
  Rdg=Rdg-0.5;
  Rdg=Rdg*100;
  lcd.setCursor(0,1);
  Rdg=(9.0/5)*(Rdg)+32;
  String output=String(Rdg)+String((char)178)+"F";
  lcd.begin(16,2);
  lcd.print(output);
  delay(2000);
  lcd.clear();
  if(Rdg<99.5 && Rdg>97.0)
  {
    lcd.begin(16,2);
    lcd.print("You are allowed");
    delay(2000);
    lcd.clear();
    servo.write(90);
    lcd.begin(16,2);
    lcd.print("Press C To close");
    i=0;
    cnt=0;
    d=0;  
  }
  else
  {
    lcd.begin(16,2);
    lcd.print("You are not allowed");
    scroll();
    delay(2000);
    lcd.clear();
    lcd.begin(16,2);
    lcd.print("Press C To Retry");
    i=0;
    cnt=0;
    d=0;  
  }         
}