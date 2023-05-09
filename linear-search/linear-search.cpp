#include <iostream>
#include <functional>
#include <chrono>
#include <vector>

using namespace std;

template<typename T>
int linear_search(vector<T>& v, function<bool(T v)> predicate);

int main()
{
    long n = 0;
    cout << "Enter count of demo data records (0 < N <= 1000000): ";
    cin >> n;

    if (n < 1) 
    {
        cout << "A number must be more than 0" << endl;
        return 0;
    }
    if (n > 1e6) 
    {
        cout << "The number of the range must be less or equals to 1000000" << endl;
        return 0;
    }
    
    int left_rand = 0;
    int right_rand = 0;

    cout << "Enter the value of the left end of the range: ";
    cin >> left_rand;

    cout << "Enter the value of the right end of the range: ";
    cin >> right_rand;

    if (left_rand >= right_rand) 
    {
        cout << "The number of the right end must be more than left end of the range" << endl;
        return 0;
    }


    srand(time(nullptr));
    vector<int> v = {};
    for (int i = 0; i < n; i++) {
        int value = left_rand + (rand() % (right_rand - left_rand + 1));
        v.push_back(value);
    }

    char answer = '\0';
    cout << "Would you like to print generated values? (Y/N): ";
    cin >> answer;

    if (answer == 'Y') {
        for (int i = 0; i < n; i++) {
            cout << v.at(i) << " ";
        }
        cout << endl << endl;
    }

    while (true) {
        int x = 0;
        cout << "Input a number to find: ";
        cin >> x;

        auto start = chrono::high_resolution_clock::now();
        int index = linear_search<int>(v, [x](int a) {
            return a == x;
        });
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        auto ms = chrono::duration_cast<std::chrono::milliseconds>(elapsed);
        auto mcs = chrono::duration_cast<std::chrono::microseconds>(elapsed) - chrono::duration_cast<std::chrono::microseconds>(ms);
        
        if (index != -1) {
            cout << "Element found at index " << index << endl;
        }
        else {
            cout << "Element not found" << endl;
        }
        std::cout << "Execution time: " << ms.count() << "." << mcs.count() << " ms\n";

        cout << endl;
        cout << "Would you like to find another one value? (Y/N): ";
        cin >> answer;

        if (answer == 'N') {
            break;
        }
        cout << endl;
    }



    return 0;
}

template<typename T>
int linear_search(vector<T> &v, function<bool(T v)> predicate) {
    for (int i = 0; i < v.size(); i++) {
        if (predicate(v.at(i))) {
            return i;
        }
    }
    return -1;
}
