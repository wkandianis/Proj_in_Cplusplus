/*
 * 2048.cpp
 * COMP11 Project 1, Spring 2019, Tufts University
 * Modified by:
 * Date: 
 */

#include <iostream>
#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;

// CONSTANTS (IF ANY) GO HERE

const int ROWS = 4;
const int COMS = 4;
const string RIGHT = "d";
const string LEFT = "a";
const string UP = "w";
const string DOWN = "s";
const string QUIT = "q";


// FUNCTION PROTOTYPES GO HERE
int string2int(string s);

string int2string(int num);

void print_padded_string(string s);

void new_boxR(int box[][COMS], int score[1]);

void new_boxL(int box[][COMS], int score[1]);

void new_boxU(int box[][COMS], int score[1]);

void new_boxD(int box[][COMS], int score[1]);

void play();

void shiftR(int box[][COMS]);

void shiftL(int box[][COMS]);

void shiftU(int box[][COMS]);

void shiftD(int box[][COMS]);

void addR(int box[][COMS], int score[1]);

void addL(int box[][COMS], int score[1]);

void addD(int box[][COMS], int score[1]);

void addU(int box[][COMS], int score[1]);

void generate_new(int box[][COMS]);

void new_board(int box[][COMS]);

void move(int box[][COMS], int score[]);

void print_board(int box[][COMS]);

bool game_over(int box[][COMS]);

int main() {
    play();
    return 0;
}





void play() {
    // START YOUR CODE HERE
    srand(time(NULL));
    int box[ROWS][COMS];
    int score[1];

    cout << "Start game. Enter 'a' for left, 'd' for right, 'w' for up, and 's' for down." << endl;
    cout << "Score: 0" << endl;

    new_board(box);
   
    print_board(box);

        while(game_over(box) == false) {

            move(box, score);
            
            generate_new(box);

            print_board(box);


        }

            if(game_over(box) == true) {
            cout << "Game over! Your score is: " << score[0] << endl;
            }
return;
}

/* string2int
 * Convert a string to an int. Returns the int form of the given string.
 * Throw logic error if the string is not numerical. 
 */
int string2int(string s) {
    stringstream ss(s);
    int result;
    ss >> result;
    if (ss.fail())
        throw logic_error("ERROR: " + s + " is not a numerical value");
    return result;
}

/* Converts an int to string.
 * Returns the string form of the given int
 */
string int2string(int num) {
    string result;
    ostringstream oss;
    oss << num;
    result = oss.str();
    return result;
}
/* Print a string (persumably an int in the form of a string) with 
 * right paddings of up to 5 spaces
 */
void print_padded_string(string s) {
    printf("%-6s", s.c_str());
}





// void new_boxR(int box[ROWS][COMS])
// purpose: run the functions shift, move and shift again in order to find the new value of the box to the right
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void new_boxR(int box[][COMS], int score[1]) {
  
    shiftR(box);
            
    addR(box, score);
           
    shiftR(box);
         
return; 
}
                                    

// void new_boxL(int box[ROWS][COMS])
// purpose: run the functions shift, move and shift again in order to find the new value of the box to the left
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void new_boxL(int box[][COMS], int score[1]) {
    
    shiftL(box);
          
    addL(box, score);
     
    shiftL(box);
   
return; 
}


// void new_boxD(int box[ROWS][COMS])
// purpose: run the functions shift, move and shift again in order to find the new value of the box below it
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void new_boxD(int box[][COMS], int score[1]) {
   
    shiftD(box);
       
    addD(box, score);
        
    shiftD(box);
        
return; 
}

// void new_boxL(int box[ROWS][COMS])
// purpose: run the functions shift, move and shift again in order to find the new value of the box above it
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none                                   
void new_boxU(int box[][COMS], int score[1]) {
   
    shiftU(box);
            
    addU(box, score);
            
    shiftU(box);
         
return; 
}
                                    


