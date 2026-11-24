#include <Arduino.h>
#include <LibRobus.h>
#include <LiquidCrystal.h>


const int CONTRASTE = 11;
const int RS = A1;
const int ENABLE = A2;
const int DIGITAL1 = 50;
const int DIGITAL2 = 52;
const int DIGITAL3 = 51;
const int DIGITAL4 = 53;
const int FLECHE = 0x7E;

byte crochet[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};

int etat_X,etat_bouton;
int position = 1;
int menu_actif = 1;
int essais = 8;
int combinaison[4];

LiquidCrystal lcd(RS,ENABLE,DIGITAL1,DIGITAL2,DIGITAL3,DIGITAL4);

void EcrireMenu(){
  lcd.home();
  lcd.print("DIFFICULTE ?");
  lcd.setCursor(0,1);
  lcd.write(FLECHE);
  lcd.print("FACILE");
  lcd.setCursor(1,2);
  lcd.print("MOYEN");
  lcd.setCursor(1,3);
  lcd.print("DIFFICILE");
  lcd.home();
}

void SelectionMenu(int ligne) {
  switch(ligne){
    case 1:
    lcd.setCursor(0,ligne+1);
    lcd.print(" ");
    lcd.setCursor(0,ligne);
    lcd.write(FLECHE);
    break;
    case 2:
    lcd.setCursor(0,ligne+1);
    lcd.print(" ");
    lcd.setCursor(0,ligne-1);
    lcd.print(" ");
    lcd.setCursor(0,ligne);
    lcd.write(FLECHE);
    break;
    case 3:
    lcd.setCursor(0,ligne-1);
    lcd.print(" ");
    lcd.setCursor(0,ligne);
    lcd.write(FLECHE);
    break;
  }
}

