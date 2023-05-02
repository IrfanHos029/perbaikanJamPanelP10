#include <EEPROM.h>
#include <Wire.h>

#define alamatRTC 0x68
#define alamatEEPROMCekToken 0
#define tokenRTC 0xAA //<== rubah token jika ingin nilai baru

String strNamaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

void setup() {
  Serial.begin(9600);
  Serial.println("Set waktu RTC otomatis dengan arduino");
  Serial.println("IRFAN ARDIANSYAH");
  Serial.println();

  Wire.begin();
  if (EEPROM.read(alamatEEPROMCekToken) != tokenRTC)
  {
    //Waktu compiler
    char bulan[12];
    byte indexBulan;
    int jam, menit, detik, tanggal, tahun;

    char *namaBulan[12] = {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun",
      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    sscanf(__TIME__, "%d:%d:%d", &jam, &menit, &detik);
    sscanf(__DATE__, "%s %d %d", bulan, &tanggal, &tahun);
    for (indexBulan = 0; indexBulan < 12; indexBulan++) {
      if (strcmp(bulan, namaBulan[indexBulan]) == 0)
        break;
    }
    tulisRTC(tanggal, indexBulan + 1, tahun-2000, jam, menit, detik);
    EEPROM.write(alamatEEPROMCekToken, tokenRTC);
    Serial.println("RTC sudah otomatis di setting (Sekali saja)");
  }
}

void loop() {
  uint16_t tahun;
  byte hari, tanggal, bulan, jam, menit, detik;
  
  bacaRTC(hari, tanggal, bulan, tahun, jam, menit, detik);
  Serial.print(strNamaHari[1]);
  Serial.print(", ");
  Serial.print(tanggal);
  Serial.print('/');
  Serial.print(bulan);
  Serial.print('/');
  Serial.print(tahun);
  Serial.print(' ');
  Serial.print(jam);
  Serial.print(':');
  Serial.print(menit);
  Serial.print(':');
  Serial.print(detik);
  Serial.println(' ');

  //while (1);
}
//Fungsi umum yang juga ada di dalam library DS1307, DS3231 (disini digunakan untuk menghemat memory)
void tulisRTC(byte tanggal, byte bulan, uint16_t tahun, byte jam, byte menit, byte detik)
{
  Wire.beginTransmission(alamatRTC);
  Wire.write((byte)0);
  Wire.write((byte)Convert_IntToBCD(detik));
  Wire.write((byte)Convert_IntToBCD(menit));
  Wire.write((byte)Convert_IntToBCD(jam)); //Make sure clock is still 24 Hour
  Wire.write((byte)hariDariTanggal(tanggal, bulan, tahun));
  Wire.write((byte)Convert_IntToBCD(tanggal));
  Wire.write((byte)Convert_IntToBCD(bulan));
  Wire.write((byte)Convert_IntToBCD(tahun));
  Wire.endTransmission();
}

void bacaRTC(byte &hari, byte &tanggal, byte &bulan, uint16_t &tahun, byte &jam, byte &menit, byte &detik)
{
  Wire.beginTransmission(alamatRTC);
  Wire.write((byte)0x00);
  Wire.endTransmission();

  Wire.requestFrom(alamatRTC, 8);
  detik = Convert_BCDToInt(Wire.read());
  menit = Convert_BCDToInt(Wire.read());
  jam = Convert_BCDToInt(Wire.read());
  hari =  Wire.read();
  tanggal = Convert_BCDToInt(Wire.read());
  bulan = Convert_BCDToInt(Wire.read());
  tahun = Convert_BCDToInt(Wire.read()) + 2000;
}

//max hex 0x63 / bcd 0x99
uint8_t Convert_IntToBCD(uint8_t DecimalValue)
{
  return DecimalValue + 6 * (DecimalValue / 10);
}

uint8_t Convert_BCDToInt(uint8_t BCDValue)
{
  return BCDValue - 6 * (BCDValue >> 4);
}

//tanggal mulai dari 1
//bulan mulai dari 1
//tahun dua digit
//minggu = 1, sabtu = 7
//basis 1 Januari 2000
uint16_t jumlahHariPerBulanHijriah[] = {0, 30, 59, 89, 118, 148, 177, 207, 236, 266, 295, 325, 354};
uint16_t jumlahHariPerBulanMasehi[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
double tahunBulan = 354.367068;

byte hariDariTanggal(byte tanggal, byte bulan, uint16_t tahun)
{
  if (tahun >= 2000)
    tahun -= 2000;

  uint32_t jumlahHari = tahun * 365;
  uint16_t tahunKabisat = tahun / 4;
  for (byte i = 0; i < tahun; i++)
  {
    if (!(i % 4))
    {
      jumlahHari++;
    }
  }
  jumlahHari += jumlahHariPerBulanMasehi[bulan - 1];
  if ( (bulan >= 2) && !(tahun % 4))
  {
    jumlahHari++;
  }
  jumlahHari += tanggal;
  return ((jumlahHari + 5) % 7) + 1;
}