// void shiftR(int box[ROWS][COMS])
// purpose: shift current index to the right while the index to the right is equal to 0
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void shiftR(int box[][COMS]) {

        int initial_value;
        
        

    for(int i = 0; i < ROWS; i++) {
        for(int j = 2; j >= 0; j--) {

            int C = j;
            

                while((C < 3) and (box[i][C + 1] == 0)) {
                initial_value = box[i][C];
                box[i][C + 1] = initial_value;
      
                box[i][C] = 0;
        
                C++;
                }
            
        }
    }
      
return;
}


// void shiftL(int box[ROWS][COMS])
// purpose: shift current index to the left while the index to the left is equal to 0
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void shiftL(int box[][COMS]) {
        int initial_value;
     
       

    for(int i = 0; i < ROWS; i++) {
        for(int j = 3; j > 0; j--) {

            int C = j;
            int R = i;

                while((C > 0) and (box[R][C - 1] == 0)) {
                initial_value = box[i][C];
                box[i][C - 1] = initial_value;
        
                    box[i][C] = 0;
                    C--;
                }
            
        }
    }
       
return;
}


// void shiftU(int box[ROWS][COMS])
// purpose: shift current index up while the index above it is equal to 0
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void shiftU(int box[][COMS]) {
    int initial_value;

    

    for(int i = 3; i > 0; i--) {
        for(int j = 0; j < COMS; j++) {

            int C = i;
            

                while((C > 0) and (box[C - 1][j] == 0)) {
                initial_value = box[C][j];
                box[C - 1][j] = initial_value;
        
                    box[C][j] = 0;
                    C--;
                }
        }
    }
return;
}



// void shiftU(int box[ROWS][COMS])
// purpose: shift current index down while the index below it is equal to 0
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void shiftD(int box[][COMS]) {

        int initial_value;
        
        

    for(int i = 2; i >= 0; i--) {
        for(int j = 0; j < COMS; j++) {

            int R = i;
            

                while((R < 3) and (box[R + 1][j] == 0)) {
                initial_value = box[R][j];
                box[R + 1][j] = initial_value;
      
                box[R][j] = 0;
        
                R++;
                }
            
        }
    }
      
return;
}


// void addR(int box[ROWS][COMS])
// purpose: add the current index to the index to the right only if they are equal
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void addR(int box[][COMS], int score[1]) {

    int initial_value;
    
    
    for(int i = 0; i < ROWS; i++) {
        for(int j = 3; j > 0; j--) {

            if(box[i][j] == box[i][j - 1]) {
            initial_value = box[i][j] + box[i][j - 1];
            box[i][j] = initial_value;
            box[i][j - 1] = 0;
            score[0] = score[0] + initial_value;
            }
        }
                   
    } 
     cout << "Current score: " << score[0] << endl;
return;
}


// void addL(int box[ROWS][COMS])
// purpose: add the current index to the index to the left only if they are equal
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void addL(int box[][COMS], int score[1]) {
    
    int initial_value;
  
    

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COMS - 1; j++) {

            if(box[i][j] == box[i][j + 1]) {
            initial_value = box[i][j] + box[i][j + 1];
            box[i][j] = initial_value;
            box[i][j + 1] = 0;
            score[0] = score[0] + initial_value;
            }
        }
                
    }  
    cout << "Current score: " << score[0] << endl;
return;
}


// void addD(int box[ROWS][COMS])
// purpose: add the current index to the index below it only if they are equal
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void addD(int box[][COMS], int score[1]) {

    int initial_value;
    

    for(int i = 0; i < ROWS - 1; i++) {
        for(int j = 0; j < COMS; j++) {
            if(box[i][j] == box[i + 1][j]) {
                initial_value = box[i][j] + box [i + 1][j];
                box[i + 1][j] = initial_value;
                box[i][j] = 0;
                score[0] = score[0] + initial_value;
            }
        }
    }
 cout << "Current score: " << score[0] << endl;
return;
}

