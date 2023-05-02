/*************************************************************************************
JAM_DIGITAL_MODIF 64 X 16
28/02/2021
**************************************************************************************/
#include <SPI.h>
#include <DMD3asis.h>
#include <font/KecNumber.h>
#include <font/BigNumber.h>
#include <font/Font4x6.h>
#include <font/SystemFont5x7.h>
#include <font/Font3x5.h>
#include <font/EMSans8x16.h>
#include <font/Calibri14.h>

#include <DS3231.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <MemoryFree.h>

#define BUZZ    2 

#define Font0 Font4x6
#define Font3 BigNumber
#define Font2 Font3x5
#define Font1 SystemFont5x7
#define Font4 KecNumber
#define Font5 EMSans8x16
#define Font6 Calibri14
    
// Object Declarations
DMD3 Disp(2,1);
char *pasar[] ={"WAGE", "KLIWON", "LEGI", "PAHING", "PON"}; 
//char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char *mounthJawa[]= {"Muharram","Shafar","Rab.awal","Rab.akhir","Jum.awal","Jum.akhir","Rajab","Sya'ban","Ramadhan","Syawal","Dzulqa'dah","Dzulhijah"};
char *sholatCall[] = {"IMSAK","SUBUH","TERBIT","DHUHA","DUHUR","ASHAR","MAGRIB","ISYA","JUM'AT"};   
//char *sholatCallDis[] = {"IMSAK","SUBUH","TERBT","DHUHA","DUHUR","ASHAR","MAGRB","ISYA","JUMAT"};  
int maxday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
RTClib          RTC;
DS3231          Clock;
char Hari[7][12] = {"MINGGU","SENIN","SELASA","RABU","KAMIS","JUM'AT","SABTU"};

//Structure of Variable 
typedef struct  // loaded to EEPROM
  {
    uint8_t state;   // 1 byte  add 0
    float   L_LA;    // 4 byte  add 1
    float   L_LO;    // 4 byte  add 5
    float   L_AL;    // 4 byte  add 9
    float   L_TZ;    // 4 byte  add 13
    uint8_t MT;      // 1 byte  add 17  // value 1-masjid  2-mushollah 3-surau 4-langgar 
    uint8_t BL;      // 1 byte  add 18
    uint8_t IH;      // 1 byte  add 19
    uint8_t SO;      // 1 byte  add 20
    uint8_t JM;      // 1 byte  add 21
    uint8_t I1;      // 1 byte  add 22
    uint8_t I4;      // 1 byte  add 23
    uint8_t I5;      // 1 byte  add 24
    uint8_t I6;      // 1 byte  add 25
    uint8_t I7;      // 1 byte  add 26
    uint8_t BZ;      // 1 byte  add 27
    uint8_t SI;      // 1 byte  add 28
    uint8_t ST;      // 1 byte  add 29
    uint8_t SU;      // 1 byte  add 30
    int8_t  CH;      //20 1 byte  add 31
    int8_t  II;      //21 1 byte  add 32
    int8_t  IS;      //22 1 byte  add 33
    int8_t  IL;      //23 1 byte  add 34
    int8_t  IA;      //24 1 byte  add 35
    int8_t  IM;      //25 1 byte  add 36
  } struct_param;

typedef struct  
  { 
    uint8_t   hD;
    uint8_t   hM;
    uint16_t  hY;
  } hijir_date;

   
// Variable by Structure     
struct_param    Prm;
hijir_date      nowH;   

// Time Variable
DateTime        now;
float           floatnow   = 0;
uint8_t         daynow     = 0;
uint8_t         ty_puasa   = 0;
uint8_t         hd_puasa   = 0; 
int8_t          SholatNow  = -1;
boolean         jumat      = false;
boolean         azzan      = false;
uint8_t         reset_x    = 0;   
bool            state      = false;
//Other Variable
float sholatT[8]  = {0,0,0,0,0,0,0,0};
uint8_t Iqomah[8] = {0,0,0,0,0,0,0,0};

//Blue tooth Pram Receive
char        CH_Prm[155];
int         DWidth  = Disp.width();
int         DHeight = Disp.height();
boolean     DoSwap; 
int         RunSel    = 1; //
int         RunFinish = 0 ;
const byte reset = 3;
static uint16_t saveTime = 0;
bool stateBlink=false;


float latitude = -7.238816115709593;
float longitude = 112.75318149040366;
float timezone = +7;
 String inputString = "";         // a String to hold incoming data
  bool stringComplete = false;  // whether the string is complete
  int setHours,setMinutes;
  int setTgl,setBln,setThn;
  int setDay;
//=======================================
//===SETUP=============================== 
//=======================================
void setup()
  { //init comunications 
    Wire.begin();
    Serial.begin(9600);
    digitalWrite(reset,HIGH);
     pinMode(reset,OUTPUT);
     pinMode(BUZZ, OUTPUT); 
         
    // Get Saved Parameter from EEPROM   
    updateTime();
    //init P10 Led Disp & Salam
    Disp_init();
    for(int i=0;i<2;i++){
  Buzzer(1); delay(80);
  Buzzer(0); delay(80);
 }
 Buzzer(0);
 delay(1000);
  }

