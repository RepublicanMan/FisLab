const int trig_Pin = 9;
const int echo_Pin = 8;
long durasi;
long jarak;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("tes");
  pinMode(trig_Pin, OUTPUT);
  pinMode(echo_Pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(trig_Pin,LOW);
    delayMicroseconds(2);
    digitalWrite(trig_Pin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_Pin,LOW);

    durasi = pulseIn(echo_Pin, HIGH);
    jarak = durasi*0.034/2; //menghitung jarak

    Serial.print("jarak: ");
    Serial.print(durasi);
    Serial.print(" cm");
    delay(100);
}
