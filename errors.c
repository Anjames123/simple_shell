#include "shell.h"

/**
 * _eputs - Print a string to standard output
 *
 * @str: The string to be printed
 *
 * Return: None
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Write a character to the standard error output stream
 *
 * @c: The character to be written
 *
 * Return: On success, 1 is returned.
 *         On error, -1 is returned and the `errno`
 *         variable is set appropriately.
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Write a character to the specified file descriptor
 *
 * @c: The character to be written
 * @fd: The file descriptor to write to
 *
 * Return: On success, 1 is returned.
 *         On error, -1 is returned and the `errno`
 *         variable is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Write a string to the specified file descriptor
 *
 * @str: The string to be written
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written to the file descriptor.
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
