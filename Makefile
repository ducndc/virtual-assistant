OBJS = 	src/main_assistant.o src/assistant_utils.o src/virtual_functions.o

# compile code and create executable file
assistant : $(OBJS)
	g++ -pthread -o bin/virtual_assistant $(OBJS) 

# remove extra files
clean :
	rm -rf src/*.o	bin/*
