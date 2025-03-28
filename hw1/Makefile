# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -I. -I_deps/catch2

# Имя статической библиотеки
LIB_NAME = libLongAr.a

# Исходные файлы
SRCS = LongAr.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: tests

# Правило для создания статической библиотеки
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Правило для компиляции исходных файлов в объектные
%.o: %.cpp LongNum.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_lib.o: 
	g++ -c "_deps/catch2/catch_amalgamated.cpp" -o test_lib.o 
test.o: dz_test/test.cpp
	g++ -c "dz_test/test.cpp" -o test.o

tests: LongAr.o test_lib.o test.o
	$(CXX) $(CXXFLAGS) LongAr.o test_lib.o test.o -o test_bin

# Очистка
clean:
	rm -f $(OBJS) $(LIB_NAME) test_bin test_lib.o test.o

# Флаг для предотвращения конфликтов с одноименными файлами
.PHONY: all clean
