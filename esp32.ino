void setup() {
  Serial.begin(115200); // komunikasi Serial dengan kecepatan transfer data 115200 bps
}

void loop() {
  Serial.println("Hello World"); // mengirimkan teks "Hello World" ke Serial Monitor
  neopixelWrite(RGB_BUILTIN, 255, 0, 0); // LED NeoPixel nyala (warna merah)
  delay(100); //jeda dalam 100 milidetik
  neopixelWrite(RGB_BUILTIN, 0, 255, 0); // LED NeoPixel nyala (warna hijau)
  delay(100); //jeda dalam 100 milidetik
  neopixelWrite(RGB_BUILTIN, 0, 0, 255); // LED NeoPixel nyala (warna biru)
  delay(100); //jeda dalam 100 milidetik
}