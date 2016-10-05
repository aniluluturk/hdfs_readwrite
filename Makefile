JAVA_HOME=/Library/Java/JavaVirtualMachines/jdk1.8.0_101.jdk/Contents/Home/
HADOOP_SRC_HOME=/Users/i333875/Downloads/hadoop-2.7.1-src
HADOOP_HOME=/usr/lib/hadoop/
CXXFLAGS=-O2 -g -Wall -I$(HADOOP_SRC_HOME)/hadoop-dist/target/hadoop-2.7.1/include/ -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin
LDFLAGS=-L$(HADOOP_SRC_HOME)/libs -lhdfs -L$(JAVA_HOME)/jre/lib/server -L$(JAVA_HOME)/jre/lib -ljvm

all: test_write test_read
test_write:
	g++  $(CXXFLAGS) $(LDFLAGS)  test_write.cpp -o test_write
test_read:
	g++  $(CXXFLAGS) $(LDFLAGS)  test_read.cpp -o test_read