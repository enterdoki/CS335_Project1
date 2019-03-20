/******************************************************************************
Title : tree_species.h
Author : Yu Tong Chen
Created on : 03/06/2019
Description : The interface of tree_species, derived from __tree_species.
Usage : 
Build with : Makefile
Modifications: 

******************************************************************************/

#ifndef TREE_SPECIES_H
#define TREE_SPECIES_H
#include "__tree_species.h"
#include "tree_collection.h"
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;



class TreeSpecies:public __TreeSpecies {
public:
    TreeSpecies();
    TreeSpecies(const string & name);
    ~TreeSpecies();
    /** print_all_species(out) prints all species names on out, one per line
     *  This writes the set of all common names found in the data set to the
     *  output stream out, one per line. The species names are printed in
     *  lexicographic order, using the default string comparison ordering
     *  @param ostream& [in,out]  out  the stream to be modified
     */
    void print_all_species(ostream & out) const override;

    /** number_of_species() returns the number of distinct species names
     *  This returns the total number of distinct species common names found in
     *  the data set.
     *  @return int  The number of species common names
     */
    int number_of_species() const override;

    /** add_species(s)  inserts species s into the container
     *  This adds the species to the TreeSpecies container.
     *  @param string s [in]  the string to be added.
     *  @return int It returns a 0 if the species was already in the
     *              TreeSpecies container and a 1 if it was not.
     */
    int add_species( const string & species) override;

    /** get_matching_species(s) returns a list of species that match s
     * @note This returns a list<string> object containing a list of all of the
     * actual tree species that match a given parameter string partial_name.
     * This method should be case insensitive. The list returned by this
     * function should not contain any duplicate names and may be empty.
     * The rules for matching are those described above.
     * @param string partial_name [in] string to match
     * @return list<string> list of matching species names
     */
    list<string> get_matching_species(const string & partial_name) const override;
private:
    set<string> common;     // container containing all species common names

};



#endif //TREE_SPECIES_H
