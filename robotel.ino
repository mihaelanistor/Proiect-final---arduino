#include "SoftwareSerial.h"
//#include <Servo.h>
#include "notes.h"
#include "songs.h"

//bluetooth
SoftwareSerial BTSerial(7, 8, 0); // RX, TX

String voice = "";
int dataFromBT = 0;
int lastDataFromBT = 0;
int vectorComenzi[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//wheels
#define MAX_SPEED 250
#define MIN_SPEED 200

#define MOTOR2_PIN1 3
#define MOTOR2_PIN2 5
#define MOTOR1_PIN1 6
#define MOTOR1_PIN2 9


//ultrasonic sensor
int trig = 2;
int echo = 4;

//IR sensor
int sensor[6] = {A5, A4, A3, A2, A1, A0};
int sensorReading[6] = { 0 };
int pinLedon = 12;

////avoiding objects
long timeStartRotation = 0;
boolean duringRotation = false;
int distance[4];
//servo
int servoPin = 10;
int servoDegrees[4] = {0, 50, 100, 150};
long timeLastPositionServo = 0;
int indexDegrees = 0;
int angle;
int pwm;
unsigned long lastTimeServo = 0;
//Servo myServo;

//speker
int thisNote = 0;
int thisMelody = 0;
unsigned long lastNote = 0;
int speakerPin = 13;
boolean outputTone = false;


void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);


  for (int i = 0; i < 8; i++)
  {
    pinMode(sensor[i], INPUT);
  }
  digitalWrite(pinLedon, LOW);//IR sensor disabled

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);


  pinMode(servoPin, OUTPUT);
  //
  //  myServo.attach(servoPin);
  //  myServo.write(50);

}

void loop() {

  int i;


  readDataFromBT();

  //TO DO
  //de inlocuit 7 cu o variabila

  if (dataFromBT <= 7)
  {
    vectorComenzi[dataFromBT] = 1;

    if (dataFromBT == 0) //stop
    {
      go(0, 0);
    }
  }
  if (dataFromBT > 7)
  {
    if ((dataFromBT == 14) && (vectorComenzi[7] == 1)) //stop singing
    {
      thisNote = 0;
      thisMelody = (thisMelody + 1) % 3;
    }
    vectorComenzi[dataFromBT - 7] = 0;


  }
  //nicio comanda pt miscare nu e selectata
  int ok = 1;
  for ( i = 1; i <= 6; i++)
  {
    if (vectorComenzi[i] == 1)
    {
      ok = 0;
    }
  }
  if (ok == 1)
    go(0, 0);
  //

  for (i = 1; i < 8; i++)
  {

    if (vectorComenzi[i] == 1)
    {
      switch (i)
      {
        case 1:
          go(MAX_SPEED, MAX_SPEED);
          break;
        case 2:
          go(0, MAX_SPEED);
          break;
        case 3:
          go(MAX_SPEED, 0);
          break;
        case 4:
          go(-MIN_SPEED, -MIN_SPEED);
          break;
        case 5:
          readIRSensor();
          lineFollow();
          break;
        case 6:
          avoidObjects();
          break;
        case 7:
          sing();
          break;
        default:
          go(0, 0);
      }
    }
  }



  //    switch (dataFromBT)
  //    {
  //      case 0:
  //        go(0, 0);
  //
  //        break;
  //      case 1:
  //        go(MAX_SPEED, MAX_SPEED);
  //        break;
  //      case 2:
  //        go(0, MAX_SPEED);
  //        break;
  //      case 3:
  //        go(MAX_SPEED, 0);
  //        break;
  //      case 4:
  //        go(-MIN_SPEED, -MIN_SPEED);
  //        break;
  //      case 5:
  //        readIRSensor();
  //        lineFollow();
  //        break;
  //      case 6:
  //        avoidObjects();
  //        break;
  //      case 7:
  //        sing();
  //        break;
  //      default:
  //        go(0, 0);
  //    }
}

