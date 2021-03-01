/*=============================================
 * PROGMEM DATA
 ==============================================*/
  // sholatN 9 x 8 
  const char static sholatN_E[] PROGMEM = { "IMSAK\0\0\0"
                                            "SUBUH\0\0\0" 
                                            "TERBT\0\0\0"  
                                            "DHUHA\0\0\0"   
                                            "DUHUR\0\0\0"    
                                            "ASHAR\0\0\0"   
                                            "MAGRB\0\0\0"    
                                            "ISYA\0\0\0\0"
                                            "JUMAT\0\0\0"
                                            };
  //h_month 12 x 11
  const char static h_month_E[] PROGMEM = { "MUHARRAM\0\0\0" 
                                            "SHAFAR\0\0\0\0\0"    
                                            "RAB.AWAL\0\0\0" 
                                            "RAB.AKHIR\0\0" 
                                            "JUM.AWAL\0\0\0"
                                            "JUM.AKHIR\0\0" 
                                            "RAJAB\0\0\0\0\0\0" 
                                            "SYA'BAN\0\0\0\0" 
                                            "RAMADHAN\0\0\0" 
                                            "SYAWAL\0\0\0\0\0" 
                                            "DZULQA'DAH\0" 
                                            "DZULHIJAH\0\0"};
  //m_month 12 x 10
  const char static m_month_E[] PROGMEM = { "JAN\0"      
                                            "FEB\0"       
                                            "MAR\0" 
                                            "APR\0" 
                                            "MEI\0" 
                                            "JUN\0" 
                                            "JUL\0" 
                                            "AGS\0" 
                                            "SEP\0" 
                                            "OKT\0" 
                                            "NOV\0" 
                                            "DES\0"};
  //DayName 7 x 7                                        
  const char static DayName_E[] PROGMEM = { "MINGGU\0\0\0"
                                            "SENIN\0\0"
                                            "SELASA\0" 
                                            "RABU\0\0\0" 
                                            "KAMIS\0\0" 
                                            "JUM'AT\0" 
                                            "SABTU\0\0"};

  //MT_Name 4 x 10
  const char static MT_Name_E[] PROGMEM = { "MASJID\0\0\0\0"   
                                            "MUSHOLLA\0\0"  
                                            "SURAU\0\0\0\0\0"
                                            "LANGGAR\0\0\0"};

  const char static HD_Puasa[] PROGMEM    = { 
                                            "MARI PUASA\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"   
                                            "SUDAHKAH KITA PUASA\0\0\0\0\0\0\0"  
                                            "MARI KITA PERBANYAK PUASA\0"
                                            "SELAMAT MENJALANKAN PUASA\0"
                                            };
                                            
  const char static TY_Puasa[] PROGMEM    = {
                                            "SYAWAL\0\0\0\0\0\0\0"
                                            "SYA'BAN\0\0\0\0\0\0"
                                            "SENIN\0\0\0\0\0\0\0\0"
                                            "KAMIS\0\0\0\0\0\0\0\0"
                                            "TENGAH BULAN\0"
                                            "AROFAH\0\0\0\0\0\0\0"
                                            "DZULHIJAH\0\0\0\0"
                                            "TASU'A\0\0\0\0\0\0\0"
                                            "ASYURA\0\0\0\0\0\0\0"
                                            "RAMADHAN\0\0\0\0\0"
 
                                            };
                                            
/*=============================================
// List fungsi Call Name off :
// 1. Header Puasa          : Header_Puasa(1-4)      
// 2. Sholat Name           : sholahN(integer 0-6)    0-Subuh 1-Terbit 2-Dhuha 3-Dzuhur 4-Ashar 5-Magrib 3-Isya
// 3. DayName               : DayName(1-7)            1-Minggu  .... 7-Sabtu
// 4. Hijriah Month Name    : drawGregDate(OutPut String)
// 5. Masehi Month Name     : drawHijrDate(OutPut String)
// 6. Masjid Name           : drawMasjidName(OutPut String)    depend on Masjid Tipe  1-Masjid 2-Musholla 3-Surau 4-Langgar
 ==============================================*/ 
char* msgPuasa(int hd, int ty) // get sholat name from EEPROM
    {
      static char output[50];
      char  hdBuff[26];
      int locLen = (hd-1)*26;
      memccpy_P(hdBuff,HD_Puasa+locLen  ,0,26);
      char  tyBuff[13];
      locLen = (ty-1)*13;
      memccpy_P(tyBuff,TY_Puasa+locLen  ,0,13);
      sprintf(output,"%s %s ESOK HARI" ,hdBuff,tyBuff);
      return output;
    }

char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      int locLen = number*8;
      memccpy_P(locBuff,sholatN_E+locLen  ,0,8);
      return locBuff;
    }

