//
// Created by evcmo on 9/5/2021.
//

#include "sort.h"

namespace Arrays {

    namespace {

        constexpr uint32_t
        DPQSInsertionThreshold = 32;

        /**
         * The DeBruijn constant.
         */
        constexpr uint64_t DeBruijn64 =
            0x03F79D71B4CB0A89L;

        /*
         * The DeBruijn map from key to integer
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

        /**
         * Fill trailing bits using prefix fill.
         *
         * @code
         * Example:
         *       10000000 >> 1
         *     = 01000000 | 10000000
         *     = 11000000 >> 2
         *     = 00110000 | 11000000
         *     = 11110000 >> 4
         *     = 00001111 | 11110000
         *     = 11111111
         * @endcode
         * @tparam E The type
         * @param x The integer
         */

        template<typename E>
        void parallelPrefixFill(E &x);

        template<> [[maybe_unused]]
        void parallelPrefixFill
        <uint64_t>(uint64_t& x) {
            x |= x >> 1U;
            x |= x >> 2U;
            x |= x >> 4U;
            x |= x >> 8U;
            x |= x >> 16U;
            x |= x >> 32U;
        }

        template<> [[maybe_unused]]
        void parallelPrefixFill
        <uint32_t>(uint32_t & x) {
            x |= x >> 1U;
            x |= x >> 2U;
            x |= x >> 4U;
            x |= x >> 8U;
            x |= x >> 16U;
        }

        template<> [[maybe_unused]]
        void parallelPrefixFill
        <uint16_t>(uint16_t & x) {
            x |= x >> 1U;
            x |= x >> 2U;
            x |= x >> 4U;
            x |= x >> 8U;
        }

        template<> [[maybe_unused]]
        void parallelPrefixFill
        <uint8_t>(uint8_t & x) {
            x |= x >> 1U;
            x |= x >> 2U;
            x |= x >> 4U;
        }

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

        template<typename E>
        constexpr void
        swap(E *const i,
             E *const j) {
            E const
            el = *i;
            *i = *j;
            *j = el;
        }