// void addR(int box[ROWS][COMS])
// purpose: add the current index to the index above it only if they are equal
// parameters: the array named box, the array named score
// returns: none
// effects: 
// notes: none
void addU(int box[][COMS], int score[1]) {

    int initial_value;
 
    

    for(int i = 0; i < ROWS - 1; i++) {
        for(int j = 0; j < COMS; j++) {

            if(box[i][j] == box[i + 1][j]) {
            initial_value = box[i + 1][j] + box[i][j];
            box[i][j] = initial_value;
            box[i + 1][j] = 0;
            score[0] = score[0] + initial_value;
            }
        }
                
    }
 cout << "Current score: " << score[0] << endl;
return;
}



// void new_board(int box[ROWS][COMS])
// purpose: randomly assign 2 out of 4 indexes to be 2, while the other are -
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void new_board(int box[][COMS]) {

    int random = 0;
    int random1 = 0;
    
    while((random == random1) and (random < 3) and (random1 < 3)) {
    

        random = rand() % 4;

        random1 = rand() % 3;


    }


        for(int i = 0; i < ROWS; i++) {
            for(int j = 0; j < COMS; j++) {

                if(box[i][j] != 2) {
                box[i][j] = 0;
                }
        
                    box[random1][random1] = 2;
        

                    box[random1][random1] = 2;


            }
        }
return;
}








// void generate_new(int box[ROWS][COMS])
// purpose: randomly input a new number into the array, with a 90% chance of it being a 2 and a 10% chance of it being a 4
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void generate_new(int box[][COMS]) {

    bool full_board = true;
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COMS; j++) {
            if(box[i][j] == 0) {
                full_board = false;
            }
        }
    }
    
    if(full_board == false) {
    int new_random1 = 0;
    int new_number = 0;
    int new_random2 = 0;
    int prob = rand() % 10;

    if(prob == 0) {
        new_number = 4;
    } else {
        new_number = 2;
    }
            

            new_random1 = rand() % 4;
            new_random2 = rand() % 4;
            while(box[new_random1][new_random2] != 0) {
            new_random1 = rand() % 4;
            new_random2 = rand() % 4;
            }
        
        
                box[new_random1][new_random2] = new_number;
    }

   
return;
}



// void move(int box[ROWS][COMS])
// purpose: to take in the directional input and call the corresponding function
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void move(int box[][COMS], int score[1]) {
    

    string input;

    cin >> input;

    if(input == RIGHT) {
        
        new_boxR(box, score);
    }

    
    else if(input == LEFT) {
       
        new_boxL(box, score);
    }

    else if(input == UP) {
       
        new_boxU(box, score);
    }
        
    else if(input == DOWN) {

        new_boxD(box, score);
    }

    else if(input == QUIT) {

        return;
    }
   
        
    else {
        cout << "Command not recognized. Please try again." << endl;
    }
       
        return; 
}




// void print_board(int box[ROWS][COMS])
// purpose: take in the array, convert the 0s to -, and convert the array into a string so the array can be printed as a padded function
// parameters: the array named box
// returns: none
// effects: 
// notes: none
void print_board(int box[][COMS])
{

    string result;

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COMS; j++) {
            
            if(box[i][j] == 0) {
                result = "-";
            } else {
                    result = int2string(box[i][j]);
            }

                print_padded_string(result);
        }
        cout << endl;
    }
return;
}



// void game_over(int box[ROWS][COMS])
// purpose: boolean function that allows the game to continue as long as there are possible moves
// parameters: the array named box
// returns: none
// effects: 
// notes: none
bool game_over(int box[][COMS]) {

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COMS; j++) {

            if(box[i][j] == 0) {
                return false;
            }
            if(i != 0) {
                if(box[i - 1][j] == box[i][j]) {
                    return false;
                    }
                }
            if(i != 3) {
                if(box[i + 1][j] == box[i][j]) {
                    return false;
                }
            }
            if(j != 0) {
                if(box[i][j - 1] == box[i][j]) {
                    return false;
                }
            }
            if(j != 3) {
                if(box[i][j + 1] == box[i][j]) {
                    return false;
                }
            } 
         
        }
    }
return true; 
}






























