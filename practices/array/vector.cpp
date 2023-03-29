#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Vector {

    public:
        Vector();
        ~Vector();
        int size();
        int capacity();
        bool is_empty();
        int at(int);
        void push(int);
        void insert(int, int);
        void prepend(int);
        int pop();
        void erase(int);
        void remove(int);
        int find(int);
        void print();

    protected:
        void resize(int);
        bool is_in_range(int);

    private:
        int* data;
        int full_length;
        int cursor;

};

Vector::Vector():full_length(8), cursor(0) {
    data = (int*)malloc(8 * sizeof(int));
}

Vector::~Vector() {
    free(data);
}

int Vector::size() {
    return cursor;
}

int Vector::capacity() {
    return full_length;
}

bool Vector::is_empty() {
    return (cursor == 0);
}

int Vector::at(int index) {
    if (is_in_range(index)) {
        return *(data + index);
    } else {
        throw out_of_range("vector out of range");
    }
}

void Vector::push(int item) {
    *(data + cursor) = item;
    cursor++;
    if (cursor == full_length) {
        resize(full_length * 2);
    }
}

void Vector::insert(int index, int item) {
    if (!is_in_range(index) && index != cursor) {
        throw out_of_range("unreachable index");
    }
    int mover = cursor - 1;
    while (mover >= index) {
        *(data + mover + 1) = *(data + mover);
        mover--;
    }
    *(data + index) = item;
    cursor++;
    if (cursor == full_length) {
        resize(full_length * 2);
    }
}

void Vector::prepend(int item) {
    insert(0, item);
}

int Vector::pop() {
    if (cursor == 0) {
        throw out_of_range("nothing to pop");
    }
    int value = *(data + cursor - 1);
    *(data + cursor - 1) = 0;
    cursor--;
    if (cursor < full_length / 4) {
        resize(full_length / 2);
    }
    return value;
}

void Vector::erase(int index) {
    if (!is_in_range(index)) {
        throw out_of_range("invalid index");
    }
    int mover = index + 1;
    while (mover < cursor) {
        *(data + mover - 1) = *(data + mover);
        mover++;
    }
    *(data + cursor) = 0;
    cursor--;
    if (cursor < full_length / 4) {
        resize(full_length / 2);
    }
}

void Vector::remove(int item) {
    int crawler = 0;
    while (crawler < cursor) {
        if (*(data + crawler) == item) {
            erase(crawler);
            continue;
        }
        crawler++;
    }
}

int Vector::find(int item) {
    int finder = 0;
    while (finder < cursor) {
        if (*(data + finder) == item) {
            return finder;
        } else {
            finder++;
        }
    }
    return -1;
}

void Vector::resize(int new_capacity) {
    int* new_data = (int*)malloc(new_capacity * sizeof(int));
    int crawler = 0;
    while (crawler < cursor) {
        *(new_data + crawler) = *(data + crawler);
        crawler++;
    }
    free(data);
    full_length = new_capacity;
    data = new_data;
}

bool Vector::is_in_range(int index) {
    if (index >=0 && index < cursor) {
        return true;
    } else {
        return false;
    }
}

void Vector::print() {
    cout << "[ ";
    for (int index = 0; index < cursor; index++) {
        cout << *(data + index) << ", ";
    }
    cout << "]" << endl;
}

int main() {

    auto vector = Vector();
    char control_character = ' ';
    
    while (control_character != 'Q') {
        cout << "Enter the contrl character:";
        cin >> control_character;
        int value, index, output = 0;
        string placeholder = "";
        switch (control_character) {
            case 'P': // print
                vector.print();
                break;
            case 'F': // find
                cout << "Enter the value to find:";
                cin >> value;
                output = vector.find(value);
                if (output == -1) {
                    cout << "Not found" << endl;
                } else {
                    cout << "Finded at: " << output << endl;
                }
                break;
            case 'R': // remove
                cout << "Enter the value to remove:";
                cin >> value;
                vector.remove(value);
                break;
            case 'E': // erase
                cout << "Enter the index to erase:";
                cin >> index;
                try {
                    vector.erase(index);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'O': // pop
                try {
                    output = vector.pop();
                    cout << "Popped value: " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'D': // prepend
                cout << "Enter the value to prepend:";
                cin >> value;
                vector.prepend(value);
                break;
            case 'I': // insert
                cout << "Enter the value to insert:";
                cin >> value;
                cout << "Enter the index to insert:";
                cin >> index;
                try {
                    vector.insert(index, value);
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'U': // push
                cout << "Enter the value to push:";
                cin >> value;
                vector.push(value);
                break;
            case 'A': // at
                cout << "Enter the index to retrieve:";
                cin >> index;
                try {
                    output = vector.at(index);
                    cout << "The value is " << output << endl;
                } catch (exception &e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            case 'T': // is_empty
                placeholder = vector.is_empty() ? "empty" : "not empty";
                cout << "The vector is " + placeholder << endl;
                break;
            case 'C': // capacity
                output = vector.capacity();
                cout << "The capacity is " << output << endl;
                break;
            case 'Z': // size
                output = vector.size();
                cout << "The vector size is " << output << endl;
                break;
            case 'Q':
                break;
            default:
                cout << "Unknown command" << endl;
        }
    }
}