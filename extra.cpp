//
// Created by evcmo on 9/10/2021.
//

#include<iostream>
#include<cassert>

/**
         * The DeBruijn constant.
         */
constexpr uint64_t DeBruijn64 =
        0x03F79D71B4CB0A89L;

/*
 * The DeBruijn map from hash key to integer
 * square index.
 */
constexpr uint8_t DeBruijnTableF[] = {
        0,  47,  1, 56, 48, 27,  2, 60,
        57, 49, 41, 37, 28, 16,  3, 61,
        54, 58, 35, 52, 50, 42, 21, 44,
        38, 32, 29, 23, 17, 11,  4, 62,
        46, 55, 26, 59, 40, 36, 15, 53,
        34, 51, 20, 43, 31, 22, 10, 45,
        25, 39, 14, 33, 19, 30,  9, 24,
        13, 18,  8, 12,  7,  6,  5, 63
};

/*
 * The DeBruijn map from hash key to integer
 * square index.
 */
constexpr uint8_t DeBruijnTableI[] = {
        0,   1, 48,  2, 57, 49, 28,  3,
        61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22,
        45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16,
        54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10,
        25, 14, 19,  9, 13,  8,  7,  6
};

/**
 * Fill trailing bits using prefix fill.
 *
 * @code
 * Example:
 *     10000000 >> 1
 *     01000000 |
 *     11000000 >> 2
 *     00110000 |
 *     11110000 >> 4
 *     00001111 |
 *     11111111
 * @endcode
 * @tparam E The type
 * @param x The integer
 */
template<typename E>
void parallelPrefixFill(E &x);

template<> void parallelPrefixFill
        <uint64_t>(uint64_t& x) {
    x |= x >> 1U;
    x |= x >> 2U;
    x |= x >> 4U;
    x |= x >> 8U;
    x |= x >> 16U;
    x |= x >> 32U;
}

template<> void parallelPrefixFill
        <uint32_t>(uint32_t & x) {
    x |= x >> 1U;
    x |= x >> 2U;
    x |= x >> 4U;
    x |= x >> 8U;
    x |= x >> 16U;
}

template<> void parallelPrefixFill
        <uint16_t>(uint16_t & x) {
    x |= x >> 1U;
    x |= x >> 2U;
    x |= x >> 4U;
    x |= x >> 8U;
}

template<> void parallelPrefixFill
        <uint8_t>(uint8_t & x) {
    x |= x >> 1U;
    x |= x >> 2U;
    x |= x >> 4U;
}

template<typename E>
constexpr E msb(E m) {
    E x = m;
    if (x > UINT8_MAX) {
        parallelPrefixFill(x);
        // Isolate the msb.
        x = (x >> 1U) + 1;
    } else
        // Pop each lsb until
        // only one bit remains.
        // This is the msb.
        for (; m; x = m, m &= m - 1);
    return x;
}

// Explicit instantiations.
template uint64_t msb<uint64_t>(uint64_t);
template uint32_t  msb<uint32_t>(uint32_t);
template uint16_t  msb<uint16_t>(uint16_t);
template uint8_t  msb<uint8_t>(uint8_t);

/**
 * bitScanReverse
 * @authors Kim Walisch
 * @authors Mark Dickinson
 * @param bb bitboard to scan
 * @precondition bb != 0
 * @return index (0..63) of most significant one bit
 */
template<typename E>
constexpr int bitScanRev(E l) {
    assert(l != 0);
    parallelPrefixFill(l);
    return DeBruijnTableF[(int)
            ((l * DeBruijn64) >> 58U)
    ];
}

// Explicit instantiations.
template int bitScanRev<uint64_t>(uint64_t);
template int bitScanRev<uint32_t>(uint32_t);
template int bitScanRev<uint16_t>(uint16_t);
template int bitScanRev<uint8_t>(uint8_t);

/**
 * <h1>Merge Sort</h1>
 *
 * <p>
 * A vanilla recursive merge
 * sort.
 * </p>
 *
 * @author Ellie Moore
 * @version 09.07.2021
 * @tparam E the type of
 * element to sort
 * @param low a pointer to
 * the low end of the sub-array
 * @param high a pointer to
 * the high end of the sub-array
 * @return the number of
 * inversions in the input
 * array.
 */
