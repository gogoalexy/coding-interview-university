#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

struct node {
    int value;
    node *next;
};


class Queue {

    public:
        Queue();
        ~Queue();
        bool empty();
        int dequeue();
        void enqueue(int);
        void print();

    private:
        node *head;
        node *tail;
        int length;
};

Queue::Queue(): head(nullptr), tail(nullptr), length(0) {

}

Queue::~Queue() {
    while (head != nullptr) {
        node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

bool Queue::empty() {
    return (length == 0);
}

int Queue::dequeue() {
    if (length == 0) {
        throw out_of_range("nothing in queue");
    }
    auto value = head->value;
    auto old_head = head;
    head = head->next;
    free(old_head);
    length--;
    return value;
}

void Queue::enqueue(int value) {
    node *new_node;
    try {
        new_node = new node;
    } catch (bad_alloc) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = nullptr;
    if (length == 0) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
    length++;
}


void Queue::print() {
    cout << "[ ";
    for (auto cursor = head; cursor != nullptr; cursor = cursor->next) {
        cout << cursor->value << ", ";
    }
    cout << ']' << endl;
}

int main() {

    auto q = Queue();
    char control_character = ' ';
    
    while (control_character != 'Q') {
        cout << "Enter the contrl character:";
        cin >> control_character;
        int value, output = 0;
        string placeholder = "";
        switch (control_character) {
            case 'P': // print
                q.print();
                break;
            case 'F': // pop front / dequeue
                try {
                    output = q.dequeue();
                    cout << "Popped value: " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'U': // push / push back / enqueue
                cout << "Enter the value to queue:";
                cin >> value;
                q.enqueue(value);
                break;
            case 'T': // is_empty
                placeholder = q.empty() ? "empty" : "not empty";
                cout << "The queue is " + placeholder << endl;
                break;
            case 'Q':
                break;
            default:
                cout << "Unknown command" << endl;
        }
    }
}