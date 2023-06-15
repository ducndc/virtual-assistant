OBJS = 	main_assistant.o assistant_utils.o 

# compile code and create executable file
assistant : $(OBJS)
	g++ -pthread -o vitual_assistant $(OBJS) 

# remove extra files
clean :
	rm -rf *.o	
