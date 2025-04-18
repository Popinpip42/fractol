#include "fractol.h"

static int	is_overflowing(long result, int digit, int sign)
{
	if (sign == 1 && result > (INT_MAX - digit) / 10)
		return (1);
	if (sign == -1 && result > ((-1L * INT_MIN) - digit) / 10)
		return (1);
	return (0);
}

int	is_valid_int(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		if (is_overflowing(result, (*str - '0'), sign))
			return (0);
		result = result * 10 + (*str - '0');
		str++;
	}
	while (ft_isspace(*str))
		str++;
	return (*str == '\0');
}

int	is_valid_double(const char *str)
{
	int	has_dot = 0;
	int	has_digit = 0;

	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			has_digit = 1;
		else if (*str == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else
			break;
		str++;
	}
	while (ft_isspace(*str))
		str++;
	return (*str == '\0' && has_digit);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

double	ft_atof(const char *str)
{
	double	int_part;
	double	frac_part;
	double	frac_div;
	int		sign;

	sign = 1;
	int_part = 0.0;
	frac_part = 0.0;
	frac_div = 1.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		frac_part = frac_part * 10 + (*str++ - '0');
		frac_div *= 10;
	}
	return (sign * (int_part + frac_part / frac_div));
}
