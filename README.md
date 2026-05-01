# Connected-object-by-Sigfox-Creation-of-a-weather-station-Report-2022
Station météo IoT sur Arduino MKRFox 1200 — mesure température, humidité, pression, luminosité, pluviométrie et distance, avec transmission des données via le réseau Sigfox (UNB 868 MHz).
# 🌦️ Station Météo IoT — Arduino MKRFox 1200 × Sigfox

> Conception et interprétation des données d'une station météo embarquée sur Arduino, avec transmission sans fil via le réseau **Sigfox (UNB 868 MHz)**.
---
## 📋 Description du projet

Ce projet consiste à concevoir une **station météo connectée** capable de collecter plusieurs paramètres environnementaux en temps réel et de les transmettre à distance via le réseau **Sigfox**, une technologie LPWAN (Low Power Wide Area Network) à très faible consommation énergétique.

Les données collectées sont ensuite interprétées et visualisées pour permettre une analyse de l'environnement local.
---
## 🛰️ Environnement de communication — Sigfox

**Sigfox** est un réseau de communication IoT (Internet of Things) basé sur la technologie **UNB (Ultra Narrow Band)** — bande ultra-étroite — qui offre :

- 📡 **Longue portée** : couverture de zones reculées ou difficiles d'accès
- ⚡ **Très faible consommation** énergétique, adapté aux objets connectés autonomes
- 🆓 **Bandes de fréquence libres de droit** (bandes ISM — Industrielle, Scientifique et Médicale)
  - En Europe : **868 MHz** (bande ISM)
- 📦 Jusqu'à **140 messages de 12 octets par jour** par objet
---
## 🔧 Matériel utilisé

| Composant | Rôle |
|---|---|
| **Arduino MKRFox 1200** | Microcontrôleur principal avec module Sigfox intégré |
| **BME280** | Capteur combiné : température, humidité, pression atmosphérique |
| **Capteur de pluie** | Détection et mesure des précipitations |
| **BH1750** | Capteur de luminosité (intensité lumineuse en lux) |
| **Capteur ultrason (HC-SR04 ou équivalent)** | Mesure de distance |
---
## 📡 Données collectées

- 🌡️ **Température** (°C)
- 💧 **Humidité relative** (%)
- 🔵 **Pression atmosphérique** (hPa)
- 🌧️ **Pluviométrie** — présence et intensité de pluie
- ☀️ **Luminosité** (lux)
- 📏 **Distance** (cm / m) via ultrasons
---
## 🗂️ Structure du projet

```
station-meteo-sigfox/
│
├── src/
│   ├── main.ino               # Programme principal Arduino
│   ├── sensors/
│   │   ├── bme280.ino         # Lecture température / humidité / pression
│   │   ├── rain_sensor.ino    # Lecture capteur de pluie
│   │   ├── bh1750.ino         # Lecture luminosité
│   │   └── ultrasonic.ino     # Lecture distance ultrason
│   └── sigfox/
│       └── sigfox_send.ino    # Encodage et envoi des messages Sigfox
│
├── docs/
│   └── schema_cablage.png     # Schéma de câblage
│
├── README.md
└── LICENSE
```
---
## ⚙️ Installation et configuration

### Prérequis

- [Arduino IDE](https://www.arduino.cc/en/software) (version 1.8.x ou 2.x)
- Carte **Arduino MKRFox 1200** configurée dans le gestionnaire de cartes
- Compte [Sigfox Backend](https://backend.sigfox.com/) pour visualiser les messages

### Bibliothèques Arduino requises

Installer via le gestionnaire de bibliothèques Arduino IDE :

```
- Adafruit BME280 Library
- Adafruit Unified Sensor
- BH1750 (by Christopher Laws)
- SigFox (bibliothèque officielle Arduino MKRFox)
```
### Étapes

1. Cloner le dépôt :
   ```bash
   git clone https://github.com/votre-utilisateur/station-meteo-sigfox.git
   cd station-meteo-sigfox
   ```
2. Ouvrir `src/main.ino` dans l'Arduino IDE
3. Brancher la carte **Arduino MKRFox 1200** via USB
4. Sélectionner la carte et le port dans l'IDE, puis téléverser le programme
5. Consulter les données reçues sur le [portail Sigfox Backend](https://backend.sigfox.com/)
---
## 📦 Format des messages Sigfox
Chaque message envoyé fait au maximum **12 octets** (limite Sigfox). Les données sont encodées de manière compacte avant l'envoi.
Exemple de trame :
| Octet(s) | Donnée | Résolution |
|---|---|---|
| 0–1 | Température | 0.1 °C |
| 2 | Humidité | 1 % |
| 3–4 | Pression | 1 hPa |
| 5 | Pluie | 0 = sec / 1 = pluie |
| 6–7 | Luminosité | 1 lux |
| 8–9 | Distance | 1 cm |
---
## 🔌 Schéma de câblage
> *(Voir `docs/schema_cablage.png`)*
Les capteurs communiquent avec l'Arduino via les protocoles suivants :
- **I2C** : BME280, BH1750
- **Analogique** : Capteur de pluie
- **Numérique (GPIO)** : Capteur ultrason (Trigger / Echo)
---
## 📊 Visualisation des données

Les données peuvent être consultées et interprétées via :
- Le **Sigfox Backend** (portail officiel)
- Des plateformes tierces comme **Ubidots**, **ThingSpeak** ou **Node-RED** via les callbacks Sigfox
---
## 🤝 Contribution
Les contributions sont les bienvenues ! Pour proposer une amélioration :

1. Forker le dépôt
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Committer vos changements (`git commit -m 'Ajout fonctionnalité X'`)
4. Pusher la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request
--
## 📄 Licence

Ce projet est distribué sous licence **MIT**. Voir le fichier [LICENSE](LICENSE) pour plus de détails.
---

## ✉️ Contact

Pour toute question ou suggestion, ouvrir une **issue** sur ce dépôt GitHub.

