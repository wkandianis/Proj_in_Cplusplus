//
// GeneDB.cpp
// purpose: to create a database that is able to be navigated by the user in order to find different information about the genes
// William Kandianis
// 1 April 2019
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;


const string print = "P";
const string canmutate = "CM";
const string common_sequence = "FCS";
const string printall = "PA";
const string canevolve = "CE";
const string can_cycl_mut = "CCM";
const string quit = "Q";


struct Gene;
struct Mutate
{
	Gene *DNA;
	int energy;
};

struct Gene
{
	string allele;
	int num_mutations;
	Mutate mutations[5];
};

void print_array(Gene array[], int length);
bool can_mutate(Gene source, Gene target, int max);
void find_common_sequence(Gene array[], int length);
void print_all(Gene source, Gene target, int max_allowed, string add_mut);
bool can_evolve(Gene source, Gene target, int max_cost);
void can_cyclically_mutate(Gene source, int max_mutations);
void set_array(Gene array[], string file, int length);
void operations(string input, Gene array[], int length);
void populate_array(Gene array[], string file, int length);
int read_length(string file_name);
int string2int(string s);
void can_evolve_command(Gene array[], int length);
void cyclic_command(Gene array[], int length);
int array_size(Gene array[], int length);
int create_new_index(string name, Gene array[], int length);
int look_up(string name, Gene array[], int length);
void can_mutate_command(Gene array[], int length);
void print_all_command(Gene array[], int length);
string switch_case(string input);

int main()
{
	string input;
	string file_name;
	cout << "Enter file name: " << endl;
	cin >> file_name;
	int length = read_length(file_name);
	Gene array[length];
	for(int i = 0; i < length; i++) {
		array[i].allele = "-";
	}
	set_array(array, file_name, length);
	operations(input, array, length);

} 

// void operations(string input, Gene array[], int length) 
// purpose: take in the user input and call the appropriate functions
// parameters: string input, Gene array[], int length)
// returns: nothing
// effects: 
// notes: 
void operations(string input, Gene array[], int length) 
{

	string word;

	while(input != quit) {
		
	cout << "Enter a command: " << endl;
	cin >> input;

	input = switch_case(input);

		if(input == print) {
			print_array(array, length);
		}


		if(input == canmutate) {
			can_mutate_command(array, length);
		}

		if(input == common_sequence) {
			find_common_sequence(array, length);
		}


		if(input == printall) {
			print_all_command(array, length);
		}


		if(input == canevolve) {
			can_evolve_command(array, length);
		}


		if(input == can_cycl_mut) {
			cyclic_command(array, length);
		}
	}
			while(input == quit) {
				break;
			}
			
return;
}



// int look_up(string name, Gene array[], int length)
// purpose: go through the array and search for the gene and return the index number when found
// parameters: string name, Gene array[], int length)
// returns: index number
// effects: 
// notes: 
int look_up(string name, Gene array[], int length)
{
	for(int i = 0; i < length; i++) {
		if(array[i].allele == name) {
			return i;

		}
	}
	return -1;
}


// int string2int(string s)
// purpose: convert the string length into an integer in order to use it in my array
// parameters: string s
// returns: none
// effects: 
// notes: I got this from the 2048 project
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

// int read_length(string data_file)
// purpose: read in the first line of the program which is an integer and return it
// parameters: data file
// returns: first integer
// effects: 
// notes: 
int read_length(string data_file) 
{
	ifstream in;
	in.open(data_file);


	if(in.fail()) {
		cout << "File cannot be opened. " << endl;
		return 0;
	}
	int x;
	in >> x;
	in.close();

	return x;
}

// void set_array(Gene array[], string file, int length)
// purpose: fill each index of the array with its mutations and costs
// parameters: Gene array[], string file, int length
// returns: nothing
// effects: 
// notes: 
void set_array(Gene array[], string file, int length)
{
	ifstream in;
	string line;
	in.open(file.c_str());

	if(in.fail()) {
		cout << "File cannot be opened" << endl;
	}

	int skip;
	string skip_endl;
	string temp;
	in >> skip;
	getline(in, skip_endl);
	while(not in.eof()) {
		getline(in, line);
		stringstream ss(line);
		ss >> temp;

		int x = look_up(temp, array, length);

		if(x == -1) {
			create_new_index(temp, array, length);
		}
	}
	in.close();
	populate_array(array, file, length);
return;
}

