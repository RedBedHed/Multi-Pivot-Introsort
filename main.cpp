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
    std::default_random_engine generator(clock());
    std::uniform_int_distribution<long> distribution(LONG_MIN, LONG_MAX);
    double c = 0;
    for (uint64_t y = 0; y < 20; ++y) {
        uint64_t x = 2000000;
        int *a = new int[x];
        for (int *i = a; i < a + x; ++i) {
            *i = distribution(generator) % x;
        }
        const int s = clock();
        Arrays::uSort<int32_t>(a, x);
        c += (double) (clock() - s) / CLOCKS_PER_SEC;
        if (!test(a, x)) {
            std::cout << "aw!";
            return 0;
        }
        delete[] a;
    }
    printf("%.10f\n", c);
    return 0;
}
