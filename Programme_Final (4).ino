#include <NewPing.h>

int pinIRn = 1;               // Infrarouge : Noire {Bas}
int pinIRb[2] = {2, 4};       // Infrarouge : Blanc {Gauche, Droit}
#define pinUSe 11             // Ultrason : Echo
#define pinUSt 12             // Ultrason : Triggerd
#define Max_Distance 150      // Portée maximale de l'émetteur-récepteur (max = 500cm)
int Distance_Limite = 75;     // Distance limite entre la voiture et l'obstacle
int pinBuzzer = 13;
int vitesseMoteurG = 200;          // Vitesse du moteur Gauche qu'il est possible de définir
int vitesseMoteurD = 200;          // Vitesse du moteur Droit qu'il est possible de définir
int pinMoteurAA = 5;
int pinMoteurAB = 6;
int pinMoteurBA = 9;
int pinMoteurBB = 10;

NewPing sonar(pinUSt, pinUSe, Max_Distance);

void setup() {
  pinMode(pinMoteurAA, OUTPUT);
  pinMode(pinMoteurAB, OUTPUT);
  pinMode(pinMoteurBA, OUTPUT);
  pinMode(pinMoteurBB, OUTPUT);
  pinMode(pinIRn, INPUT);
  pinMode(pinIRb[0], INPUT);
  pinMode(pinIRb[1], INPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  int statut = Detec_Obstacle();    // Vérifie la condition sur la distance entre le véhicule et le possible obstacle.
  if (statut) {                     // Si pas d'obstacle => retourne 1 (ou HIGH) donc passe à la suite
    if (digitalRead(pinIRb[1]) == HIGH && digitalRead(pinIRn) == HIGH) {   // Détecteur IR droit s'active => Elle détecte une ligne noire donc dans un virage à droite
      TournerDroite();
    }
    else if (digitalRead(pinIRb[0]) == HIGH && digitalRead(pinIRn) == HIGH) {     // Détecteur IR gauche s'active => Elle détecte une ligne noire donc dans un virage à gauche
      TournerGauche();
    }
    else if (digitalRead(pinIRn) == HIGH) {        // Détecteur IR arrière est bien en position HIGH => Le véhicule suit bien la ligne
      AvanceMoteur();
    }
    else {
      ArretMoteur();
      for (int i = 1; i <= 3; i++) {
        digitalWrite(pinBuzzer, HIGH);
        delay(500);
        digitalWrite(pinBuzzer, LOW);
        delay(500);
        delay(1000);
      }
    }
  }
}


int Detec_Obstacle() {
  if (sonar.ping_cm() <= Distance_Limite) {
    ArretMoteur();
    digitalWrite(pinBuzzer, HIGH);
    return 0;
  }
  else {
    AvanceMoteur();
    digitalWrite(pinBuzzer, LOW);
    return 1;
  }
}

// Fonctions moteur : AvanceMoteur(), ArretMoteur(), TournerGauche(), TournerDroite()

void AvanceMoteur() {
  digitalWrite(pinMoteurAA, vitesseMoteurG);
  digitalWrite(pinMoteurAB, LOW);
  digitalWrite(pinMoteurBA, vitesseMoteurD);
  digitalWrite(pinMoteurBB, LOW);
}
void ArretMoteur() {
  digitalWrite(pinMoteurAA, LOW);
  digitalWrite(pinMoteurAB, LOW);
  digitalWrite(pinMoteurBA, LOW);
  digitalWrite(pinMoteurBB, LOW);
}
void TournerGauche() {
  digitalWrite(pinMoteurAA, vitesseMoteurG);
  digitalWrite(pinMoteurAB, LOW);
  digitalWrite(pinMoteurBA, LOW);
  digitalWrite(pinMoteurBB, LOW);
}
void TournerDroite() {
  digitalWrite(pinMoteurAA, LOW);
  digitalWrite(pinMoteurAB, LOW);
  digitalWrite(pinMoteurBA, vitesseMoteurD);
  digitalWrite(pinMoteurBB, LOW);
}
