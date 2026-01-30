#include <iostream>
using namespace std;

class arrayList{
    int* array;
    int capacity;
    int Size;
    int cur;

public:
    arrayList(){
        capacity = 2;
        Size = 0;
        cur = -1;
        array = new int[capacity];
    }
    ~arrayList(){
        delete[] array;
    }

    void increase_capacity(){
        if(Size*2 >= capacity){
            int newCap = capacity * 2;
            int* newArr = new int[newCap];
            for(int i = 0; i < Size; i++){
                newArr[i] = array[i];
            }
            delete[] array;
            array = newArr;
            capacity = newCap;
        }
    }

    void decrease_capacity(){
        if(Size*4 <= capacity){
            int newCap = capacity / 2;
            int* newArr = new int[newCap];
            for(int i = 0; i < Size; i++){
                newArr[i] = array[i];
            }
            delete[] array;
            array = newArr;
            capacity = newCap;
        }
    }

    void print(){
        if(Size == 0){
            cout << "[ . ]" << endl;
            return;
        }
        cout << "[ ";
        for(int i = 0; i < Size; i++){
            cout << array[i];
            if(i == cur){
                cout << " | ";
            }
            else{
                cout << " ";
            }
        }
        cout << " ]" << endl;
    }

    void insert(int item){
        increase_capacity();
        if(Size == 0){
            array[0] = item;
            cur = 0;
            Size++;
        }
        else{
            for(int i = Size - 1; i > cur; i--){
                array[i+1] = array[i];
            }
            array[cur + 1] = item;
            cur++;
            Size++;
        }
    }

    int delete_cur(){
        if(Size == 0){
            return -1;
        }

        int old_cur = array[cur];

        if(cur == Size - 1 && cur != 0){
            Size--;
            cur--;
        }
        else{
            for(int i = cur; i < Size - 1; i++){
                array[i] = array[i + 1];
            }
            Size--;
        }
        
        decrease_capacity();
        return old_cur;
    }

    void append(int item){
        increase_capacity();
        array[Size] = item;
        Size++;
    }

    int size(){
        return Size;
    }

    void prev(int n){
        if(cur < n){
            cur = 0;
        }
        else{
            cur -= n;
        }
    }

    void next(int n){
        if((Size - 1 - cur) < n){
            cur = Size - 1;
        }
        else{
            cur += n;
        }
    }

    int is_present(int n){
        for(int i = 0; i < Size; i++){
            if(array[i] == n){
                return 1;
            }
        }
        return 0;
    }

    void clear(){
        delete[] array;
        Size = 0;
        capacity = 2;
        array = new int[capacity];
        cur = -1;
    }

    int delete_item(int item){
        for(int i = 0; i < Size; i++){
            if(array[i] == item){
                for(int j = i; j < Size - 1; j++){
                    array[j] = array[j + 1];
                }
                cur = i;
                Size--;
                decrease_capacity();
                return 1;
            }
        }
        return 0;
    }

    void swap_ind(int ind1, int ind2){
        if(ind1 >= Size || ind2 >= Size || ind1 < 0 || ind2 < 0){
            return;
        }
        
        int temp = array[ind1];
        array[ind1] = array[ind2];
        array[ind2] = temp;
        cout << "Swap index " << ind1 << " and " << ind2 << endl;
    }

    int search(int item){
        for(int i = 0; i < Size; i++){
            if(array[i] == item){
                cur = i;
                return i;
            }
        }
        return -1;
    }

    int find(int ind){
        if(ind >= Size || ind < 0){
            return -1;
        }
        else{
            cur = ind;
            return array[ind];
        }
    }
    
    int update(int ind, int value){
        if(ind >= Size || ind < 0){
            return -1;
        }
        else{
            cur = ind;
            int old_val = array[ind];
            array[ind] = value;
            return old_val;
        }
    }

    int trim(){
        if(Size == 0){
            return -1;
        }
        int old_val = array[Size - 1];
        Size--;
        if(cur == Size - 1 && cur != 0){
            cur--;
        }
        decrease_capacity();
        return old_val;
    }

    void reverse(){
        if(Size == 0){
            return;
        }

        int low = 0;
        int up = Size - 1;

        while(low < up){
            int temp = array[low];
            array[low] = array[up];
            array[up] = temp;

            low++;
            up--;
        }
    }
};

