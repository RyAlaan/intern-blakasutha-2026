void setup() 
{
  serial.baud(115200);
}

void loop() 
{
  while (serial.avaibility()>0) 
  {
    int buffer=serial.read();
    int massagePos=0;
    char massage[];

    if (buffer!='\n') 
    {
      massage[massagePos]=buffer;
      massagePos++;
    } else {
      serial.println(massage);
      massagePos=0;
    }
  }
}