int alg=PB8;
int dgl=PA2;

void setup()
{
  pinMode(alg, OUTPUT);
  pinMode(dgl, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  if(Serial.available()>0)
  {
    char input=(char)Serial.read();
    
    if(input=='a')
    {
     digitalWrite(dgl, HIGH);
     analogWrite(alg, 150);
     delay(250);
    }
    else if(input=='s')
    {
      analogWrite(alg, 0);
    }
    else if(input=='d')
    {
      digitalWrite(dgl, HIGH);
      analogWrite(alg, 150);
      delay(250);
    }

    
  }
}