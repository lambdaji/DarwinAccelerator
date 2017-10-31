# 
#
PROGRAM_NAME = expinfo
CC = gcc
CXX = g++
RM = rm -f

CXXFLAGS = --std=c++11 -g -O3 -msse3
CPPFLAGS = -I/usr/local/include/ -I/home/lambdaji/protobuf/include/ -I/home/lambdaji/boost_1_64_0/include/ -I/home/lambdaji/cityhash/include/ -I/home/lambdaji/glog/include/ -I/dockerdata/lambdaji/ml_packages/gflags/include/
LDFLAGS = -L/usr/local/lib -L/home/lambdaji/boost_1_64_0/lib -L/home/lambdaji/protobuf/lib -L/home/lambdaji/cityhash/lib -L/home/lambdaji/glog/lib -L/dockerdata/lambdaji/ml_packages/gflags/lib
LDLIBS = -lboost_system -lprotobuf -lcityhash -lglog -lgflags -lpthread

INSTALL_DIR = /usr/local/bin

SRCS = $(wildcard *.cpp) $(wildcard *.pb.cc)
OBJS = $(subst .pb.cc,.pb.o,$(subst .cpp,.o,$(SRCS)))
DEPS = $(subst .pb.cc,.pb.d,$(subst .cpp,.d,$(SRCS)))

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJS)
	    $(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

-include $(DEPS)

clean:
	    $(RM) $(OBJS) $(PROGRAM_NAME)

install:
	    cp  $(PROGRAM_NAME) $(INSTALL_DIR)

uninstall:
	    $(RM) $(INSTALL_DIR)/$(PROGRAM_NAME)

dist-clean: clean
	    $(RM) *~  $(DEPS)

