double channel; 
double value;
void setup() {
  pinMode(2,INPUT);
  //Setup serial connection
  Serial.begin(9600); 
}
 
void loop() {
  value = digitalRead(2);
  channel = pulseIn(2,LOW);
  Serial.println(channel); 
  delay(100);
}