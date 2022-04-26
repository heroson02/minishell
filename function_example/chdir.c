#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *before_dir;
	char after_dir[BUFSIZ];

	before_dir = (char *)malloc(sizeof(char) * BUFSIZ);
	getcwd(before_dir, BUFSIZ);
	// before_dir = getcwd(NULL, BUFSIZ);

	printf("before dir: %s\n", before_dir);
	int ret = chdir("./mini");
	if (!ret)
		printf("\x1b[34msuccess!\n\x1b[0m");
	else
		printf("\x1b[31mfailed\n\x1b[0m");
	getcwd(after_dir, BUFSIZ);
	printf("after dir: %s\n", after_dir);
	free(before_dir);
	// system("leaks minishell");
	return (0);
}