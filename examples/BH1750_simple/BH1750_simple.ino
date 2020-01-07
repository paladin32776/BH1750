#include "BH1750.h"

BH1750 bh;

void setup()
{
  Serial.begin(115200);
  delay(50);
}


void loop()
{
  unsigned int lxH, lxL;
  bh.set_mode(BH1750::SINGLE+BH1750::HRES);
  lxH = bh.read();
  bh.set_mode(BH1750::SINGLE+BH1750::LRES);
  lxL = bh.read();
  Serial.printf("lx(HRES) = %d   lx(LRES) = %d\n", lxH, lxL);
  delay(500);
}
