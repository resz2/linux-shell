default:
	make externals
	make shell
	make run
	make clear

shell:
	gcc shell.c -o shell.out

run:
	./shell.out

externals:
	gcc ls.c -o ls
	gcc cat.c -o cat
	gcc date.c -o date
	gcc mkdir.c -o mkdir
	gcc rm.c -o rm

clear:
	rm shell.out ls cat date mkdir rm help/history.txt