#include <iostream>
#include <random>
#include <time.h>
#include "sort.h"
#include <random>
#include <stdio.h>
#include <climits>
#include <algorithm>

bool test(int* const a, const int len) {
    //std::cout << *a << ' ';
    for(int* i = a + 1; i < a + len; ++i) {
        if (*(i - 1) > *i) return false;
        //std::cout << *i << ' ';
    }
    return true;
}

void quickers(int* const low, int* const high) {
    const int x = high - low;
    if(low >= high) return;

    int pi = rand() % x;
    int p = *(low + pi);
    *(low + pi) = *low;

    int* i = low, *j = high + 1;
    while(true) {
        while(*++i <= p) if(i >= high) break;
        while(*--j > p) if(j <= low) break;
        if(i >= j) break;
        const int t = *i;
        *i = *j;
        *j = t;
    }
    *low = *j;
    *j = p;

    if(i == j) ++i;
    --j;

    if(low < j) quickers(low, j);
    if(i < high) quickers(i, high);
}

int comparator (const void * p1, const void * p2) {
    return (*(int*)p1 - *(int*)p2);
}

int main() {
    srand(time(NULL));
    std::default_random_engine generator(clock());
    std::uniform_int_distribution<long> distribution(LONG_MIN, LONG_MAX);
    double c = 0;
    for (uint64_t y = 0; y < 20; ++y) {
        uint64_t x = 2000000;
        int *a = new int[x];
        for (int *i = a; i < a + x; ++i) {
            *i = distribution(generator) % x;
            //std::cout << *i << ' ';
        }
        const int s = clock();
        qsort(a, x, sizeof(int), comparator);
        //Arrays::uSort<int32_t>(a, x);
        //quickers(a, a + x);

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
