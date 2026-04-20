#include <iostream>
#include <cmath>
#include <exception>

using namespace std;

// Class ของ div0
class div0 : public exception {
public:
    const char* what() const noexcept override {
        return "Divided by zero";
    }
};

// Class สำหรับการจัดการ cin.fail()
class my_cin : public exception {
public:
    const char* what() const noexcept override {
        return "Incorrect type entered";
    }
};

int main() {
    // ทดสอบ bad_alloc
    try {
        for (int i = 0; i < 1000; i++) {
            double* ptr = new double[1000000];
            delete[] ptr; 
    }
    catch (const bad_alloc& e) {
        cerr << "Caught standard exception: " << e.what() << endl;
    }

    int x, y;
    double d;
    int repeat;

    do {
        repeat = 0;
        try {
            // รับเลข 2 เลข 
            cout << "Enter 2 numbers: ";
            cin >> x >> y;

            // ตรวจสอบ cin.fail() ถ้าใส่ตัวอักษรแทนตัวเลข
            if (cin.fail()) throw my_cin();

            // (Optional) ตัวเลขอยู่ใน Range -10000 ถึง 1000
            if (x < -10000 || x > 1000 || y < -10000 || y > 1000)
                throw "Value out of range";

            // Check ตัวหารเป็น 0
            if (y == 0) throw div0();

            d = static_cast<double>(x) / y;
            cout << "The result is " << d << endl;
        }
        catch (const my_cin& e) {
            cerr << e.what() << endl;
            cin.clear();            // เคลียร์สถานะ error ของ cin
            cin.ignore(1000, '\n'); // ทิ้งตัวอักษรที่ค้างอยู่ในบัฟเฟอร์
            repeat = 1;             // ตั้งค่าเพื่อให้วนรับใหม่
        }
        catch (const div0& e) {
            cerr << e.what() << endl;
            repeat = 1;             // ถ้ายัง fail ให้วนรับใหม่
        }
        catch (const char* e) {
            cerr << e << endl;
            repeat = 1;             // ถ้ายัง fail ให้วนรับใหม่
        }
    } while (repeat);

    return 0;
}