CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include
LDFLAGS  =
TARGET   = presupuesto_hotelero
SRCDIR   = src
OBJDIR   = obj

SRCS = $(SRCDIR)/main.cpp              \
       $(SRCDIR)/Hotel.cpp             \
       $(SRCDIR)/Hostel.cpp            \
       $(SRCDIR)/Apartamento.cpp       \
       $(SRCDIR)/AlojamientoDecorator.cpp \
       $(SRCDIR)/Piscina.cpp           \
       $(SRCDIR)/Desayuno.cpp          \
       $(SRCDIR)/Gimnasio.cpp          \
       $(SRCDIR)/Wifi.cpp

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
