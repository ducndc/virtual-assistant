OBJS = 	src/main_assistant.o src/assistant_utils.o 

# compile code and create executable file
assistant : $(OBJS)
	g++ -pthread -o bin/vitual_assistant $(OBJS) 

# remove extra files
clean :
	rm -rf src/*.o	
