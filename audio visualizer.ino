int micPin = A0;

const int sampleWindow = 50;
unsigned int sample;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(micPin, INPUT);
  for (int i = 0; i < 10; i++) {  //Setter opp alle LED
    pinMode(i+2, OUTPUT); 
  }
  

}

void loop() {
  // put your main code here, to run repeatedly:
   unsigned long startMillis = millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   int volts = ((peakToPeak * 3.3) / 0.1024)/32.23;  // convert to volts

   Serial.println(volts);

   for (int j = 0; j < 10; j++) {
     if (volts >= j) {
      digitalWrite(j+2, HIGH);
     }
   else {
      digitalWrite(j+2, LOW);
   }
   }
}
