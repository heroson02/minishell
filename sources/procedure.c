#include "./minishell.h"

void pipeline();
void command();
void cmd_element();
void redirection();
void path();
void filename();


void pipeline()
{
	t_tok next;
	command();
	if (next.type == PIPE)
	{
		pipeline();
	}
}

void command()
{
	t_tok next;

	cmd_element();
	if (next.type == TOKEN)
		command();
	else if (next.type == REDIR)
		command();
}

void cmd_element()
{
	t_tok next;

	if (next.type == TOKEN)
		path();
	else if (next.type == REDIR)
		redirection();
}

void redirection()
{
	t_tok next;

	if (next.type == TOKEN)
		filename();
}

void path()
{
	t_tok next;

	if (next.type == END)
		accept();
	else
		error();
}

void filename()
{
	t_tok next;

	if (next.type == END)
		accept();
	else
		error();
}