        /**
         * <b>
         *  <i>
         * Insertion Sort
         *  </i>
         * </b>
         *
         * <p>
         * Classical ascending insertion sort packaged with a
         * "pairing" optimization to be used in the context of
         * Quick Sort.
         * This optimization is used whenever the portion of
         * the array to be sorted is padded on the left by
         * a portion with lesser elements. The fact that all of
         * the elements on the left are automatically less than
         * the elements in the current portion allows us to skip
         * the costly lower boundary check in the nested loops.
         * </p>
         *
         * @authors Josh Bloch
         * @authors Jon Bently
         * @authors Ellie Moore
         * @tparam E the element type
         * @param low a pointer to the leftmost index
         * @param high a pointer to the rightmost index
         * @param isLeftmost whether or not this subarray is a
         * left-most partition.
         */
        template<typename E, bool Leftmost>
        inline void
        iSort(E *const low,
              E *const high) {
            E* l = low;
            E* r = high;
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

        /**
         *
         * A generic "sift down" method (AKA max-heapify)
         *
         * @tparam E the element type
         * @param a the pointer to the base of the current
         * sub-array
         * @param i the starting index
         * @param size the size of the current sub-array
         */
        template<typename E>
        inline void
        siftDown(E* const a,
                 const int i,
                 const int size) {

            // Store size in
            // a local variable.
            const uint32_t n = size;

            // Establish non-leaf
            // boundary.
            const uint32_t o = n >> 1U;

            // Extract the element
            // to sift.
            E z = a[i];

            // initialize temporary
            // variables.
            uint32_t x = i, l, r;

            // consider only non-leaf
            // nodes.
            while(x < o) {

                // y is currently
                // left child element.
                // Note: "l" here stands
                // for "left"
                r = (l = (x << 1U) + 1) + 1;
                E y = a[l];

                // if right child is
                // within the heap...
                // AND
                // if right child element
                // is greater than left
                // child element,
                // THEN
                // assign right child to
                // y and right index to l.
                // Note: "l" now stands
                // for "larger"
                if(r < n && y < a[r])
                    y = a[l = r];

                // if y is less than or
                // equal to the element
                // we are sifting, then
                // we are done.
                if(y <= z) break;

                // move y up to the
                // parent index.
                a[x] = y;

                // Set parent index to
                // be the index of
                // the largest child.
                x = l;
            }

            // Place the sifted element.
            a[x] = z;
        }

        /**
         * <b>
         *  <i>Heap Sort</i>
         * </b>
         *
         * <p>
         * Classical heap sort that sorts the given range
         * in ascending order, building a max heap and
         * continuously sifting/swapping the max element
         * to the previous rightmost index.
         * </p>
         * @author Ellie Moore
         * @tparam E the element type
         * @param low a pointer to the leftmost index
         * @param high a pointer to the rightmost index
         */
        template<typename E>
        inline void
        hSort(E* const low,
              E* const high) {
            E* r = high + 1;
            E* const l = low;
            int x = r - l;
            for(int i =
                (x >> 1U); i >= 0; --i)
                siftDown(l, i, x);
            while(l < --r) {
                const E z = *l; *l = *r;
                siftDown(l, 0, --x);
                *r = z;
            }
        }

        /**
         * <b>
         *  <i>Introspective Multi-Pivot Quick Sort</i>
         * </b>
         *
         * <p>
         * This sort uses a recursive pattern to re-arrange data
         * in ascending order. Whenever the size of the current
         * interval falls below the threshold of 32 elements,
         * insertion sort is used. On return, the data in the
         * current interval will be in sorted order.
         * </p>
         *
         * <p>
         *  <a href =
         *  "https://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf"
         *  >
         * Here
         *  </a>
         * is the original Dual-Pivot Quicksort by Vladimir
         * Yaroslavskiy.
         * </p>
         *
         * <p>
         *  <a href =
         *  "https://www.researchgate.net/publication/289974363_Multi-Pivot_Quicksort_Theory_and_Experiments"
         *  >
         * Here
         *  </a>
         * is the three pivot partition algorithm by Kushagra,
         * Lopez-Ortix, Munro, and Qiao.
         * </p>
         *
         * <p>
         * An optimized Dual-Pivot Quicksort by Bloch and
         * Bently can be found in the open-source jdk within
         * the java.util library.
         * </p>
         *
         * <p>
         * This sort is derived from the resources listed above.
         * </p>
         *
         * <p>
         *  <b>
         * <i>Optimizations:</i>
         *  </b>
         * </p>
         * <p>
         *  <ol>
         *   <li>
         *    <p>
         *     <u>
         * Use Smart Pivot Selection
         *     </u>
         *    </p>
         *    <p>
         * Pivots are carefully selected from a set of
         * five candidates. These candidates are the leftmost
         * element, the element at the first tercile, the middle
         * element, the element at the second tercile, and the
         * rightmost element. All five of these candidates are
         * sorted in place. If none are equal, three pivots are
         * chosen from the middle.
         * If an outside pair is equal, two pivots are selected
         * from the tercile indices. However, if a middle pair
         * is equal, then a single pivot will be selected from the
         * middle and traditional Quick Sort will be used. This
         * process helps to select pivots that divide the data
         * as evenly as possible, mitigating the possibility of
         * the worst-case O(N<sup>2</sup>) time complexity.
         *    </p>
         *   </li>
         *   <li>
         *    <p>
         *     <u>
         * Use Four-Way or Three-Way Partitioning When Possible
         *     </u>
         *    </p>
         *    <p>
         * Multi-way partitioning results in smaller intervals to
         * partition in recursive calls. This makes cache hits more
         * likely. Multi-way partitioning also helps to trim the
         * height of the sort tree.
         *    </p>
         *   </li>
         *   <li>
         *    <p>
         *     <u>
         * Ignore Elements when possible
         *     </u>
         *    </p>
         *    <p>
         * Equal elements and elements that respect the partition
         * will be ignored.
         *    </p>
         *   </li>
         *   <li>
         *    <p>
         *     <u>
         * Keep the Middle Portion(s) as Small as Possible
         *     </u>
         *    </p>
         *    <p>
         * After partitioning with more than one pivot, if the middle
         * portion comprises more than 2/3 of the current interval,
         * we swap all elements equal to the pivots out of the way
         * before recursively sorting.
         *    </p>
         *   </li>
         *   <li>
         *    <p>
         *     <u>
         * Use Insertion Sort On Little Sub-Arrays
         *     </u>
         *    </p>
         *    <p>
         * Insertion Sort is small and relies heavily on swapping.
         * Fewer instructions help to alleviate the overhead that
         * plagues sorting algorithms, and consistent swapping
         * leverages CPU caching to its fullest extent. These
         * features allow insertion sort to beat the runtimes of
         * O(nlogn) sorts on small sets of data.
         *    </p>
         *   </li>
         *     <li>
         *    <p>
         *     <u>
         * Use Heap Sort to prevent Quicksort's worst-case time
         * complexity.
         *     </u>
         *    </p>
         *    <p>
         * This sort is an introspective sort&mdash a sort that
         * switches to a guaranteed O(nlogn) algorithm whenever
         * time complexity is becoming quadratic. Here, Heap Sort
         * is used to avoid the overhead of auxilliary storage.
         *    </p>
         *   </li>
         *  </ol>
         * </p>
         * @authors Vladimir Yaroslavskiy
         * @authors Josh Bloch
         * @authors Jon Bently
         * @authors Shrinu Kushagra
         * @authors Alejandro Lopez-Ortiz
         * @authors J. Ian Munro
         * @authors Aurick Qiao
         * @authors Ellie Moore
         * @tparam E the element type
         * @tparam Leftmost whether we are considering
         * a leftmost partition.
         * @param low a pointer to the leftmost index
         * @param high a pointer to the rightmost index
         * @param height the distance of the current sort
         * tree from the initial height of 2log<sub>2</sub>n
         */
        template
        <typename E, bool Leftmost = true>
        void qSort(E *const low,
                   E *const high,
                   const int height) {

            // Find the interval width.
            const uint32_t x = high - low;

            // Insertion sort
            // small intervals.
            if (x < DPQSInsertionThreshold)
                return iSort<E, Leftmost>(
                    low, high
                );

            // Heap sort when the sort
            // tree becomes excessively
            // tall.
            if(height < 0)
                return hSort(low, high);

            // Find an inexpensive
            // approximation of a third of
            // the interval.
            const uint32_t
                y = x >> 2U,
                third = y + (y >> 1U);

            // Find an approximate
            // midpoint of the interval.
            E *const mid = low + (x >> 1U);

            // Assign tercile indices
            // to candidate pivots.
            E *const sl = low + third;
            E *const sr = high - third;

            // Insertion sort all five
            // candidate pivots in-place.
            if (*sl < *low) {
                E e  =  *sl;
                *sl  = *low;
                *low =    e;
            }

            if (*mid < *sl) {
                E e  = *mid;
                *mid =  *sl;
                *sl  =    e;
                if (e < *low) {
                    *sl  = *low;
                    *low =    e;
                }
            }

            if (*sr < *mid) {
                E e  =  *sr;
                *sr  = *mid;
                *mid =    e;
                if (e < *sl) {
                    *mid = *sl;
                    *sl  =   e;
                    if (e < *low) {
                        *sl  = *low;
                        *low =    e;
                    }
                }
            }

            if (*high < *sr) {
                E e   = *high;
                *high =   *sr;
                *sr   =     e;
                if (e < *mid) {
                    *sr  = *mid;
                    *mid =    e;
                    if (e < *sl) {
                        *mid = *sl;
                        *sl  =   e;
                        if (e < *low) {
                            *sl  = *low;
                            *low =    e;
                        }
                    }
                }
            }

            // If none of the sorted
            // candidate pivots are
            // equal.
            if (*low <  *sl &&
                *sl  < *mid &&
                *mid <  *sr &&
                *sr  < *high) {

                // Use Three-Pivot Quick Sort.

                // Assign the elements at
                // the first tercile,
                // midpoint and second
                // tercile to the pivot
                // variables.
                E p1 = *sl,
                  p2 = *mid,
                  p3 = *sr;

                // Bring the first and
                // last elements inside.
                // These spots will be
                // filled and pivots will
                // be swapped into place
                // later.
                *sl  =       *low;
                *mid = *(low + 1);
                *sr  =      *high;

                // Initialize l and g.
                // "less" and "great"
                // respectively.
                E* l = low + 1,
                 * g = high;

                // Skip elements that
                // are already in order.
                while (++l < high && *l < p1);
                while (--g > low  && *g > p3);

                // Copy ll and gg.
                // "less-less" and
                // "great-great"
                // respectively.
                E* ll = l,
                 * gg = g;

                // Partition using the 4-way
                // scheme.
                while(l <= g) {
                    while(*l < p2 &&
                          l <= g) {
                        if(*l < p1)
                            swap(ll++, l);
                        ++l;
                    }
                    while(*g > p2 &&
                          l <= g) {
                        if(*g > p3)
                            swap(gg--, g);
                        --g;
                    }
                    if(l > g) break;
                    if(*l > p3) {
                        const E u = *l;
                        if (*g < p1) {
                            *l++  = *ll;
                            *ll++ =  *g;
                        } else
                            *l++  =  *g;
                        *g--  = *gg;
                        *gg-- =   u;
                    } else {
                        const E u = *l;
                        if (*g < p1) {
                            *l++  = *ll;
                            *ll++ =  *g;
                        } else
                            *l++  =  *g;
                        *g-- = u;
                    }
                }

                // Fill ends. Swap the
                // pivots back into place.
                *(low + 1) = *--ll;
                *ll = p2; swap(--l, ll);
                *low = *--ll; *ll = p1;
                *high = *++gg; *gg = p3;

                // Copy pivot 1 and 3
                // pointers.
                E* o = ll,
                 * e = gg;

                // Skip elements equal to p1
                // and p3.
                while (--o > low && *o == p1);
                while (++e < high && *e == p3);

                // Sort the leftmost and
                // rightmost portion(s).
                qSort<E, Leftmost>(
                    low, o, height - 1
                );
                qSort<E, false>(
                    e, high, height - 1
                );

                // Copy pivot 1 and 2
                // pointers.
                e = ll;
                o =  l;

                // Skip elements equal to
                // p1 and p2.
                while (e < o && *e == p1)
                    ++e;
                while (o > e && *o == p2)
                    --o;

                // If leftmost middle
                // portion is too large
                // (>= 2/3 of the interval),
                // get pivot duplicates out
                // of the way.
                const uint32_t twoThirds =
                    third << 1U;
                if ((o - e) >=
                    (twoThirds)) {
                    for (E *k  = e;
                         k <= o; ++k)
                        if (*k == p1)
                            swap(k, e++);
                        else if (*k == p2) {
                            swap(k, o--);
                            if (*k == p1)
                                swap(k, e++);
                        }
                }

                // Sort the leftmost middle
                // portion.
                qSort<E, false>(
                    e, o, height - 1
                );

                // Copy pivot 2 and 3
                // pointers.
                e =  l;
                o = gg;

                // Skip elements equal to
                // p2 and p3.
                while (e < o && *e == p2)
                    ++e;
                while (o > e && *o == p3)
                    --o;

                // If rightmost middle
                // portion is too large
                // (>= 2/3 of the interval),
                // get pivot duplicates out
                // of the way.
                if ((o - e) >=
                    (twoThirds)) {
                    for (E *k  = e;
                         k <= o; ++k)
                        if (*k == p2)
                            swap(k, e++);
                        else if (*k == p3) {
                            swap(k, o--);
                            if (*k == p2)
                                swap(k, e++);
                        }
                }

                // sort rightmost middle
                // portion.
                qSort<E, false>(
                    e, o, height - 1
                );

                // If none of the middle-most
                // candidate pivots are equal.
            } else if (*sl < *mid &&
                       *mid < *sr) {

                // Use Dual-Pivot Quick Sort.

                // Assign the elements at
                // the first and second
                // terciles to the pivot
                // variables.
                const E lp = *sl;
                const E rp = *sr;

                // Bring the first and
                // last elements inside.
                // These spots will be
                // filled and Pivots will
                // be swapped into place
                // later.
                *sl = *low;
                *sr = *high;

                // Initialize l and g.
                // "less" and "great"
                // respectively.
                E *l = low,
                  *g = high;

                // Skip elements that
                // are already in order.
                while (++l < high && *l < lp);
                while (--g > low && *g > rp);

                // Partition with
                // the Dutch flag
                // algorithm
                // proposed by
                // Yaroslavskiy.
                for (E *k  = l;
                     k <= g; ++k)
                    if (*k < lp)
                        swap(k, l++);
                    else if (*k > rp) {
                        while (*g > rp &&
                               k < g)
                            --g;
                        swap(k, g--);
                        if (*k < lp)
                            swap(k, l++);
                    }

                // Fill ends. Swap the
                // pivots back into place.
                *low  = *--l;
                *l    =   lp;
                *high = *++g;
                *g    =   rp;

                // Copy pivot indices.
                E *p = l,
                  *q = g;

                // Skip elements that are
                // equal to the pivots.
                while (p > low && *p == lp)
                    --p;
                while (q < high && *q == rp)
                    ++q;

                // Sort right and left
                // portions.
                qSort<E, Leftmost>(
                    low, p, height - 1
                );
                qSort<E, false>(
                    q, high, height - 1
                );

                // Skip over elements that
                // are equal to the pivots.
                while (l < g && *l == lp)
                    ++l;
                while (g > l && *g == rp)
                    --g;

                // If middle portion is
                // too large (>= 2/3 of
                // the interval),
                // get pivot duplicates out
                // of the way.
                if ((g - l) >=
                    (x - third)) {
                    for (E *k = l;
                         k <= g; ++k)
                        if (*k == lp)
                            swap(k, l++);
                        else if (*k == rp) {
                            swap(k, g--);
                            if (*k == lp) {
                                swap(k, l++);
                            }
                        }
                }

                //Sort middle portion.
                qSort<E, false>(
                    l, g, height - 1
                );

                // If one or more critical pivot
                // candidates are equal.
            } else {

                // Use traditional, Single-Pivot
                // Quick Sort.

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

                // Skip over elements that
                // are already in order.
                while (l < high && *l < p)
                    ++l;
                while (g > low && *g > p)
                    --g;

                // Partition.
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

                // Copy l, recycle g. "less"
                // and "great" respectively.
                g = l;

                // Skip over elements that
                // are equal to the pivot.
                while (l > low && *l == p)
                    --l;
                while (g < high && *g == p)
                    ++g;

                // Sort left and right portions.
                qSort<E, Leftmost>(
                    low, l, height - 1
                );
                qSort<E, false>(
                    g, high, height - 1
                );
            }
        }
    }

    template <typename E>
    inline void uSort(E* const a,
                      const uint32_t cnt) {
        const int log2Cnt = bitScanRev(cnt) << 1U;
        return qSort(a, a + (cnt - 1), log2Cnt);
    }

    template void
    uSort<int64_t>(int64_t*, uint32_t);
    template void
    uSort<int32_t>(int32_t*, uint32_t);
    template void
    uSort<int16_t>(int16_t*, uint32_t);
    template void
    uSort<int8_t>(int8_t*, uint32_t);
}