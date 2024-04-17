#include <Wire.h>

// LED Pins
const int pinR = 6;
const int pinG = 3;
const int pinB = 5;

// RGB Werte fuer LED
int r = 0;
int g = 0;
int b = 0;


void setup() {
    Serial.begin(9600);

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);

    Wire.begin(0x02); // I2C als Target initialisieren
    Wire.onReceive(updateRGB); // LED mit gesendeten Werten aktualisieren
}


void loop() {
    // Reagiert nur auf Anfragen mit `Wire.onReceive` / `Wire.onRequest()`
}


// Aktualisiert RGB Werte
void updateRGB() {
    Serial.println("Update Anfrage von Master erhalten");
    if (Wire.available()) {
        // Werte auslesen (jeweils 1 byte)
        r = Wire.read();
        g = Wire.read();
        b = Wire.read();
        Serial.println("Werte erfolgreich ausgelesen");

        printRGB();
    } else {
        Serial.println("Error: Keine Daten von Master verfuegbar");
    }

    updateLED();
}


// LED Farbe an aktuelle RGB Werte anpassen
void updateLED() {
    digitalWrite(pinR, r);
    digitalWrite(pinG, g);
    digitalWrite(pinB, b);
}


// Hilfsfunktionen

// Ausgabe aktueller RGB Werte
void printRGB() {
    Serial.println("Aktuelle RGB Werte");
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
}