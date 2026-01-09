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


enum Forms {
    PHYS, DIGI
};

enum Timeframes {
    DAY, MONTH, YEAR, SPAN
};


tuple<struct tm, Timeframes> transformFlexiDateInt(int dateInt);


#endif