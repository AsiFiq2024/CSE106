#include <iostream>
#include <fstream>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c;
    //int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }

    ofstream out_file("out1.txt");
    streambuf *old_buff = cout.rdbuf();
    cout.rdbuf(out_file.rdbuf());

    int key,val;
    string MaxOrMin,TravMethod;

    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        if(c == 'F'){
            in_file >> key;

            if(bst -> find(key)){
                cout << "Key " << key << " found in BST" << endl;
            }
            else{
                cout << "Key " << key << " not found in BST" << endl;
            }
        }
        else if(c == 'E'){
            if(bst -> empty()){
                cout << "Empty" << endl;
            }
            else{
                cout << "Not Empty" << endl;
            }
        }
        else if(c == 'I'){
            in_file >> key;
            val = key;

            if(bst -> insert(key, val)){
                cout << "Key " << key << " inserted into BST, BST (Default): ";
            }
            else{
                cout << "Insertion failed! Key " << key << " already exists in BST, BST (Default): ";
            }

            bst -> print('D');
            cout << endl;
        }
        else if(c == 'D'){
            in_file >> key;

            if(bst -> remove(key)){
                cout << "Key " << key << " removed from BST, BST (Default): ";
            }
            else{
                cout << "Removal failed! Key " << key << " not found in BST, BST (Default): ";
            }

            bst -> print('D');
            cout << endl;
        }
        else if(c == 'M'){
            in_file >> MaxOrMin;

            if(MaxOrMin == "Min"){
                key = bst -> find_min();
                cout << "Minimum value: " << key << endl;
            }
            else{
                key = bst -> find_max();
                cout << "Maximum value: " << key << endl;
            }
        }
        else if(c == 'T'){
            in_file >> TravMethod;

            if(TravMethod == "In"){
                cout << "BST (In-order): ";
                bst -> print('I');
            }
            else if(TravMethod == "Pre"){
                cout << "BST (Pre-order): ";
                bst -> print('P');
            }
            else if(TravMethod == "Post"){
                cout << "BST (Post-order): ";
                bst -> print('O');
            }

            cout << endl;
        }
        else if(c == 'S'){
            cout << "Size: " << bst -> size() << endl;
        }
        // End your code here
    }
    
    in_file.close();
    cout.rdbuf(old_buff);
    out_file.close();
    delete bst;
    
    return 0;
}
