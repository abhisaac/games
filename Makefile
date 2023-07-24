LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
build/a.out: main.cpp
	g++ -g $^ $(LDFLAGS)

