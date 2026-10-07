#include <Arduino.h>
#include <LibRobUS.h>
#include <math.h>

    int etape = 0;
    float vitesse = 0.25;
    float pidrotation = vitesse;
    float pidvitesse = vitesse;


void setup() 
{
   BoardInit();

Serial.begin(9600);
delay(1500);

  Serial.println("PROGRAMME DEMARRE");
}

void devant(int activation, float pid, float vitesse)
{

  int32_t encodeur1 = 0;
  int32_t encodeur2 = 0;
  float erreur = 0;
  float correction = 0;
   encodeur1 = ENCODER_ReadReset(LEFT);
   encodeur2 = ENCODER_ReadReset(RIGHT);

if (activation == 1)
  {

 while (encodeur1 <= 6683  && encodeur2 <= 6683)
    {
      encodeur1 = ENCODER_Read(LEFT);
      encodeur2 = ENCODER_Read(RIGHT);
      erreur = encodeur1 - encodeur2;
      correction = erreur * 0.0001;
      MOTOR_SetSpeed(LEFT, vitesse - correction);
      MOTOR_SetSpeed(RIGHT, pid + correction);
    }
  
      MOTOR_SetSpeed(LEFT, 0);
     MOTOR_SetSpeed(RIGHT, 0);
     Serial.println("deplacement terminé");

    encodeur1 = ENCODER_ReadReset(LEFT);
     encodeur2 = ENCODER_ReadReset(RIGHT);
     activation = 0;
   
  } 
}

void rotagauche(int activation, float pid, float vitesse)
{

  int32_t encodeur1 = 0;
  int32_t encodeur2 = 0;
  float erreur = 0;
  float correction = 0;
   encodeur1 = ENCODER_ReadReset(LEFT);
   encodeur2 = ENCODER_ReadReset(RIGHT);

if (activation == 1)
  {

 while (abs(encodeur1) <= 1867  && abs(encodeur2) <= 1867)
    {
      encodeur1 = ENCODER_Read(LEFT);
      encodeur2 = ENCODER_Read(RIGHT);
      erreur = abs(encodeur2) - abs(encodeur1);
      correction = erreur * 0.0001;
      MOTOR_SetSpeed(LEFT, vitesse + correction);
      MOTOR_SetSpeed(RIGHT, -(pid - correction));
    }
  
      MOTOR_SetSpeed(LEFT, 0);
     MOTOR_SetSpeed(RIGHT, 0);
     Serial.println("deplacement terminé");

    encodeur1 = ENCODER_ReadReset(LEFT);
    encodeur2 = ENCODER_ReadReset(RIGHT);
     activation = 0;
   
  } 
}



void loop() 
{
    int bumperArr = 0;

    bumperArr = ROBUS_IsBumper(3);

    if (bumperArr == 1)
    { 
      devant(1, vitesse, vitesse);
      delay(1000);
      rotagauche(1, vitesse, vitesse);
      delay(1000);
      rotagauche(1, vitesse, vitesse);
      delay(1000);
      devant(1, vitesse, vitesse);
      delay(1000);
      rotagauche(1, vitesse, vitesse);
      delay(1000);
      rotagauche(1, vitesse, vitesse);
      delay(1000);
      devant(1, vitesse, vitesse);
      delay(1000);
    }

}









     /* if (bumperArr = 1 && etape == 0)
    {
    
      pid(vitesse, pidvitesse, pidrotation);
      etape++;
      delay(5000);
    }
    else if (etape == 1)
    {
    
      devant(1, pidvitesse, vitesse);
      etape++;
      delay(2000);
    }
    else if (etape == 2)
    {
    
      rotagauche(1, pidrotation, vitesse);
      etape++;
      delay(2000);
    }
    else if (etape == 3)
    {
    
      devant(1, pidvitesse, vitesse);
      etape = 0;
      delay(2000);
    }
    else 
    {
      MOTOR_SetSpeed(LEFT, 0);
      MOTOR_SetSpeed(RIGHT, 0);
    }*/
