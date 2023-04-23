#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cstring>
#include <ctype.h>
#include <stdio.h>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
       size_t k_length = k.length();
size_t result_hash = 0;

unsigned long long converted_values[5] = {0, 0, 0, 0, 0};
int array_idx = 4;
int base36_exp = 0;

for (int idx = k_length - 1; idx >= 0; idx--) {
    size_t exponent = convertToBase36(base36_exp);

    if (isdigit(k.at(idx))) {
        char digit = (k.at(idx));
        size_t value = (digit - 22);
        converted_values[array_idx] += value * exponent;
    } else if (isalpha(k.at(idx))) {
        char letter = tolower(k.at(idx));
        size_t value = (letter - 97);
        converted_values[array_idx] += value * exponent;
    }

    base36_exp++;

    if (base36_exp == 6) {
        array_idx--;
        base36_exp = 0;
    }
}

for (int i = 0; i < 5; i++) {
    result_hash += (rValues[i] * converted_values[i]);
}

return result_hash;

    }

     HASH_INDEX_T convertToBase36(int n) const
    {
      unsigned long long x = 1;
      for(int i = 0; i < n; i++)
      {
        x *= 36;
      }
      return x;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
