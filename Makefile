CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -lSDL2 -lSDL2_ttf
OBJDIR = build
SRCDIR = source

OS ?=
ifeq ($(OS), win32)
    SOURCE := $(SRCDIR)/socket_windows.cpp
else
    SOURCE := $(SRCDIR)/socket_unix.cpp
endif

SOURCE += $(SRCDIR)/main.cpp               \
          $(SRCDIR)/menu.cpp               \
          $(SRCDIR)/setup.cpp              \
          $(SRCDIR)/game.cpp               \
          $(SRCDIR)/rendering.cpp          \
          $(SRCDIR)/board.cpp              \
          $(SRCDIR)/ship.cpp               \
          $(SRCDIR)/game_state.cpp         \
          $(SRCDIR)/socket_factory.cpp

OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCE))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

sinking-ships: $(OBJECTS)
	$(CXX) $(OBJECTS) -o sinking-ships $(LDFLAGS)

clean:
	rm -rf $(OBJDIR) sinking-ships
