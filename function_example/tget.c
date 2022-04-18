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

	if (!env)
		printf("$TERM is null!\n");
	else
		printf("$TERM is %s\n", env);

	int bflag = tgetflag("cm");
	
	if (!bflag)
		printf("Impossible\n");
	else
		printf("Possible\n");
	return (0);
}