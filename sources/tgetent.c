#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <curses.h>
#include <term.h>

int main(void)
{
	char *env = getenv("TERM");
	char str[2048];

	if (!env)
	{
		printf("Before tgetent(): $TERM is null!\n");
		return (0);
	}
	else
		printf("Before tgetent(): $TERM is %s\n", env);
	
	int ret = tgetent(str, env);
	
	if (!ret)
		printf("After tgetent(NULL, %s): $TERM is empty string.\n", env);
	else if (ret < 0)
		printf("After tgetent(NULL, %s): Failed\n", env);
	else
		printf("After tgetent(NULL, %s): $TERM is %s\n", env, getenv("TERM"));
	printf("This is bp: %s\tenv : %s\n", str, env);
	return (0);
}