#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

/*
 * rl_catch_signals: readline실행 중에 signal을 표시할지 안할지 설정하는 변수 (default = 1)
 * echoctl 보기
 */

void handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line(); //readline 실행 중 다음 줄로 이동되었다고 설정해주는 함수
		rl_replace_line("", 0); // readline 실행 중 들어온 입력을 첫번째 인자로 다시 설정해주는 함수
		rl_redisplay(); // readline 실행 중 다시 readline을 실행할 때 사용하는 함수
	}
}

int main(void)
{
	char *line;
	struct termios t;

	signal(SIGINT, handler);
	tcgetattr(0, &t);
	t.c_lflag &= ~(ICANON | ECHOCTL); //https://80000coding.oopy.io/13bd7bb7-3a7f-4b51-b84a-905c47368277
	tcsetattr(0, TCSANOW, &t);

	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			printf("output> %s\n", line);
			add_history(line);
			free(line);
			line = NULL;
		}
		else
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}