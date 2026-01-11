#include <iostream>
#include <bits/stdc++.h>
#include <sqlite3.h>
#include <string.h>
#include <map>
#include <random>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <vector>
#include <array>


#include "interpreter.h"
#include "datautils.h"
#include "schemas.h"


using namespace filesystem;
using namespace std;

int main(int argc, char** argv){

  if(argc == 1){
    return 0;
  }
    const char * dbFileName = "../seascape_a.db";
  
    sqlite3 *sscDb;
    sqlite3_open(dbFileName, &sscDb);
    string raw = argv[1];
    string command = renderCommand(raw);
    char **err;
    sqlite3_exec(sscDb, command.c_str(), sql_exec_callback, NULL, err);
    cout << "SQLite3 Error: " << (err != NULL ? *err : "None") << "\n";
    sqlite3_close(sscDb);


return 0;


}



int sql_exec_callback(void *data, int argc, char **argv, char **azColName){

  static int results_count = 0;
  int date = atoi(argv[1]);
  Forms form = (argv[2][0] == 'P' ? PHYS : DIGI);
  int runicon = atoi(argv[5]);
  Artefact art = Artefact(argv[0], date, form, argv[3], argv[4], runicon, argv[6], argv[7], argv[8]);
  cout << art.seacode << "  |   " << art.name << "  |  " << art.desc << "  |  " << art.type << "\n";

 return 0;
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



string dataQueryBuilder(string input, int seq){
  static QA_CMDS cmd;
  string token;
  // QA/ofevent/E123456...
  // QA/istrue/FIELD/VALUE
  // QA/isfalse/FIELD/VALUE
  // QA/after/dateInt
  // QA/before/dateInt


if(seq == 1){
  for(int i = 0; i < qa_cmd->length(); i++){
    if(input == qa_cmd[i]){
      cmd = static_cast<QA_CMDS>(i);
      // use cmd val to look up string to append
      return qa_cmd_sql[i];
    }
  }
if(cmd == NULL){
  cout << "Error: Invalid QA command\n";
  return "";
}  

} else {
  // for seq 2, expect E val if cmd=EVENT, int if AFTER/BEFORE, else string
  if(cmd == EV){
    token = singleQuoteWrap(input);
  } else {
    token = input;
  }
}
  return token;
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
      start.append("SELECT * FROM artefacts WHERE");
      cmdType = QUERY;
      
    }
  } else {
    // store schema in seperate dict
    // extrap out into fucntion that checks using count if field is text and if so adds quotes
   if(cmdType == QUERY){
     // build query command

      start.append(dataQueryBuilder(temp, count));


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
  count++;
}
// replace dots with calculated vals now whole command processed
size_t dotIndex = start.find(".");
switch(domain){
  case ARTIFACT:
     start.replace(dotIndex, 1, get_artf_seacode(typecode));

    break;
  case EVENT:

      start.replace(dotIndex, 1, get_event_seacode(typecode));

    break;
}
if(cmdType != QUERY){
  start.append(")");
} 
start.append(";");
return start;

}