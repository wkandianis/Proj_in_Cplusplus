#include <iostream>
#include <fstream>
#include <string>
#include "ArrayList.h"
#include "FSTree.h"

using namespace std;
void traversal(DirNode *root, string directory);

int main(int argc, char *argv[])
{

   if(argc != 3) {
       cerr << "Usage:  gerp directory output_file" << endl;
       exit(0);
   } else {
       string directory = argv[1];
       FSTree myTree = FSTree(directory);
       DirNode *root = myTree.getRoot();
       traversal(root, directory);
   }
    
    return 0;
}

void traversal(DirNode *node, string directory) 
{
  ArrayList myList;
    string currPath = directory + '/';
    if(node == nullptr) {
        return;
    }
    //prints each file name after the current path
    for(int i = 0; i < node->numFiles(); i++) {       
        cout << currPath << node->getFile(i) << endl;
        myList.read_file(node->getFile(i));

    }
    //after all files have been printed, recursively calls itself with first subdirectory
    //in order to print the files in there
    for(int j = 0; j < node->numSubDirs(); j++) {
        traversal(node->getSubDir(j), currPath + node->getSubDir(j)->getName());
    }
}