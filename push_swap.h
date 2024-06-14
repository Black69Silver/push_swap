/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 03:02:31 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 18:23:37 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>	/* to use 'exit', 'free', 'malloc' */
# include <unistd.h>	/* to use 'read', 'write' */
# include <limits.h>	/* to use 'INT_MIN', 'INT_MAX' */

# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

struct s_stack
{
	struct s_element	*head;
	int					size;
};

struct s_element
{
	int					nbr;
	struct s_element	*next;
};

// push_swap.c
int					main(int argc, char **argv);

// array_utils.c
//void				print_array(int num_count, int **array, int z);
int					**initialize_2d_array(int cols);
int					**fill_array1(int **array, int *array_copy, int *num_count);
int					**index_array(int *num_count, int **array);
int					**handle_quotes(int *num_count, char **argv);
int					**make_index_array(int *num_count, char **argv);

// parser.c
int					duplicates_check(int num_count, int *array[0]);
int					push_swap_atoi(char input_str[], int *i, int sign,
						int **array);
int					ascii_sign(char input_str, int *i);
int					is_digit(char **input_str, int **array);
int					**parse_input(int num_count, char **input_str, int **array);

// stack_utils.c
// void 				print_stack(struct s_stack *stack_a);
struct s_element	*create_element(int nbr);
void				*insert_element(int nbr, struct s_stack *stack_a);
struct s_stack		*fill_stack(int num_count, int **array,
						struct s_stack *stack_a);
struct s_stack		*initialize_stack(void);

// sorting.c
void				sort_3(struct s_stack *stack_a);
void				reduce_to_3(struct s_stack *stack_a,
						struct s_stack *stack_b, int stack_a_size);
void				sort_small_stack(struct s_stack *stack_a,
						struct s_stack *stack_b);
void				sort_digit(struct s_stack *stack_a,
						struct s_stack *stack_b, int chkr);
void				sort(struct s_stack *stack_a);

// sorting_utils.c
int					not_sorted(struct s_stack *stack_a);
void				swap(struct s_stack *stack);
void				push(struct s_stack *stack_1, struct s_stack *stack_2);
void				rotate(struct s_stack *stack_a);
void				reverse_rotate(struct s_stack *stack_a);

// ft_split.c
int					word_counter(char const *str, char c);
int					find_start(const char *s, char c, int i);
int					find_end(const char *s, char c, int i);
void				free_memory(char ***pointers, int arr[]);
char				**ft_split(char const *s, char c);

// memory_control.c
void				fn_free(char *variable);
void				fn_free_ptr(char **ptr);
void				free_array(int **array);
void				free_stack(struct s_stack *stack);

// utils.c
int					ft_strlen(const char *str);
char				*ft_substr_end(char *substr, int len_substr,
						char const *s, unsigned int start);
char				*ft_substr(char const *s, int start, int len);
int					*bubble_sort(int *array_copy, int *num_count);

#endif
