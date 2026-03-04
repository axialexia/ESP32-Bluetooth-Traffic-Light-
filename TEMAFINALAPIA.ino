#include <Arduino.h>
#include <BluetoothSerial.h>

#define A 18
#define B 19
#define C 5
#define D 15
#define E 2
#define F 21
#define G 13
#define DP 4
#define DIGIT1 22
#define DIGIT2 23
#define MAX_TIME 10
const int LED1 = 0;
const int LED2 = 16;
const int LED3 = 17;
BluetoothSerial ESP_BT;
String incoming;
void setup()
{
  Serial.begin(115200);
  pinMode(A, OUTPUT);      // A
  pinMode(B, OUTPUT);      // B
  pinMode(C, OUTPUT);      // C
  pinMode(D, OUTPUT);      // D
  pinMode(E, OUTPUT);      // E
  pinMode(F, OUTPUT);      // F
  pinMode(G, OUTPUT);      // G
  pinMode(DP, OUTPUT);     // DP
  pinMode(DIGIT1, OUTPUT); // DIGIT1
  pinMode(DIGIT2, OUTPUT); // DIGIT2
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  ESP_BT.begin("SEMAFOR");
  Serial.println("Bluetooth Device is Ready to Pair");
}

void afisareStart() {
  // Afișează 'S' pe primul digit
digitalWrite(DIGIT1,LOW); //DIGIT1
digitalWrite(DIGIT2,HIGH); //DIGIT2
digitalWrite(A,HIGH); //a
digitalWrite(B,LOW); //b
digitalWrite(C,HIGH); //c
digitalWrite(D,HIGH); //d
digitalWrite(E,LOW); //e
digitalWrite(F,HIGH); //f
digitalWrite(G,HIGH); // g
digitalWrite(DP,LOW); // DP
delay(5);
// Afișează 't' pe al doilea digit
digitalWrite(DIGIT1,HIGH); //DIGIT1
digitalWrite(DIGIT2,LOW); //DIGIT2
digitalWrite(A,LOW); //a
digitalWrite(B,LOW); //b
digitalWrite(C,LOW); //c
digitalWrite(D,HIGH); //d
digitalWrite(E,HIGH); //e
digitalWrite(F,HIGH); //f
digitalWrite(G,HIGH); // g
delay(5);
digitalWrite(DP,LOW); // DP
}

void afisareintermediar()
{
  // Afișează 'I' pe primul digit
digitalWrite(DIGIT1,LOW); //DIGIT1
digitalWrite(DIGIT2,HIGH); //DIGIT2
digitalWrite(A,LOW); //a
digitalWrite(B,HIGH); //b
digitalWrite(C,HIGH); //c
digitalWrite(D,LOW); //d
digitalWrite(E,LOW); //e
digitalWrite(F,LOW); //f
digitalWrite(G,LOW); // g
digitalWrite(DP,LOW); // DP
delay(5);
// Afișează 'n' pe al doilea digit
digitalWrite(DIGIT1,HIGH); //DIGIT1
digitalWrite(DIGIT2,LOW); //DIGIT2
digitalWrite(A,LOW); //a
digitalWrite(B,LOW); //b
digitalWrite(C,HIGH); //c
digitalWrite(D,LOW); //d
digitalWrite(E,HIGH); //e
digitalWrite(F,LOW); //f
digitalWrite(G,HIGH); // g
digitalWrite(DP,LOW); // DP
delay(5);
}

