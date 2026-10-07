#include <Arduino.h>
#include <LibRobUS.h>

void setup()
{
  Serial.begin(9600);
  BoardInit();
}

int32_t encodeur1 = 0;
int32_t encodeur2 = 5;
int difference = 0;
float correction = 0;
float vitesse_gauche = 0.30;

  
int main()
{
  Serial.println("main");
  
  while(true)
  {
    Serial.println("while");

    float vitesse_droite = vitesse_gauche - correction;

    if(ROBUS_IsBumper(3))
    {
      Serial.println("bumper");
      ENCODER_ReadReset(RIGHT);
      ENCODER_ReadReset(LEFT);
      delay(1000);

      MOTOR_SetSpeed(RIGHT, vitesse_droite);
      MOTOR_SetSpeed(LEFT, vitesse_gauche);
      delay(2000);

      MOTOR_SetSpeed(RIGHT, 0);
      MOTOR_SetSpeed(LEFT, 0);
      delay(1000);

      ENCODER_Read(LEFT);
      ENCODER_Read(RIGHT);

      encodeur1 = ENCODER_Read(RIGHT);
      encodeur2 = ENCODER_Read(LEFT);

      Serial.println(encodeur1);
      Serial.println(encodeur2);
    
    
      // trouver la pondération de l'erreur
      difference = encodeur1 - encodeur2;
      
      correction = difference * 0.0001;
      Serial.println(difference);
      Serial.println(correction);
    }

    if (encodeur1 == encodeur2 && vitesse_droite < 0.3)
    {
      Serial.println("moteur calibré!");
      Serial.println(correction);
      break;
    }
  }
  return 0;
}

  

 