OBJS = src/main.o src/assistant_object.o

# compile code and create executable file
assistant : $(OBJS)
	g++ -pthread -o bin/virtual_assistant $(OBJS) 

# remove extra files
clean :
	rm -rf src/*.o	bin/*
