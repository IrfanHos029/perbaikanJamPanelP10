/*=============================================
 * PROGMEM DATA
 ==============================================*/
  // sholatN 9 x 8 
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
                                            "DES\0"
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

char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      sprintf(locBuff,"%s",sholatCallDis[number]);
      return locBuff;
    }

char * DayName(int number)  // get Day Name from EEPROM
    {
      static char  locBuff[7];
      sprintf(locBuff,"%s",daysOfTheWeek[number]);
      return locBuff;
    }

// char * MonthName(int number)  // get  Month Name from EEPROM
//     {
//       static char  locBuff[4];
//       int   locLen = (number-1)*4;
//       memccpy_P(locBuff,m_month_E+locLen,0,4);
//       return locBuff;
//     }

char * drawDayDate()
  {
      static char  out[45];
      sprintf(out,"%s,%02d-%02d-%04d",DayName(daynow-1),now.day(),now.month(),now.year());
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
    char  Buff_up[50];
    char  Buff[20];
    sprintf(HNSL,"%s" ,Hari[daynow-1]);    //HARI NASIONAL
    sprintf(HJAWA,"%s" ,pasar[jumlahhari()%5]); //HARI JAWA
    sprintf(Buff_up,"%02d:%02d%s",now.hour(),now.minute(),DayName(daynow));
    //sprintf(Buff,"%02d:%02d",now.hour(),now.minute());    
 
    DoSwap = true; 


    ////////////
    fType(1); dwCtr(0,0,Buff_up); //tulisan hari nasional
    //fType(1); dwCtr(17,0,HNSL );
    fType(1); dwCtr(0,9,HNSL);   //tulisan hari jawa
    //ftype(1); dwCtr(00,9,HJAWA );
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
      //int   locLen = (nowH.hM-1)*11;
      printf(locBuff,"%s",mounthJawa[nowH.hM-1]);
      
       
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
      static char  out[45];
      sprintf(out,"%02d-%s-%dH\0",nowH.hD,mounthJawa[nowH.hM-1],nowH.hY);
      
      return out;     
             
  }

  void drawTgl(uint16_t y)   // Draw tanggal nasional
  {
      static char  out[30];
      sprintf(out,"%02d-%02d-%04d",now.day(),now.month(),now.year());   
    dwCtr(2,y,out);
    DoSwap = true; 
  }
