#include <iostream>

using namespace std;

struct List{
    int index;
    char name[10];
    List *next;
}*head, *tail;

List* add(int index, char *name){
    List *p = new List;

    p->index = index;
    p->next = nullptr;
    tail->next = p;
    tail = p;
}

void outPut(){
    List *p;
    p = head;
    while(p != nullptr){
        if(p == head){
            cout<<p->index<<"| ";
            p = p->next;
        }else{
            cout<<p->index<<" ";
            p = p->next;
        }
    }
}

void deleteNode(int index){
    List *p = head; List *prev = head;

    while(p->index != index){
        prev = p;
        p = p->next;
    }
    if(p){
        prev->next = p->next;
        delete(p);
    }

}

int main() {
    cout << "Hello, World!" << endl;
    head = new List;
    tail = head;
    head->index = -1;
    for(int i = 0; i<10; i++){
        add(i, name);
    }
    outPut();
    return 0;
}