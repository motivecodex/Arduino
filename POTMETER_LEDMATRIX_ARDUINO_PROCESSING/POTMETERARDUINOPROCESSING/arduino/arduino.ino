int A0VAL, A1VAL;

void setup ()
{
  Serial.begin(9600);
}

void loop ()
{
  // Write to processing
  A0VAL = analogRead(A0);
  A1VAL = analogRead(A1);
  Serial.write((byte *) &A0VAL, 2);
  Serial.write((byte *) &A1VAL, 2);
  delay(200);
}
