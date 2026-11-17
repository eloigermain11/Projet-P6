#include <Arduino.h>
#include <LibRobus.h>

mode_veille();

if (doigt_detecte == 1)
{
  afficher_loading();
  //faire jouer son de chargement (timer)
}

afficher_menu();
//choix difficulté avec joystock
afficher_confirmation();

if(dif == facile)
{
  // generer combinaisons facile aleatoire peux pas repeter couleur et utilise juste 4 couleur
  afficher_debut();
  afficher_essais():
  if(//enfant confirme pas en moins de 60 sec)
    {
      mode_veille():
    }
  else if(//enfant confirme 4 choix de blocs)
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
  else if(nb_essais == 0)
  {
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille
  }

}
}

if(dif == moyen)
{
  // generer combinaisons moyenne aleatoire toutes les combinaisons sont possibles mais plus de feedback
   // generer combinaisons facile aleatoire peux pas repeter couleur et utilise juste 4 couleur
  afficher_debut();
  afficher_essais():
  if(//enfant confirme pas en moins de 60 sec)
    {
      mode_veille():
    }
  else if(//enfant confirme 4 choix de blocs)
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
  else if(nb_essais == 0)
  {
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille
  }

}

if(dif == difficile)
{
  // generer combinaisons difficile aleatoire toutes les combinaisons sont possibles mais moins de feedback
   // generer combinaisons facile aleatoire peux pas repeter couleur et utilise juste 4 couleur
  afficher_debut();
  afficher_essais():
  if(//enfant confirme pas en moins de 60 sec)
    {
      mode_veille():
    }
  else if(//enfant confirme 4 choix de blocs)
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
  else if(nb_essais == 0)
  {
    // del 1, 2, 3, 4 flash rouge on/off
    afficher_lose();
    //faire jouer chanson defaite

    //pendant x pulses et alterner gauche-droite pour faire des nons
    MOTOR_SetSpeed(RIGHT,0.5 );
    MOTOR_SetSpeed(LEFT, 0.5);
    // timer de x secondes apres retour mode_veille
  }

}
