
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int input = analogRead(A0); 
  if (input >= 0){
  Serial.write(input/4);}
  delay(1);
}
