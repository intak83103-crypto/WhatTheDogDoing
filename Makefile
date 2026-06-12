CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = main
SRCS = main.cpp \
       src/IO.cpp \
       src/Item.cpp \
       src/Product.cpp \
       src/Shop.cpp \
       src/Creature.cpp \
       src/DogDoing.cpp \
       src/User.cpp \
       src/Items.cpp \
       src/Products.cpp \
       src/Editor.cpp

all:
	@clear 2>/dev/null || true
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET) main_split_test
