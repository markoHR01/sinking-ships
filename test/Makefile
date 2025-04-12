CXX = g++
CXXFLAGS = -Wall -I../include -I../source
LDFLAGS = -lSDL2 -lSDL2_ttf
OBJDIR = build

OBJECTS = build/setup.o build/rendering.o build/test_game.o

test-game : $(OBJECTS)
	$(CXX) $(OBJECTS) -o test-game $(LDFLAGS)

$(OBJDIR)/setup.o : ../source/setup.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/rendering.o : ../source/rendering.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/test_game.o : test_game.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) test-game