template<typename E>
void mSort(E *const low,
           E *const high) {

    if(low >= high) return;

    // Find the approximate
    // midpoint of the interval.
    // mid = (high + low) / 2;
    E *const mid =
            low + ((high - low) >> 1U);

    // Sort left and right
    // portions.
    mSort(low, mid);
    mSort(mid + 1, high);

    // If the mid is less than
    // or equal to the next
    // element over, there is
    // no reason to merge.
    if (*(mid) <= *(mid + 1))
        return;

    // Calculate the lengths
    // of the auxiliary
    // (temporary) arrays
    // needed to hold the
    // runs.
    const int
            ltLength =
            mid + 1 - low,
            rtLength =
            high - mid;

    // Initialize temporary
    // arrays on the heap.
    // These arrays will hold
    // runs.
    E *const lt =
            new E[ltLength],
            *const rt =
            new E[rtLength];

    // left pointer, starts
    // at low.
    E *l = low,

    // Right pointer, starts
    // at mid + 1.
    *r = mid + 1,

    // A pointer to the base of
    // the left auxiliary array.
    *ll = lt,

    // A pointer to the base of
    // the right auxiliary array.
    *rr = rt;

    // Fill left and right
    // temporary arrays.
    for (; l <= mid; ++l, ++ll)
        *ll = *l;
    for (; r <= high; ++r, ++rr)
        *rr = *r;

    // recycle pointers.
    ll = lt;
    rr = rt;
    l = low;

    // Initialize upper bound
    // pointers to act as
    // sentinels for the
    // auxiliary arrays.
    E *const lLim =
            lt + ltLength,
            *const rLim =
            rt + rtLength;

    // Merge the runs and
    // count inversions.
    while (ll < lLim &&
           rr < rLim)
        if (*ll < *rr)
            *l++ = *ll++;
        else
            *l++ = *rr++;

    // add any remaining
    // elements to the end
    // of the interval.
    for (; ll < lLim; ++l, ++ll)
        *l = *ll;
    for (; rr < rLim; ++l, ++rr)
        *l = *rr;

    // dispose.
    delete[] lt;
    delete[] rt;
}

/**
 * Binary Radix Quicksort MSB
 *
 * <summary>
 *  <p>
 * This is a binary radix quick sort that starts at the
 * most significant bit.
 *  </p>
 *  <p>
 * This is an unstable, in-place sort for the integer data
 * type. The order of sorted equivalent elements is not
 * guaranteed. However, the sort only uses O(1) extra
 * storage and its overall time complexity is O(M*N)
 * where M is the max number of bits.
 *  </p>
 * </summary>
 * @param m the mask to isolate bits
 * @param low the pointer to the bottom of the frame
 * @param high the pointer to the top of the frame
 * @author Ellie Moore
 * @version 08.25.2021
 */
template<typename E, bool Leftmost>
void rSort(const uint64_t m,
           E *const low,
           E *const high) {

    // If we have considered
    // all bits, the array
    // is sorted.
    if (!m) return;

    // Initialize mutable
    // pointers.
    E *l = low,
      *r = high;

    if ((r - l) > 16) {

        // Binary
        // Radix
        // Quick
        // Sort
        // Partition the
        // array into a
        // 0's portion
        // and a 1's
        // portion,
        // considering
        // the masked
        // bit in each
        // element.
        do {
            if (*l & m) {
                while(*r & m
                && r - l > 1)
                    --r;
                const E
                 t = *l;
                *l = *r;
                *r-- = t;
            } else l++;
        } while (l < r);

        // Adjust pointers
        // as needed
        // to ensure that
        // the correct
        // portions are
        // carried into the
        // recursive step.
        if (*l & m) l--;
        else r++;

        // Shift mask to
        // the right.
        const uint64_t q =
                m >> 1U;

        // Sort the two parts
        // recursively.
        rSort<E, Leftmost>(q, low, l);
        rSort<E, false>(q, r, high);
    } else {
        if (Leftmost) {

            // Traditional
            // insertion
            // sort.
            for (E *i = l;
                 i <= r;
                 ++i) {
                const E t = *i;
                E *j = i - 1;
                for (; j >= l &&
                       t < *j; --j)
                    *(j + 1) = *j;
                *(j + 1) = t;
            }
        } else {
            // Pair insertion sort.
            // Skip elements that are
            // in ascending order.
            do if (l++ >= r) return;
            while (*l >= *(l - 1));

            // This sort requires
            // prior partitioning
            // to use the sub-array
            // at left as a sentinel.
            for (E *i = l;
                 ++l <= r;
                 i = ++l) {
                E ex = *i, ey = *l;
                if (ex < ey) {
                    ey = ex;
                    ex = *l;
                }
                while (ex < *--i)
                    *(i + 2) = *i;
                *(++i + 1) = ex;
                while (ey < *--i)
                    *(i + 1) = *i;
                *(i + 1) = ey;
            }
            E ez = *r;
            while (ez < *--r)
                *(r + 1) = *r;
            *(r + 1) = ez;
        }
    }

    template
            <typename E>
    void tradSort(E *const low,
                  E *const high) {

        if(low >= high) return;

        const int x = high - low;
        const int y = (rand() % x);
        // Find an approximate
        // midpoint of the interval.
        E *const mid = low + y;

        // Assign midpoint to pivot
        // variable.
        const E p = *mid;

        // Bring left end inside.
        // Left end will be
        // replaced and pivot will
        // be swapped back later.
        *mid = *low;

        // Initialize l and g.
        // "less" and "great"
        // respectively.
        E *l = low + 1,
                *g = high;

        for (E *k = l;
             k <= g; ++k)
            if (*k < p)
                swap(k, l++);
            else if (*k > p) {
                while (*g > p &&
                       k < g)
                    --g;
                swap(k, g--);
                if (*k < p)
                    swap(k, l++);
            }

        // Replace left end.
        *low = *--l;

        // Swap pivot into place.
        *l = p;

        if(l > low)
            --l;
        if(g < high)
            ++g;

        // Copy l, recycle g. "less"
        // and "great" respectively.

        // Sort left and right portions.
        tradSort<E>(
                low, l
        );
        tradSort<E>(
                g, high
        );
    }

}