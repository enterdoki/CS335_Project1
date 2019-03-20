/******************************************************************************
Title : tree_species.cpp
Author : Yu Tong Chen
Created on : 03/06/2019
Description : The implementation of tree_species, a derived class of __tree_species.
Usage :
Build with : Makefile
Modifications: Interface (H) file provided by Professor Weiss

******************************************************************************/

#include "tree_species.h"


// helper function to convert a string to lowercase without hyphens
string hyphenLower(string s) {
    string new_str;

    for (int i = 0; i < s.length(); i++) {
        new_str+=tolower(s[i]);
    }

    for(int j = 0; j<new_str.length(); j++) {
        if(new_str[j]=='-')
            new_str[j] = ' ';
    }

    return new_str;
}
// helper function to convert string to lower
string turnLower(string s) {
    string new_str;

    for (int i = 0; i < s.length(); i++) {
        new_str+=tolower(s[i]);
    }

    return new_str;
}

// helper function to split the strings into two when encountering whitespace
void splitOnSpace(string s, string & before, string & after) {
    // reset strings;
    before = "", after = "";
    // accumulate space
    int i = 0;
    while(i<s.size() && (s[i] != ' ' || s[i] != '-')) {
        before += s[i];
        i++;
    }
    //skip space
    i++;
    // accumulate space
    while(i<s.size()) {
        after += s[i];
        i++;
    }
}



// default constructor
TreeSpecies::TreeSpecies() {
    add_species("");
}

// constructor
TreeSpecies::TreeSpecies(const string & name) {
    add_species(name);
}

// destructor
TreeSpecies::~TreeSpecies() {
    common.clear();
}


// sorts container lexicographically then outputs data to out file
void TreeSpecies::print_all_species(ostream & out) const {
    for (const string &i : common)
        out << i << endl;
}

// returns the size of the container AKA the total number of distinct species common name
int TreeSpecies::number_of_species() const {
    return common.size();
}

/* adds input species IFF the container doesn't already have that species
 * return 0 if duplicate and 1 if unique and will be added to container */
int TreeSpecies::add_species( const string & species) {
    if(find(common.begin(), common.end(), species) != common.end())
        // species already container, duplicate
        return 0;
    else {
        common.insert(species);
        return 1;
    }
}
// returns a list of all common names that partially matches the input, case insensitive
list<string> TreeSpecies::get_matching_species(const string & partial_name) const {
    list<string> species_match;
    string lower_partial_name = hyphenLower(partial_name);

    for (const string &i : common) {
        if(hyphenLower(i).find(lower_partial_name) != string::npos) {
               species_match.push_back(turnLower(i));
        }
    }
    return species_match;


}

