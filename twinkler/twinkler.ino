// Pins

//musical fun buzzer game with happy birthday sound and twinker sound 


const int buzzer1 = 8;  // Small buzzer
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;

// Frequencies of notes (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494.
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880

// ---------- SONGS ---------- //

// Happy Birthday
int melody1[] = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};
int durations1[] = {
  4,4,2,2,2,1,
  4,4,2,2,2,1,
  4,4,2,2,2,2,1,
  4,4,2,2,2,1
};
int length1 = sizeof(melody1) / sizeof(melody1[0]);

// Meow Meow TikTok (simplified)
int melody2[] = {
  NOTE_E5, NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_D5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_G5
};
int durations2[] = {
  4,4,4,4,4,4,2,
  4,4,4,4,4,2
};
int length2 = sizeof(melody2) / sizeof(melody2[0]);

// Twinkle Twinkle Little Star
int melody3[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};
int durations3[] = {
  4,4,4,4,4,4,2,
  4,4,4,4,4,4,2
};
int length3 = sizeof(melody3) / sizeof(melody3[0]);

// ---------- FUNCTIONS ---------- //
void playSong(int melody[], int durations[], int length) {
  for (int i = 0; i < length; i++) {
    int noteDuration = 1000 / durations[i];

    // Both buzzers play the same note
    tone(buzzer1, melody[i], noteDuration);

    // LED pattern
    if (i % 3 == 0) {
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
    }
    else if (i % 3 == 1) {
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
    }
    else {
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
    }

    delay(noteDuration * 1.3);
    noTone(buzzer1);
  }
  
  // All LEDs off after song
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  delay(1500);
}

void setup() {
  pinMode(buzzer1, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  playSong(melody1, durations1, length1); // Happy Birthday
  playSong(melody2, durations2, length2); // Meow Meow TikTok
  playSong(melody3, durations3, length3); // Twinkle Twinkle
}
