#The following four macros should be defined.
TARGET1=time_serv
OBJECT1=time_serv.o
TARGET2=time_client
OBJECT2=time_client.o
CC=gcc
CXX=g++
LD_FLAGS=
C_FLAGS=
# end of userconfiguration
all: $(TARGET1) $(TARGET2)
$(TARGET1) : $(OBJECT1)
	$(CXX) $(LD_FLAGS) $^ -o $@
$(TARGET2) : $(OBJECT2)
	$(CXX) $(LD_FLAGS) $^ -o $@
%.o : %.c
	$(CC) $(C_FLAGS) -c $<
%.o : %.cpp
	$(CXX) $(C_FLAGS) -c $<
.PHONY: clean
clean : -rm -f $(OBJECT1)  $(OBJECT2) $(TARGET1) $(TARGET2)
