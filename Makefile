OBJS = StacksExpressions.cpp

#Change compiler here if required
CC = g++

OBJ_NAME = StacksExpressions

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)