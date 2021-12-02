# *Multi Pivot Introsort*
 
A highly-optimized (un-tuned) Introsort assembled from several different research papers and open-source libraries, ported into the C++ language.
         
<p>
          This sort uses a recursive pattern to re-arrange data
          in ascending order. Whenever the size of the current
          interval falls below the threshold of 32 elements,
          insertion sort is used. On return, the data in the
          current interval will be in sorted order.
          </p>
         
<p>
           <a href =
           "https://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf"
           >
          Here
           </a>
          is the original Dual-Pivot Quicksort by Vladimir
          Yaroslavskiy.
          </p>
         
<p>
           <a href =
           "https://www.researchgate.net/publication/289974363_Multi-Pivot_Quicksort_Theory_and_Experiments"
           >
          Here
           </a>
          is the three pivot partition algorithm by Kushagra,
          Lopez-Ortix, Munro, and Qiao.
          </p>
         
<p>
          An optimized Dual-Pivot Quicksort by Bloch and
          Bently can be found in the open-source jdk within
          the java.util library.
          </p>
         
<p>
          This sort is derived from the resources listed above.
          </p>
         
<p>
           <h1><b>
          <i>Optimizations:</i>
           </b></h1>
          </p>
          <p>
           <ol>
            <li>
             <p>
              <u>
          Use Smart Pivot Selection
              </u>
             </p>
             <p>
          Pivots are carefully selected from a set of
          five candidates. These candidates are the leftmost
          element, the element at the first tercile, the middle
          element, the element at the second tercile, and the
          rightmost element. All five of these candidates are
          sorted in place. If none are equal, three pivots are
          chosen from the middle.
          If an outside pair is equal, two pivots are selected
          from the tercile indices. However, if a middle pair
          is equal, then a single pivot will be selected from the
          middle and traditional Quick Sort will be used. This
          process helps to select pivots that divide the data
          as evenly as possible, mitigating the possibility of
          the worst-case O(N<sup>2</sup>) time complexity.
             </p>
            </li>
            <li>
             <p>
              <u>
          Use Four-Way or Three-Way Partitioning When Possible
              </u>
             </p>
             <p>
          Multi-way partitioning results in smaller intervals to
          partition in recursive calls. This makes cache hits more
          likely. Multi-way partitioning also helps to trim the
          height of the sort tree.
             </p>
            </li>
            <li>
             <p>
              <u>
          Ignore Elements when possible
              </u>
             </p>
             <p>
          Equal elements and elements that respect the partition
          will be ignored.
             </p>
            </li>
            <li>
             <p>
              <u>
          Keep the Middle Portion(s) as Small as Possible
              </u>
             </p>
             <p>
          After partitioning with more than one pivot, if the middle
          portion comprises more than 2/3 of the current interval,
          we swap all elements equal to the pivots out of the way
          before recursively sorting.
             </p>
            </li>
            <li>
             <p>
              <u>
          Use Insertion Sort On Little Sub-Arrays
              </u>
             </p>
             <p>
          Insertion Sort is small and relies heavily on swapping.
          Fewer instructions help to alleviate the overhead that
          plagues sorting algorithms, and consistent swapping
          leverages CPU caching to its fullest extent. These
          features allow insertion sort to beat the runtimes of
          O(nlogn) sorts on small sets of data.
             </p>
            </li>
              <li>
             <p>
              <u>
          Use Heap Sort to prevent Quicksort's worst-case time
          complexity.
              </u>
             </p>
             <p>
          This sort is an introspective sort&mdash a sort that
          switches to a guaranteed O(nlogn) algorithm whenever
          time complexity is becoming quadratic. Here, Heap Sort
          is used to avoid the overhead of auxilliary storage.
             </p>
            </li>
           </ol>
          </p>
