### Goal of the project
Sorting a set of integers in a stack using an auxiliary stack, the fewest possible moves, and the following instructions:
* `sa`	(swap a)			:	Swap the first 2 elements at the top of stack 'a'.  
							Do nothing if there is only one or no elements.
* `sb`	(swap b)			:	Swap the first 2 elements at the top of stack 'b'.  
							Do nothing if there is only one or no elements.
* `ss` 						:	'sa' and 'sb' at the same time.  

* `pa`	(push a)			:	Take the first element at the top of 'b' and put it at the top of 'a'.  
							Do nothing if 'b' is empty.
* `pb` 	(push b)			:	Take the first element at the top of 'a' and put it at the top of 'b'.  
							Do nothing if 'a' is empty.

* `ra` 	(rotate a)			:	The first element of stack 'a' becomes the last one.  
							All elements of stack 'a' shift up by 1. 
* `rb` 	(rotate b)			:	The first element of stack 'b' becomes the last one.  
							All elements of stack 'b' shift up by 1.
* `rr` 						:	'ra' and 'rb' at the same time.

* `rra`	(reverse rotate a)	:	The last element of stack 'a' becomes the first one.  
							All elements of stack 'a' shift down by 1.
* `rrb`	(reverse rotate b)	:	The last element of stack 'b' becomes the first one.  
							All elements of stack 'b' shift down by 1.
* `rrr`						:	'rra' and 'rrb' at the same time.

### Example  
`$>./push_swap 2 1 3 5 4`  
`stack_a			|	stack_a			|	stack_a			stack_b			||	stack_a		`  
`original input	|	sa				|	pb, pb							||	end result	`  
`----------------	|	-----------------	|	----------------------------------	||	-------------`  
`sentinel node	|	sentinel node	|	sentinel node	sentinel node	||	sentinel node`  
`2				|	1				|	3				2				||	1			`  
`1				|	2				|	5				1				||	2			`  
`3				|	3				|	4								||	3			`  
`5				|	5				|									||	4			`  
`4				|	4				|									||	5			`  

### Solution
1. Create an `(argc - 1) * 2` array of integers.  
2. Fill the first row of the array with values contained in `argv`.  
3. Check for duplicates and invalid arguments (`< INT_MIN`, `> INT_MAX`, non-digits).  
4. Using buble sort, index the first row.  
  <https://en.wikipedia.org/wiki/Bubble_sort>  
5. Fill the second row of the array with the indexes of the first row numbers.  
6. Make a circular singly linked list with sentinel node from the second row of the array.  
  <https://en.wikipedia.org/wiki/Linked_list>  
7. For stacks with more than 5 elements, use binary radix sort algorithm.  
  <https://en.wikipedia.org/wiki/Radix_sort>
	* Starting from the least significant digit, push the `0`s to the auxiliary stack and rotate the `1`s to the end of the original stack.  
 	* Push the `0`s back to the original stack.  
  	* Go to the next more significant digit and repeat the previous two steps.  
8. For small stacks there is an optimized algorithm.  

### User interaction  
* Clone the repository  
* Run in command line: `make`  
* Run in command line: `./push_swap 1 2 3 4 -00 5 -69  +9    -9 -1234567890 | ./checker_original 1 2 3 4 -00 5 -69  +9    -9 -1234567890` or alike to check the correctness of the algorithm.
* For entertainment purposes, you may want to use <https://github.com/o-reo/push_swap_visualizer>.
