CXX := g++
CXXFLAGS := -std=c++20 -O2 -Wall -Wextra -pthread
CPPFLAGS := -Iinclude -Iinclude/twobot -Iinclude/twobot/include
LDFLAGS :=
LDLIBS := -ldpp -lcurl -lssl -lcrypto

TARGET := twobot

SRCS := \
	src/Application.cpp \
	include/twobot/twobot.cc \
	include/twobot/apiset.cc

OBJS := $(SRCS:.cpp=.o)
OBJS := $(OBJS:.cc=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
