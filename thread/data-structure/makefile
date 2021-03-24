TARGET = test
CC =g++ -L../src -g -O3 -Wall -std=c++11
INCLUDE =$(shell find ./ -name "*.hpp")
SOURCE =$(shell find ./ -name "*.cpp")
OBJS =$(SOURCE:%.cpp=%.o)
LIBS =-pthread -lboost_thread -latomic
CFLAGS =-I./

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.cpp $(INCLUDE)
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)
	
all:$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)
