//VARIABLES MOTEUR
int M1 = 4; //moteur droit connecté au pin4
int M2 = 7; //moteur gauche connecté au pin 7
int E1 = 5; //controle vitesse moteur droit 
int E2 = 6; //controle vitesse moteur droit gauche

// Variables line finder
const int capteurDroit = A0; // Connecter le capteur Droit en A0
const int capteurGauche = A2; // Connecter le capteur Gauche en A

// Configuration de la broche d'interruption
#define interruptPin 2
volatile bool interruptFlag = false;
void interruptFunction() {
  interruptFlag = true;
}

// VARIABLES ET CONSTANTE UKTRASONNIC
const int S = 7; //droit
long microsecondsToInches(long microseconds) { return microseconds / 74 / 2; }
long microsecondsToCentimeters(long microseconds) {return microseconds / 29 / 2; }

void setup() {

  //moteur
  pinMode (M1, OUTPUT); //moteur droit en sortie
  pinMode (M2, OUTPUT); //moteur gauche en sortie
  Serial.begin(9600); // Initialise la communication série à 9600 bauds

//line finder
  pinMode(capteurDroit, INPUT); //capteur droit recois le signal lumineux
  pinMode(capteurGauche, INPUT); //capteur gauche recois le signal lumineux
  Serial.begin(9600); 

// Configuration de la broche d'interruption faisait agire le code ultrason quand la tension baisse(donc la distance)
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interruptFunction, FALLING); 

}


void loop() {

int etatDroit = digitalRead(capteurDroit); // Lit état capteur droit
int etatGauche = digitalRead(capteurGauche); // Lit état capteur gauche
  
  if (etatGauche == LOW && etatDroit == LOW) { // les deux HORS ligne --> AVANCER
    digitalWrite(M1, HIGH); 
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 255);
  }

  else if (etatGauche == LOW && etatDroit == HIGH) { //droit SURligne -->DROITE (roue gauche va moins vite)
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 100);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 200);
  }

 else if (etatGauche == HIGH && etatDroit == LOW) { //gauche sur ligneligne -->gauche   (roue droite va moin vite)  
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 200);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 100);
}  

else if (etatGauche == HIGH && etatDroit == HIGH) { // les deux surligne --> AVANCER
     digitalWrite(M1, HIGH); 
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 255); 
}
delay(5);    

  float distance = 0;
  long duration = 0;
while (distance < 10) {
long duration, distancei, distance;
   
  pinMode(S, OUTPUT);
  digitalWrite(S, LOW);
  delayMicroseconds(2);
  digitalWrite(S, HIGH);
  delayMicroseconds(5);
  digitalWrite(S, LOW);

  pinMode(S, INPUT);
  duration = pulseIn(S, HIGH);

  distancei = microsecondsToInches(duration);
  distance = microsecondsToCentimeters(duration);

    if (distance < 4 || interruptFlag)  { //gauche sur ligneligne -->gauche   (roue droite va moin vite)  
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 200);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 100);
}  

else if (distance < 10 && distance > 7) { //droit SURligne -->DROITE (roue gauche va moins vite)
		digitalWrite(M1, HIGH); 
    analogWrite(E1, 100);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 200);
  }

    else if (distance > 4 && distance < 7) { // les deux HORS ligne --> AVANCER
    digitalWrite(M1, HIGH); 
    analogWrite(E1, 255);
    digitalWrite(M2, HIGH); 
    analogWrite(E2, 255);
  }
  }
  delay(100);

  // Réinitialiser le drapeau d'interruption
    interruptFlag = false;
    delay(5);
}
