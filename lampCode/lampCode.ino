#define CHAIR_PIN 9   //doe button in D8
#define BUTTON_PIN 5  //doe button in D4


//dit stuk gaat over de db lamp
#include <Adafruit_NeoPixel.h>
#define PIN 2         // Steek de ledstrip in D2
#define NUMPIXELS 15  // aantal ledjes in je strip
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// dit stuk gaat over de stroom lamp
#define ENERGY_PIN 6  // 2e ledstrip in D6
#define NUMENERGY 15  // aantal ledjes in je strip
Adafruit_NeoPixel energy(NUMENERGY, ENERGY_PIN, NEO_GRB + NEO_KHZ800);

int motorPin = 3;  //motor transistor is connected to pin 3

bool vibrate = false;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //neem deze altijd op in je  code voor debuggen

  pinMode(CHAIR_PIN, INPUT);  //Zegt dat button de input is

  pinMode(motorPin, OUTPUT);  //zegt dat trilmotor een output is


  //lamp
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.show();   // Zet alle pixels uit
  pixels.setBrightness(10);

  //energy
  energy.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  energy.show();   // Zet alle pixels uit
  energy.setBrightness(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  // meet pressureState (zit er iemand op de stoel)
  int pressureState = 0;
  pressureState = digitalRead(CHAIR_PIN);

  // Serial.println(pressureState);

  //meet decibel en laat zien
  int decibel = 0;
  decibel = analogRead(A1);

  Serial.println(decibel);

  //meet button state (drukt iemand op de knop)
  int buttonState = 0;
  buttonState = digitalRead(BUTTON_PIN);

  // Serial.println(buttonState);



  // als er niemand zit dan moet de lamp uit zijn
  if (pressureState == HIGH) {
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      energy.setPixelColor(i, energy.Color(0, 0, 0));
    }
    pixels.show();
    energy.show();

  }

  //als de knop wel ingedrukt is moet de lamp rustgevend licht zijn
  else {

    // als het geluid harder is dan ...db zet dan alle lampjes op rood
    if (decibel >140) {

      //als de irritatie knop is ingedrukt voer dan knipper functie uit
      if (buttonState == 0) {
      blink();
      Serial.println("check1");
      }

      //maak alle lampjes rood
      for (int i = 0; i < 16; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
        energy.setPixelColor(i, energy.Color(255, 0, 0));
      }
      pixels.show();
      energy.show();
      delay(1000);

      if (vibrate == false){
      digitalWrite(motorPin, HIGH);  //vibrate
      delay(1000);                   // delay one second
      digitalWrite(motorPin, LOW);   //stop vibrating

      vibrate = true;

      }

    }


    // als het geluid niet boven ...db komt zet lamp dan weer op rust
    if (decibel < 140) {


      for (int i = 0; i < 16; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));  //blauw
        energy.setPixelColor(i, energy.Color(0, 255, 0));  //groen
      }

      pixels.show();
      energy.show();

      delay(1000);

      for (int i = 0; i < 16; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 255));  //paars
      }

      pixels.show();
      delay(1000);

      vibrate = false;
    }
  }

  // Serial.println(vibrate);
}




  //knipper functie
  void blink() {

    Serial.println("check");

    //1 keer knipper
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));  //rood
    }
    pixels.show();
    digitalWrite(motorPin, HIGH);  //vibrate
    delay(1000);

    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));  //uit
    }
    pixels.show();
    digitalWrite(motorPin, LOW);  //Stop vibrate
    delay(1000);

    //2 keer knipper
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));  //rood
    }
    pixels.show();
    digitalWrite(motorPin, HIGH);  //vibrate
    delay(1000);

    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));  //uit
    }
    pixels.show();
    digitalWrite(motorPin, LOW);  //Stop vibrate
    delay(1000);

    //3e keer knipper
    //1 keer knipper
    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));  //rood
    }
    pixels.show();
    digitalWrite(motorPin, HIGH);  //vibrate
    delay(1000);

    for (int i = 0; i < 16; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));  //uit
    }
    pixels.show();
    digitalWrite(motorPin, LOW);  //Stop vibrate
    delay(1000);
  }
