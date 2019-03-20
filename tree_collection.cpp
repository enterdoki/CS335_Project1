/******************************************************************************
Title : tree_collection.cpp
Author : Yu Tong Chen
Created on : 03/06/2019
Description : The implementation of tree_collection, a derived class of __tree_collection.
Usage : 
Build with : Makefile
Modifications: 
    Interface (H) file provided by Professor Weiss
******************************************************************************/


#include "tree_collection.h"
#include <cmath>

// helper function to convert a string to lowercase removing hyphens
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

/* calculate the distance between two distance on sphere (The Haversine Formula)
 * Used to compute the approximate distance between two points when they are each defined by their decimal latitude
 * and longitude in degrees.
 */
double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6372.8;        // radius of earth in km
    const double TO_RAD = M_PI/180.0;   // conversion of degrees to rads
    lat1 = TO_RAD * lat1;
    lat2 = TO_RAD * lat2;
    lon1 = TO_RAD * lon1;
    lon2 = TO_RAD * lon2;
    double dLat = (lat2- lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a = sin(dLat);
    double b = sin(dLon);

    return 2 * R * asin(sqrt(a*a + cos(lat1) * cos(lat2)*b*b));
}

// default constructor
TreeCollection::TreeCollection():root(nullptr){
}

//constructor
TreeCollection::TreeCollection(Tree & new_tree):AvlTree(new_tree){
    add_tree(new_tree);
}

//destructor
TreeCollection::~TreeCollection()  {
    makeEmpty();
}

// return total number of trees
int TreeCollection::total_tree_count() {
    int count = 0;
    for(int i = 0; i < 5; i++) {
        count += boroughs[i].count;
    }
    return count;
}

// return total number of tree_species
int TreeCollection::count_of_tree_species ( const string & species_name ) {
    list<string> list_species = traverseSpecies(root, species_name);
    if(list_species.size() == 0)
        return 0;

    return list_species.size();
}

// return total number of tree specie sin specified boro
int TreeCollection::count_of_tree_species_in_boro ( const string & species_name,
                                    const string & boro_name ) {
    return traverseSpeciesBoro(root, species_name, boro_name);
}


// return the total number of trees all the boros combined
int TreeCollection::get_counts_of_trees_by_boro ( const string & species_name,
                                  boro  tree_count[5] ) {
    int total_count = 0;
    tree_count[5] =  traverseSpeciesByBoro(root, species_name);
    for(int i = 0; i < 5; i++) {
        total_count += tree_count[i].count;
    }
    return total_count;
}

// return total number of trees in boro
int TreeCollection::count_of_trees_in_boro( const string & boro_name ) {
    return traverseBoro(root, boro_name);
}

/* Adds into the collection of trees, updates list of species name, count of trees and types of trees in borough
 * hard coded specific values for each borough as recommeneded by Professor Weiss
borough[0] = Manhattan, borough[1] = Bronx, borough[2] = Brooklyn, borough[3] = Queens, borough[4] = Staten Island
 */
int TreeCollection::add_tree( Tree & new_tree) {
    collection.insert(new_tree);
    bool find = false;
    for(auto &i : list_of_species) {
        if(i == new_tree.common_name()) {
            find = true;
        }
        if(!find) {
            list_of_species.insert((new_tree.common_name()));
            tree_count++;       // keeps track of distinct species added
            if(new_tree.borough_name() == "Manhattan") {
                boroughs[0].count++;
            }
            else if(new_tree.borough_name() == "Bronx"){
                boroughs[1].count++;
            }
            else if(new_tree.borough_name() == "Brooklyn") {
                boroughs[2].count++;
            }
            else if(new_tree.borough_name() == "Queens"){
                boroughs[3].count++;
            }
            else if(new_tree.borough_name() == "Staten Island") {
                boroughs[4].count++;
            }
        }
    }

}

// print all species collection to out file
void TreeCollection::print_all_species(ostream & out) const {
    set<string> all_species = traverseAll(root);
    for(auto &i : all_species)
        out << i;
}

// prints whole collection of trees to out file
void TreeCollection::print(ostream & out ) const {

}

// returns a list of species in the collectioin that partially matches input
list<string> TreeCollection::get_matching_species(const string & species_name) const {
    list<string> species_match = traverseMatch(root, species_name);
    return species_match;
}

// returns a list of all common tree species located around given zipcode, no duplicates
list<string> TreeCollection::get_all_in_zipcode(int zipcode) const {
    list<string> zip_common = travereseSpecieZipcode(root, zipcode);
    return zip_common;
}

// returns a list of all species within a given distance from GPS location
list<string> TreeCollection::get_all_near(double latitude, double longitude,
                          double  distance) const {
    list<string> common_within = traverseAllInZip(root,latitude,longitude,distance);
    return common_within;

}

/* helper for print_all_tree_species
 * returns a list of all trees species in collection
 */
list<string> TreeCollection::traverseSpecies(AvlNode<Tree> *t, const string &species) {
    list<string> list_species;
    if (t != nullptr) {
        traverseSpecies(t->left, species);
        if(hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            list_species.push_back(hyphenLower(species));
        }
        traverseSpecies(t->right, species);
    }
    return list_species;
}


/* helper for print_all_species to print_all that traverses collection and appends to a sorted data structure
 * returns an ordered set of all trees in collection
 */
