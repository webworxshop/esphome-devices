
#include "esphome.h"
#include "SPI.h"
using namespace esphome;

class SparkfunSerial7Segment : public Component
{
    private:
        static const uint8_t CS_PIN = 15;
        SPISettings *spi_settings = nullptr;

    public:
        void setup() override
        {
            delay(1000); // allow display to boot
            spi_settings = new SPISettings(250000, MSBFIRST, SPI_MODE0);
            pinMode(CS_PIN, OUTPUT);
            SPI.begin();

            // blank the 7 segment display
            blank();
        }

        void write(const char *data, uint8_t len)
        {
            SPI.beginTransaction(*spi_settings);
            digitalWrite(CS_PIN, LOW);
            for(uint8_t i = 0; i < len; i++)
            {
                SPI.transfer(data[i]);
            }
            digitalWrite(CS_PIN, HIGH);
            SPI.endTransaction();
        }

        void blank()
        {
            write("\x76", 1);
            //write("\x77\x00", 2);
        }

        void colon()
        {
            write("\x77\x10", 2);
        }

        void cursor(uint8_t pos)
        {
            char cmd[2];
            cmd[0] = 0x79;
            cmd[1] = pos;
            write((const char*)cmd, 2);
        }

        void loop() override
        {
        }
};
