#ifndef RANDOMNUMBER_HPP
#define RANDOMNUMBER_HPP

#include <bits/stdc++.h>

class RandomNumber
{
public:
    static double uniform();
    static double uniform(double, double);
    static int uniformInt(int, int);
    static double exponential(double mean);
};

#endif