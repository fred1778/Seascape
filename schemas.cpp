#include <iostream>
#include <bits/stdc++.h>
#include <sqlite3.h>
#include <string.h>
#include <map>
#include <random>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <ctime>


using namespace std;


/*CREATE TABLE artefacts (
  seacode TEXT,
  keyDate INTEGER,
  form TEXT,
  name TEXT,
  desc TEXT,
  rubicon INTEGER,
  event TEXT,
  type TEXT,
  flags TEXT
)*/

enum Forms {
    PHYS, DIGI
};

enum Timeframes {
    DAY, MONTH, YEAR, SPAN
};

class Artefact {
public:
  string seacode;
  struct tm keyDate;
  Forms form;
  string name;
  string desc;
  int rubicon;
  string eventID;
   string type;
    string flags;
    Timeframes timeframe;
Artefact(string sc, int kd, Forms f, string n, string d, int r, string e, string t, string fl){
   
   // Derive dt struct from time int and set timeframe 
   
   if(kd <= 99){
    timeframe = YEAR;
    keyDate.tm_year = kd + 1900 + (kd < 96 ? 100 : 0); // range is 1996 to 
   } else {

    // yr/mo same calculation whether day or month timeframe
    keyDate.tm_year = (kd % 100) + (kd < 96 ? 100 : 0);
    keyDate.tm_mon = (kd / 100) -1;

    if(kd < 10000){
    timeframe = MONTH;

   } else{
    timeframe = DAY;
    keyDate.tm_mday = (kd / 10000);
   }
}
    seacode = sc;
    form = f;
    name = n;
    desc = d;
    rubicon = r;
    eventID = e;
    type = t;
    flags = fl;
  }

};