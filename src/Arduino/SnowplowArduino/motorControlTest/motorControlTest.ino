int a, p; 

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 pinMode(10,OUTPUT);
 digitalWrite(10,LOW);
 a = 1;
 p = 1; 
}

void loop() {
  // put your main code here, to run repeatedly: 
  analogWrite(10, a);
  if (a == 255 || a == 0)
  { p *= -1;}
  
  a += p; 
  
  delay(50);  
}
