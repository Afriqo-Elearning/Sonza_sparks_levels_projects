#define ldr A0
#define led 2
#define buzzer 3

const int  ldrthreshold =  300;

void setup() {
  Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  float ldrvalue = analogRead(ldr);
  if(ldrvalue > ldrthreshold){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }

  Serial.println(ldrvalue);

  // put your main code here, to run repeatedly:

}
