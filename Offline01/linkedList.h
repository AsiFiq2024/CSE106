#include <iostream>
using namespace std;

class Node{
public:
    int element;
    Node* next;
    Node* prev;

    Node(int val){
        element = val;
        next = nullptr;
        prev = nullptr;
    }
};

class linkedList{
private:
    Node* head;
    Node* tail;
    Node* cur;
    int Size;

public:
    linkedList(){
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        Size = 0;
    }

    ~linkedList(){
        Node* temp = head;
        while(temp != nullptr){
            Node* nextNode = temp -> next;
            delete temp;
            temp = nextNode;
        }
    }

    void print()
    {
        if(head == nullptr){
            cout << "[ . ]" << endl;
            return;
        }

        Node* temp = head;
        cout << "[ ";
        while(temp -> next != nullptr){
            cout << temp -> element;
            if(temp == cur){
                cout << " | ";
            }
            else{
                cout << " ";
            }
            temp = temp -> next;
        }
        cout << temp -> element;
        if(temp == cur){
            cout << " | ]" << endl;
        }
        else{
            cout << " ]" << endl;
        }
    }
    
    void insert(int item)
    {
        Node* newNode = new Node(item);
        
        if(head == nullptr){
            head = tail = cur = newNode;
            Size++;
            return;
        }

        newNode -> prev = cur;
        newNode -> next = cur -> next;

        if(cur -> next != nullptr){
            cur -> next -> prev = newNode;
        }
        else{
            tail = newNode;
        }
        cur -> next = newNode;
        cur = newNode;
        Size++;
    }

    int delete_cur(){
        if(head == nullptr){
            return -1;
        }
        
        int val = cur -> element;
        Node* temp_cur = cur;

        if(cur -> prev != nullptr){
            cur -> prev -> next = cur -> next;
        }
        else{
            head = cur -> next;
        }

        if(cur -> next != nullptr){
            cur -> next -> prev = cur -> prev;
        }
        else{
            tail = cur -> prev;
        }

        if(cur -> next != nullptr){
            cur = cur -> next;
        }
        else{
            cur = cur -> prev;
        }

        delete temp_cur;
        Size--;
        return val;
    }

    void append(int item){
        Node* newNode = new Node(item);
        
        if(head == nullptr){
            head = tail = cur = newNode;
            Size++;
            return;
        }
        
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
        Size++;
    }

    int size(){
        return Size;
    }

    void prev(int n){
        if(head == nullptr){
            return;
        }

        while(n-- && cur -> prev != nullptr){
            cur = cur -> prev;
        }
    }

    void next(int n){
        if(head == nullptr){
            return;
        }

        while(n-- && cur -> next != nullptr){
            cur = cur -> next;
        }
    }

    int is_present(int n){
        Node* temp = head;
        int found = 0;
        while(temp != nullptr){
            if(temp -> element == n){
                found = 1;
                return found;
            }
            temp = temp -> next;
        }
        return found;
    }

    void clear(){
        Node* temp = head;
        while(temp != nullptr){
            Node* nextNode = temp -> next;
            delete temp;
            temp = nextNode;
        }
        head = tail = cur = nullptr;
        Size = 0;
    }

    int delete_item(int item){
        Node* temp = head;
        int found = 0;
        while(temp != nullptr){
            if(temp -> element == item){
                if(temp == cur){
                    delete_cur();
                }
                else{
                    if(temp == head){
                        head = temp -> next;
                        if(head != nullptr)
                            head->prev = nullptr;
                    }
                    else if(temp == tail){
                        tail = temp -> prev;
                        if(tail != nullptr)
                            tail->next = nullptr;
                    }
                    else{
                        temp -> prev -> next = temp -> next;
                        temp -> next -> prev = temp -> prev;
                    }
                    delete temp;
                    Size--;
                }
                found = 1;
                return found;
            }
            temp = temp -> next;
        }
        return found;
    }

    void swap_ind(int ind1, int ind2){
        if(ind1 >= Size || ind2 >= Size || ind1 < 0 || ind2 < 0){
            return;
        }
        
        Node* n1 = head;
        Node* n2 = head;
        
        while(ind1--){
            n1 = n1 -> next;
        }
        while(ind2--){
            n2 = n2 -> next;
        }

        int temp = n1 -> element;
        n1 -> element = n2 -> element;
        n2 -> element = temp;
    }

    int search(int item){
        Node* temp = head;
        int index = 0;
        while(temp != nullptr){
            if(temp -> element == item){
                cur = temp;
                return index;
            }
            temp = temp -> next;
            index++;
        }
        return -1;
    }

    int find(int ind){
        Node* temp = head;
        
        if(ind >= Size || ind < 0){
            return -1;
        }

        while(ind--){
            temp = temp -> next;
        }

        cur = temp;
        return temp -> element;
    }

    int update(int ind, int value){
        Node* temp = head;

        if(head == nullptr || ind >= Size){
            return -1;
        }

        while(ind--){
            temp = temp -> next;
        }

        int old_val = temp -> element;
        temp -> element = value;
        cur = temp;
        
        return old_val;
    }

    int trim(){
        if(head == nullptr){
            return -1;
        }
        
        Node* last_node = tail;
        int last_item = last_node -> element;

        if(head == tail){
            delete last_node;
            head = tail = cur = nullptr;
            Size = 0;
            return last_item;
        }

        tail = last_node -> prev;
        tail -> next = nullptr;
        if(cur == last_node){
            cur = last_node -> prev;
        }
        delete last_node;
        Size--;
        return last_item;
    }

    void reverse(){
        Node* front = head;
        Node* back = tail;

        int frnt = 0;
        int bck = Size - 1;

        while(frnt < bck){
            int temp = front -> element;
            front -> element = back -> element;
            back -> element = temp;
            front = front -> next;
            back = back -> prev;
            frnt++;
            bck--;
        }
    }
};