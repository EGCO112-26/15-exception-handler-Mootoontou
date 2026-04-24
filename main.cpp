#include <iostream>
#include <stdexcept>
#include <new>

using namespace std;

class div0 : public exception {
public:
    const char* what() const noexcept override {
        return "Divided by zero";
    }
};

class my_cin : public exception {
public:
    const char* what() const noexcept override {
        return "Incorrect type entered";
    }
};

int main() {
    int x, y;
    double d;
    int repeat;

    do {
        repeat = 0;
        try {
            cout << "Enter 2 numbers: ";
            cin >> x >> y;

            if (cin.fail()) throw my_cin();

            if (x < -10000 || x > 1000 || y < -10000 || y > 1000)
                throw runtime_error("Value out of range");

            if (y == 0) throw div0();

            d = static_cast<double>(x) / y;
            cout << "The result is " << d << endl;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            repeat = 1; 
        }
    } while (repeat);

    cout << "\n--- Testing bad_alloc ---" << endl;
    try { 
        while (true) {
            double* ptr = new double[100000000]; 
        }
    }
    catch (const exception& e) { 
        cerr << "Caught standard exception: " << e.what() << endl;
    }

    return 0;
}