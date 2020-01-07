#include "BH1750.h"
#define PRINTBIN(Num) for (uint32_t t = (1UL<< (sizeof(Num)*8)-1); t; t >>= 1) Serial.write(Num  & t ? '1' : '0'); // Prints a binary number with leading zeros (Automatic Handling)

BH1750::BH1750(): I2C_COMM(BH_DEFAULT_ADDRESS)
{
  init();
}

BH1750::BH1750(unsigned char _addr): I2C_COMM(_addr)
{
  init();
}

BH1750::BH1750(unsigned char SDApin, unsigned char SCLpin): I2C_COMM(BH_DEFAULT_ADDRESS, SDApin, SCLpin)
{
  init();
}

BH1750::BH1750(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin): I2C_COMM(_addr, SDApin, SCLpin)
{
  init();
}

void BH1750::init()
{
  write_regbyte(BH_POWER_ON);
  power_on = true;
  mode = CONT+HRES;
  set_mode(mode);

}
void BH1750::wait()
{
  if (mode & 0x0F == LRES)
    delay(BH_LRES_DELAY);
  else
    delay(BH_HRES_DELAY);
}

void BH1750::set_mode(unsigned char _mode)
{
  mode = _mode;
  write_regbyte(mode);
  wait();
}

unsigned char BH1750::get_mode()
{
  return mode;
}

unsigned int BH1750::read()
{
  if (mode & 0xF0 == SINGLE)
  {
    write_regbyte(BH_POWER_ON);
    write_regbyte(mode);
    wait();
  }
  unsigned int lx = read_word_no_reg();
  if (mode & 0x0F == HRES)
    lx = lx * 69/(1.2*mt);
  else if (mode & 0x0F == HRES2)
    lx = lx * 69/(1.2*mt*2);
  else
    lx = lx * 69/(1.2*mt);
  return lx;
}

void BH1750::set_mt(unsigned char _mt)
{
  write_regbyte(BH_CHANGE_TIME_H_MASK + (_mt>>5));
  write_regbyte(BH_CHANGE_TIME_L_MASK + (_mt && 0x1F));
}
