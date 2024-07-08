#include "macroshell.h"

void swap(char **a, char **b) 
{
	char *temp = *a;
	*a = *b;
	*b = temp;
}

void ft_export() 
{
	int	count;
	int i;
	int j;
    char **env_copy;

	count = 0;
	i = 0;
	j = 0;

	// Count the number of environment variables
	while (environ[count] != NULL) 
		count++;

	// Create a copy of the environ pointer for sorting
    env_copy = (char **)malloc((count + 1) * sizeof(char *));
	if (env_copy == NULL) 
		return (perror("minishell : print_sorted_env:"));

	// Copy the environment variables to the new array
	while (i < count)
	{
		env_copy[i] = environ[i];
		i++;
	}
	env_copy[count] = NULL;

	// Sort the environment variables using bubble sort
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1) 
		{
			if (strcmp(env_copy[j], env_copy[j + 1]) > 0)
				swap(&env_copy[j], &env_copy[j + 1]);
			j++;
		}
		i++;
	}

	// Print the sorted environment variables
	i = 0;
	while (i < count)
	{
        write(1, "declare -x ", 11);
		ft_putstr_fd(env_copy[i], 1);
        write(1, "\n", 1);
		i++;
	}

	// Free the copied environment variables
	free(env_copy);
}
