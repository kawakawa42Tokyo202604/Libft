#include "libft.h"

int main(void)
{
    ft_putendl_fd("Hello, 42!", STDOUT_FILENO);
    return (ft_strlen("Hello, 42!") != 10);
}
