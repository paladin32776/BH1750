#include "Arduino.h"
#include "I2C_COMM.h"

#define BH_DEFAULT_ADDRESS 0x23
#define BH_HRES_DELAY 180
#define BH_LRES_DELAY 24

#define BH_POWER_DOWN 0x00
#define BH_POWER_ON 0x01
#define BH_RESET 0x07
#define BH_CHANGE_TIME_H_MASK 0x40
#define BH_CHANGE_TIME_L_MASK 0x60

class BH1750 : public I2C_COMM
{
  private:
    bool power_on = false;
    unsigned char mode = 0x10;  // CONT + HRES
    unsigned char mt = 69;
    void init();
    void wait();
  public:
    static unsigned const char SINGLE=0x20, CONT=0x10;
    static unsigned const char HRES=0x00, HRES2=0x01, LRES=0x03;
    BH1750();
    BH1750(unsigned char _addr);
    BH1750(unsigned char SDApin, unsigned char SCLpin);
    BH1750(unsigned char _addr, unsigned char SDApin, unsigned char SCLpin);
    void set_mode(unsigned char _mode);
    unsigned char get_mode();
    unsigned int read();
    void set_mt(unsigned char _mt);
};
