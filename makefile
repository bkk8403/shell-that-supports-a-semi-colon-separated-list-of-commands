all:
	gcc main.c display.c read_command.c interpret_command.c built_in_command.c ls_command.c fgbgprocess.c exit_children.c repeat.c redirection.c pipe.c jobs.c sig.c fg.c bg.c signal_handling.c -g -o shell
