/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:46:19 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/15 17:26:10 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Handles format specifiers and calls the appropriate function
 *  to print the value.
 * 
 * @param str The format specifier character (e.g., 's', 'd', 'p').
 * @param args The list of variadic arguments.
 * @return int The number of characters printed for the specific format.
 */
int	ft_check_format(char str, va_list args)
{
	int	i;

	i = 0;
	if (str == '%')
		i = i + ft_printf_putchar('%');
	else if (str == 'c')
		i = i + ft_printf_putchar(va_arg(args, int));
	else if (str == 's')
		i = i + ft_printf_putstr(va_arg(args, char *));
	else if (str == 'd' || str == 'i')
		i = i + ft_putnbr(va_arg(args, int));
	else if (str == 'p')
		i = i + ft_putptr(va_arg(args, void *));
	else if (str == 'u')
		i = i + ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (str == 'x')
		i = i + ft_putnbr_base(va_arg(args, unsigned long), "0123456789abcdef");
	else if (str == 'X')
		i = i + ft_putnbr_base(va_arg(args, unsigned long), "0123456789ABCDEF");
	return (i);
}

/**
 * @brief Custom implementation of printf that handles basic format
 *  specifiers.
 * 
 * @param str The format string containing text and format specifiers.
 * @param ... Variable arguments corresponding to the format specifiers.
 * @return int The number of characters printed.
 */
int	ft_printf(const char *str, ...)
{
	int		i;
	int		total;
	va_list	args;

	va_start(args, str);
	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			i++;
			total = total + ft_check_format(str[i], args);
		}
		else
			total = total + ft_printf_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (total);
}

// #include <stdio.h>
// #include "ft_printf.h"

// int	main(void)
// {
// 	int	ret_ft;
// 	int	ret_std;
// 	char	*str = "Hello, World!";
// 	char	empty_str[] = "";
// 	char	c = 'A';
// 	int		num = 42;
// 	int		neg = -42;
// 	int		zero = 0;
// 	unsigned int	un = 3000000000;
// 	unsigned int	max_unsigned = 4294967295;
// 	int		max_int = 2147483647;
// 	int		min_int = -2147483648;
// 	void	*ptr = (void *)0x7ffe2b8ef1dc;
// 	void	*null_ptr = NULL;
// 	unsigned int	vals[] = {0, 1, 42, 300, 4294967295U};
// 	int	i = 0;

// 	printf("==== STRING TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [%s]\n", str);
// 	ret_std = printf("printf   : [%s]\n", str);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== EMPTY STRING TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [%s]\n", empty_str);
// 	ret_std = printf("printf   : [%s]\n", empty_str);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== CHARACTER TEST ====\n");
// 	ret_ft = ft_printf("ft_printf: [%c]\n", c);
// 	ret_std = printf("printf   : [%c]\n", c);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== INTEGER TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [INT_MIN: %i]\n", min_int);
// 	ret_std = printf("printf   : [INT_MIN: %i]\n", min_int);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [INT_MAX: %d]\n", max_int);
// 	ret_std = printf("printf   : [INT_MAX: %d]\n", max_int);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [Zero: %d]\n", zero);
// 	ret_std = printf("printf   : [Zero: %d]\n", zero);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [Negative: %i]\n", neg);
// 	ret_std = printf("printf   : [Negative: %i]\n", neg);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== UNSIGNED TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [Unsigned: %u]\n", un);
// 	ret_std = printf("printf   : [Unsigned: %u]\n", un);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [UINT_MAX: %u]\n", max_unsigned);
// 	ret_std = printf("printf   : [UINT_MAX: %u]\n", max_unsigned);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== HEXADECIMAL TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [Hex lower: %x]\n", 255);
// 	ret_std = printf("printf   : [Hex lower: %x]\n", 255);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [Hex upper: %X]\n", 255);
// 	ret_std = printf("printf   : [Hex upper: %X]\n", 255);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== POINTER TESTS ====\n");
// 	ret_ft = ft_printf("ft_printf: [Pointer: %p]\n", ptr);
// 	ret_std = printf("printf   : [Pointer: %p]\n", ptr);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	ret_ft = ft_printf("ft_printf: [NULL pointer: %p]\n", null_ptr);
// 	ret_std = printf("printf   : [NULL pointer: %p]\n", null_ptr);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== NULL STRING TEST ====\n");
// 	ret_ft = ft_printf("ft_printf: [NULL string: %s]\n", NULL);
// 	ret_std = printf("printf   : [NULL string: %s]\n", NULL);
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== PERCENT SIGN TEST ====\n");
// 	ret_ft = ft_printf("ft_printf: [%%]\n");
// 	ret_std = printf("printf   : [%%]\n");
// 	printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 	printf("==== TEST WITH %%u ====\n");
// 	while (i < 5)
// 	{
// 		printf("Testing with value: %u\n", vals[i]);

// 		ret_ft = ft_printf("ft_printf: [%u]\n", vals[i]);
// 		ret_std = printf("printf   : [%u]\n", vals[i]);
// 		printf("Return ft_printf: %d | printf: %d\n\n", ret_ft, ret_std);

// 		i++;
// 	}

// 	return (0);
// }
