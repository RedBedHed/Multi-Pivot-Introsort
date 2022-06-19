# *Multi Pivot Introsort*
 
A highly-optimized (un-tuned) Introsort assembled from research papers and open-source libraries, ported into the C++ language.
         
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
          Lopez-Ortiz, Munro, and Qiao.
          </p>
         
<p>
          An optimized Dual-Pivot Quicksort by Bloch and
          Bently can be found in any jdk after version 6.
          </p>
         
<p>
          This sort is derived from the resources listed above.
          </p>
         
<p>
           <h1><b>
          <i>Optimizations</i>
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
          is also equal, then a single pivot will be selected from the
          middle and traditional Quick Sort will be used. This
          process helps to select pivots that divide the data
          as evenly as possible, mitigating the possibility of
          the worst-case O(N<sup>2</sup>) time complexity. This
          process also helps to ensure that the partitioning
          algorithm used is optimal for the sub-array sampled.
             </p>
            </li>
            <li>
             <p>
              <u>
          Use Four-Way or Three-Way Partitioning When Possible
              </u>
             </p>
             <p>
          Multi-way partitioning has been shown to yeild a higher
          number of cache hits than traditional two-way partitioning. 
          Multi-way partitioning also helps to trim the height of the 
          sort tree.
             </p>
             <p>
              <u>
          Keep the Middle Portion(s) as Small as Possible In 
          Multi-Pivot Partitioning.
              </u>
             </p>
            </li>
            <li>
             <p>
          The middle portions may contain elements equal to the pivots
          in multi-pivot partitioning. Therefore, after partitioning 
          with more than one pivot, if the middle portion comprises 
          more than 2/3 of the current interval, we swap all elements
          equal to the pivots out of the way before recursively sorting. 
          This helps to boost performance on arrays with many equal 
          elements.
             </p>
            </li>
            <li>
             <p>
              <u>
          Use Insertion Sort On Little Sub-Arrays
              </u>
             </p>
             <p>
          Insertion sort performs better than O(nlogn) sorts
          on small arrays where asymptotic complexity matters
          less and instruction overhead matters more.
             </p>
            </li>
            <li>
             <p>
              <u>
          Use Jon Bentley's Pair Insertion Sort On Small, Non-Leftmost
          Partitions.
              </u>
             </p>
             <p>
          Pair insertion sort-- which ignores the lower bound check-- is
          possible on non-leftmost partitions. Pair insertion sort inserts
          two elements for each iteration of its outer loop.
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
          This sort is an introspective sort-- a sort that
          switches to a guaranteed O(nlogn) algorithm whenever
          time complexity is becoming quadratic. Here, Heap Sort
          is used to avoid the overhead of auxilliary storage.
             </p>
            </li>
           </ol>
          </p>
          
# *Performance*
<p align = "center">
 <img src="/figures/test.png" />
</p>

# *Credits*
<p>
 <ul>
  <li>
   <i>
    Alejandro Lopez-Ortiz
   </i>
  </li>
  <li>
   <i>
    Aurick Qiao
   </i>
  </li>
  <li>
   <i>
    David Musser
   </i>
  </li>
  <li>
   <i>
    Ellie Moore
   </i>
  </li>
  <li>
   <i>
    J. Ian Munro
   </i>
  </li>
  <li>
   <i>
    Jon Bently
   </i>
  </li>
  <li>
   <i>
    Josh Bloch
   </i>
  </li>
  <li>
   <i>
    Shrinu Kushagra
   </i>
  </li>
  <li>
   <i>
    Tony Hoare
   </i>
  </li> 
 </ul>
</p>

# *A Compiler's View*
<a href="https://godbolt.org/z/6qvf5hqev">
 <img src="/figures/exp.png" />
</a>
