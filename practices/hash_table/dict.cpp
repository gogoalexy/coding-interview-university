#include <cmath>
#include <exception>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class hash_data {

    public:
        hash_data();
        bool is_null();
        bool is_deleted();
        int get_key();
        int get_value();
        void set(int, int);
        void del();
    private:
        int key;
        int value;
        bool uninit;
        bool deleted;
};

class Dict {

    public:
        Dict();
        int hash(int);
        void add(int, int);
        bool exists(int);
        int get(int);
        void remove(int);
        void print();

    private:
        const hash_data placeholder;
        vector<hash_data> table;
        int capacity;
        int used;
};

hash_data::hash_data(): value(0), uninit(true), deleted(false){

}

bool hash_data::is_deleted() {
    return deleted;
}

bool hash_data::is_null() {
    return uninit;
}

int hash_data::get_key() {
    return key;
}

int hash_data::get_value() {
    return value;
}

void hash_data::set(int key, int value) {
    this->key = key;
    this->value = value;
    deleted = false;
    uninit = false;
}

void hash_data::del() {
    value = 0;
    key = 0; 
    deleted = true;
}

Dict::Dict(): placeholder(hash_data()), capacity(8), used(0) {
    table.assign(capacity, placeholder);
}

int Dict::hash(int k) {
    return k % capacity;
}

void Dict::add(int key, int value) {
    int index = hash(key);
    while (index < capacity) {
        if (table.at(index).is_null()) {
            table.at(index).set(key, value);
            used++;
            if (used == capacity) {
                vector<hash_data> tmp = std::move(table);
                capacity *= 2;
                table.assign(capacity, placeholder);
                for (auto &element : tmp) {
                    if (!element.is_null() && !element.is_deleted()) {
                        this->add(element.get_key(), element.get_value());
                    }
                }
            }
            return;
        }
        if (table.at(index).get_key() == key) {
            table.at(index).set(key, value);
            return;
        }
        index++;
    }
}

bool Dict::exists(int key) {
    int index = hash(key);
    while (index < capacity) {
        if (table.at(index).is_null()) {
            return false;
        }
        if (table.at(index).get_key() == key) {
            if (table.at(index).is_deleted()) {
                return false;
            } else {
                return true;
            }
        }
        index++;
    }
    return false;
}

int Dict::get(int key) {
    int index = hash(key);
    while (index < capacity) {
        if (table.at(index).is_null()) {
            throw runtime_error("Not exists");
        }
        if (table.at(index).get_key() == key) {
            if (table.at(index).is_deleted()) {
                throw runtime_error("Deleted");
            } else {
                return table.at(index).get_value();
            }
        }
        index++;
    }
    throw runtime_error("Not found");
}

void Dict::remove(int key) {
    int index = hash(key);
    while (index < capacity) {
        if (table.at(index).is_null()) {
            throw runtime_error("Not exists");
        }
        if (table.at(index).get_key() == key) {
            table.at(index).del();
            used--;
            if (used < capacity/4) {
                vector<hash_data> tmp = std::move(table);
                capacity /= 2;
                table.assign(capacity, placeholder);
                for (auto &element : tmp) {
                    if (!element.is_null() && !element.is_deleted()) {
                        this->add(element.get_key(), element.get_value());
                    }
                }
            }
            return;
        }
        index++;
    }
    throw runtime_error("Not found");
}


int main() {

    auto dict = Dict();
    char control_character = ' ';
    
    while (control_character != 'Q') {
        cout << "Enter the contrl character:";
        cin >> control_character;
        int key, value, output = 0;
        string placeholder = "";
        switch (control_character) {
            case 'H': // hash
                cout << "Enter the key to hash:";
                try {
                    cin >> key;
                    output = dict.hash(key);
                    cout << "Hashed key: " << output << endl;
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
                break;
            case 'A': // add
                cout << "Enter the key to add:";
                try {
                    cin >> key;
                    cout << "Enter the value:";
                    cin >> value;
                    dict.add(key, value);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
                break;
            case 'E': // exists
                cout << "Enter the key to check:";
                try {
                    cin >> key;
                    placeholder = dict.exists(key) ? "exists" : "not exists";
                    cout << "The key " + placeholder << endl;
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
                break;
            case 'G': // get
                cout << "Enter the key to retrieve:";
                try {
                    cin >> key;
                    output = dict.get(key);
                    cout << "Got value: " << output << endl;
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
                break;
            case 'R': // remove
                cout << "Enter the key to remove:";
                try {
                    cin >> key;
                    dict.remove(key);
                } catch (exception &e) {
                    cout << e.what() << endl;
                }
                break;
            case 'Q':
                break;
            default:
                cout << "Unknown command" << endl;
        }
    }
}