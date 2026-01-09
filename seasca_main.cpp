#include <iostream>
#include <bits/stdc++.h>
#include <sqlite3.h>
#include <string.h>
#include <map>
#include <random>
#include <filesystem>
#include <algorithm>
#include <fstream>

#define ART_COLS 9
#define UNDEFINED "99"
#define EVENT_TYPE_INDEX 4
using namespace std;

using namespace filesystem;

enum CommandTypes {
  INSERT, UPDATE, QUERY
};
enum Domains {
  ARTIFACT,
  EVENT,
  STATE
};

map<string, string> artf_types = {{"23", "TRAVEL DOC"}, {"04", "MD VISUAL ART"}, {"02", "MD DOC"}, {"22", "EVENT DOC"}, {"21", "IDENTITY DOC"}, {"25", "OFFICAL DOC"}, {"26", "GEN DOCS"}, {"11", "OCCASION INB"}, {"12", "CORRESPONDENCE INB"}, {"13", "GENERAL EXT"}, {"09", "NOTES"}, {"31", "EXAM ANS"}};
map<string, string> event_types = {{"11", "BIRTH"}, {"12", "CAL BDAY"}, {"13", "CAL XMAS"}, {"14", "CAL VAL"}, {"21", "FAMHOL"}, {"22", "FAMTRIP"}, {"23", "ITRAV"}, {"24", "ITRIP"}, {"25", "EDUTRIP"}, {"26", "WRKTRVL"}};

path stagingDir{"staging"};

bool process_artefact_file(){

for(const auto &entry : directory_iterator("staging")){
  //cout << entry.path().filename().string() << '\n';

}

 return true;

}

bool eventArtefactsGet(string eventCode){
return true;
}
string rand_number_string_gen(){
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(10000, 99999);

  return to_string(dist(mt));
}
string get_artf_seacode(string typecode){
  string newCode = "A";
  newCode.append(typecode);
  newCode.append(rand_number_string_gen());
 cout << newCode;
  return newCode;
}

string get_event_seacode(string typecode){
  string newCode = "E";
  newCode.append(typecode);
  newCode.append(rand_number_string_gen());
  cout << newCode;
  return newCode;
}

bool art_isstring[9] = {true, false, true, true, true, false, true, true, true};
bool event_isstring[9] = {true, false, false, true, true, true, false, true, true};


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

IE/./000000/999999/23/TESTEV/TEST EV DSC/1/LOC/X
*/
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

string dataQueryBuilder(string input, int seq){
  string token;


  return "d";

}
string IECommandBuilder(string input, int seq, string& typecode){
  string token;
// The code is v similar to IA 

    if(event_isstring[seq - 1]){
      token.append("\"");
    }
    token.append(input);
    if(event_isstring[seq - 1]){
      token.append("\"");
    }
    if(seq == EVENT_TYPE_INDEX){
     // cout<<input;
      typecode = input;
    }
    if(!(seq == ART_COLS)){
    token.append(", ");
    }

  return token;
}
string IACommandBuilder(string input, int seq, string& typecode){
  string token;


    if(art_isstring[seq - 1]){
      token.append("\"");
    }
    token.append(input);
    if(art_isstring[seq - 1]){
      token.append("\"");
    }
    if(seq == (ART_COLS - 1)){
      typecode = input;
    }
    if(!(seq == ART_COLS)){
    token.append(", ");
    }

  return token;
}

string renderCommand(string input){

  // I/./080717/P/Emirates Boarding Pass/Main part of boarding pass from EK029 from Dubai to London, the final leg of the June-July 2017 Eurasian adventure/1/TBA//
  //IE/./080717/P/Event Name/Event Description/1/TBA//

stringstream stream(input);
string temp;
char splitter = '/';

string start = "";

int count = 0;
string typecode = UNDEFINED;
Domains domain;
CommandTypes cmdType;

while(getline(stream, temp, splitter)){
  if(count == 0){

    // make more dry 
    if(temp == "IA"){
      start.append("INSERT INTO artefacts VALUES (");
      domain = ARTIFACT;
      // call IA function
    }
    if(temp == "IE"){
      start.append("INSERT INTO events VALUES (");
      domain = EVENT;
    }
    if(temp == "IS"){
      // INSERT STATE
      domain = STATE;
    }
    if(temp == "QA"){
      // QUERY ARTEFACT
      cmdType = QUERY;
      
    }
  } else {
    // store schema in seperate dict
    // extrap out into fucntion that checks using count if field is text and if so adds quotes
   if(cmdType == QUERY){
     // build query command




   } else {
   switch(domain){
     case ARTIFACT:
      start.append(IACommandBuilder(temp, count, typecode));
     break;
     case EVENT:
      start.append(IECommandBuilder(temp, count, typecode));
     break;
   
   }
   }
  }
  //cout << temp
  count++;
}
// replace dots with calculated vals now whole command processed
size_t dotIndex = start.find(".");
switch(domain){
  case ARTIFACT:
     start.replace(dotIndex, 1, get_artf_seacode(typecode));

    break;
  case EVENT:
    // IE
      //cout<<typecode;
      start.replace(dotIndex, 1, get_event_seacode(typecode));

    break;
}
start.append(");");
//out<< start << "\n";
return start;

}

//static int execCallback(void *data, int argc

int main(int argc, char** argv){

  if(argc == 1){
    //printf("ERROR: No arguememnt provided!\n");
    return 0;
  }


    process_artefact_file();

    const char * dbFileName = "seascape_a.db";
  
    sqlite3 *sscDb;
    sqlite3_open(dbFileName, &sscDb);

   // char *tableSetup = "CREATE TABLE entities(id varchar(255), domain varchar(255), form varchar(255), rubicon int, name varchar(255), desc varchar(255), startDate varchar(255), endDate varchar(255), created int)";
    const char *getAll = "SELECT * FROM artefacts);";
    const char *insert = "INSERT INTO artefacts VALUES('AXX00001', 1000, 'DWS', 'testName', 'testDesc', 3, 'E00001', '23', 'X*s');";
    string test = "IA/./080717/P/Emirates Boarding Pass/Main part of boarding pass from EK029 from Dubai to London, the final leg of the June-July 2017 Eurasian adventure/1/TBA//";
    string raw = argv[1];
    string command = renderCommand(raw);
    //cout << command.c_str();
    sqlite3_exec(sscDb, command.c_str(), NULL, NULL, NULL);
    sqlite3_close(sscDb);


return 0;


}