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

#ifndef DATAUTILS_H
#define DATAUTILS_H

using namespace std;

#define ART_COLS 9
#define UNDEFINED "99"
#define EVENT_TYPE_INDEX 4


enum QA_CMDS{
    EV, IS_TRUE, IS_FALSE, AFTER, BEFORE
};

// Raw value of QA_CMD maps to index in this array


enum CommandTypes {
  INSERT, UPDATE, QUERY
};

enum Domains {
  ARTIFACT,
  EVENT,
  STATE
};

enum Forms {
    PHYS, DIGI
};

enum Timeframes {
    DAY, MONTH, YEAR, SPAN
};


tuple<struct tm, Timeframes> transformFlexiDateInt(int dateInt);
string singleQuoteWrap(string input);

#endif