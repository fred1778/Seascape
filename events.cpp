#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <tuple>
#include <artefacts.cpp>



using namespace std;

/*CREATE TABLE events (
  seacode TEXT,
  start INTEGER,
  end INTEGER,
  type TEXT,
  name TEXT,
  desc TEXT,
  rubicon INTEGER,
  location TEXT,
  agents TEXT
)
*/

class Event{
    public:
    string seacode;
    struct tm startDate;
    struct tm endDate;
    string type;
    string name;
    string desc;
    int rubicon;
    string location;
    string agents;

};
