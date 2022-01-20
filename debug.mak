project_debug : llist.o user_interface.o
	g++ -o project_debug user_interface.o llist.o
llist.o : llist.cpp
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c llist.cpp
user_interface.o : user_interface.cpp
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c user_interface.cpp
