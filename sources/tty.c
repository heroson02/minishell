#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int fd;

	//iTerm에서 tty 명령어를 통해 현재 표준 입력에 연결된 터미널의 이름을 표준 출력으로 보여줌.
	//쓰여진 이름은 ttyname()에 의해 반환된 문자열임.
	//표준 입력이 터미널이 아닌 경우 tty는 'not a tty' 메시지를 출력함.
	fd = open("/dev/ttys001", O_RDWR);
	if (fd == -1)
		printf("\nThis is error message: %s\n", strerror(errno));
	else
		printf("\n/dev/ttys001 is a terminal device\n");

	printf("\x1b[34mttyname()의 결과: %s\n\x1b[0m", ttyname(fd));

	printf("\x1b[31mttyslot()이 반환한 fd를 ttyname()에 전달한 결과: %s\n\x1b[0m", ttyname(ttyslot()));

	close(fd);
	return (0);
}