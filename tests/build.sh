# /bim/bash

# gcc -Wall -Wextra -Werror -g  \
# 	-Ilibft -Iinclude \
# 	-Llibft -l:libft.a \
# 	-L. -l:libft_malloc_x86_64_Linux.so \
# 	test/test001.c

# gcc -g  test001.c -I../libft -L../libft -l:libft.a
gcc -g test_001.c -o test_001
gcc -g test_002.c -o test_002
gcc -g test0.c -o test0
gcc -g test1.c -o test1
gcc -g test2.c -o test2
gcc -g test3.c -o test3
gcc -g test4.c -L../ -lft_malloc -o test4
gcc -g test5.c -o test5
