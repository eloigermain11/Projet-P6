#include <Arduino.h>
#include <LibRobUS.h>

const int32_t PULSES_50CM = 6683;    // 50 cm
const int32_t PULSES_90_DEG = 2000;  // a recalibrer 

const float VITESSE_CROISIERE = 0.30;
const float VITESSE_ROTATION = 0.20;
const unsigned long DELAI = 50; // delai entre les mesures

const float KP = 0.0001;
const float KI = 0.00002;

void arreter_moteurs();
void avancer();
void tourner_gauche();
void tourner_droite();

void setup() {
  Serial.begin(9600);
  BoardInit();
}

void loop() {

  // bumper arriere
  if (ROBUS_IsBumper(3)) {
    delay(500);

    // mouvement test
    avancer();
    delay(500);

    tourner_droite();
    delay(500);

    avancer();
    delay(500);

    tourner_gauche();
    delay(500);
  }
}


void arreter_moteurs() {
  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);
  delay(100);
}

void avancer() {
  ENCODER_ReadReset(LEFT);
  ENCODER_ReadReset(RIGHT);

  int32_t total_gauche = 0;
  int32_t total_droite = 0;
  int32_t erreur_cumulee = 0;

  float vitesse_droite = VITESSE_CROISIERE;

  while (total_gauche < PULSES_50CM) {
    MOTOR_SetSpeed(LEFT, VITESSE_CROISIERE);
    MOTOR_SetSpeed(RIGHT, vitesse_droite);

    delay(DELAI);

    int32_t delta_gauche = ENCODER_ReadReset(LEFT);
    int32_t delta_droite = ENCODER_ReadReset(RIGHT);

    total_gauche += delta_gauche;
    total_droite += delta_droite;

    int32_t erreur_vitesse = delta_gauche - delta_droite;
    erreur_cumulee = total_gauche - total_droite;

    float correction = (erreur_vitesse * KP) + (erreur_cumulee * KI);
    vitesse_droite = VITESSE_CROISIERE + correction;

    if (vitesse_droite > 1.0) vitesse_droite = 1.0;
    if (vitesse_droite < 0.15) vitesse_droite = 0.15;
  }

  arreter_moteurs();
}


void tourner_gauche() {
  ENCODER_ReadReset(LEFT);
  ENCODER_ReadReset(RIGHT);

  // directions des roues inversées
  MOTOR_SetSpeed(LEFT, -VITESSE_ROTATION);
  MOTOR_SetSpeed(RIGHT, VITESSE_ROTATION);

  while (abs(ENCODER_Read(RIGHT)) < PULSES_90_DEG) {
    delay(10);
  }

  arreter_moteurs();
}

void tourner_droite() {
  ENCODER_ReadReset(LEFT);
  ENCODER_ReadReset(RIGHT);

  // directions des roues inversées
  MOTOR_SetSpeed(LEFT, VITESSE_ROTATION);
  MOTOR_SetSpeed(RIGHT, -VITESSE_ROTATION);

  while (abs(ENCODER_Read(LEFT)) < PULSES_90_DEG) {
    delay(10);
  }

  arreter_moteurs();
}