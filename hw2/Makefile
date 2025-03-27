# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -Wextra -O2 -std=c++17 

# Имя статической библиотеки
LIB_NAME = libExp.a

# Исходные файлы
SRCS = Test.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Правило по умолчанию
all: tests

# Правило для создания статической библиотеки
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Правило для компиляции исходных файлов в объектные
%.o: %.cpp Expression.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


tests: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o test_bin

# Очистка
clean:
	rm -f $(OBJS) $(LIB_NAME) test_bin

# Флаг для предотвращения конфликтов с одноименными файлами
.PHONY: all clean