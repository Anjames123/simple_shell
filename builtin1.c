#include "shell.h"

/**
 * display_history - displays the history list of
 * previously executed commands
 * @info: structure containing potential arguments (unused)
 *
 * This function displays the history list of previously
 * executed commands, with each command
 * on a separate line and preceded by a line number
 * starting at 0. The function doesn't return
 * anything, but it prints the history list to standard output.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias that has been previously
 * set to a string value
 * @info: structure containing information about the command to be executed
 * @str: the string value of the alias to be removed
 *
 * This function removes an alias that has been previously
 * set to a string value. It
 * returns 0 if the alias was successfully removed,
 * and 1 if an error occurred.
 *
 * Return: 0 on success, 1 on error
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets an alias to a string value
 * @info: structure containing information
 * about the command to be executed
 * @alias: the name of the alias to be set
 * @value: the string value of the alias
 *
 * This function sets an alias to a string value.
 * It returns 0 if the alias was successfully
 * set, and 1 if an error occurred.
 *
 * Return: 0 on success, 1 on error
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * This function prints the name and value of an alias.
 * It returns 0 on success, and 1 on error.
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias built-in command
 * @info: structure containing information about
 * the command to be executed
 *
 * This function mimics the behavior of the alias
 * built-in command. It can be used to set,
 * unset, or print aliases.
 *
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
