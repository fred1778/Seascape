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

tuple<struct tm, Timeframes> transformFlexiDateInt(int dateInt) {

  Timeframes timeframe;
  struct tm keyDate = {0};

   if(dateInt <= 99){
    timeframe = YEAR;
    keyDate.tm_year = dateInt + 1900 + (dateInt < 96 ? 100 : 0); // range is 1996 to 
   } else {
    // yr/mo same calculation whether day or month timeframe
    keyDate.tm_year = (dateInt % 100) + (dateInt < 96 ? 100 : 0);
    keyDate.tm_mon = (dateInt / 100) -1;
    if(dateInt < 10000){
    timeframe = MONTH;
   } else {
    timeframe = DAY;
    keyDate.tm_mday = (dateInt / 10000);
   }
}
return tuple<struct tm, Timeframes>(keyDate, timeframe);
}


string singleQuoteWrap(string input){
  string output = "'";
  output.append(input);
  output.append("'");
  return output;
}