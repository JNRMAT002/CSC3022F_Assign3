C = g++
CFLAGS = -std=c++11 -static-libgcc -static-libstdc++ #INCLUDE THESE LAST TWO FLAGS ANYTIME YOU USE VECTORS
SRCS = findcomp.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = findcomp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(C) $(CFLAGS) $(OBJS) -o $(TARGET)

findcomp.o: findcomp.cpp
	$(C) $(CFLAGS) -c findcomp.cpp

# FrameSequence.o: FrameSequence.cpp
# 	$(C) $(CFLAGS) -c FrameSequence.cpp

# run:
# 	.\$(TARGET) larger_image.pgm -t 0 0 100 100 -s 100 100 -w none SIMPLE

clean:
	del /q $(OBJS) $(TARGET).exe
	# del *.pgm
