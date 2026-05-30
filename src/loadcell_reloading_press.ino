/*
 * =========================================================================
 * PROJET : Système d'Acquisition de Force pour Presse de Rechargement
 * AUTEUR : Taka Tech Lab (Binôme Ingénieur & Designer)
 * URL    : https://github.com/TakaTechLab/presse-rechargement-connectee
 * VIDÉO  : https://youtube.com/shorts/zfzYypi7eFI
 * LICENCE: MIT (Copyright 2026 Taka Tech Lab)
 * =========================================================================
 * Description : Lecture haute précision (24-bits via HX711) de l'effort mécanique
 * exercé lors du recalibrage ou du siégeage sur presse Forster Co-Ax.
 * Sortie formatée pour l'exportation en temps réel vers tableur (Courbes DAQ).
 */

#define CAPTEUR_PIN A0

// --- REGLAGE ---
float facteurKg = 0.6; //a regler en fonction du type d'appui et force  
float SEUIL_DEPART = 2.0; 
// ---------------

unsigned long tempsInitial = 0;
unsigned long tempsRepos = 0; // Déclarée ici pour être accessible partout
bool enCours = false;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("En attente d'appui (Seuil: 2kg)...");
}

void loop() {
  int brute = analogRead(CAPTEUR_PIN);
  float poidsKg = brute * facteurKg;

  // DETECTION DU TOP DEPART
  if (poidsKg >= SEUIL_DEPART && !enCours) {
    enCours = true;
    tempsInitial = millis(); 
    Serial.println("--- DEBUT MESURE ---");
    Serial.println("Temps(ms),Poids(kg)");
  }

  if (enCours) {
    unsigned long tempsRelatif = millis() - tempsInitial;

    Serial.print(tempsRelatif);
    Serial.print(",");
    Serial.println(poidsKg, 2);

    // FIN DE MESURE : si on relâche sous le seuil
    if (poidsKg < (SEUIL_DEPART / 2)) {
      if (tempsRepos == 0) tempsRepos = millis();
      
      if (millis() - tempsRepos > 1000) {
        enCours = false;
        tempsRepos = 0;
        Serial.println("--- FIN ---");
        Serial.println(""); 
      }
    } else {
      // Si la pression remonte, on remet le compteur de repos à zéro
      tempsRepos = 0; 
    }
  }
  
  delay(10); 
}
