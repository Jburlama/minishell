# libft whit ft_printf and get next line plus aditional funtions

| function name  |  prototype                  | description  |
| :--------  |-----------------------------------|--------------|
| ft_strcut| char *ft_strcut(char *str, char c)| Take a string and return a malloc copy of the string until the first occurrence of 'c', c not included. returns a copy of the string if c was not found|
|ft_strlcut| char *ft_strlcut(char *str, char c)| Take a string and return a malloc copy of the string until the last occurrence of 'c', c not included. returns a copy of the string if c was not found|
|ft_chrcount| int ft_chrcount(char *str, char c)| returns the amount of times c is found in str|
| ft_atod | double ft_atod(char *str)| convert ascii string to double |
|ft_rng |int ft_rng(void) | return a possitive random integers, returns -1 if a syscall fails|
