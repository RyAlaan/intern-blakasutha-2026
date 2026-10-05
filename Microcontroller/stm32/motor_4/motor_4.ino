// -- kanan depan (1)
#define dgl_fr PA2
#define alg_fr PB8

// -- kiri depan (2)
#define dgl_fl PA3
#define alg_fl PB7

// -- kiri belakang (3)
#define dgl_bl PA4
#define alg_bl PB6

// -- kanan belakang (4)
#define dgl_br PA5
#define alg_br PB9

// -- Simple Movement
void maju();
void mundur();
void kanan();
void kiri();
void stop();

// -- Diagonal Movement
void diag_majuKanan();
void diag_majuKiri();
void diag_mundurKanan();
void diag_mundurKiri();


void setup()
{
  pinMode(dgl_fr, OUTPUT);
  pinMode(alg_fr, OUTPUT);
  pinMode(dgl_fl, OUTPUT);
  pinMode(alg_fl, OUTPUT);
  pinMode(dgl_br, OUTPUT);
  pinMode(alg_br, OUTPUT);
  pinMode(dgl_bl, OUTPUT);
  pinMode(alg_bl, OUTPUT);
  Serial.begin(115200);
}



void loop()
{
  if(Serial.available()>0)
  {
    char input=(char)Serial.read();

    switch(input)
    {
      case 'q':
        diag_majuKiri();
        break;

      case 'w':
        maju();
        break;

      case 'e':
        diag_majuKanan();
        break;

      case 'a':
        kiri();
        break;

      case 's':
        stop();
        break;

      case 'd':
        kanan();
        break;

      case 'z':
        diag_mundurKiri();
        break;

      case 'x':
        mundur();
        break;

      case 'c':
        diag_mundurKanan();
        break;
    }
  }
}

//HIGH=CW/Kanan;
//LOW=CCW/Kiri;
//Relatif depan roda;

void maju()
{
  digitalWrite(dgl_fr, LOW);
  analogWrite(alg_fr, 150);

  digitalWrite(dgl_fl, HIGH);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, LOW);
  analogWrite(alg_br, 150);

  digitalWrite(dgl_bl, HIGH);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void mundur()
{
  digitalWrite(dgl_fr, HIGH);
  analogWrite(alg_fr, 150);

  digitalWrite(dgl_fl, LOW);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, HIGH);
  analogWrite(alg_br, 150);

  digitalWrite(dgl_bl, LOW);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void kanan()
{
  digitalWrite(dgl_fr, LOW);
  analogWrite(alg_fr, 150);

  digitalWrite(dgl_fl, LOW);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, HIGH);
  analogWrite(alg_br, 150);

  digitalWrite(dgl_bl, HIGH);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void kiri()
{
  digitalWrite(dgl_fr, HIGH);
  analogWrite(alg_fr, 150);

  digitalWrite(dgl_fl, HIGH);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, LOW);
  analogWrite(alg_br, 150);

  digitalWrite(dgl_bl, LOW);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void stop()
{
  analogWrite(alg_fr, 150);
  analogWrite(alg_fl, 150);
  analogWrite(alg_br, 150);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void diag_majuKanan()
{
  analogWrite(alg_fr, 0);

  digitalWrite(dgl_fl, LOW);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, HIGH);
  analogWrite(alg_br, 150);

  AnalogWrite(alg_bl, 0);
  delay(250);
}

void diag_majuKiri()
{
  digitalWrite(dgl_fr, HIGH);
  analogWrite(alg_fr, 150);

  analogWrite(alg_fl, 0);

  analogWrite(alg_br, 0);

  digitalWrite(dgl_bl, LOW);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void diag_mundurKanan()
{
  digitalWrite(dgl_fr, LOW);
  analogWrite(alg_fr, 150);

  analogWrite(alg_fl, 0);

  analogWrite(alg_br, 0);

  digitalWrite(dgl_bl, HIGH);
  AnalogWrite(alg_bl, 150);
  delay(250);
}

void diag_mundurKiri()
{
  analogWrite(alg_fr, 0);

  digitalWrite(dgl_fl, HIGH);
  analogWrite(alg_fl, 150);

  digitalWrite(dgl_br, LOW);
  analogWrite(alg_br, 150);

  AnalogWrite(alg_bl, 0);
  delay(250);
}