set<string> TreeCollection::traverseAll(AvlNode<Tree> *t) const {
    set<string> all_species;
    if (t != nullptr) {
        traverseAll(t->left);
        all_species.insert(t->element.common_name());
        traverseAll(t->right);
    }
    return all_species;
}


/* helper for get_matching_species to traverse tree and find matching species
 * returns a list of species that match given partial string
 */
list<string> TreeCollection::traverseMatch(AvlNode<Tree> *t, const string &species) const{
    list<string> list_species;
    if (t != nullptr) {
        traverseMatch(t->left, species);
        if(hyphenLower(t->element.common_name()).find(hyphenLower(species)) != string::npos) {
            for(auto &i : list_species) {
                if( hyphenLower(i) != hyphenLower(species))
                    list_species.push_back(hyphenLower(t->element.common_name()));
            }
        }
        traverseMatch(t->right, species);
    }
    return list_species;
}

/* helper for count_of_trees_in_boro
 * returns a list of trees in a given boro
 */
int TreeCollection::traverseBoro(AvlNode<Tree> *t, const string&boro) {
    int count_tree_boros;
    if (t != nullptr) {
        traverseMatch(t->left, boro);
        if(hyphenLower(t->element.borough_name()) == hyphenLower(boro)) {
            count_tree_boros++;
        }
        traverseMatch(t->right, boro);
    }
    return count_tree_boros;
}


/* helper for count_of_tree_species_in_boro
 * returns a list of species in a given boro
 */
int TreeCollection::traverseSpeciesBoro(AvlNode<Tree> *t, const string&species, const string&boro) {
    int species_boro_count;
    if (t != nullptr) {
        traverseSpeciesBoro(t->left, species, boro);
        if(hyphenLower(t->element.borough_name()) == hyphenLower(boro) && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            species_boro_count++;
        }
        traverseSpeciesBoro(t->right, species, boro);
    }
    return species_boro_count;
}

/* helper for count_of_tree_species_by_boro
 * returns array of number of species in each borough
*/
boro TreeCollection::traverseSpeciesByBoro(AvlNode<Tree> *t, const string&species) {
    boro species_boroughs[5];
    //borough[0] = Manhattan, borough[1] = Bronx, borough[2] = Brooklyn, borough[3] = Queens, borough[4] = Staten Island
    // hard coded specific values for each borough as recommeneded by Professor Weiss
    int manhattan_count = 0, bronx_count = 0, brooklyn_count = 0, queens_count = 0, statenisland_count = 0;

    if (t != nullptr) {
        traverseSpeciesByBoro(t->left, species);
        if(hyphenLower(t->element.borough_name()) == hyphenLower("Manhattan") && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            manhattan_count++;
            species_boroughs[0].count = manhattan_count;
            species_boroughs[0].name = hyphenLower(species);
        }
        else if(hyphenLower(t->element.borough_name()) == hyphenLower("Bronx") && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            bronx_count++;
            species_boroughs[1].count = bronx_count;
            species_boroughs[1].name = hyphenLower(species);
        }
        else if(hyphenLower(t->element.borough_name()) == hyphenLower("Brooklyn") && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            brooklyn_count++;
            species_boroughs[2].count = brooklyn_count;
            species_boroughs[2].name = hyphenLower(species);
        }
        else if(hyphenLower(t->element.borough_name()) == hyphenLower("Queens") && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            queens_count++;
            species_boroughs[3].count = queens_count;
            species_boroughs[3].name = hyphenLower(species);
        }
        else if(hyphenLower(t->element.borough_name()) == hyphenLower("Staten Island") && hyphenLower(t->element.common_name()) == hyphenLower(species)) {
            statenisland_count++;
            species_boroughs[4].count = statenisland_count;
            species_boroughs[4].name = hyphenLower(species);
        }

        traverseSpeciesByBoro(t->right, species);
    }
    return species_boroughs[5];
}

/* helper for get_all_in_zip
 * returns a list of species in a given zipcode
 */
list<string> TreeCollection::travereseSpecieZipcode(AvlNode<Tree> *t, int zipcode) const{
    list<string> species_zipcode;
    if (t != nullptr) {
        travereseSpecieZipcode(t->left, zipcode);
        if((t->element.zip_code()) == zipcode) {
            for(auto &i : species_zipcode) {
                if(hyphenLower(i) != hyphenLower(t->element.common_name())) {
                    species_zipcode.push_back(hyphenLower(t->element.common_name()));
                }
            }
        }
        travereseSpecieZipcode(t->right, zipcode);
    }
    return species_zipcode;
}

/* helper for get_all_near
 * returns a list of all species within given zipcode based on GPS location
 */
list<string> TreeCollection::traverseAllInZip(AvlNode<Tree> *t, double latitude, double longitude, double distance) const {
    list<string> species_within;
    double lat, lon;
    double within_distance;

    if (t != nullptr) {
        traverseAllInZip(t->left, latitude, longitude, distance);
        t->element.get_position(lat,lon);
        within_distance = haversine(lat,lon,latitude,longitude);
        if(within_distance <= distance) {
            for(auto &i : species_within) {
                if( i != t->element.common_name()) {
                    species_within.push_back(i);
                }
            }
        }

        traverseAllInZip(t->right, latitude, longitude, distance);
    }

    return species_within;
}