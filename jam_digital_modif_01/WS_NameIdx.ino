

char* sholatN(int number) // get sholat name from EEPROM
    {
      static char  locBuff[8];
      sprintf(locBuff,"%s",sholatCall[number]);
      return locBuff;
    }

char * DayName(int number)  // get Day Name from EEPROM
    {
      static char  locBuff[7];
      sprintf(locBuff,"%s",Hari[number]);
      return locBuff;
    }

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

void drawShow1(int sNum,int c) // Box Sholah Time   tampilan jadwal sholat
  {
    static uint32_t   lsRn;
    uint32_t          Tmr = millis();
    char  Buff_hariN[20];
    char  Buff_hariJ[20];
    char Buff_Jam[20];
    char Buff_Men[20];
    char point1[2] = ":";
    char point0[2] = " ";
//    sprintf(HNSL,"%s" ,Hari[daynow-1]);    //HARI NASIONAL
//    sprintf(HJAWA,"%s" ,pasar[jumlahhari()%5]); //HARI JAWA
    sprintf(Buff_hariN,"%s   ",Hari[daynow-1]); 
    sprintf(Buff_hariJ,"%s   ",pasar[jumlahhari()%5]); 
    sprintf(Buff_Jam,"%02d",now.hour()); 
    sprintf(Buff_Men,"%02d",now.minute());

    if((Tmr-lsRn)>1000){state = !state; lsRn=Tmr; }
    ////////////
    fType(1); dwCtr(0,0,Buff_hariN); //tulisan hari biasa
    fType(1); dwCtr(0,9,Buff_hariJ);   //tulisan hari jawa 
    fType(1); dwCtr(42,0,Buff_Jam);
    fType(1); dwCtr(42,9,Buff_Men);
    if(state){fType(1); dwCtr(59,4,point1);}
    else{fType(1); dwCtr(59,4,point0);}

    DoSwap = true;          
  }
  
void drawShow2(int sNum,int c){
     static uint32_t   lsRn;
    uint32_t          Tmr = millis();
    char Jam[10];
    char tgl[10];
    
    if((Tmr-lsRn)>1000){state = !state; lsRn=Tmr; }
    if(state){sprintf(Jam,"%02d %02d",now.hour(),now.minute());}
    else{sprintf(Jam,"%02d:%02d",now.hour(),now.minute()); }
    
    sprintf(tgl,"%02d-%02d-%04d",now.day(),now.month(),now.year());
    
     Disp.drawRect(1,11,63,12);
    
    fType(1); dwCtr(0,9,Jam); //tulisan nama
    fType(1); dwCtr(0,0,tgl);   //tulisan tangal lahir 

    DoSwap = true;
}

void Reset(byte state){
  if(state==1){
    digitalWrite(reset,0);
  }
  else{
    digitalWrite(reset,0);
  }
}

/*
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
  */
