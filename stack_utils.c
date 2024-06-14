/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggeorgie <ggeorgie@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 22:23:54 by ggeorgie          #+#    #+#             */
/*   Updated: 2024/04/29 18:06:52 by ggeorgie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// void print_stack(struct s_stack *stack)
// {
// 	struct s_element *current;

// 	if (stack == NULL) 
// 	{
// 		printf("The stack is empty.\n");
// 		return;
// 	}
// 	current = (*stack).head;
// 	current = (*current).next;
// 	printf("current order: sentinel node -> ");
// 	while (current != (*stack).head)
// 	{
// 		printf("%d -> ", (*current).nbr);
// 		current = (*current).next;
// 	}
// 	printf("(to je konec, which leads to the head / top / sentinel node)\n");
// }

/**
 * Function to create a new element.
 * @param	int		nbr: the value of the new element.
 * @return	struct s_element	*new_element: the newly created element.
 */
struct s_element	*create_element(int nbr)
{
	struct s_element	*new_element;

	new_element = malloc(sizeof(struct s_element));
	if (!new_element)
		return (NULL);
	(*new_element).nbr = nbr;
	(*new_element).next = NULL;
	return (new_element);
}

/**
 * Function to insert a node at the end of the circular linked list.
 * @param	int		nbr: the value of the new element.
 * @param	struct s_stack	*stack_a: the stack to which the element is added.
 * @param	struct s_element	*current: a temporary element.		
 * @return	struct s_element	*new_element: the newly created element.
 */
void	*insert_element(int nbr, struct s_stack *stack_a)
{
	struct s_element	*current;
	struct s_element	*new_element;

	if (!nbr || !stack_a)
		return (NULL);
	current = (*stack_a).head;
	new_element = create_element(nbr);
	if (!new_element)
		return (NULL);
	while (current && (*current).next != (*stack_a).head)
		current = (*current).next;
	(*current).next = new_element;
	(*new_element).next = (*stack_a).head;
	(*stack_a).size++;
	return (new_element);
}

/**
 * Takes the elements from array row 1 and inserts them into the stack.
 * @param	int		*num_count: number of arguments passed to the function.
 * @param	int 	**array: Pointer to the array with indexed input.
 * @param	int		i: counter.
 * @return	struct s_stack	*stack : Pointer to the filled stack.
 */
struct s_stack	*fill_stack(int num_count, int **array, struct s_stack *stack_a)
{
	int	i;

	i = 0;
	while (i < num_count - 1)
	{
		insert_element(array[1][i], stack_a);
		i++;
	}
	if (!stack_a)
		return (NULL);
	return (stack_a);
}

/**
 * Stack initialization, including creation of a head/sentinel node.
 * @param	struct s_element	*head : Pointer to the head/sentinel node.
 * @param	struct s_stack		*stack : Pointer to the stack.
 * @return	A pointer to the newly created stack.
 */
struct s_stack	*initialize_stack(void)
{
	struct s_element	*head;
	struct s_stack		*stack;

	head = create_element(0);
	if (!head)
		return (NULL);
	stack = malloc(sizeof(struct s_stack));
	if (!stack)
		return (fn_free((char *)head), NULL);
	(*stack).head = head;
	(*head).next = head;
	(*stack).size = 0;
	return (stack);
}
