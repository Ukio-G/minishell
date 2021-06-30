#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char * line = readline("Readline: ");

	rl_redisplay();
	printf("|%s|", rl_line_buffer);
	return 0;
}
