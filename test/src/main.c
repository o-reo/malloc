#include "ft_printf.h"

int main()
{
    void *ptr;

    ptr = malloc(2);
    ft_printf("memory is %p\n", ptr);
    return (0);
}
