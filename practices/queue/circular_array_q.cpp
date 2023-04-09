#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Queue {

    public:
        Queue();
        ~Queue();
        bool empty();
        bool full();
        int dequeue();
        void enqueue(int);
        void print();

    private:
        const int capacity;
        int *queue;
        int head;
        int tail;
};

Queue::Queue(): head(0), tail(0), capacity(8) {
    try {
        queue = new int(capacity);
    } catch (bad_alloc) {
        exit(EXIT_FAILURE);
    }
}

Queue::~Queue() {
    delete [] queue;
}

bool Queue::empty() {
    return (head == tail);
}

bool Queue::full() {
    return (head == (tail + 1) % capacity);
}

int Queue::dequeue() {
    if (empty()) {
        throw out_of_range("nothing in queue");
    }
    auto value = queue[head];
    queue[head] = -1;
    head = (head + 1) % capacity;
    return value;
}

void Queue::enqueue(int value) {
    if (full()) {
        throw out_of_range("no space to queue");
    }
    queue[tail] = value;
    tail = (tail + 1) % capacity;
}


void Queue::print() {
    cout << "[ ";
    for (auto cursor = head; cursor != tail; cursor = (cursor + 1) % capacity) {
        cout << cursor << ':' << queue[cursor] << ", ";
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
                try {
                    q.enqueue(value);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'T': // is_empty
                placeholder = q.empty() ? "empty" : "not empty";
                cout << "The queue is " + placeholder << endl;
                break;
            case 'L': // full
                placeholder = q.full() ? "full" : "not full";
                cout << "The queue is " + placeholder << endl;
                break;
            case 'Q':
                break;
            default:
                cout << "Unknown command" << endl;
        }
    }
}