CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -lSDL2 -lSDL2_ttf
OBJDIR = build
SRCDIR = source

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.cpp))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

sinking-ships: $(OBJECTS)
	$(CXX) $(OBJECTS) -o sinking-ships $(LDFLAGS)

clean:
	rm -rf $(OBJDIR) sinking-ships
