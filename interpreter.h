#include <iostream>
#include <bits/stdc++.h>
#include <sqlite3.h>
#include <string.h>
#include <map>
#include <random>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include "datautils.h"
#include "schemas.h"
#include <vector>
#include <array>

using namespace filesystem;
using namespace std;

map<string, string> artf_types = {{"23", "TRAVEL DOC"}, {"04", "MD VISUAL ART"}, {"02", "MD DOC"}, {"22", "EVENT DOC"}, {"21", "IDENTITY DOC"}, {"25", "OFFICAL DOC"}, {"26", "GEN DOCS"}, {"11", "OCCASION INB"}, {"12", "CORRESPONDENCE INB"}, {"13", "GENERAL EXT"}, {"09", "NOTES"}, {"31", "EXAM ANS"}};
map<string, string> event_types = {{"11", "BIRTH"}, {"12", "CAL BDAY"}, {"13", "CAL XMAS"}, {"14", "CAL VAL"}, {"21", "FAMHOL"}, {"22", "FAMTRIP"}, {"23", "ITRAV"}, {"24", "ITRIP"}, {"25", "EDUTRIP"}, {"26", "WRKTRVL"}};
string qa_cmd[5] = {"ofevent", "istrue", "isfalse", "after", "before"};
string qa_cmd_sql[] = {" event = ", "", "", " keyDate >", " keyDate <"};
path stagingDir{"staging"};

int sql_exec_callback(void *data, int argc, char **argv, char **azColName);
string rand_number_string_gen();
string get_artf_seacode(string typecode);
string get_event_seacode(string typecode);
string dataQueryBuilder(string input, int seq);
string IACommandBuilder(string input, int seq, string& typecode);
string IECommandBuilder(string input, int seq, string& typecode);
string renderCommand(string input);



bool art_isstring[9] = {true, false, true, true, true, false, true, true, true};
bool event_isstring[9] = {true, false, false, true, true, true, false, true, true};