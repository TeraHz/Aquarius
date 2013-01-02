INCLUDES := -I/home/terahz/rpi/boost/include -I../../ -I/home/terahz/rpi/cmake/include -I../../../../I2C/src -I../../../../MCP23008/src
LIBRARIES := -L/home/terahz/rpi/boost/lib -L/home/terahz/rpi/cmake/lib -L../../../../I2C/src -L../../../../MCP23008/src
LIBS := -lwthttp -lwt -lboost_signals -lboost_thread -lboost_program_options -lboost_date_time -lboost_random -lboost_regex -lboost_system -lboost_filesystem -lMCP23008 -lI2C
LDFLAGS := $(LIBS) 
RM := rm -rf
CXXFLAGS := -rdynamic -O3 -fPIC -g -Wall -Werror $(INCLUDES) $(LIBRARIES) $(LIBS)
#CXX := g++
CXX := arm-unknown-linux-gnueabi-g++
MAJOR := 0
MINOR := 1
NAME := PowerOutletPlugin
VERSION := $(MAJOR).$(MINOR)
RM := rm -rf

all: $(NAME).so 

$(NAME).so: $(NAME).o PowerOutlet.o
	$(CXX) $(CXXFLAGS) -rdynamic -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@
	
clean:
	$(RM) *.o *.so* 
