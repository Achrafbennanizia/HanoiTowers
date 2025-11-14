# 🏰 Türme von Hanoi – Qt Widgets Anwendung

Eine interaktive Visualisierung des klassischen **Türme von Hanoi** Problems, vollständig implementiert in **C++** mit **Qt 6 Widgets**.  
Das Projekt demonstriert Rekursion, objektorientierte Modellierung, MVC-Strukturierung und einfache Animationen in einer grafischen Benutzeroberfläche.

---

## 📌 Features

- 🎨 **Grafische Darstellung** von drei Pflöcken + variabler Anzahl farbiger Scheiben
- 🔁 **Rekursive Lösung** der Türme-von-Hanoi-Aufgabe
- ▶️ **Schrittweise Animation** der Züge
- ⚙️ **Einstellungsfenster**:
  - Anzahl der Scheiben (1–12)
  - Dauer pro Zug (100–5000 ms)
- 🧭 **Steuerbuttons**:
  - **Neu** – Startzustand neu aufbauen
  - **Start** – Animation abspielen
  - **Pause** – Animation pausieren / fortsetzen
  - **Beenden** – Anwendung schließen
- 📊 **Statuszeile**:
  - Scheibenzahl
  - Anzahl bisheriger Züge
  - Zustand (bereit, läuft, pausiert, fertig)
- 🧹 **Saubere Architektur**:
  - Model: reine Logik in `HanoiGame`, `Disk`, `Peg`, `Move`
  - View: `QGraphicsScene` + `QGraphicsView`
  - Controller: `MainWindow`

---

## 📁 Projektstruktur
```bash
HanoiTowers/
│
├── main.cpp
│
├── mainwindow.h
├── mainwindow.cpp
│
├── hanoigame.h
├── hanoigame.cpp
│
├── disk.h
├── peg.h
├── move.h
│
├── settingsdialog.h
├── settingsdialog.cpp
│
└── CMakeLists.txt
```
---

## 🧠 Software-Architektur

Das Projekt folgt einem **MVC-inspirierten Aufbau**:

### **Model**

- `HanoiGame` generiert rekursiv die gesamte Zugliste
- `Disk`, `Peg`, `Move` bilden die reine Datenstruktur
- keine Qt-Abhängigkeit → sauberer Kern

### **View**

- `QGraphicsScene` zeichnet Pflöcke + Scheiben
- Farben, Größen, Positionen werden automatisch bestimmt

### **Controller**

- `MainWindow` steuert:
  - Animation (QTimer)
  - Benutzerinteraktionen
  - Menü + Button-Events
  - Statusleiste

### **Einstellungen**

- `SettingsDialog` ermöglicht Änderungen an:
  - Scheibenzahl
  - Animationsgeschwindigkeit

---

## 🚀 Installation

### Voraussetzungen

- Qt 6 (Widgets-Modul)
- CMake ≥ 3.16
- C++ Compiler (Clang, GCC, MSVC)

### Build-Anleitung

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
Starten
```bash
./HanoiTowers
```
Unter macOS erscheint eine .app in build/.

### 🎯 Funktionsweise der Rekursion
Der Algorithmus entspricht der klassischen Definition:
bewege(n-1, von, nach, hilf)
bewege(1, von, hilf, nach)
bewege(n-1, hilf, von, nach)
Dies führt zu (2^n – 1) Zügen.
### 🛠 Erweiterungsmöglichkeiten
QPropertyAnimation für geschmeidige Bewegungsbahnen
Soundeffekte bei Bewegungen
Highscore-System / Anzahl benötigter Züge
Undo/Redo-System
3D-Version (Qt Quick 3D)
