#include <iostream>
#include <fstream>
#include "arrayList.h"
//#include "linkedList.h"

using namespace std;

int main()
{
    ifstream file("in.txt");
    if(!file){
        cout << "Error while opening file" << endl;
        return 1;
    }

    arrayList list;
    //linkedList list;

    int func, param, param2;
    while(file >> func && func != 0)
    {
        if(func == 1 && file >> param){
            cout << "Insert " << param << endl;
            list.insert(param);
            list.print();
        }
        else if(func == 2){
            cout << "Delete current item" << endl;
            int ret = list.delete_cur();
            if(ret>=0){
                list.print();
                cout << ret << " is deleted" << endl;
            }
            else
                cout << "List is empty" << endl;
        }
        else if(func == 3 && file >> param){
            cout << "Append " << param << endl;
            list.append(param);
            list.print();
        }
        else if(func == 4){
            int ret = list.size();
            cout << "Size of the list is: " << ret << endl;
        }
        else if(func == 5 && file >> param){
            cout << "Prev " << param << endl;
            list.prev(param);
            list.print();
        }
        else if(func == 6 && file >> param){
            cout << "Next " << param << endl;
            list.next(param);
            list.print();
        }
        else if(func == 7 && file >> param){
            int ret = list.is_present(param);
            if(ret){
                cout << param << " is present" << endl;
            }
            else{
                cout << param << " is not present" << endl;
            }
        }
        else if(func == 8){
            list.clear();
            cout << "Clear list" << endl;
            list.print();
        }
        else if(func == 9 && file >> param){
            int ret = list.delete_item(param);
            if(ret){
                cout << "Delete " << param << endl;
            }
            else{
                cout << param << " is not present" << endl;
            }
            list.print();
        }
        else if(func == 10 && file >> param >> param2){
            list.swap_ind(param,param2);
            list.print();
        }
        else if(func == 11 && file >> param){
            int ret = list.search(param);
            cout << "Search " << param << endl;
            if(ret >= 0){
                list.print();
                cout << param << " is found at " << ret << endl;
            }
            else{
                cout << param << " is not found" << endl;
            }
        }
        else if(func == 12 && file >> param){
            int ret = list.find(param);
            cout << "Find " << param << endl;
            if(ret >= 0){
                list.print();
                cout << ret << " is found at " << param << endl;
            }
            else{
                cout << param << " is not a valid index" << endl;
            }
        }
        else if(func == 13 && file >> param >> param2){
            int ret = list.update(param,param2);
            cout << "Update element at " << param << endl;
            if(ret >= 0){
                list.print();
                cout << ret << " is updated by " << param2 << endl;
            }
            else{
                cout << param << " is not a valid index" << endl;
            }
        }
        else if(func == 14){
            int ret = list.trim();
            cout << "Trim" << endl;
            if(ret >= 0){
                list.print();
                cout << ret << " removed" << endl;
            }
            else{
                cout << "The list is empty" << endl;
            }
        }
        else if(func == 15){
            list.reverse();
            cout << "Reverse" << endl;
            list.print();
        }
    }

    cout << "End" << endl;

    return 0;
}