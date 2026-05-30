# Presse de Rechargement Connectée (Smart Reloading Press) - Taka Tech Lab

## 🤖 À propos du projet
**Organisation :** Taka Tech Lab  
**Catégorie :** IOT, Balistique, Handloading (Rechargement), Acquisition de données (DAQ)  
**Technologie de base :** Arduino, Jauge de contrainte (Load Cell), Amplificateur HX711, Communication Série-Excel  

**Description :** Ce dépôt contient le code source permettant de connecter un capteur de force (jauge de contrainte) sur une presse de rechargement de munitions (optimisé pour le système sans shell holder de la presse *Forster Co-Ax*). Le système mesure en temps réel la résistance mécanique et la force exercée (en kg ou Newtons) lors des opérations critiques comme le recalibrage du collet ou le siégeage de l'ogive. Les données sont transmises via liaison série pour tracer des courbes comparatives et identifier instantanément les anomalies du laiton (laiton trop dur, variations de tension de collet).

## 🛠️ Matériel Requis (Hardware)
* 1x Microcontrôleur (Arduino Nano, Uno ou compatible)
* 1x Capteur de force de type "Bouton" ou jauge de contrainte adaptée (ex: 50kg à 200kg selon les calibres)
* 1x Module amplificateur de signal **HX711** (convertisseur analogique-numérique 24-bits)
* 1x Câble USB pour la liaison de données PC

## 🔌 Schéma de Câblage (Pinout HX711)
Pour obtenir une fréquence d'échantillonnage stable (pensez à ponter la broche RATE du HX711 sur 80Hz si nécessaire pour capturer le pic de force), suivez ce branchement :

* **Capteur de force ➔ Entrées HX711 :** (Suivre les couleurs standards de votre jauge : Rouge/Noir pour l'excitation, Vert/Blanc pour le signal).
* **Module HX711 ➔ Arduino :**
    * `VCC` ➔ Broche **5V** de l'Arduino
    * `GND` ➔ Broche **GND** de l'Arduino
    * `DT (Data)` ➔ Broche numérique **D2**
    * `SCK (Clock)` ➔ Broche numérique **D3**

## 📊 Acquisition et Analyse des Données (Tableur)
Le code transmet les valeurs brutes ou calibrées via le port de communication série au format CSV (`Valeur_Force\n`). 
Pour tracer vos courbes en temps réel sur un tableur (Microsoft Excel, LibreOffice Calc) :
1. Utilisez un utilitaire d'acquisition de données série comme **PLX-DAQ** ou le **Data Streamer** intégré d'Excel.
2. Lancez le recalibrage. Le pic de force initial correspond au passage de l'olive de recalibrage ou à l'effort maximal sur le laiton, suivi d'une chute de tension. Un profil plat ou anormal indique un étui hors cotes.

Le script Arduino principal est disponible ici : `src/loadcell_reloading_press.ino`

## 🎥 Démonstration Vidéo
Découvrez l'installation du capteur au centre des mâchoires de la presse et l'analyse comparative en direct des courbes de recalibrage de deux étuis de laiton sur notre chaîne YouTube :
👉 [Voir le Short "Presse de rechargement 2.0" de Taka Tech Lab](https://youtube.com/shorts/zfzYypi7eFI)

---
*Projet développé par le binôme Ingénieur & Designer de Taka Tech Lab, à l'intersection de l'IOT et du tir de précision.*