void Confirmation(int ligne) {
  switch(ligne){
    case 1:
    lcd.setCursor(7,1);
    lcd.write(byte(0));
    delay(1500);
    lcd.clear();
    menu_actif = 0;
    break;
    case 2:
    lcd.setCursor(6,2);
    lcd.write(byte(0));
    delay(1500);
    lcd.clear();
    menu_actif = 0;
    break;
    case 3:
    lcd.setCursor(10,3);
    lcd.write(byte(0));
    delay(1500);
    lcd.clear();
    menu_actif = 0;
    break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  pinMode(A5,INPUT); // X
  pinMode(A6,INPUT); // Y
  pinMode(A7,INPUT); // Bouton
  pinMode(CONTRASTE,OUTPUT);
  analogWrite(CONTRASTE,75); //Chiffre pour bien voir l'écriture
  lcd.begin(16,4);
  lcd.clear();
  Serial.println("DEBUT");
  lcd.createChar(0, crochet);
  EcrireMenu();
  SelectionMenu(position);
}

void GenererCombinaison(int position)
// le mieux est d'appeler la fonction juste une fois par partie vu que toutes les diffcultés sont dans la focntion
{
    int tableau [4];
    randomSeed(micros());
    // pour difficulté moyenne et difficile
    if(position == 2 || position == 3)
    {
    for (int i = 0; i < 4; i++)
    {
        combinaison[i] = random(0 , 6);
        Serial.println (combinaison[i]);
    }
    }
    //pour difficulté facile
   else if(position == 1)
    {
        for (int i = 0; i < 4; i++)
	{
		int test = 1;
		while(test == 1)
		{
			test = 0;
			tableau[i] = random(0, 6);
		for (int j = 0; j < i; j++)
		{
			if (combinaison[j] == tableau[i])
			{
				test = 1;
			}
			
		}
		if (test == 0)
		{
			combinaison[i] = tableau[i];
		}		
		}
	}
}
}

void afficher_menu(){
  analogWrite(CONTRASTE,75); //Chiffre pour bien voir l'écriture
  lcd.begin(16,4); // Peut être juste lcd.display() si lcd utilisé avant
  lcd.clear();
  Serial.println("DEBUT");
  lcd.createChar(0, crochet);
  EcrireMenu();
  SelectionMenu(position);
  // Choix de la difficulté
  while (menu_actif == 1){
  etat_X = analogRead(A5);
  etat_bouton = analogRead(A7);
  if (etat_bouton < 50){ // Le bouton est appuyé
    Confirmation(position);
  }
  if ((etat_X > 900)&&(menu_actif)){ // On monte dans le menu
    if (position == 1){
      position = position + 1;
    }
    position = position - 1;
    SelectionMenu(position);
    delay(250);
  }
  else if ((etat_X < 200)&&(menu_actif)){ // On descend
    if (position == 3){
      position = position - 1;
    }
    position = position + 1;
    SelectionMenu(position);
    delay(250);
  }
}
}

void afficher_essais(){
delay(1000);
lcd.home();
lcd.print("Essai(s)");
lcd.setCursor(0,1);
lcd.print("restant(s)");
lcd.setCursor(0,2);
lcd.print(essais);
delay(50000);
}


void loop()
{
mode_veille();

if (doigt_detecte == 1)
{
  afficher_loading();
  //faire jouer son de chargement (timer)
}

afficher_menu();
//choix difficulte avec joystick
SelectionMenu(); //manque un paramètre
Confirmation(); //manque un paramètre

if(position == 1)
{
  GenererCombinaison(1);
  afficher_essais();
  while(essais < 8)
  {

  if(/*enfant confirme pas en moins de 60 sec*/)
    {
      mode_veille();
    }
  else if(/*enfant confirme 4 choix de blocs*/)
  {
    read_capteur(1);
    read_capteur(2);
    read_capteur(3);
    read_capteur(4);
  
  if(capteur1 == combinaison[0])
  {
    //del 1 allume vert
  }
 else 
  {
    // del 1 allume jaune
  }
  // meme principe pou capteur 2, 3, 4
  if (capteur1 == combinaison[0] && capteur2 == combinaison[1] && capteur3 == combinaison[2] && cpateur4 == combinaison[3])
  {
    // del 1, 2, 3, 4 flash vert on/off
    afficher_win();
    // faire jouer chanson victoire
    //pendant x pulses pour faire tour sur lui-meme
    MOTOR_SetSpeed(RIGHT, 0.5);
    MOTOR_SetSpeed(LEFT, -0.5);
    // timer de x secondes apres retour mode_veille
  }
  }
  essais = essais + 1;
}
  //si nb essais max atteint
  
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille
  

}

if(position == 2)
{
  GenererCombinaison(2);
  // generer combinaisons moyenne aleatoire toutes les combinaisons sont possibles mais plus de feedback
   // generer combinaisons facile aleatoire peux pas repeter couleur et utilise juste 4 couleur
  afficher_essais();
while (essais <8)
{
  if(/*enfant confirme pas en moins de 60 sec*/)
    {
      mode_veille();
    }
  else if(/*enfant confirme 4 choix de blocs*/)
  {
    read_capteur(1);
    read_capteur(2);
    read_capteur(3);
    read_capteur(4);
  
  if(capteur1 == combinaison[0])
  {
    //del 1 allume vert
  }

  else if(capteur1 == combinaison[1] || combinaison[2] || combinaison[3])
  {
    //alume del 1 jaune
  }
  else 
  {
    //allume del 1 rouge
  }
  // meme principe pou capteur 2, 3, 4
  if (capteur1 == combinaison[0] && capteur2 == combinaison[1] && capteur3 == combinaison[2] && cpateur4 == combinaison[3])
  {
    // del 1, 2, 3, 4 flash vert on/off
    afficher_win();
    // faire jouer chanson victoire
    //pendant x pulses pour faire tour sur lui-meme
    MOTOR_SetSpeed(RIGHT, 0.5);
    MOTOR_SetSpeed(LEFT, -0.5);
    // timer de x secondes apres retour mode_veille
  }
}
essais = essais + 1;
}

  //lorsque nb essais max
  
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille
  
}


if(position == 3)
{
  GenererCombinaison(3);
  // generer combinaisons difficile aleatoire toutes les combinaisons sont possibles mais moins de feedback
   // generer combinaisons facile aleatoire peux pas repeter couleur et utilise juste 4 couleur
  afficher_essais();
  while(essais < 8)
  {
  if(/*enfant confirme pas en moins de 60 sec*/)
    {
      mode_veille();
    }
  else if(/*enfant confirme 4 choix de blocs*/)
  {
    read_capteur(1);
    read_capteur(2);
    read_capteur(3);
    read_capteur(4);
  
  if(capteur1 == combinaison[0])
  {
    //del 1 allume vert
  }
  else 
  {
    //allume del 1 rouge
  }
  // meme principe pou capteur 2, 3, 4
  if (capteur1 == combinaison[0] && capteur2 == combinaison[1] && capteur3 == combinaison[2] && cpateur4 == combinaison[3])
  {
    // del 1, 2, 3, 4 flash vert on/off
    afficher_win();
    // faire jouer chanson victoire
    //pendant x pulses pour faire tour sur lui-meme
    MOTOR_SetSpeed(RIGHT, 0.5);
    MOTOR_SetSpeed(LEFT, -0.5);
    // timer de x secondes apres retour mode_veille
  }
}
  essais = essais + 1;
}
  // lorsque nb essais max atteint
  
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille  

}
}