#undef printf

#include<stdio.h>
#include<stdint.h>

int get_char(FILE *fp) {
  while(!(Serial.available()));
  return (Serial.read());
}

int put_char(char c, FILE *fp) {
  Serial.write(c);
  return c;
}

void setup() {
  pinMode(A0, INPUT);

  Serial.begin(115200);
  fdevopen(put_char, get_char);
}

void loop() {

  uint16_t adc = analogRead(A0);
  float vol = (adc/1024.f)*5.f;

  printf("ADC:\t%u\tVoltage:\t%s\tOutput:\t%u\n", adc, String(vol).c_str(), vol<3.25f);

  delay(100);

}
