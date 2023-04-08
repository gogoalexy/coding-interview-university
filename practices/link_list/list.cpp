#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

struct node {
    int value;
    node *next;
};


class List {

    public:
        List();
        ~List();
        int size();
        bool empty();
        int value_at(int);
        void push_front(int);
        int pop_front();
        void push_back(int);
        int pop_back();
        int front();
        int back();
        void insert(int, int);
        void erase(int);
        int value_n_from_end(int);
        void reverse();
        void remove_value(int);
        void print();

    private:
        node *head;
        int length;
};

List::List(): head(nullptr), length(0) {

}

List::~List() {
    while (head != nullptr) {
        node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

int List::size() {
    return length;
}

bool List::empty() {
    return (length == 0);
}

int List::value_at(int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("invalid index");
    }
    node *cursor = head;
    for (int counter = 0; counter < index; counter++) {
        cursor = cursor->next;
    }
    return cursor->value;
}

void List::push_front(int value) {
    node *new_node;
    try {
        new_node = new node;
    } catch (bad_alloc) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = head;
    head = new_node;
    length++;
}

int List::pop_front() {
    if (length == 0) {
        throw out_of_range("nothing to pop");
    }
    auto value = head->value;
    auto old_head = head;
    head = head->next;
    free(old_head);
    length--;
    return value;
}

void List::push_back(int value) {
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
    } else {
        auto cursor = head;
        while (cursor->next != nullptr) {
            cursor = cursor->next;
        }
        cursor->next = new_node;
    }
    length++;
}

int List::pop_back() {
    if (length == 0) {
        throw out_of_range("nothing to pop");
    }
    auto cursor = head;
    int value;
    if (length == 1) {
        value = cursor->value;
        free(head);
        head = nullptr;
    } else {
        while (cursor->next->next != nullptr) {
            cursor = cursor->next;
        }
        value = cursor->next->value;
        free(cursor->next);
        cursor->next = nullptr;
    }
    length--;
    return value;
}

int List::front() {
    if (head == nullptr) {
        throw out_of_range("no data");
    }
    return head->value;
}

int List::back() {
    if (length == 0) {
        throw out_of_range("no data");
    }
    auto cursor = head;
    while (cursor->next != nullptr) {
        cursor = cursor->next;
    }
    return cursor->value;
}

void List::insert(int index, int value) {
    if (index > length || index < 0) {
        throw out_of_range("index out of range");
    }
    if (index == 0) {
        push_front(value);
    } else {
        node *new_node;
        try {
            new_node = new node;
        } catch (bad_alloc) {
            exit(EXIT_FAILURE);
        }
        new_node->value = value;
        auto cursor = head;
        for (int counter = 0; counter < (index - 1); counter++) {
            cursor = cursor->next;
        }
        new_node->next = cursor->next;
        cursor->next = new_node;
        length++;
    }
}

void List::erase(int index) {
    if (index >= length || index < 0) {
        throw out_of_range("index out of range");
    }
    if (index == 0) {
        pop_front();
    } else {
        auto cursor = head;
        for (int counter = 0; counter < (index - 1); counter++) {
            cursor = cursor->next;
        }
        auto new_neighbor = cursor->next->next;
        free(cursor->next);
        cursor->next = new_neighbor;
        length--;
    }
}

int List::value_n_from_end(int n) {
    if (n < 1 || n > length) {
        throw out_of_range("invald index");
    }
    int index = length - n;
    return value_at(index);
}

void List::reverse() {
    if (length < 2) {
        return;
    }
    auto cursor = head->next;
    auto prev = head;
    auto next = cursor->next;
    prev->next = nullptr;
    while (next != nullptr) {
        cursor->next = prev;
        prev = cursor;
        cursor = next;
        next = cursor->next;
    }
    cursor->next = prev;
    head = cursor;
}

void List::remove_value(int value) {
    auto cursor = head;
    if (length == 0) {
    } else if (cursor->value == value) {
        pop_front();
    } else {
        node *prev;
        while (cursor->next != nullptr) {
            prev = cursor;
            cursor = cursor->next;
            if (cursor->value == value) {
                prev->next = cursor->next;
                free(cursor);
                length--;
                break;
            }
        }
    }
}

void List::print() {
    cout << "[ ";
    for (auto cursor = head; cursor != nullptr; cursor = cursor->next) {
        cout << cursor->value << ", ";
    }
    cout << ']' << endl;
}

int main() {

    auto list = List();
    char control_character = ' ';
    
    while (control_character != 'Q') {
        cout << "Enter the contrl character:";
        cin >> control_character;
        int value, index, output = 0;
        string placeholder = "";
        switch (control_character) {
            case 'P': // print
                list.print();
                break;
            case 'V': // reverse
                list.reverse();
                break;
            case 'R': // remove / remove value
                cout << "Enter the value to remove:";
                cin >> value;
                list.remove_value(value);
                break;
            case 'E': // erase
                cout << "Enter the index to erase:";
                cin >> index;
                try {
                    list.erase(index);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'F': // pop front
                try {
                    output = list.pop_front();
                    cout << "Popped value: " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'O': // pop / pop back
                try {
                    output = list.pop_back();
                    cout << "Popped value: " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'D': // prepend / push front
                cout << "Enter the value to push front:";
                cin >> value;
                list.push_front(value);
                break;
            case 'I': // insert
                cout << "Enter the value to insert:";
                cin >> value;
                cout << "Enter the index to insert:";
                cin >> index;
                try {
                    list.insert(index, value);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'U': // push / push back
                cout << "Enter the value to push back:";
                cin >> value;
                list.push_back(value);
                break;
            case 'A': // at
                cout << "Enter the index to retrieve:";
                cin >> index;
                try {
                    output = list.value_at(index);
                    cout << "The value is " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'N': // value n from end (starts from 1)
                cout << "Enter the reverse index to retrieve:";
                cin >> index;
                try {
                    output = list.value_n_from_end(index);
                    cout << "The value is " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'B': // back
                try {
                    output = list.back();
                    cout << "The value is " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'G': // front
                try {
                    output = list.front();
                    cout << "The value is " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'T': // is_empty
                placeholder = list.empty() ? "empty" : "not empty";
                cout << "The list is " + placeholder << endl;
                break;
            case 'Z': // size
                output = list.size();
                cout << "The list size is " << output << endl;
                break;
            case 'Q':
                break;
            default:
                cout << "Unknown command" << endl;
        }
    }
}