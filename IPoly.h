#ifndef IPOLY_H
#define IPOLY_H

#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;


//int random_int(int a,int b);

class IPoly//Всі арифметичні операціі відбуваються за модулем m-1
{
private:
    unsigned int m;
    vector <int> p;
    size_t n;

    int mod(int a);

public:
    IPoly();

    friend ostream& operator<< (ostream &out,const IPoly &poly);
    friend istream& operator>> (istream &in,IPoly &poly);

    void set_polinom();

    int value(int x);

    IPoly operator +(const IPoly & other);

    IPoly operator -(const IPoly & other);

    IPoly operator *(const IPoly & other);

    IPoly operator /(const IPoly & other);

    IPoly operator %(const IPoly & other);

    IPoly derivative();

    IPoly integral();

    int definite_integral(int a,int b);

    void write_to_file(string path);

    void read_file(string path);

    void printPoly();

    ~IPoly();
};

ostream& operator<< (ostream &out,const IPoly &poly);
istream& operator>> (istream &in,IPoly &poly);


#endif // IPOLY_H