// void print_array(Gene array[], int length)
// purpose: print function upon print command in the appropriate format 
// parameters: Gene array[], int length
// returns: nothing
// effects: 
// notes: 
void print_array(Gene array[], int length)
{
	
	for(int i = 0; i < length; i++) {
		cout << "== " << array[i].allele << " ==" << endl;
		cout << "Mutations: " << endl;
		if(array[i].num_mutations == 0) {
			cout << "None" << endl;
		}
		for(int j = 0; j < array[i].num_mutations; j++) {
			cout << array[i].mutations[j].DNA -> allele; 
			cout << " - Cost: " << array[i].mutations[j].energy << endl;
		}
	}
return;
}

// void create_new_index(Gene array[], string file, int length)
// purpose: creates new information in index and returns the new index
// parameters: Gene array[], string file, int length
// returns: the index
// effects: 
// notes: 
int create_new_index(string name, Gene array[], int length)
{
	int position = 0;

	for(int i = 0; i < length; i++) {

		if(array[i].allele == "-") {
			array[i].allele = name;
			position = i;
			array[i].num_mutations = 0;
			return position;
		}		
	}
return position;
}

// void populate_array(Gene array[], string file, int length)
// purpose: populate the array with the first gene in every line
// parameters: Gene array[], string file, int length
// returns: nothing
// effects: 
// notes: 
void populate_array(Gene array[], string file, int length)
{
	ifstream in;
	string line;
	string temp;
	int i = 0;
	in.open(file);

	if(in.fail()) {
		cout << "File cannot be opened" << endl;
	}

	getline(in, temp);
	while(i < length) {
		int energy = 0;
		int j = 0;
		getline(in, line);
		stringstream ss(line);
		ss >> temp;		
		string mutation_name;
		while(ss >> mutation_name) {

			int x = look_up(mutation_name, array, length);
			array[i].mutations[j].DNA = &(array[x]);
			ss >> energy;
			array[i].mutations[j].energy = energy;
			j++;
			array[i].num_mutations ++;
		}
		i++;
	}
in.close();
return;
}

// bool can_mutate(Gene source, Gene target, int max_cost)
// purpose: to go through the array and check if the source can mutate to the target with the given cost
// parameters: Gene source, Gene target, int max_cost
// returns: a boolean value
// effects: 
// notes: 
bool can_mutate(Gene source, Gene target, int max_cost) 
{


	if(max_cost == 0){
		return false;
	}

	for(int i = 0; i < source.num_mutations; i++) {
		if(source.mutations[i].DNA -> allele == target.allele) {
			return true;
		}
	}

	for(int j = 0; j < source.num_mutations; j++) {
		bool x = can_mutate(*source.mutations[j].DNA, target, max_cost - 1);
		if(x == true) {
			return true;
		}
		if(max_cost - 1 == 0) {
			break;
		}
	}
return false;
}

// void fine_common_sequence(Gene array[], int length)
// purpose: to go through the array and print out any allele that can mutate within 10
// parameters: Gene array[], int length
// returns: none
// effects: 
// notes: 
void find_common_sequence(Gene array[], int length)
{
	int max_mutations = 10;
	bool x = true;
	bool y = false;
	for(int i = 0; i < length; i++) {
		for(int j = 0; j < length; j++) {
			if(i == j) {
				continue;
			}
			x = can_mutate(array[i], array[j], max_mutations);
			if(x == false) {
				break;
			}
		}
		if(x == true) {
			cout << array[i].allele << " is a common sequence." << endl;
			y = true;
		}
	}
	if(y == false) {
		cout << "There are no common sequences in the database" << endl;
	}
return;
}

// void can_cyclically_mutate(Gene source, int max_mutations)
// purpose: to go through the array and call can_mutate. If can mutate is true then it can cyclically mutate
// parameters: Gene source, int max_mutations
// returns: none
// effects: 
// notes: 
void can_cyclically_mutate(Gene source, int max_mutations)
{
	int x = can_mutate(source, source, max_mutations);

	if(x == true) {
		cout << source.allele << " can perform cyclic mutation in " << max_mutations << " steps or less" << endl;
	} else {
		cout << source.allele << " cannot perform cyclic mutation in " << max_mutations << " steps or less" << endl;
	}
return;
}

// void print_all(Gene source, Gene target, int max_allowed, string add_mut)
// purpose: to print out every step of the evolutionary path 
// parameters:Gene source, Gene target, int max_allowed, string add_mut
// returns: none
// effects: 
// notes: 
void print_all(Gene source, Gene target, int max_allowed, string add_mut)
{


	if(add_mut == "") {
		add_mut = source.allele;
	} else {
		add_mut += " --> " + source.allele;
	}
	if(max_allowed == 0) {
		return;
	}
	for(int i = 0; i < source.num_mutations; i++) {
		if(source.mutations[i].DNA -> allele == target.allele) {
			add_mut += " --> " + target.allele;
			cout << add_mut << endl;		
		}
	}
	for(int j = 0; j < source.num_mutations; j++) {
		print_all(*source.mutations[j].DNA, target, max_allowed - 1, add_mut);
		if(max_allowed - 1 == 0) {
			break;
		}
	}
return;
}


