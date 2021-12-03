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
          Elements equal to the pivot(s) and elements that respect the 
          partition will be ignored.
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
          before recursively sorting. This helps to avoid the case
          in which we need to use heap sort.     
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
          plagues large sorting algorithms, and consistent swapping
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

<iframe width="800px" height="200px" src="https://godbolt.org/e?readOnly=true#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgOykrgAyeAyYAHI%2BAEaYxCAAnADMABykAA6oCoRODB7evgEZWTkCoeFRLLHxyWl2mA65QgRMxAT5Pn5cgfWNAs2tBOWRMXGJqbYtbR2F3ZODw5XV4ykAlLaoXsTI7BwmGgCCAPRH%2B8dHANRuxJhMBJjoF9EAnheYAG7ILKgXAhcJRwArEczBozFwAHRnE5nWFmJJhZDeLAXExJNxOBQEG6sNHYOEIhhIrwotFuUQKJRtPGww7MNgKdJMHYXA7EYhMZ4KVH%2BKyHM4XQUXemYRnMzA8vkHAVC2VoBhYzCqdLEC5eMIEJJmAD6BBlssFABFlABFIQASQVcUcAgAKggbgoEJ5HmjDRctWipfqDUcAFR%2Bn0Gv0Xe0Sw2YCzEdXaBgXeVYwwEKGHA2yv2nVNp%2BMCRXK1XqwQANkkuouEajMYYJdRSUNQezGlUGiSADF/AlDf4uBZJG4LIcUglgl7aQdsxd/Q2hSGw%2BXI9G8LGLiwmOkLlRiKgWBcANaYV5EC4azDAOLTwUhhQARy8rQlYSwqhT44nGYvCfu%2BbVGpSZYri6xraTDRPQrYmICViAu6bqShesoaKQgqSIEgpcEhgJFkhkhpBcZioXhSFFoh8FCoCqGSAk2HoR6qFmLhXBYYKSREehpGCoC0gXICuFJICGFmBhiEXJIgl4TRkjSOxHq8WJZhUXhLEXHMyk0SJRGCdJkhMYC/F4TpCmSMJSRMVwemAix0lJFxgI0aC2FKUkdliVwwmSPx0lmHpSQKVISFJEpXAKUkwn/EhZhSVmE5oYFuEXAxYkXARTHcURSQXiY/j1kk3pRb6AbwSGrZ0LQFzYkwdBhMATyENyXjZEYFwqpgNCqBuJUvtFgZ5cGFwAAJoFghUXNgqisOk4jDWmrkaLNc21viSTYMpU1CrBGgzXNGg8m4ylbXNq2CrBXCbfNNJLXhh21u6s0nVtO2qftGhXcdJ2nQteIiS9dYXFtb1cA9/1bd97r/f9w19a4g2YBDBBMhyO7LXOBDPOkMM9em/Xw6wFxtXOJ5nsQhWZtKGOCvcLATXcMPoijaMiiNNJkxc7yoHgjzY7Q9C0MoNytcVXMQMt5hFqoqyjvyzMU1T9xkp9EFQRYq7PLE2peAw9UPBB9bQRerPs01rRiNzvMtXgqgC7Q0mymShYECWup4hAdsO3qZhFrjqxwczsptZlbiwX7S2fVwcgS6%2B0W4ztgcfRdZhhzl0l%2B/4Ac/UHi3LZICdSpHgrJ6n7rp59KTZ0n0dp7Hy2MaXPtCvnMfnctWo1xHBqZfWkut7K0sGLL6Ly5BCvK6r6ua%2Bg2sT8z%2Bsc0bXOYDzfPm5b1treidtao7S3OxqG8EKi7ue97XfZvXFeN8pLe51H/sN8HceX7np%2BF5XIkP5HT/X3fy0l%2BHV8f0XF1q6/2zO3McE4e7UzlhdBWQ9OQjw1koceutdZTzZjPDkc8F5mwtiVFeR014akYpvbA29BBEL3iLQ%2BmUc6P3Ls/c%2BodgHvzoZ/DOeE37RX/i/LOTDOEsIAd/DhNsspgOzBAvuqdhaD0gsPTAasEFa2QR3Y%2Bgpp6GwwSbReOCuZ4NrG4O2f49RbwMWWShYsj5/34S/Rhida55ysefeOvCJxcPPjw2xKieTKIvP6bqniLghmiIQEQhgABKHw4hKAhkwLwBBnTEG5AAaTwDuAA6mIPAChkAIGibE%2BJ3IACyrRdzljwMgXcYQFACAhtjHc0Rog1QINEVArRHhHiyYYGpNx5T4BtHGepFwwBgHWhDG4BAthxkfEqC4EANAQghEWJIXtUBUBXFkPe2RgAMDwDQUQghfjhEacTC84iaZuDpowVgEoM4flzF%2BFUx59lBOEHs8J7whYXFoF7ah0kmCUmtBAUqQz1riw8VfTmmjsGW0BaCmhkcxkTPnJWJcDBgKgUwOBSCEANTizsQaKApUQwASrCWb5X9uIl1xf4tauswUgJEZ3cBmBKa9zORchmNzmafiVA86eF4FAAHc1wfL9J%2BY8pBrbLVFXci42hvm8mkstT80l57XQCXgZx2Y/R4DVX6bQmq0x6rVfPA1XjRFpl8cNMk0Qmb%2BJDHojVwcfYhktFSPpFwhAkD1M6/BbgjiOvxD6skRwbVOrtVa9E6RbVdSuAYSkZSxAXD%2BTsBg%2BBGqVOtLkC4VS2iG3KUwM8jwBWEAQEmq1ZgzBMjwMQKq5gzC/HSI4FgeAABedws1HliGqRBjyyoIAlPKL8e8VnDRNOqcpHqvWdTfKGBAmSG1Ntbe2v486x4XAFf28I7w4h9olJkNoWaR0%2BriRKVoHJDw/C7Tm%2B4jx51MnQFgR4fwT2fJanvF4w0mBNS9Vm4tcTX3/NVPPZljACAKAhLOiUVBmR7ziXcJNXNfhUGGi%2B4DbBBDcmff219VA973iTbE7c7bRBc1ePQSkfbOnHuw2h0D3Iwi7vjFsG4%2Bz93uuNqgAVdVuTtIqVG6jA71m0DI5xndzT1boFaK8bJDQSkMZfeERUjxaCoFQOkcDEa/VRrDV1XJcSSDcgAFJZFLRYFT2S9P5IuMZuMFhQPCcswZkaXM8ASgKapm4sNakjUY7R/ZFyalGx3CpgVSbv0nlVEeF99BcPfCxI8p8gWEYXDncAUtX7MgRbKj8F9Na0sEDi3vKZqgks40ycEN9hX139pPaqEgwpUCwbndyBQXhohns5MebkTBhoxYIAAWiq/DRwfTp1apJkyllkDaao0uWwEaSFmmeAuBV2L6zo3ZjCLQMIEo%2BXMzwJ6toIqxUhYlXiwUUqxWpYQPKuF0VsAhlKrBELprZQPYuKqWC13XtCh2TM1bBX1m3fNVfSclxbQcl6bkMQuiTiPLdbkWHlxr1jdB/wVUIqdXPZ%2B7nLH/cfpEzpaDtM1hrB4GB%2Bd7MYrloUJ%2BtqnH92AnaDVTq/rK0ifE6FOjmZXpZWx3dE992ItdG51p7tPVvP%2Bv9blSLrVEBmfWGUmS90EuOec4CfL/eFgldqqMXdq%2BoC8XtzeLQJQR8kcXGUBVVUGaD1/BRxboQfGTcgYw5RvDnnKeCjhwx5Nrgqq/GIFgYgqOr7oB%2BH9wFpPLD84%2B17BFxAGAM9lBuugEoIB%2Bie3fFXgKLhs64KsWFIOr5w/tPO69H3MC3mraKC3KonCqmG6UbZRgLdHk1ox1r0R%2BsdeeBb%2BDfWk3dezaBnbtBQ%2B5255jtVVs1fq%2Bj2ZvRsFCf6/V79tVC%2BvkWLXxdt4QcVd4CQgeXVs/V/E8j9MskbxngU%2BpcT4/sElTJ9zpfunp/ZdHQZXf6Kqf6AzNf%2BLlLuTh/sGNilrnhMruqs/oahAAvljjHgXsaiVnPsTr/ung/uiAEkAVSjvjAfAdrogbBPTigaDn6GAYroQT9AeNAWal7j5pgC2rqivromgf/owVfn6FLsQDgbgWQZ9ggZAX6MwXQXweAZQe6AwQzobp4tIT4gVM6sNOOGeOEDWsgPvGYNkLhhcOHgKknhWiuJgPpo8BAAcIkuOKuKoP1v2muDsjfoVF5kFj5qhvQOhrBrNqVjuF%2Bi%2BploIDulFthu1mbisoxsgMxqBsNF3j3uyJyB4ceJ3lMI4Omqmk/j6n1N5tkC2hKC%2BhkRKMES%2BqEeyKBtmm1lEeesclLMyjLGyrNhyhtmmFtjtizGgvyjsgQIaJxgwELCGGKkwGdt/gaGKhqOKiLoMfsjkbftJHDs0CQBKDkY8pMZcF%2BuZomu8K0HgCBPQBPmmGKuvDqHvHGLBDkeHAsSNImKBJkqWgwAIP1vQEwMhninDuJqmlJlsQMTKrsWWD8LBAceSjYrlN/nDqNOVA4L5i4eEQ8ZcO0q0a8W9hcOwT9D1pBBqrSv8SXpcGEDkBkpkWVJUSQFJicasTWhsaKDCUKB8XvPvuKp8khMIaTACZcAmOzDugIMJg1gwDcbcPcfSQ1lgBpnimgRAEHLtKgBMXQXDq8POgUSxgQA5mKZcIPtknQI8H5smBbhEI1uwOoVbPof2jcNmi0KmgoBbtznWn1nWrop9j9LnrBIKUvpgaHN8gIWITQctK8LBIiWZhPB4hbn9nlggHvIqbQLekaXKeuiWvJthtYekPMqSRapcAcBEMourj7qsn6QGXOkGS7q4T6dyMADiPcJFggIYDht6v0UKHDoGcqWCYIH0cmeDgABLYARD97xpbIfZ4D5bxgZltKoAW6vCGCPBpkJbTJHjj5qkakgBal1oNahaJiGnGn1ammtCEzml0E7IQCWm7QHFC4HxumYEelEzQQ8E757nugelZ7uiHnZSomc4pkXASncjkY8ZFlxgkAW5V53ilT%2BESgqkW4Cqnp6maGJHABIQnpJ6hn/lJp6nh7hCxkGjrl7kFxwlezRA4i7jHGhnfDbr3lqjrjfl173j7LFZwWygeklbQRqp97emhlCCGHqJFHFbZYW5dovqMVHplne6QnYYGDEBnjxaVkkV1wz5SFf4nHKAGAsjZGtEPBZmgZwVkXaxqotqmqyHMyWpBroihqBp2q%2BoBr1m3DriHZGJ%2BoBqaYhp1GGqababaUxpuBxrZAkYpYGXZperu4uVtDPkSjAB4DbpxgchGDow6W%2B5ZL%2B6NQkDB6LbqhBkB5foWFOVrhJqprDSDphBeCbAKCslAVVRHCCprjpAB4vpxW/nHo5bYbNTvBOD1Ttn5ZVbEVmXWWOaqjYAuZuYeaBUxp9RwyOE040bVluFoyxEhZhY%2BEFnZaMZ9a1XJElapHebXbDVsy%2BGRalUShpmTWJbOoTZiKVGspkjspXKMw6abYMDbaHJ7aeIIBGVdE5gKh7ynYrzvZXYdk3bb6RzvaWnuhzUUEM4PUyoXmfKcYM5DGUmqhs7v54ro7YpEXXR4K2kMJyCwpxHnQ3SS79bAF0FAXtG6GApISH6ewM4ClZ67RcG37q7U5wkn686Z5ME0EY0dHY2/RIRS5iw0FCFKUiVJn0reJqXyE6XWoWW9QOp4iWjYhZBoyNDYUFJeC0COD9bKA%2BWNYXBjplIlJGXBqmUaV%2BpaX2Ea0NU%2Bpl4tauWazD7dJbDZDYVMgEAFlxhHg3ClGGBnjaF3A9Y%2BrBUppprVThVxAQapKboRKFmzGtq5GrL5FhGCDDQRarGlTQZczcixBDUvpxKOjOiZnBFaiyUYa1kzq27uoV6rqIIQYADyflhhEyoF2GkmLQvaJ6yVodRWi1kdYZiGXaDG16MlntIe9V/N6YVlXdM4vqX6DoLU0NPq6h/pcMCgIAJw0MoEIEEIaALARwAq6Q/Wg6oGRwXgE0LS6ACgIIs0AIGgAIhon5ctrMBASt5SKO6Q6AyGFaU0vdl4Fw%2BlnuOleiRwPWh1WqXWjGJAHZYQiaR9Ygst8te859u4FeLwFwAAagYPgM2kTD6gAJqtBZAGDvAKAVLPAwkhjBq63ho6330BL90pZ8zD0v11pj3qaT2L0CoCoQiOi3DbAIDADUwQjhAEBHDpBtbbaiB9IghDgJD%2BCSAmRJDaiS3S14BAOn3aigPXrahhgkDPDagDnaijRow1quFGm30j0EMhhP3tUzqv3v02VZ2eV9o3B7rAPqIjZZpiDAA/1xJ1KvCJL1RFl5m9HDTBBqYMH9YF0HqqBISS0MBbhIQDmK3rGoBYOv24O6b4Mf2GqsivmNopKB2PAAO0CSMK0yOuUQNmaoDZKJXjw%2Bp2aCCsl7JPBQabCppV3YZePslVJbAsjaDoAlJ/pzrgU6UvraBMCrEQixJ0CfJ4CoUvGd1xPBg92jOYz63uVFbcjB4%2BUyWbjbiMaOibDbCigDNKZJrNLbqRM4M6PjPGOf16Ja0a0BoF1JPNptp9IT1q06O%2BrmUTN917OPMP1kjRMGNkieB3O%2BrbbfO%2BrvNHOrz6J3OKAShCCri5on0K20X2B9LfR%2BpeB/NRNItvN3NQtgZQUDr3hUBS2ZXAYOALNbieEj7Dpckxo0DYV7L4AV0kmQZm5UvszUzdZ6nRaVbrY%2Boqll0/l9VJpNZQbVrxYFnIBp5csrjszoD0DDScugmu54Z8sj49I4nbAisFO7rDSrXrLp3JisiIYUtB27r0sDmMv3DMv6Of2t23pxhUw7AQbmirJXGHL4YfliBl3mNNTAOmvJXOhKBxiLM7iFXiubHDR2uJW/CxLZAohVo27cjOu0CgUCo/D5Wn2msj6wtaw%2Bp%2BuMZCtp4JZlK0v1mibbpkDHirKxWBt7rW7h0xu3guu7pxhfoNTAB/5JsK3FpN2zH4s3obhEtqs%2BrNoPp/6hPlRQ4CCJqgOTq5ptulRdpjwQb63DQqh5Oijcj9q0DqZjW9B7wtsYtwZ7z4AVUogvoV3O06V/JvC%2BWslnuZDxropITNqODMPAWMbXvZBBLbYoxIYobYYJsJIDYUgSgF0QDNnoitbWVmDBqgd4hexNqCYspKiECYOHTPOHPxP3O/MvOEM/Pq0v3/NIt6KIsYchigsXCtirP9bpKvD1b2jmPkedZW4Hp9IB4%2B2MCW5ZCvuSsj1Avr0ovogcM8duAAvxNiMy1CqvBN6MeNSOhS0Yst2rhzw2711iA8a9k%2BridZoMYm0JLzPxjGzgazrzqrj7jciiAyYpa1RrLP0xrbb7jCYQbCcSOidWPN4xWm4/CrvrtRbqO9s6X9pPWkud6uXYiYCYCRNceCcC2v3ococRdkhRdIeRp4e2x3PmhbIzHOayvcgboscvuDMcc4f3MEfReYxhf8fheYzYA1ulQqndZVPVduWOhi3ytqfVI%2BpTvlPHipc3DoChf3Nld91ofYcxpYeleJdrx3OJLBd4XYYFLlusd26dEKBexnvgvGxD6sc3t5dDdceFfxdaYjeEesi4Y7rNct7VStMWdZEvkHIWOn043B3Yb9sStmvxNsZZrz315KDcjfAstXdmBHBJBIYhG12PIFmR2Z2f2QW5Xrird1extjXeEethv%2BcvqifDSxDo4rUNCm3zOZU/pGA9fIsHcDd/OxeDcGO4dE9As7c%2BrEeuqZp/BGUXBF0raEAylgslFsjnohn5ev3U/5fIe7d9cP10/zcTszPZpyelShM3DbbrPWEVWsn25CrpD5X4/DStiYD/kKdYjRh9AKhOVrtjXGwfDrH3Df1FvWFtJFmlkxpUzABeDrPXoud2M1oOMKAhNVOMmKhjHK%2Bq/AC9Z%2B0FrrNuDKByA6eKmNRHjmc4tzzxZKj3CCBzv9pRIZu3DjKOgIZDXZ1ZoV6dpp/LPqwweYZkszqAfHWoBbJezXqYZxgKCS8kvF%2BO0tAE8C%2BcfBpxecfDeU96JC%2BYdU8gtm76UJWM9HjlVFFZNtBgAcCZcGZ/t/JZEpLPe9Tvf0CqAIcE%2B8/8d8fd%2BosHdTO501cg9biMgNCODYXXoiwsCSZOhha5/W8RF/oybKdhb29Gy%2BEyVl8qaV8IYu8lo7hZdbpzwx6RfjmDg5r8P286WIPPQDw1t0AHIRwMgAgx6MkIQ/Qyl6irbdoZKR4bpmgnN5xBLegPGJGvxcxSZ9SeJM8C3146997UkXMnkc2DRfMDurfHSn1BiT6YEkUDGBsk1VBINj%2BqDdBngD7ypE2BVmYzDf1yYWZhBeSJzDZguDFMZSQglgSIKcxCAHQqVC4M4ydAFoOQjVbkAcHoBdNU0W4FbF4xbQ%2BMD0ylKQewKMy2tiygTLcLoNZBbBlaYTJgCpyUHSCOBzVWXhcHcwzEHCyWHqty1lZlR3CqRLqslgBxVYsutWddABUEwKgmSNaVvD6iWJst4sJ3SJmkUcJDUMsC1Uat%2BRLJrUUiLA2ak9XmpZZChGreLMVliK%2BdOyR7TJAaRZB5FsMUpIohf2PRutM2rFbZI4ETT1D/SgPMwF/zJBd48Q4HXjuMKWjtMuom1NMKcgygzZ6Y%2B1bAItlUylQohmrWCNiAd7301E14S6pdl%2BqcZwe6uY4TdTM5pYzhnOUYnvEGEEBRS3JYqFU16Gg9E0xadAHEjgo7Ed4exT%2BB9XKGg0Aa1FbkiLxzroCISEvVbhHSU5wVI8QpcsKaAtBWh5u1HUUMnXQDHlQcCeSZKrXRBrCVs6QoxCQhAKnYrhOSOgkXkZS5w4cqA6ZtVhY7ZFIR3JILhKCgHbh1mSoHYPGm3SylWRxseEVQAgAPC9Ev0bEVfFxEpZLq5I67NSLpJokSOj4UNjtmVCMAzaS/bMHDjypbg1%2Bq4d1MES8Jzog8n7KEW8LiCR0fh7xP4Y7DoKnlWEn0eODcNFzGjXQP0N0jHggB7k2EDpDCs8OVHFkdRqAPUZAihH9sRqgPc0cQEtGKoAkYqftqQyvhDVFciAIEf9QFRkofR8NP0YqIOCtlracQYVn/kfB5tueioo8Ayxpbutk2cFC4fFgyoz5OM4BOJNWnHgkFYS0qS4QoHeoUi88faVsTmNpGXBwROfVyqtz1YnFKx1MasY1nozslrWIXaSJHj9ANiOCIWEmpzmWgSg1UASDKizQbEn4QRZ%2BLqMmJ%2BhCgaYx44RFzW/zLiExHBDKhuOJxbj8EKuftizTvFniVxYNDiruNKg7jBQF43RBfjFGZ5OMj4tfF%2BJfEBIXs7Y3OKBNCywRzxNBaQgblEp4plx3YkCf23AlXxnxO4lcbSXVwESoJfoN8bBMNQfj3QSE8ifBVWQQAJQ94rfD8joLphKJv4mgumAPGIS3gHE37HRIYmYF4JOE3glxLfxHiQC6YU8VRIAm8TP8HNYnChNziqUbxdEv0J9UEndjhJr1N4KvBVzfYaJ6YdSdJIIn7jVQUE2UIBLXL8SsJ7MLSaQUwm6oyJl4uCWxOonOTI4wExiXZKIlsSvxsk4MKJOkmWSfxE4TyYJPXEvVcChqQKdBPEksS4JUkiyf5KvEgFFJCkr/KhOvGKiQ2DrfVsyLaDptuSU4s3tu09ZQjY2QomZPBLFG/j94RYYXCIVEni47xO5eqSIQ/G7Rdx/BeqULkalmSOCco83KGWI7ojMAGTEBuOhVpTpi8Q41kPmJlYaNeWbebDDQF/ZKsixmAZ0ZHDhzhj8hqrJQD0jbyFic2hQ7dhbkJLrF0UfJH8ctHSAAwiCGVLabnHSD1oiC/bJ6ZHHSAA8HptJC3FGAKorSBWeGJKqGTjR7w6ulSJkoJU4p0tZimQDFm11iDGkSoMlUJqVMbpWxQyV6X3jJQ1CJsJKmo7afKWpgd1Gpf47iZJLik/jSJBsIgoCibEUF5RREhyRTMvD6SbyxOOHJaExLbZsSUvKpsAGhlg4tSy7acqEzrR5k0%2Bq5H8XDga6n8ceiHOgu9j%2BrJiECH0mdNVC%2BxPVBxnMy4E7jwDrg6uu7fvHqTEA4h0AEpV8kHi9osEMy6eTfGKM%2BqtToJYou6UzM5ysEIAUuTWRdCGp1TKEfoH2bdKWQ6zQccODwOkDIz8zHgwAQWRblNLLsOSlIMWSDJlmXAJZ%2BZfrJLLuDSy6yleE/uLXniKybpj2FWerM/qxy1U/vUEXnPo7WM/g9UAGRKEkD9ZUeoZLJP2jYBCyCadpd0MAG8m5wBSVNK/C9P9m9SQpkcQmrBH7mRSop65YeZgTdkSTswUPQFNqSsCWAkIXyZKWtEsDWBvxUUtKWviHlBymor01qcvINBTyfoM85iRPPqLCjA5C0JqCHPimRxV5scqXEhH7k7zBQ3s/yUfPVzrks8y0GeahVuDoUDJm2R%2BSApfkDzicZNLwBTSgUeTVJPs3aG7NnlRSZw68xXCfgPnYLDUOiPeTHkQmBzf5XiE3Cn3vkniF85k8hSgq6jAApcJE2ORQsDnMK2c3Egju5OijG554ZuO%2BYQsFCILkFvCq%2BMuPQVNRCCCqN%2BbQpIXa58FFCySbgtIWfjq54ipSVlCoWEzsFmeOhfhI0WXyAknCtVDwtSkZTOcykvOZbDeCGkIMQgZXt5zznoz2sE6PGU1AJlCyyCqsggoISlw6JGFmeP6i9N5yryAlW87eUEsSmcEbip%2BaCSEq4As0jJASBfGwpygmKfZ7oL6aHMVERyxOljAGKE3SihkRqkSIWe9i%2BI/QuY5c%2BJgJL7lGKaRusj1M7lh6Vcxqd0/vFUy%2Bndy7ZMyKXFUuWiqyepHsP0FUuyjZKC8NBT2QvgEm7QnZIygJPUtghfT5RjuQLtxWJEFMLc1Qrdj%2BgEAQBFuQsw4egIJFIQthWIJ2GSNOG/AkIoo/PLondnE4Tl1IM5RuCU40xSRcizaRSLuWYA/OfYpJVSNyWzT8lM4veEUqqbgdSl%2BQ8pbonqWfICFxOcZYKG/GO5WlfVatp%2BSYqlLIVHMMwL0pzb0SxRXxZ2X6GWU/Ql5ci2ZdMr6UQBBlOk4XAfDGXQ1KVZgCUZzgGUgqiZFwENhNU1aPdNut5S4K9xXTKcfgPFM8BblgLZ48I/3SMdhlhFfJalsoOHGeC3aWN0AG9bhkyyR4W5WhEoUTkLN%2BGCBd4ZUBNmXiDzcg3QIBFsSaKgS7Q/iQEuifSr7GYBMxNquRRAAIAWrXRi3eBdFCnxSoSkxqZRSUigTuheyGShfLuA5U75lx4ausCsqmVyKJwq83cEfgXxPLsFAih8KpMTUTKz5Aa9XOmqQioApc2a4RSWyqkFrk1caqtdmmV4QAM1PEhRZWtwKAKtFWU4VWL3GpbLBVuiicHDlFUMBjl%2BItwISOjpRIt4IBH5agD%2BUAqHlwKmuT2rBXbs8IqrEpWnPCyLVrp6uBFZ8hoIor0lHMsOXrIxUZc3g7SogHXnrRoykghKv/MSqvykrFl5K1ldkvZWpSFFwU9XJ7IZUMSyV4ylZa/JoVcqV1zSkNrsrFYDtB1WokVfssmTirPky5ODXGR5yyq/uAPA1SDwtFiB1gFudVeCu0LaqE0JrPVaGRw1GrnVMyV1WzndX84QC3q31a2P9VYLicQagJCGsfxhre5vwXnDGvrVAL81H6otcYtlClrW1G8iwO2p3y5rq1GeWtZSqWTsbsFkm8tf1lk3YKE1oml6UJuEWSaYYbaihZ2sjjWKe1FeaDQOrryIax1pyidUhCnWfLYC3ystQus7JLqfxayqETlIEB5SHu5bQbOyyKlGsqx6Mp1pVzgr8LTceaqqauMEktSRll8mmW6PFyaShp264jmk3GmK1JpYvF8BbjzGbJravVS9TnNDIvpVp8WUJgdIECFNt12bcjPDzKrANzpaxYknutuEyohl64B6UitBxk1iAvWunN2O5XRQ4c/0yPoDLWkDkLcYMrVnOIjaLjQyYYM3IyFnEYzymyMueI8FCbotMuuCLGbMRxmWtR%2BBMubSTO8XxaVcMEzRZeEwlEF2ZM0nldzP6G8yJQ0ci4HHNDIJzk5%2BhcWRWmzluxoV26uWYXNs66IpUKs04bLiflay0sY2odeeoNkLb3cJs09LQHNmWzA8weR9fbIUWE1exTK0ZYTrXZaaJwns72c/OGUBzT5Q27zdurrnN4wycSZaeGFiT5MqABgf3qGVsb2MEALAOvFuGvYyUP0oZXgSg26YCDi56uTjX6G43VKKFiapChoq1zWBY1IBHTVfjJ3GLJNqimTf5Pk1a6Lo9O1TX%2BrpVw6TdvWi%2BamtzjK6vt%2BmnfP/MYVpqm1LazheTs5zG7doOu23WmD11ZqAFaE7dbYtcB6dHFCVauqUsR5uK5MggfGeKG8UxKAlLNFWdpju0BIUlgYBRY0uplZKPs6e57eNsuBrrLGJYnkRUoCTDaBcKq4MNeCrmI74NLSlHUbOt6Yt3y165auCs62oE6Vw2oZQzLJXV7ns6QR3dFClyF66Cns%2BvVfgWUByZ9SagnKPu/XSbrwje9DYzyHKhMzSMK%2Bbj3tBwvLjKhIi5SSJc00LyR6QdzUMM83q5PdaYQ/WSEnUfKrlci68HcqepX694N%2BznAzrzn6z1wqAItqjuNm869ScPU6R6zx0zJCdmsslReRH1j6Jwm%2BWlUStPmC431WS5fMvrkXO7T12U1ZAOu/Si9MkbeVTCht4r2zMN8q9innKjGR0CNoZIjeuq1UTQyN6zTYDbx7VUbOQQsyPNAD7FMTs8TGtqGzjtVYji12YOXQWsPUu6Jwyu6eQJoUUa6/dCm%2BXaJt900LXdwqFtfrrv2g4jdImm1UvokPE5JNHu5RXxJrXqHR9ZugzW7q3mB7ZDZmyxYQtM18Lg9dZRnoQZHV2bXlDm95TFpf3n7v5n%2BwFY8vX3CyQ2fmwPBd3jCu8E0pUM6VCOKnrMItn5KLdovk13yLcxHYds3lrZCAqo9AcaRbnHZGUCtoZIrR2TjC7Shio/VraGQunEljV3WpqI5PZgRHVVlwSbdVEHyuB4cUMi3ADjsVFoSoW20MjcAXG7bulljKdsxWO15VRdzIEpKylJnUzfJt2ovUjt5V9D1i72z5Kq2%2B3brftmjO9VUwzlSytGoO0UI1wVmV6F5AuQfQQVr3ph89T2ppWeub0AGgDre8rduvwxmzbgFs3tO3SgPWlMCc%2B5lYTuwM0LkDjCz2WgcH0YHn5MJqKbga2NN6mdo2XRFIeEpOHBQ8hm%2BYoek3KGaF3upqIgdzgB7jN%2BJgw1Yc%2Bg2GhFwiz2Zbtuljy2pmhyOPbp/kqHZQ6JlQ2YYrUULyTqJhtYKGpPSa9DSBjwz2vCQLiSyIxpPQzLpwp6INnxiPeuHXUeKFxSetVJPoVGrq1MZGGkg0GeBIgvKEGE47nJ7UA6zAQO6cmDrP5FyhZ%2BetFTRWdyAGd0vxzg80rSOJoIDp9ME7App1QndNlJtMKqYz0InHZ5Q4nSYrDMr7rAue9ZbmkHzS8AVI6/fVfAf1vKT9QRqKeSLjZOVF1K0ZdRnpzP%2BGnN%2BZ3AiBV%2BXFmPNpZrzezQyguHaCrcH0Kcj0R7V5snKVuA0VOq4CvARw7ojKnca26TVmof4cgEEB2S7h/1YAGYDcD7JYIzyEJAwDeQQBpzjwu0o6qERCgpRh%2BiAL0TCwpitzgK9YPOcXMzneEshYPWcCGKrgwgEAcCRqBDBfpvimvEHgrE2hek7sENIYnjmRoZK8cjqg6NGoUVo1PEHpZEjBB%2BiOo7snPTkBPRABDn7NNo0/cec2jZr/zUNEZMBbFE/nwL0myC2moIDoAQAKADgzubLRIlfzPoLAPQFljSIzyxxLKBwHWC0BOAgIXgH4A4BaBSAqATgAHAUUuUGmgGpyLwAICaB2L6wXcCAEBCIROLHASQDxeksCXOAvACeohCkt8X2LpAOALACQDvc08ZACgJue3D5V6A8QYACdEEg0BpakSSgNEDUtBJmAxAZ4JwB4CkB56rhIusJjUtYBVwRgcQLpdID4BukTpieqFaVBY97gnl3gCeCUv8XtsQzdyx4CwBqXsQKSeK%2BsC50FoFAkDVzAKnOaMB4rMgQQCEnEB%2BR%2BAggUFmoDUu6B0IBgIwCgAXz6BBmE9SAOsDUzXNOAPjJIJpc7a5AXAqaGYF0CCCppFgoweIOhGvbN4xregOa30imtVAxg6ETdk0ASILX1rQ1/oAkRWvLB1rW1zwJ0D0CJg2gB1ta%2BsHqZrM9AbInK/oC4uqXQrgljgKoBSBFh%2BsNYYAMgDUInQIQ9aCAMJek1IRcAhARcvCBogeBKYJl/eE5FWCSXpLheUgHJYUuPXlLz1/i69c0sgBtLSNji5wDMCY3eA2N0gDpa0DI2i22QZwJICAA%3D%3D">
</iframe>
