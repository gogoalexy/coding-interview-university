#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int binary_search(int needle, vector<int> haystack) {
    auto low = 0;
    auto high = haystack.size() - 1;
    while (high > low) {
        auto mid = (high + low) / 2;
        if (haystack.at(mid) == needle) {
            return mid;
        } else if (haystack.at(mid) > needle) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int binary_search_recurse(int needle, vector<int> haystack, int low, int high) {
    if (high <= low) {
        return -1;
    }
    auto mid = (high + low) / 2;
    if (haystack.at(mid) == needle) {
        return mid;
    } else if (haystack.at(mid) > needle) {
        return binary_search_recurse(needle, haystack, low, mid);
    } else {
        return binary_search_recurse(needle, haystack, mid + 1, high);
    }
}

int main() {
    vector<int> haystack{5, 8, 30, 31, 35, 47, 89, 91, 112};
    int index;
    cout << "Binary search" << endl;
    index = binary_search(0, haystack);
    cout << "Search for 0: " << index << endl;
    index = binary_search(91, haystack);
    cout << "Search for 91: " << index << endl;
    index = binary_search(22, haystack);
    cout << "Search for 22: " << index << endl;
    
    cout << "Binary search (recursive)" << endl;
    index = binary_search_recurse(0, haystack, 0, haystack.size() - 1);
    cout << "Search for 0: " << index << endl;
    index = binary_search_recurse(91, haystack, 0, haystack.size() - 1);
    cout << "Search for 91: " << index << endl;
    index = binary_search_recurse(22, haystack, 0, haystack.size() - 1);
    cout << "Search for 22: " << index << endl;
}