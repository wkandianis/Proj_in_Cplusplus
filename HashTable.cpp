/********************************************
* Comp 15 - Fall 2019
* Project 2
* Will Kandianis
* 12/7/2019
* 
* HashTable implementation
*********************************************/


#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"


using namespace std;

// constructor
// Parameters: original hashttable size
// Returns: none
// Does: sets curr occ to 0, sets the 
// size to OGsize
HashTable::HashTable(int OGsize)
{
currOcc = 0;
dictionary.resize(OGsize);
size = OGsize;
}

// read_file
// Parameters:filename
// Returns: none
// Does: opens a file, reads it, and pushes the
// lines back on the sentence vectors and assigns
// proper values
void HashTable::read_file(string filename)
{	

ifstream in;
in.open(filename);
if(in.fail()) {
cerr << "Failed to open file" << endl;
exit(0);
}
int line_number = 1;
while(not in.eof()) {
string line;
getline(in, line);
Line_Struct temp_line;
// assign each attribute of Line struct
temp_line.filename = filename;
temp_line.sentence = line;		
temp_line.line_number = line_number;
// add line to sentences vector
sentences.push_back(temp_line);
stringstream ss(line);
string word;
while(ss >> word) {
	insert(word);
}
line_number++;
}
in.close();
}

// insert
// Parameters: word
// Returns: none
// Does: hashes the word. Checks if it is already
// in the table. Inserts word into table
void HashTable::insert(string word)
{
bool duplicate = false;
word = stripNonAlphaNum(word);
string toHash = shift_word(word);

if(currOcc / dictionary.size() > loadFactor)
{
expand();
}
size_t bucket = hash<string>{}(toHash) % dictionary.size();
// if that bucket already has elements in it
if(dictionary.at(bucket).size() > 0) {

for(size_t i = 0; i < dictionary.at(bucket).size(); i++) {

	Word_Struct *toFind = &dictionary.at(bucket).at(i);
	if(toFind->word == word) {

		if(toFind->index.at(toFind->index.size() - 1) != (int) sentences.size() - 1) {
		toFind->index.push_back(sentences.size() - 1);
		currOcc++;
		return;

		}
		duplicate = true;
	}
}
}
// if the word isn't already in the table
if(duplicate == false) {
Word_Struct add_word;
add_word.word = word;
add_word.index.push_back(sentences.size() - 1);
dictionary.at(bucket).push_back(add_word);
currOcc++;
}
}

// search
// Parameters: string word, ofstream out
// Returns: none
// Does: hashes word to find it in table in constant
// time. Prints filename line number and sentence to 
// output file
void HashTable::search(string word, ofstream &out)
{
word = stripNonAlphaNum(word);
string toHash = shift_word(word);
size_t bucket = hash<string>{}(toHash) % dictionary.size();

bool found = false;

for(size_t i = 0; i < dictionary.at(bucket).size(); i++) {

Word_Struct toFind = dictionary.at(bucket).at(i);
// if the word exists in the bucket, print
if(toFind.word == word) {

found = true;

for(size_t j = 0; j < toFind.index.size(); j++) {
	out << sentences.at(toFind.index.at(j)).filename << ":"
	<< sentences.at(toFind.index.at(j)).line_number 
	<< ": " << sentences.at(toFind.index.at(j)).sentence << endl;
}
break;
}
}

if(found == false) {
out << word << " Not Found. Try with @insensitive or @i." << endl;
}

}

// insensitive_search
// Parameters: string word, ofstream out
// Returns: none
// Does: hashes word to find it in table in constant
// time. Prints filename line number and sentence to 
// output file
// note: this function only gets called if @i or @insensitive
// is inputed before a word
void HashTable::insensitive_search(string word, ofstream &out)
{
word = stripNonAlphaNum(word);
string shifted = shift_word(word);
size_t bucket = hash<string>{}(shifted) % dictionary.size();
bool found = false;


for(size_t i = 0; i < dictionary.at(bucket).size(); i++) {

Word_Struct toFind = dictionary.at(bucket).at(i);
string search_shifted = shift_word(toFind.word);
// if the word exists in bucket, print
if(search_shifted == shifted) {

found = true;

for(size_t j = 0; j < toFind.index.size(); j++) {
	out << sentences.at(toFind.index.at(j)).filename << ":"
	<< sentences.at(toFind.index.at(j)).line_number << ": " 
	<< sentences.at(toFind.index.at(j)).sentence << endl;
}
}
}

if(found == false) {
	out << word << " Not Found." << endl;
}
}

// expand
// Parameters: none
// Returns: none
// Does: creates a new temporary vector. rehashes
// every word in the sentences vector and puts them
// in their new bucket in the new vector
void HashTable::expand()
{
vector<vector<Word_Struct>> temp;
temp.resize(dictionary.size() * 2);

for(size_t i = 0; i < dictionary.size(); i++) {
for(size_t j = 0; j< dictionary.at(i).size(); j++) {
	// rehash the words in each bucket
	string rehash = dictionary.at(i).at(j).word;
	rehash = stripNonAlphaNum(rehash);
	rehash = shift_word(rehash);
	size_t new_bucket = hash<string>{}(rehash) % temp.size();

	Word_Struct temp_word = dictionary.at(i).at(j);
	temp.at(new_bucket).push_back(temp_word);

}
}

dictionary = temp;
}


// shift_wird
// Parameters: string word
// Returns: string
// Does: takes in a word and makes them
// all uppercase in order to eliminate
// case sensitivity
string HashTable::shift_word(string word)
{
string result = "";
for(size_t i = 0; i < word.length(); i++) {
	char temp = word[i];
	temp = toupper(temp);
	result = result + temp;
}
return result;
}

void HashTable::print()
{
for(size_t i = 0; i < dictionary.size(); i++) {
for(size_t j = 0; j < dictionary.at(i).size(); j++) {
	cout << dictionary.at(i).at(j).word << endl;
}
}
}


// stripNonAlphaNum
// Parameters: string word
// Returns: string
// Does: strips all non alphabetic or numeric
// values from the front and back of a word
string HashTable::stripNonAlphaNum(string word)
{
for(size_t i = 0; i < word.length(); i++) {
char temp = word[i];
temp = toupper(temp);
if (temp < 65 or temp > 90) {
if (temp < 48 or temp > 57) {
    word.erase(word.begin() + i);
    i--;
} else {
    break;
}
} else {
break;
}
}

for (size_t i = word.length(); i > 0; i--) {
char back = word[i - 1];
back = toupper(back);
if (back < 65 or back > 90) {
if (back < 48 or back > 57) {
    word.erase(word.begin() + i - 1);
} else {

    break;
}
} else {
break;
}
}
return word;
}