void afisareStop()
{
  // Afișează 'S' pe primul digit
digitalWrite(DIGIT1,LOW); //DIGIT1
digitalWrite(DIGIT2,HIGH); //DIGIT2
digitalWrite(A,HIGH); //a
digitalWrite(B,LOW); //b
digitalWrite(C,HIGH); //c
digitalWrite(D,HIGH); //d
digitalWrite(E,LOW); //e
digitalWrite(F,HIGH); //f
digitalWrite(G,HIGH); // g
digitalWrite(DP,LOW); // DP
delay(5);
// Afișează 'p' pe al doilea digit
digitalWrite(DIGIT1,HIGH); //DIGIT1
digitalWrite(DIGIT2,LOW); //DIGIT2
digitalWrite(A,HIGH); //a
digitalWrite(B,HIGH); //b
digitalWrite(C,LOW); //c
digitalWrite(D,LOW); //d
digitalWrite(E,HIGH); //e
digitalWrite(F,HIGH); //f
digitalWrite(G,HIGH); // g
digitalWrite(DP,LOW); // DP
delay(5);
}

void OFF()
{
  // Stinge mesajul de pe cele 7 segmente
digitalWrite(DIGIT1,LOW); //DIGIT1
digitalWrite(DIGIT2,HIGH); //DIGIT2
digitalWrite(A,LOW); //a
digitalWrite(B,LOW); //b
digitalWrite(C,LOW); //c
digitalWrite(D,LOW); //d
digitalWrite(E,LOW); //e
digitalWrite(F,LOW); //f
digitalWrite(G,LOW); // g
digitalWrite(DP,LOW); // DP
delay(5);
digitalWrite(DIGIT1,HIGH); //DIGIT1
digitalWrite(DIGIT2,LOW); //DIGIT2
digitalWrite(A,LOW); //a
digitalWrite(B,LOW); //b
digitalWrite(C,LOW); //c
digitalWrite(D,LOW); //d
digitalWrite(E,LOW); //e
digitalWrite(F,LOW); //f
digitalWrite(G,LOW); // g
digitalWrite(DP,LOW); // DP
delay(5);
}

void loop()
{
  if (ESP_BT.available())
  {
    char functie = ESP_BT.read();
    Serial.print("Received:");
    Serial.println(functie); // folosim pt a reusi sa citeasca separat comenzile de "VERDE", "GALBEN", "ROSU"
    if (functie != '\n')
    {
      incoming += functie;
    }
    else
    {
      incoming.trim();
      if (incoming.equals("VERDE"))
      {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        ESP_BT.println("Este verde, puteti traversa strada!"); // apare culoarea verde

        // Aprindere start
         for (int i = 0; i < 1000; i++) 
         { // Afișează 'St' timp de câteva secunde
          afisareStart();
         }
        OFF();
        
        //Folosirea LED ului suplimentar
        for (int i = 0; i < 3; ++i)
        {
          int frequency = 1000 / (i + 1); // 0.5 Hz, 1 Hz, 1.5 Hz
          for (int j = 0; j < 5; ++j)
          {
            digitalWrite(LED3, HIGH);
            delay(frequency / 2);
            digitalWrite(LED3, LOW);
            delay(frequency / 2);
          }     
        }
           //Stingerea LED ului verde si al celui suplimentar
           digitalWrite(LED1, LOW);
           digitalWrite(LED2, LOW);
           
      }

      if (incoming.equals("GALBEN"))
      {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        ESP_BT.println("Este galben"); // apare culoarea galben

         for (int i = 0; i < 1000; i++) 
         { // Afișează 'In' timp de câteva secunde
          afisareintermediar();
         }
        delay(1500);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        OFF();
      }

      if (incoming.equals("ROSU"))
      {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);

        ESP_BT.println("Este rosu, asteptati sa se faca verde"); // apare culoarea rosu

         for (int i = 0; i < 1000; i++) 
         { // Afișează 'Sp' timp de câteva secunde
           afisareStop();
         }
        OFF();

        // LED suplimentar
        for (int i = 0; i < 3; ++i)
        {
          int frequency = 1000 / (i + 1); // 0.5 Hz, 1 Hz, 1.5 Hz
          for (int j = 0; j < 5; ++j)
          {
            digitalWrite(LED3, HIGH);
            delay(frequency / 2);
            digitalWrite(LED3, LOW);
            delay(frequency / 2);
          }
        }
       
        // off led
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
      
      }
      incoming = " ";
    }
  }
}