// bool can_evolve(Gene source, Gene target, int max_cost)
// purpose: to determine if a source gene can evolve into a target gene in the given cost
// parameters:Gene source, Gene target, int max_cost
// returns: a boolean value
// effects: 
// notes: 
bool can_evolve(Gene source, Gene target, int max_cost)
{
	if(max_cost <= 0) {
		return false;
	}
	for(int i = 0; i < source.num_mutations; i++) {
		if(source.mutations[i].DNA -> allele == target.allele) {
			max_cost -= source.mutations[i].energy;
			if(max_cost <= 0) {
				return false;
			} else {
				return true;
			}
		}
	}
	for(int j = 0; j < source.num_mutations; j++) {
		bool x = can_mutate(*source.mutations[j].DNA, target, max_cost -= source.mutations[j].energy);
		if(x == true) {
			return true;
		}
	}
	return false;
}


// void can_mutate_command(Gene array[], int length)
// purpose: to set up and run can_mutate when called in the operations function
// parameters: Gene array[], int first line
// returns:none
// effects: 
// notes: 
void can_mutate_command(Gene array[], int length)
{
	string source;
	string target;
	int max;

		// cout << "Enter source, target, max allowed" << endl;
		cin >> source >> target >> max;
		int x = look_up(source, array, length);
		if(x == -1) {
			cout << "Source DNA not in database" << endl;
			return;
		}


		int y = look_up(target, array, length);
		if(y == -1) {
			cout << "Target DNA not in database" << endl;
			return;
		}
		Gene source_gene = array[x];
		Gene target_gene = array[y];
		bool blank = can_mutate(source_gene, target_gene, max);
		if (blank == true) {
			cout << source << " can mutate into " << target << " in " << max << " steps or less." << endl;
		}
		if (blank == false) {
			cout << source << " cannot mutate into " << target << " in " << max << " steps or less." << endl;
		}
return;
}

// void print_all_command(Gene array[], int length)
// purpose: to set up and run print_all when called in the operations function
// parameters: Gene array[], int first line
// returns:none
// effects: 
// notes: 
void print_all_command(Gene array[], int length)
{
	string source;
	string target;
	int max;

		
		cin >> source >> target >> max;
		int x = look_up(source, array, length);
		if(x == -1) {
			cout << "Source DNA not in database" << endl;
			return;
		}
		int y = look_up(target, array, length);
		if(y == -1) {
			cout << "Target DNA not in database" << endl;
			return;
		}
		Gene source_gene = array[x];
		Gene target_gene = array[y];
		string path;
		print_all(source_gene, target_gene, max, path);
return;
}


// void can_evolve_command(Gene array[], int length)
// purpose: to set up and run can_evolve when called in the operations function
// parameters: Gene array[], int first line
// returns:none
// effects: 
// notes: 
void can_evolve_command(Gene array[], int length)
{

	string source;
	string target;
	int max;
		
		cin >> source >> target >> max;
	
		int x = look_up(source, array, length);

		if(x == -1) {
			cout << "Source DNA not in database" << endl;
			return;
		}

		int y = look_up(target, array, length);
		if(y == -1) {
			cout << "Target DNA not in database" << endl;
			return;
		}

		Gene source_gene = array[x];
		Gene target_gene = array[y];
		bool evolvable = can_evolve(source_gene, target_gene, max);
			if(evolvable == true) {
				cout << source << " can evolve into " << target << " with <= " << max << " evolutionary cost." << endl;
			}
			if(evolvable == false) {
				cout << "Not possible for " << source << " to mutate into " << target << endl;
			}
return;

}


// void cyclic_command(Gene array[], int length)
// purpose: to set up and run can_cyclically_mutate when called in the operations function
// parameters: Gene array[], int first line
// returns:none
// effects: 
// notes: 
void cyclic_command(Gene array[], int length)
{
	string source;
	string target;
	int max;
		
		cin >> source >> max;
		int x = look_up(source, array, length);
		if(x == -1) {
			cout << "Source DNA not in database" << endl;
			return;
		}
		Gene source_gene = array[x];
		can_cyclically_mutate(source_gene, max);
return;
}


string switch_case(string input)
{
	int length = input.length();
	string word = "";
	for(int i = 0; i < length; i++) {
		char c = input[i];
		word += toupper(c);
	}

return word;
}






