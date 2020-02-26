all:
	gcc main.c -o regx -Wall -Wextra -pedantic -g -O2 -Werror=format-security -Wl,-z,defs -Wl,-z,now -Wl,-z,relro
install:
	sudo rm -v /usr/bin/regx
	sudo ln -sv /home/sebastian/dev/regx/regx /usr/bin/regx
