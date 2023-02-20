#include <stdio.h>
#include "../include/minishell.h"

//THIS IS UNNESSESARY!

// int ft_passby(char *str, int *i, char c)
// {
//     int start;

//     start = *i;
//     while(str[*i] == c && str)
//         *i += 1;
//     if (start == *i)
//         return (0);
//     return (1);
// }

void switch_flag(int *flag)
{
    if (*flag == 0)
        *flag = 1;
    else if (*flag == 1)
        *flag = 0;
}


int is_char(char place, char c)
{
    if (place == c)
        return (1);
    return (0);
}

// int ft_isredirwithoutspace(char *str, int i)
// {
//     if ((str[i] == '<' && ft_isalpha(str[i + 1])) 
//         || (str[i] == '>' && ft_isalpha(str[i + 1])))
//         return (1);
//     if ((str[i] == '<' && str[i + 1] == '<' && ft_isalpha(str[i + 2])) 
//         || (str[i] == '>' && str[i + 1] == '>' && ft_isalpha(str[i + 2])))
//         return (1);
//     return (0);
// }

int jump_delimiters(char *str, int *i)
{
    int start;

    start = *i;
    while(ft_iswhitespace(str[*i])) //|| ft_isredirwithoutspace(str, *i))
        *i += 1;
    if (start == *i)
        return (0);
    return (1);   
}

int cut_ws_redir(char *str, int *i)
{
    int start;

    start = *i;
    while((ft_iswhitespace(str[*i])))
        *i += 1;
    // while((ft_isredirwithoutspace(str, *i)))
    //     *i += 1;
    if (start == *i)
        return (0);
    return (1);   
}


int countstrs(char *str)
{
    // if >, <, ' ', count, exept after echo or in between " " or ' '
    int i;
    int count;
    int flag;

    i = 0;
    count = 0;
    flag = 0;
    //i = jumpoverredir(str, i);
    while (str[i])
    {
        //printf("when count-> l: %c, c: %d, i: %d\n", str[i], count, i);
        if (is_char(str[i], '\''))
            switch_flag(&flag);
        if (flag == 0)
        {
            if (jump_delimiters(str, &i))
                count++;
            else
                i++;
        }
        else
            i++;
    }
    return (count);
}

char **allocate(char **split, int strnumber)
{
    int i;

    i = 0;
    split = malloc(sizeof(char *) * (strnumber + 1));
    while (i < strnumber + 1)
    {
        split[i] = NULL;
        i++;
    }
    return (split);
}

char **makestring(char **split, char *str, int start, int i)
{
    int count;
    int range;

    count = 0;
    range = i - start;
    while (split[count])
        count++;
    split[count] = malloc(range + 1);
    split[count][range] = '\0';
    ft_strlcpy(split[count], str + start, range);
    printf("split; %s\n", split[count]);
    return (split);
}

char **createstrings(char **split, char *str)
{
    int i;
    int flag;
    int start;

    i = 0;
    flag = 0;
    start = i;
    //i = jumpoverredir(str, i);
    //printf("bef: %s, i: %d\n", str + i, i);
    while (str[i])
    {
        if (is_char(str[i], '\''))
            switch_flag(&flag);
        if (flag == 0)
        {
            //printf("hi\n");
            if (cut_ws_redir(str, &i))
            {
                split = makestring(split, str, start, i);
                start = i;
            }
            else
                i++;
        }
        else
            i++;
    }
    return (split);
}

char **splitme (char *str)
{
    char **split;
    int strnumber;

    split = NULL;
    str = ft_strtrim(str, "\n\t\v\f\r ");
    strnumber = countstrs(str);
    // printf("%d\n", strnumber);
    // printf("%s\n", str);
    split = allocate(split, strnumber);
    while (strnumber > 0)
    {
        createstrings(split, str);
        strnumber--;
    }
    //printf("%s\n", split[0]);
        //printf("%s\n", split[1]);

    // ft_free();
    return (split);
}

int main ()
{
    char **split;
    split = splitme("  <<in cat >out>out > out         ");
    return 0;
}
// int jumpoverredir(char *str, int i)
// {
//     if (str[i] == '>')
//     {
//         while (str[i] == '>')
//             i++;
//     }
//     else if (str[i] == '<')
//     {
//         while (str[i] == '<')
//             i++; 
//     }
//     return (i);
// }
// int cutredir(char *str, int *i)
// {
//     int start;

//     start = *i;
//     while((ft_iswhitespace(str[*i]) || ft_isredirwithoutspace(str, *i)))
//         *i += 1;
//     if (start == *i)
//         return (0);
//     return (1);    
}