void readDataFromBT()
{
  while (BTSerial.available() > 0)
  {
    char c = BTSerial.read(); //Conduct a serial read

    delay(10); //Delay added to make thing stable

    if (c == '#')
    {
      break; //Exit the loop when the # is detected after the word
    }
    voice += c; //Shorthand for voice = voice + c
    Serial.println(voice);
  }

  if (voice.length() > 0)
  {
    BTSerial.println(voice);

    if (voice == "*stop")
    {
      dataFromBT = 0;
    }
    else if (voice == "*go")
    {
      dataFromBT = 1;
    }
    else if (voice == "*left")
    {
      dataFromBT = 2;
    }
    else if (voice == "*right")
    {
      dataFromBT = 3;
    }
    else if (voice == "*back")
    {
      dataFromBT = 4;
    }
    else if (voice == "*line")
    {
      dataFromBT = 5;
    }
    else if (voice == "*avoid")
    {
      dataFromBT = 6;
    }
    else if (voice == "*sing")
    {
      dataFromBT = 7;
    }
    else if (voice == "*Ngo")
    {
      dataFromBT = 8;
    }
    else if (voice == "*Nleft")
    {
      dataFromBT = 9;
    }
    else if (voice == "*Nright")
    {
      dataFromBT = 10;
    }
    else if (voice == "*Nback")
    {
      dataFromBT = 11;
    }
    else if (voice == "*Nline")
    {
      dataFromBT = 12;
    }
    else if (voice == "*Navoid")
    {
      dataFromBT = 13;
    }
    else if (voice == "*Nsing")
    {
      dataFromBT = 14;
    }

    voice = "";
  }

}

void go(int speedLeft, int speedRight)
{
  if (speedLeft > 0)
  {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  }
  else
  {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }

  if (speedRight > 0)
  {
    analogWrite(MOTOR2_PIN2, speedRight);
    analogWrite(MOTOR2_PIN1, 0);
  }
  else
  {
    analogWrite(MOTOR2_PIN2, 0);
    analogWrite(MOTOR2_PIN1, -speedRight);
  }
}

void readIRSensor()
{

  digitalWrite(pinLedon, HIGH);

  for (int i = 0; i < 6; i++)
  {
    if (analogRead(sensor[i]) > 200)
      sensorReading[i] = 0;
    else
      sensorReading[i] = 1;
    Serial.print(sensorReading[i]);
    Serial.print(" ");

  }
  Serial.println(" ");
  digitalWrite(pinLedon, LOW);
}
void lineFollow()
{
  int weights[6] = { -5, -3, -1, 1, 3, 5};
  int error = 0, sum = 0;
  int left = MIN_SPEED;
  int right = MIN_SPEED;

  //  for (int i = 0; i < 6; i++)
  //  {
  //    if ((sensorReading[i] == 1) && (sensorReading[5 - i] == 0))
  //    {
  //      if (i < 1)
  //      {
  //        left = 0;
  //       // right = MAX_SPEED;
  //      }
  //      if ( i > 4)
  //      {
  //        right = 0;
  //       // left = MAX_SPEED;
  //
  //      }
  //    }
  //  }
  //  int i;
  //    for (i = 0; i < 6; i++)
  //  {
  //    error += sensorReading[i] * weights[i];
  //    if (sensorReading[i] == 1)
  //    {
  //      sum = sum + 1;
  //    }
  //  }
  //
  //  error = error / sum;
  //    if (sum == 0)
  //    error = 6;
  //
  //  left = left + 20 * error;
  //  right = right - 20 * error;


  for (int i = 0; i < 6; i++)
  {
    if ((sensorReading[i] == 0) && (sensorReading[5 - i] == 1))
    {
      if (i < 1)
      {
        left = -MIN_SPEED / 2;
        right = MIN_SPEED;
      }
      if ( i > 4)
      {
        right = -MIN_SPEED / 2;
        left = MIN_SPEED;

      }
    }
  }
  go(left, right);

}
int distanceFromUltrasonicSensor()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long Time = pulseIn(echo, HIGH);

  int dist = Time * 0.034 / 2;

  Serial.print("distance: ");
  Serial.println(dist);

  return dist;
}
void avoidObjects()
{
  int timeRotate90degrees = 1000;

  int delayServo = 50;

  if (millis() - timeLastPositionServo >= delayServo)
  {
    servoPulse(servoPin, servoDegrees[indexDegrees]);
    distance[indexDegrees] = distanceFromUltrasonicSensor();
    if (millis() - timeLastPositionServo >= 200)
    {
      indexDegrees = (indexDegrees + 1) % 4;
      timeLastPositionServo = millis();
    }
  }

  if ((distance[1] <= 5) || (distance[2] <= 5))
  {
    go(-MIN_SPEED, -MIN_SPEED);
    duringRotation = true;
  }
  else
  {
    if (duringRotation == true)
    {
      if ((distance[1] <= 10 ) || (distance[2] <= 10))
      {
        go(-MIN_SPEED, -MIN_SPEED);
        timeStartRotation = millis();
      }
      else
      {
        if (millis() - timeStartRotation  < timeRotate90degrees)
        {
          if (distance[0] < 10)
            go(0, -MIN_SPEED);
          else if (distance[3] < 10)
            go(-MIN_SPEED, 0);
          else
            go(0, -MIN_SPEED);
        }
        else
          duringRotation = false;
      }
    }

    else
      go(MAX_SPEED, MAX_SPEED);
  }
}



