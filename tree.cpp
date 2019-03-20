/******************************************************************************
Title : tree.cpp
Author : Yu Tong Chen
Created on : 03/06/2019
Description : The implementation of tree interface.
Usage : 
Build with : Makefile
Modifications: 
    Interface (H) file provided by Professor Weiss
******************************************************************************/

#include "tree.h"

using namespace std;


// helper function to check if string is a number
bool isNumber(string s) {
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

// helper function to check if string is a non-negative number
bool negativeNumber(string s) {
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false && stoi(s) > 0)
            return false;

    return true;
}

// helper function to convert a string to lowercase
string toLower(string s) {
    string new_string = s;
    transform(new_string.begin(), new_string.end(), new_string.begin(), ::tolower);
    return new_string;
}

// constructor
Tree::Tree():tree_id(0), tree_dbh(0), status(""), health(""), spc_common(""), zipcode(0), address(""), boroname(""), latitude(0), longitude(0)  {}  // creates an empty tree

// constructor that pulls 10 required fields from input of 41 fields
Tree::Tree(const string & str) {
    istringstream csv_stream(str);
    string csv_element;
    vector<string> data;
    vector<string> treeData;

    while(getline(csv_stream, csv_element, ',')) {
        data.push_back(csv_element);
    }


    /* In the vector, positions:
     * 0 = tree_id
     * 1 = tree diameter
     * 6 = tree status
     * 7 = tree health
     * 10 = tree common
     * 26 = tree address
     * 27 = boroname
     * 28 = tree zip
     * 39 = tree latitude
     * 40 = tree longitude
     */
    for(int i = 0; i< data.size(); i++) {
        if (i == 0 || i == 1 || i == 6 || i == 7 || i == 10 || i == 26 || i == 27 || i == 28 || i == 39 ||
            i == 40) {     // numbers represent the values in which the required fields are in
            treeData.push_back(data[i]);
        }
    }

    // validation of input string for required 10 fields in proper notation
    if((!negativeNumber(data[0]) && !negativeNumber(data[1]) && (data[6] == "Alive" || data[6] == "Dead" || data[6] == "Stump" || data[6] == " ") &&  (data[7] == "Good" || data[7] == "Fair" || data[7] == "Poor" || data[7] == " ")
    && !isNumber(data[10]) && !data[26].empty() && (data[27] == "Manhattan" || data[27] == "Bronx" || data[27] == "Brooklyn" || data[27] == "Queens" || data[27] == "Staten Island" ) && (data[28].length() == 5 && isNumber(data[28])
    && isNumber(data[39]) && isNumber(data[40])))) {
        tree_id = stoi(data[0]);
        tree_dbh = stoi(data[1]);
        status = data[6];
        health = data[7];
        spc_common = data[10];
        address = data[26];
        boroname = data[27];
        zipcode = stoi(data[28]);
        latitude = stoi(data[39]);
        longitude = stoi(data[40]);
    }
    else {      // if above condition is not fully satisfied, create empty tree
        tree_id = 0;
        tree_dbh = 0;
        status = "";
        health = "";
        spc_common = "";
        address = "";
        boroname = "";
        zipcode = 0;
        latitude = 0;
        longitude = 0;
    }

}

// constructor that sets private members to parameters
Tree::Tree(int id, int diam,  string stat, string hlth, string name,
     int zip, string addr, string boro, double lat, double longtd) {
         tree_id = id;
         tree_dbh = diam;
         status  = stat;
         health = hlth;
         spc_common = name;
         zipcode = zip;
         address = addr;
         boroname = boro;
         latitude = lat;
         longitude = longtd;
     }

// writes to ostream the required fields separated by a comma
ostream& operator<< (ostream & os, const Tree & t) {
    string separator = ",";
    os << t.spc_common << separator << t.tree_id << separator << t.tree_dbh << separator << t.status << separator << t.health << separator << t.address << separator << t.zipcode << separator << t.boroname << separator << t.latitude << separator << t.longitude;
}


// checks if t1 and t2 equal in both it's common name and id
bool operator==(const Tree & t1, const Tree & t2) {
    return (toLower(t1.spc_common) == toLower(t2.spc_common)) && (t1.tree_id == t2.tree_id);
}

// checks if t t1 is less than t2 or if it has the same common name, check if id of t1 is less than id of 2
bool operator<(const Tree & t1, const Tree & t2) {
    if(toLower(t1.spc_common) < toLower(t2.spc_common))
        return true;

    else if((toLower(t1.spc_common) == toLower(t2.spc_common)) && (t1.tree_id < t2.tree_id))
        return true;
    else
        return false;
}

// checks if t1 and t2 contain the same species name
bool samename(const Tree & t1, const Tree & t2) {
    return toLower(t1.spc_common) == toLower(t2.spc_common);
}

// checks if t1's common name < t2's common name
bool islessname(const Tree & t1, const Tree & t2) {
    return toLower(t1.spc_common) < toLower(t2.spc_common);
}

string Tree::common_name() const {
    return spc_common;
}

string Tree::borough_name() const {
    return boroname;
}

string Tree::nearest_address() const {
    return address;
}

string Tree::life_status() const {
    return status;
}

string Tree::tree_health() const {
    return health;
}

int Tree::id()       const {
    return tree_id;
}

int Tree::zip_code() const {
    return zipcode;
}

int Tree::diameter() const {
    return tree_dbh;
}


// update parameters with private member values
void Tree::get_position(double & latitude,double & longitude) const {
    latitude = latitude;
    longitude = longitude;
}

