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
#include <tuple>
#include "datautils.h"


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

// put in seperate data util file i




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
   
   tuple<struct tm, Timeframes> dtTuple = transformFlexiDateInt(kd);
    keyDate = get<0>(dtTuple);
    timeframe = get<1>(dtTuple);

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