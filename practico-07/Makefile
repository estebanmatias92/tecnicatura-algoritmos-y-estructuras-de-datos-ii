CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
LDFLAGS  =
TARGET   = navigator
SRCDIR   = src
OBJDIR   = obj

SRCS = $(SRCDIR)/main.cpp              \
       $(SRCDIR)/Navigator.cpp          \
       $(SRCDIR)/Peaton.cpp             \
       $(SRCDIR)/Coche.cpp              \
       $(SRCDIR)/TransportePublico.cpp

OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean run

all: $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