//=======================================
//===MAIN LOOP Function =================   
//=======================================
void loop()
  { 
    // Reset & Init Display State
    update_All_data();   //every time
    check_azzan();
    Reset(); //fungsion restart
    DoSwap  = false ;
    //fType(1);  
    Disp.clear();

    // =========================================
    // List of Display Component Block =========
    // =========================================

    anim_JG(1);                                                 // addr: 1 show date time
  //  drawHari(1); //hari
    //dwCek(TGLJAWA(),75,2,3);  //tanggalan
//    dwMrq(drawShow1(),75,2,1);
//    dwMrq(drawShow2 ,75,2,2);
    drawSide2(2);
    drawSide1(3);
    dwMrq(drawNama(),75,1,4);  //running text
    
    //drawSholat(1);
    drawAzzan(100); 
    runningAfterAdzan(101);
    // =========================================
    // Display Control Block ===================
    // =========================================
    if(RunFinish==1) {RunSel = 2; RunFinish =0;}                      //after anim 1 set anim 2
    if(RunFinish==2) {RunSel = 3; RunFinish =0;}                      //after anim 2 set anim 3
    if(RunFinish==3) {RunSel = 4; RunFinish =0;}
    if(RunFinish==4)  {RunSel = 1;  RunFinish =0;} 

    if (stringComplete) {
    if(inputString.substring(0,2) == "CK")
    {//Serial.println(inputString);
      String setJam,setMenit;
      inputString.remove(0,2);
      delay(50);
      setJam = inputString.substring(0,2);    
      setMenit = inputString.substring(3,5);
      setHours = setJam.toInt();
      setMinutes = setMenit.toInt();
      Clock.setHour(setHours);
      Clock.setMinute(setMinutes);
      inputString = "";
      stringComplete = false;
    }
    else if(inputString.substring(0,2) == "DT")
    {
      String setTgls,setBlns,setThns;
      inputString.remove(0,2);
      delay(50);
      setTgls = inputString.substring(0,2);
      setBlns = inputString.substring(2,4);
      setThns = inputString.substring(4,6);

//      Serial.println(String() + "tanggal:" + setTgls);
//      Serial.println(String() + "bulan  :" + setBlns);
//      Serial.println(String() + "tahun  :" + setThns);
      
      setTgl = setTgls.toInt();
      setBln = setBlns.toInt();
      setThn = setThns.toInt();

      Clock.setDate(setTgl);
      Clock.setMonth(setBln);
      Clock.setYear(setThn);

      inputString = "";
      stringComplete = false;
    }
    else if(inputString.substring(0,2) == "DY")
    {
      String setDays;
      inputString.remove(0,2);
      delay(50);
      setDays = inputString.substring(0,1);
      setDay = setDays.toInt();
      if(setDay > 0 && setDay < 8){  Clock.setDoW(setDay); }
      //Serial.println(String() + "hari:" + setDay);
      inputString = "";
      stringComplete = false;
    }

    
    else
    {
       inputString="";
    }
  }
    //if(RunFinish==101)  {RunSel = 1;  RunFinish =0;} 
    //if(RunFinish==4)  {RunSel = 1;  RunFinish =0;} 
    // =========================================
    // Swap Display if Change===================
    // =========================================
    if(DoSwap){Disp.swapBuffers();} // Swap Buffer if Change
  }


// =========================================
// DMD3 P10 utility Function================
// =========================================
void Disp_init() 
  { Disp.setDoubleBuffer(true);
    Timer1.initialize(2000);
    Timer1.attachInterrupt(scan);
    setBrightness(200);
    fType(1);  
    Disp.clear();
    Disp.swapBuffers();
    }

void setBrightness(int bright)
  { Timer1.pwm(9,bright);}

void scan()
  { Disp.refresh();}
  
// =========================================
// Time Calculation Block===================
// =========================================
void updateTime()
  { now = RTC.now();
    floatnow = (float)now.hour() + (float)now.minute()/60 + (float)now.second()/3600;
    daynow   = Clock.getDoW();    // load day Number
  }
  
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Buzzer(1);
    delay(50);
    Buzzer(0);
    delay(50);
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println("DONE");
    }
  }
}

void update_All_data()
  {
  uint8_t   date_cor = 0;
  updateTime();
  sholatCal();                                                // load Sholah Time                                         // check jadwal Puasa Besok
  if(floatnow>00.00) {date_cor = 1;}                     // load Hijr Date + corection next day after Mhagrib 
  nowH = toHijri(now.year(),now.month(),now.day(),date_cor);  // load Hijir Date
  
  }
  
    
void check_azzan()
  { //Check Waktu Sholat
    SholatNow  = -1;
    for(int i=0; i <=7; i++)
      {
        if (i!=0 and i!=2 and i!=3)  // bukan terbit dan bukan dhuha
          {
            if(floatnow >= sholatT[i])
              {
                SholatNow = i;
                if(!azzan and (floatnow > sholatT[i]) and (floatnow < (sholatT[i]+0.03))) 
                  { 
                    azzan =true;
                    RunSel = 100;
                  }  
              }
          }
      }
  }
