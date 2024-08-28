CC = gcc
CFLAGS = -Wall -I./src/include
LDFLAGS = -lglfw -lGLEW -lsndfile -lGL -lm -ldl -lpthread

SRCS = main.c src/gui.c src/bpm_analyzer.c src/audio_processing.c
OBJS = $(SRCS:.c=.o)
TARGET = bpm_analyzer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
