int motorPin1 = 8;	// Blue   - 28BYJ48 pin 1
int motorPin2 = 9;	// Pink   - 28BYJ48 pin 2
int motorPin3 = 10;	// Yellow - 28BYJ48 pin 3
int motorPin4 = 11;	// Orange - 28BYJ48 pin 4
int motorSpeed = 3;     //variable to set stepper speed
int obr = 512; // szacowane na obrót 512
int i;
//int zmm = 0;
int pozAkt = 5;
int pozDoc = 5;
long del = 150;
long licznik = 1;
#define styg 4
#define styd 5
#define przg 3
#define przd 2
#define ledPin 13

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int stemp = 50;
int ntemp = 50;

//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(styg, INPUT_PULLUP);
  pinMode(styd, INPUT_PULLUP);
  pinMode(przg, INPUT_PULLUP);
  pinMode(przd, INPUT_PULLUP);
  Serial.begin(9600);
  sensors.begin();
  //  attachInterrupt(0, pozX, LOW);
  //  attachInterrupt(1, pozX, LOW);
  //lcd.init();                      // initialize the lcd
  //lcd.backlight();
}
void off() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  // delay(5000);
}
void counterclockwise() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
void clockwise() {
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay (motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay (motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}
void obrclockwise() {
  for (i = 1; i < obr; i++)
  {
    clockwise();
  }
  off();
  Serial.println("otw");
}
void obrcounterclockwise() {
  for (i = 1; i < obr; i++)
  {
    counterclockwise();
  }
  off();
  Serial.println("zamyk");
}

void mig() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void start()
{
  
  }

void pozycjonuj()
{
  if (pozAkt > pozDoc && pozAkt <= 38)
  {
    obrclockwise();
    pozAkt--;
  }
  else if (pozAkt < pozDoc && pozAkt >= 2 )
  {
    obrcounterclockwise();
    pozAkt++;
  }
  else
  {
    mig;
  }
}

void sprTempNowaPoz()
{

  ntemp = (sensors.getTempCByIndex(0));
  Serial.print("SPR T ntemp");
  Serial.print(ntemp);
  Serial.print("...");
  Serial.print("stemp");
  Serial.print(stemp);
  Serial.print("...");

  if (ntemp < 40)
  { pozDoc--;
    if (pozDoc > 17)
    {
      pozDoc = 17;
    }

  }

  else if (ntemp >= 40 && ntemp < 52)
  { if (ntemp > stemp)
    {
      mig;
    }
    else if (ntemp < stemp)
    {
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      pozDoc--;
    }
    if (pozDoc > 20)
    {
      pozDoc = 20;
    }
  }


  else if ((ntemp >= 52) && (ntemp < 59))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    else if (ntemp == stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc > 24)
    {
      pozDoc = 24;
    }
    if (pozDoc < 12)
    {
      pozDoc = 12;
    }
  }

  else if ((ntemp >= 59) && (ntemp <= 65))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      pozDoc--;
    }
    if (pozDoc > 32)
    {
      pozDoc = 32;
    }
    if (pozDoc < 16)
    {
      pozDoc = 16;
    }
  }

  else if ((ntemp > 65) && (ntemp < 70))
  { if (ntemp > stemp)
    {
      pozDoc++;
    }
    else if (ntemp < stemp)
    {
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      mig();
    }
    if (pozDoc > 36)
    {
      pozDoc = 36;
    }
    if (pozDoc < 20)
    {
      pozDoc = 20;
    }
  }

  else if ((ntemp >= 70) && (ntemp <= 72))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc < 24)
    {
      pozDoc = 24;
    }
  }

  else if ((ntemp > 72) && (ntemp <= 75))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc < 24)
    {
      pozDoc = 24;
    }
  }

  else if ((ntemp > 75) && (ntemp < 77))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    {
      pozDoc++;
    }
    else if (ntemp < stemp)
    {
      mig;
    }
    if (pozDoc < 28)
    {
      pozDoc = 28;
    }
  }

  else if (ntemp >= 77)
  { pozDoc++;
    if (pozDoc < 32)
    {
      pozDoc = 32;
    }
  }

  stemp = ntemp;
  Serial.print("stemp po spr");
  Serial.print(stemp);
  Serial.print("...");
  Serial.print("nowaT");
  Serial.println(ntemp);
  //obrclockwise    pozDoc--;
  //obrcounter      pozDoc++;
}

//void pozX()
//{
//  pozDoc=25;
//}


void loop() {

  if (pozDoc > 38) {
    pozDoc = 38;
  }
  if (pozDoc < 2) {
    pozDoc = 2;
  }

  pozycjonuj();

  sensors.requestTemperatures();

  Serial.print("pozDoc");
  Serial.print(pozDoc);
  Serial.print("...");
  Serial.print("pozAkt");
  Serial.print(pozAkt);
  Serial.print("...");
  Serial.print("licznik");
  Serial.print(licznik);
  Serial.print("...");
  Serial.print("SPR T ntemp");
  Serial.print(ntemp);
  Serial.print("...");
  Serial.print("stemp");
  Serial.print(stemp);
  Serial.print("...");


  Serial.print("del");
  Serial.println(del);

  licznik++;
  if (licznik > del)
  {
    sprTempNowaPoz();
    licznik = 0;
  }

  if (digitalRead(styg) != 1)
  {
    pozAkt = 2;
  }
  if (digitalRead(styd) != 1)
  {
    pozAkt = 38;
  }

  if (ntemp < 40)
  {
    del = 200;
  }
  else if (ntemp >= 40 && ntemp <= 62)
  {
    del = 20;
  }
  else if (ntemp >= 62 && ntemp <= 68)
  {
    del = 60;
  }
  else if (ntemp >= 68 && ntemp <= 76)
  {
    del = 20;
  }
  else if (ntemp > 76)
  {
    del = 1;
  }
  else
  {
    del = 100;
  }
}


