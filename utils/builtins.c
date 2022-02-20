#include "../minishell.h"

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ unset with no options
◦ export with no options
◦ env with no options or arguments - getenv
◦ exit with no options - exit
*/

int check_quot_sequence(char *str, char c)
{
    int i;

    i = 0;
    if (str[i] == c)
    {
        i = ft_strlen(str)-1;
        if (str[i] == c)
            return (1);
    }
    return (0);
}

char    *cut_quot_sequence(char **str, char c)
{
    int     i;
    char    *new_str;

    i = 1;
    new_str = (char *)malloc(ft_strlen(str[1] - 2) * sizeof(char));
    if (str[i])
    {
        if (check_quot(str[i], c))
            new_str = ft_substr(str[i],1, ft_strlen(str[1] - 1));
        return (new_str);
    }
    else
        return (NULL);
}

int count_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == ' ')
        {
            printf("there is a space\n");
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_echo(char **str)
{
    int         i;
    bool        flag;
    bool        space;
    bool        quots;
    char        *outputstr;

    i = 1;
    flag = false;
    space = false;
    quots = false;
    if (!str[i])
    {
        printf("str is empty\n");
        return (0);
    }
    while (str[i])
    {
        if (!ft_strncmp(str[i], "-n", 2))
        {
            if (str[i + 1])
            {
                flag = true;
                i++;
            }
            else
            {
                printf(" ");
                break ;
            }
        }
        if (check_quot(str[i], '"'))
        {
            outputstr = ft_substr(str[i], 1, ft_strlen(str[i])-2);
            outputstr[ft_strlen(str[i])-1] = 0;
            printf("%s\n", outputstr);
        }
        printf("%s\n", str[i]);
        i++;
    }
    if (!flag)
        printf("\n");
    return (1);
}

int doublestr_len(char **cmd_arg)
{
    int i;
    int j;
    int s_t;

    i = 0;
    j = 0;
    s_t = 0;
    while (cmd_arg[i])
    {
        while (cmd_arg[i][j])
        {
            j++;
        }
        s_t += j;
        i++;
    }
    return (s_t);
}

int builtin_picker(char *cmd_arg)
{
    if (!ft_strncmp(cmd_arg[0], "echo", doublestr_len(cmd_arg)))
    {
        ft_echo(cmd_arg);
        return (1);
    }
    return (0);
}
