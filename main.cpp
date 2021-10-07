#include <iostream>
#include <random>
#include <time.h>
#include "sort.h"
#include <random>
#include <climits>

bool test(int* const a, const int len) {
    for(int* i = a + 1; i < a + len; ++i) {
        if (*(i - 1) > *i) return false;
        //std::cout << *i << ' ';
    }
    return true;
}

int main() {
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution(LONG_MIN, LONG_MAX);
    uint64_t y = 0;
    srand(clock());
    double c = 0;
    for(; y < 50; ++y) {
        //if(!(y & 0x3)) std::cout << "#";
        uint64_t x = 2000000;
        //std::cout << x << '\n';
        int *a = new int[x];
        for (int *i = a; i < a + x; i++) {
            *i = distribution(generator) % 2000000;
        }
        //for(int* i = a; i < a + x; i++)
        //    std::cout << *i << ' ';
        //std::cout << "\n\n";
        //const int s = clock();
        const int s = clock();
        Arrays::uSort<int32_t>(a, x);
        c += (double) (clock() - s) / CLOCKS_PER_SEC;
        //std::cout << (double) (clock() - s) / CLOCKS_PER_SEC << '\n';
        if (!test(a, x)) {
            std::cout << "aw!";
            return 0;
        }
        //std::cout << *(a) << '\n';
        delete[] a;
    }
    std::cout << c << '\n';
    std::cout << "yay!";
    return 0;
}