void sing()
{
  switch (thisMelody)
  {
    case 0:
      singAnthem();
      break;
    case 1:
      singTetris();
      break;
    case 2:
      singMario();
      break;
    default:
      singAnthem();
  }
}
void servoPulse (int servo, int angle)
{
  pwm = (angle * 11) + 500;    // Convert angle to microseconds

  if (millis() - lastTimeServo >= 50)
  {
    lastTimeServo = millis();
    digitalWrite(servo, HIGH);
    delayMicroseconds(pwm);
  }

  digitalWrite(servo, LOW);

  // delay(50);                   // Refresh cycle of servo
}
void singTetris()
{
  int tetrisMelody[] = {
    NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5,
    NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
    NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, 0
  };
  int tetrisNoteDurations[] = {
    4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 3, 8,
    4, 4, 4, 4, 8, 8, 8, 8, 3, 8, 4, 8, 8, 3,
    8, 4, 8, 8, 4, 8, 8, 4, 4, 4, 4, 4, 4
  };

  float noteDuration = 1000.00 / tetrisNoteDurations[thisNote];

  tone(speakerPin, tetrisMelody[thisNote], noteDuration);

  int pauseBetweenNotes = noteDuration * 1.3;
  int size = sizeof(tetrisMelody) / sizeof(int);

  if (millis() - lastNote >= pauseBetweenNotes)
  {
    noTone(speakerPin);
    thisNote = (thisNote + 1) % size;
    lastNote = millis();
  }
}
void singMario()
{

  int marioMelody[] = {
    NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0,
    NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0,

    NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7,
    NOTE_D7, NOTE_B6, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0,
    0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7,
    NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0, 0
  };
  //Mario main them tempo
  int marioNoteDurations[] = {
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 9, 9, 9,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  };
  
  float noteDuration = 1000.00 / marioNoteDurations[thisNote];

  tone(speakerPin, marioMelody[thisNote], noteDuration);

  int pauseBetweenNotes = noteDuration * 1.3;
  int size = sizeof(marioMelody) / sizeof(int);

  if (millis() - lastNote >= pauseBetweenNotes)
  {
    noTone(speakerPin);
    thisNote = (thisNote + 1) % size;
    lastNote = millis();
  }
}
void singAnthem()
{
  //imn
  int nationalAnthemMelody[] = {
    NOTE_A3, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_D5,
    NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
    NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4,
    NOTE_D4, NOTE_D4, NOTE_D5, NOTE_D5, NOTE_D5,
    NOTE_D5, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4,
    NOTE_A4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int nationalAnthemNoteDurations[] = {
    4, 3, 8, 4, 4, 2, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4,
    4, 2, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4, 4, 4, 4, 4, 2, 4, 3, 8, 4, 4,
    2, 4, 4, 3, 8, 4, 4, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4,
    4, 2, 4, 3, 8, 4, 4, 3, 8, 4, 4, 4, 4, 4, 4, 4, 2
  };
  
  float noteDuration = 1000.00 / nationalAnthemNoteDurations[thisNote];

  tone(speakerPin, nationalAnthemMelody[thisNote], noteDuration);

  int pauseBetweenNotes = noteDuration * 1.3;
  int size = sizeof(nationalAnthemMelody) / sizeof(int);

  if (millis() - lastNote >= pauseBetweenNotes)
  {
    noTone(speakerPin);
    thisNote = (thisNote + 1) % size;
    lastNote = millis();
  }
}
