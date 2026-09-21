int pot = A0;
int led[6] = {5, 6, 3, 2, 7};

void setup()
{
  Serial.begin(115200);
   for (int i =0; i <= 5; i++){
        pinMode(led[i], OUTPUT);
    }
  pinMode(pot, INPUT);
}

int map() {
  
}

void loop()
{
  int val = analogRead(pot);
  int maping = map(val, 0, 1023, 0, 255);

  if (maping >= 1 && maping <= 51)
    analogWrite(led[0], maping);
  else if (maping >= 52 && maping <= 102)
      analogWrite(led[1], maping);
   else if (maping >= 103 && maping <= 153)
      analogWrite(led[2], maping);
   else if (maping >= 154 && maping <= 204)
      analogWrite(led[3], maping);
   else if (maping >= 105 && maping <= 255)
      analogWrite(led[4], maping);
    else {
    for (int i =0; i <= 5; i++){
      analogWrite(led[i], 0);
    }
  }
    
  delay(100);
}