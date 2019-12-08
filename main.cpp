#include "IPoly.h"

void test()
{
    IPoly p,p1,p2;

    cin >> p1;
    cout << p1;
    cin >> p2;
    cout << p2;
    cout << p1 + p2;
    cout << p1 - p2;
    cout << p1 * p2;
    cout << p1 / p2;
    cout << p1 % p2;

    p.read_file("polinom.txt");
    cout << p;

    cout << p.value(10) << endl;
    cout << p.derivative();
    cout << p.integral();
    cout << p.definite_integral(2,5) << endl;

    p1.write_to_file("myTxt.txt");
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL) );

    test();

    return 0;
}

