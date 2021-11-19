void setup() {
  // put your setup code here, to run once:
  // initialize digital pin PB1 as an output
     pinMode(PC13, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite (PC13, HIGH); // turn the LED on by making the voltage HIGH
  delay(1000);              // wait for a second
  digitalWrite (PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
