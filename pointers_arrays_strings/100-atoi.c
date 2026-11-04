#include "main.h"
#include <limits.h>

/**
 * _atoi - Converts a string to an integer
 * @s: String to convert
 *
 * Return: Converted integer, or 0 if no digits are found
 */
int _atoi(char *s)
{
	int i = 0;
	int nombre = 0;
	int signe = 1;
	int trouve = 0;
	int chiffre;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			chiffre = s[i] - '0';

			if (nombre < INT_MIN / 10 ||
			    (nombre == INT_MIN / 10 &&
			     chiffre > -(INT_MIN % 10)))
				return (0);

			nombre = nombre * 10 - chiffre;
			trouve = 1;
		}
		else if (trouve == 1)
		{
			break;
		}
		else if (s[i] == '-')
		{
			signe = signe * -1;
		}
		i++;
	}

	if (signe == 1)
	{
		if (nombre < -INT_MAX)
			return (0);
		return (-nombre);
	}

	return (nombre);
}
