#The following four macros should be defined.
TARGET1=thread-ex
OBJECT1=thread-ex.o
#TARGET2=time_client
#OBJECT2=time_client.o
CC=gcc
CXX=g++
LD_FLAGS= -lpthread
C_FLAGS=
# end of user configuration
all: $(TARGET1) $(TARGET2)
$(TARGET1) : $(OBJECT1)
	$(CXX)  $^ -o $@ $(LD_FLAGS)
$(TARGET2) : $(OBJECT2)
	$(CXX) $^ -o $@ $(LD_FLAGS)
%.o : %.c
	$(CC) $(C_FLAGS) -c $<
%.o : %.cpp
	$(CXX) $(C_FLAGS) -c $<
.PHONY: clean
clean : -rm -f $(OBJECT1)  $(OBJECT2) $(TARGET1) $(TARGET2)

