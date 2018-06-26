/**
 * @file sketch_may18a.ino
 * @brief Written for SIA 2017/2018 
 * 
 * Dieser Code soll auf dem ArduinoUNO im Hauptfahrzeug laufen, 
 * die Kommunikation mit der <b>Fernsteuerng</b> und dem 
 * ArduinoNANO übernehmen. Zusätzlich sollen hier alle
 * Fahrfunktionen wie Autonomes-Fahren integriert werden.
 * 
 * @warning Da WIP nicht vollständig im Doxygen-Standard dokumentiert
 * 
 * @version 0.1.0
 * 
 * @author ZetShock
 * @author eagleSIA
 * 
 */

/* Anfang -- Macro definitionen für eBoard.h */

#define PREPROCESS_DEBUG 0x1      /* Aktiviere Preprocessor Debug */
#define EBOARD_BLUETOOTH 0x1      /* Aktiviere Bluetooth Funktionen */
#define PIN_BLUETOOTH_STATE 9     /* Setze Bluetooth STATE Pin gleich dem RX Pin => Deaktiviert */
#define PIN_BLUETOOTH_RX 9        /* Setze Bluetooth RX Pin auf 9 (10 blockiert durch SPI) */
#define PIN_BLUETOOTH_TX 11       /* Setze Bluetooth TX Pin auf 11 */
#define EBOARD_DEBUG_SPEED 38400  /* Setze Debug-Geschwindigkeit auf 38400 (unabhängig von Bluetooth) => 38400 im Seriellen Monitor */ 
#define EBOARD_CHECK_PINS 0x0     /* Deaktiviere Pin-Kontrollen */
#define EBOARD_CHECK_PINS_PWM 0x0 /* Deaktiviere PWM-Pin-Kontrollen */

/* Ende   -- Macro definitionen für eBoard.h */

#include <eBoard.h>

SoccerBoard board; /* Das SoccerBoard objekt */
// String endCommand; /* Entfernt => Obsolet */

// int regel = 0; /* Entfernt => Obsolet */
/* Anfang -- main - Funktion */
int main() {
    //int regel = 0; /* Entfernt => Obsolet */

    /* INFO: RB14Scan sollte das gleiche machen - aufm global Scope */ 

    SoftwareSerial BTSerial(9, 11);
    BTSerial.begin(19200);
    
    pinMode(PIN_MOTOR_DIR, OUTPUT); /* Sollte eigentlich auch überflüssig sein */ 

    /* 
     * Der Idle am Anfang um zu Warten bis das smart servo shield ansprechbar ist
     * Diese Zeit kann genutzt werden!
     */
    for(int i = 0; i  < 200; i++) {
        board.motor(1,150); /* Linker  Servo - Nicht verifiziert => <b>testen</b> */ 
        board.motor(2,150); /* Rechter Servo - Nicht verifiziert => <b>testen</b> */ 
        delay(10); /* Wartet insgesamt 2 Sekunden - Verkürzen? */
    }

    
    /*
     * ENDLOSSCHLEIFE - Abbruch einbauen ?
     * > Notaus ? 
     */
    for (;;) {

        /* lesen ob die Fernbedienung etwas sendet - 64 byte Buffer */
        int Command = BTSerial.read(); /* INFO Man kann int Command auch rausziehen damit das nicht jedesmal gemacht wird */
        
        if (Command >= 0) { /* Wenn etwas empfangen wurde... */ 

            Serial.println(Command); /* DEBUG */
            Serial.println(); /* DEBUG */

            /* 0-20 wird als Geschwindigkeit interpretiert - 10 ist hier stillstand */
            if (Command < 21) {
                board.motor(0, (Command - 10) * 20); /* INFO: Dass das Fahren nicht funktioniert hat lag an einem cast bug ^^ */ 
                digitalWrite(PIN_MOTOR_DIR, Command < 10); /* Werte kleiner 10 werden als 'rückwärts' interpretiert - Obsolet da in motor integiert */

            }
            /* 29-31 wird als Lenkwinkel interpretiert - 30 ist hier die Mitte, 31 Rechts, 30 Links */
            else if (Command > 28 && Command < 32) {
                board.motor(1,-(Command-31)*30 + 120);
                board.motor(2,-(Command-31)*30 + 120);
            }
            /* Alles andere resultiert in einem Anhalten */
            else 
                board.motor(0, 0);
            }
        }
    }
  
}
/* Ende   -- main - Funktion */

/* Entfernt - Alte Regel-Verwaltung */
