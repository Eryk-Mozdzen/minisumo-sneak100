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

uint16_t adc = 0;
uint16_t analog = 0;
float alpha = 0.1;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);

  Serial.begin(115200);
  fdevopen(put_char, get_char);
}

void loop() {

  uint16_t adc_curr = analogRead(A0);
  analog = 0.9*analog + 0.1*analogRead(A1);
  
  adc = (1.f-alpha)*adc + alpha*adc_curr;

  digitalWrite(13, (adc<analog));
  
  float vol = (adc/1024.f)*5.f;

  printf("In:\t%u\tADC:\t%u\tVoltage:\t%s\tOutput:\t%u\n", analog, adc, String(vol).c_str(), (adc<analog));

  delay(10);

}