char * DayName(int number)  // get Day Name from EEPROM
    {
      static char  locBuff[7];
      int locLen = (number-1)*7;
      memccpy_P(locBuff,DayName_E+locLen  ,0,7);
      return locBuff;
    }

char * MonthName(int number)  // get  Month Name from EEPROM
    {
      static char  locBuff[4];
      int   locLen = (number-1)*4;
      memccpy_P(locBuff,m_month_E+locLen,0,4);
      return locBuff;
    }

char * drawDayDate()
  {
      char  locBuff[20];
      static char  out[45];
      int   locLen = (nowH.hM-1)*11;
      memccpy_P(locBuff,h_month_E+locLen,0,11);
      sprintf(out,"%s %s,%02d-%02d-%04d   %02d %s %dH\0",DayName(daynow),pasar[jumlahhari()%5],now.day(),now.month(),now.year(),nowH.hD,locBuff,nowH.hY);
      return out;
  }

char * drawTglOnly()
{
       


  
}
char *  keluarga()

 {   char  nama[] = "test";
     static char  out[85];
      char  locBuff[10];
      sprintf(out,"%s",locBuff,nama);
      return out;
}

char *  drawNama()
  {
      static char  out[150]="Suhartono.Khusnul.Irfan.Alfin.Alfian";
      return out;
  }

void drawHari_S(int sNum,int c) // Box Sholah Time   tampilan jadwal sholat
  {
    
uint16_t y;
     char  HJAWA[45];
    char  HNSL[45];
    sprintf(HNSL,"%s" ,Hari[daynow-1]);    //HARI NASIONAL
    sprintf(HJAWA,"%s" ,pasar[jumlahhari()%5]); //HARI JAWA
 
    DoSwap = true; 


    ////////////
    fType(1); dwCtr(00,0,HNSL); //tulisan hari nasional
    fType(1); dwCtr(00,9,HJAWA);   //tulisan hari jawa
    DoSwap = true;          
  }




 void dwCek(const char* msg, int Speed, int dDT, int DrawAdd) //ranning tanggalan single
  { 
    // check RunSelector
    static uint16_t   x; 
    if(!dwDo(DrawAdd)) return;
    if (reset_x !=0) { x=0;reset_x = 0;}    
      
      char  locBuff[20];
      static char  TGLNSL[45];
      int   locLen = (nowH.hM-1)*11;
      memccpy_P(locBuff,h_month_E+locLen,0,11);
      
       
    static uint16_t   lsRn;
    int fullScroll = Disp.textWidth(msg) + DWidth;    
    uint16_t          Tmr = millis();
    if((Tmr-lsRn)> Speed)
      { lsRn=Tmr;
        if (x < fullScroll) {++x;}
        else {  dwDone(DrawAdd); 
                x = 0;return;}
     if(dDT==1)
        {
        fType(1);  //Marquee    jam yang tampil di bawah
        Disp.drawText(DWidth - x, 0, msg); //runing teks diatas
        fType(1);
        if (x<=6)                     { drawGreg_TS(16-x);}
        else if (x>=(fullScroll-6))   { drawGreg_TS(16-(fullScroll-x));}
        else                          { 
          //Disp.drawRect(1,8,30,8);//garis tengah
                                        drawGreg_TS(9);}//posisi jamnya yang bawah
        }
     else if(dDT==2) //jam yang diatas
        {    
        fType(1);
        if (x<=6)                     { drawTgl(x-6);}
        else if (x>=(fullScroll-6))   { drawTgl((fullScroll-x)-6);}
        else                          { 
          //Disp.drawRect(1,7,30,7);//garis tengah
                                        drawTgl(0);}  //posisi jam nya yang diatas
        fType(1); //Marquee  running teks dibawah
        Disp.drawText(DWidth - x, 9 , msg);//runinng teks dibawah
        }
     else
        {
        fType(1);
    //    Disp.drawLine(1,2,62,2);  nampilkan garis
     //   Disp.drawLine(1,13,62,13); //nampilkan garis
     //   Disp.drawText(DWidth - x, 4, msg);
        }
        DoSwap = true; 
      }          
  }


  char * TGLJAWA()
{
      char  locBuff[20];
      static char  out[45];
      int   locLen = (nowH.hM-1)*11;
      memccpy_P(locBuff,h_month_E+locLen,0,11);
      sprintf(out,"%02d-%s-%dH\0",nowH.hD,locBuff,nowH.hY);
      return out;     
             
  }

  void drawTgl(uint16_t y)   // Draw tanggal nasional
  {
    char  locBuff[20];
      static char  out[30];
      int   locLen = (nowH.hM-1)*11;
      memccpy_P(locBuff,h_month_E+locLen,0,11);
      sprintf(out,"%02d-%02d-%04d",now.day(),now.month(),now.year());   
    dwCtr(2,y,out);
    DoSwap = true; 
  }
