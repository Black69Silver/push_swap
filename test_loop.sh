#!/bin/bash

# This script sets N to the number of times you want to run the code, then uses a for loop to run make that many times. The echo commands are used to print the current run number and a blank line for readability.
# To run this script, save it to a file (for example, run.sh), give it execute permissions with chmod +x run.sh, and then run it with ./run.sh.

N=1  # replace with the number of times you want to run the code
		# 25 for 500, 100 for 100, 300 for 2, 3, 4, 5

# for ((i=1; i<=N; i++))
# do
#     echo "Run $i:"
# 	make test
#     echo
# done


# Write a script that will run the push_swap program 'N' times subsequently with 2, 3, 4, 5, 100, and 500 different arguments each time and compare the result with the checker program. If the result is KO, the script must stop and display the error. There may be duplicates in the arguments and they can be any ascii character. The script must also use valgrind to check for memory leaks and show the number of instructions used to complete the sorting.

# Array of argument counts
arg_counts=(2 3 5 100 500)
#arg_counts=(2 3 5 8)

# Function to generate a list of random ASCII characters
generate_args() 
{
	local count=$1
	local args=""
	for ((i=0; i<$count; i++)); do
		# Generate:
#		char=$(printf "\\$(printf '%03o' $((RANDOM % 94 + 32)))")				# ASCII characters
		char=$(jot -r 1 -2147483648 2147483647 | tr '\n' ' ')					# Random integers
		args="$args $char"
	done
	echo $args
}

make re
# Run the program N times for each argument count
for count in ${arg_counts[@]}; do
	for ((i=0; i<$N; i++)); do
		args=$(generate_args $count)
#		printf "Test $i with $count arguments: $args\n"
		printf "Test $i with $count arguments:\n"
		output=$(./push_swap $args | ./checker_original $args)
#		output=$(./push_swap $args)
		printf "Output: $output\n"
		if [[ $output == "KO" ]]; then
			echo "Error: push_swap failed with arguments: $args"
			exit 1
		fi
		# echo "Instructions:"
		# ./push_swap $args | wc -l
		valgrind --leak-check=full --error-exitcode=1 ./push_swap $args > /dev/null
		echo
	done
done

printf "Already sorted stack:\n"
valgrind --leak-check=full ./push_swap 1 2 3 4 5 6 | ./checker_original 1 2 3 4 5 6
printf "\nStack with duplicates:\n\t"
valgrind --leak-check=full ./push_swap 0 02 -0 +0002 | ./checker_original 0 02 -0 +0002
printf "\nStack with non-numerical values:\n\t"
valgrind --leak-check=full ./push_swap -1 2f s3 +4 | ./checker_original -1 2f s3 +4
printf "\nStack with multiple signs:\n\t"
valgrind --leak-check=full ./push_swap -1 +2 +-3 --4 ++5 | ./checker_original -1 +2 +-3 --4 ++5
printf "\nStack beyond INT_MIN and INT_MAX limits:\n\t"
valgrind --leak-check=full ./push_swap 0 -2147483649 2147483648 1 | ./checker_original 0 -2147483649 2147483648 1
printf "\nBlank input:\n\t"
valgrind --leak-check=full ./push_swap "" | ./checker_original ""
printf "\nMultiple quotation marks:\n\t"
valgrind --leak-check=full ./push_swap "2" 4 " 5" | ./checker_original "2" 4 " 5"
printf "\nSimple stack in quotation marks:\n\t"
valgrind --leak-check=full ./push_swap ' 5 4 3 2 1 ' | ./checker_original '5 4 3 2 1 '
printf "\nStack in quotation marks:\n\t"
valgrind --leak-check=full ./push_swap ' 1 2 3 4 -00 5 -69  +9    -9 -1234567890 ' | ./checker_original ' 1 2 3 4 -00 5 -69  +9    -9 -1234567890 '

# printf "Already sorted stack:\n"
# ./push_swap 1 2 3 4 5 6	
# printf "\nStack with duplicates:\n\t"
# ./push_swap 0 02 -0 +0002
# printf "\nStack with non-numerical values:\n\t"
# ./push_swap -1 2f s3 +4
# printf "\nStack beyond INT_MIN and INT_MAX limits:\n\t"
# ./push_swap 0 -2147483649 2147483648 1 | ./checker_original 0 -2147483649 2147483648 1
# printf "\nSimple stack without quotation marks:\n\t"
# ./push_swap  5 4 3 2 1  | ./checker_original 5 4 3 2 1 
# 		echo "Instructions:"
# 		./push_swap  5 4 3 2 1  | wc -l
# printf "\nSimple stack in quotation marks:\n\t"
# ./push_swap ' 5 4 3 2 1 ' | ./checker_original '5 4 3 2 1 '
# 		echo "Instructions:"
# 		./push_swap ' 5 4 3 2 1 ' | wc -l
# printf "\nStack in quotation marks:\n\t"
# ./push_swap ' 1 2 3 4 -00 5 -69  +9    -9 -1234567890 ' | ./checker_original '1 2 3 4 -00 5 -69  +9    -9 -1234567890 '
# 		echo "Instructions:"
# 		./push_swap ' 1 2 3 4 -00 5 -69  +9    -9 -1234567890 ' | wc -l
# printf "\nStack without quotation marks:\n\t"
# ./push_swap  1 2 3 4 -00 5 -69  +9    -9 -1234567890  | ./checker_original 1 2 3 4 -00 5 -69  +9    -9 -1234567890 
# 		echo "Instructions:"
# 		./push_swap 1 2 3 4 -00 5 -69  +9    -9 -1234567890  | wc -l

# printf "\nStack with duplicates:\n\t"
# printf "\npush_swap:\n\t"
# ./push_swap 0 02 -0 +0002
# printf "\npush_swap + checker_original:\n\t"
# ./push_swap 0 02 -0 +0002 | ./checker_original 0 02 -0 +0002
# printf "\nvalgrind + push_swap:\n\t"
# valgrind --leak-check=full ./push_swap 0 02 -0 +0002
# # printf "\nvalgrind + push_swap + checker_original:\n\t"
# valgrind --leak-check=full ./push_swap 0 02 -0 +0002 | ./checker_original 0 02 -0 +0002

# printf "\npush_swap:\n\t"
# ./push_swap 0 -2147483649 2147483648 1 
# printf "\npush_swap + checker_original:\n\t"
# ./push_swap 0 -2147483649 2147483648 1 | ./checker_original 0 -2147483649 2147483648 1
# printf "\nvalgrind + push_swap:\n\t"
# valgrind --leak-check=full ./push_swap 0 -2147483649 2147483648 1 
# printf "\nvalgrind + push_swap + checker_original:\n\t"
# valgrind --leak-check=full ./push_swap 0 -2147483649 2147483648 1 | ./checker_original 0 -2147483649 2147483648 1

# printf "\nStack without quotation marks:\n\t"
# valgrind --leak-check=full ./push_swap  1 2 3 4 -00 5 -69  +9    -9 -1234567890  | ./checker_original 1 2 3 4 -00 5 -69  +9    -9 -1234567890 

echo "All tests completed."
exit 0
