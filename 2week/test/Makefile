TARGET1=processtree
OBJECT1=processtree.o
CC=gcc
CXX=g++
LD_FLAGS= -lpthread
C_FLAGS=
# end of user configuration
all: $(TARGET1) 
$(TARGET1) : $(OBJECT1)
	$(CXX)  $^ -o $@ $(LD_FLAGS)
%.o : %.cpp
	$(CXX) $(C_FLAGS) -c $<
.PHONY: clean
clean : -rm -f $(OBJECT1)  $(TARGET1) 
