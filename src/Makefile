INCLUDES := -I/home/terahz/rpi/boost/include -I/home/terahz/rpi/cmake/include -I../I2C/src -I../PCA9685/src -I../MCP23008/src
LIBRARIES := -L/home/terahz/rpi/boost/lib -L/home/terahz/rpi/cmake/lib -L../I2C/src -L../MCP23008/src -L../PCA9685/src
LIBS := -lwthttp -lwt -lboost_signals -lboost_thread -lboost_program_options -lboost_date_time -lboost_random -lboost_regex -lboost_system -lboost_filesystem -lPCA9685 -lMCP23008 -lI2C
CXXFLAGS := -O3 -g -Wall -Werror $(INCLUDES) $(LIBRARIES) $(LIBS)
LDFLAGS := $(LIBS) 
DISTPATH := /mnt/aquarius
RM := rm -rf

#CXX := g++
CXX := arm-unknown-linux-gnueabi-g++
NAME := Aquarius

all: $(NAME) copy

$(NAME): $(NAME).o LEDChannel.o PowerOutlet.o
	$(CXX) $(CXXFLAGS) -Wl,-rpath,'$$ORIGIN/lib' $^ -o $@

copy:
	cp $(NAME) $(DISTPATH)
	
clean:
	$(RM)  *.o *.so* $(TEST)

