TARGET = sb_test

CFLAGS = -O3 -Wall -Wextra -ggdb -fdiagnostics-color=always -fprofile-arcs -ftest-coverage 
# LDFLAGS = 
BUILD_DIR = build
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)


all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean test
clean:
	rm -rf $(BUILD_DIR) *.gcda *.gcno *.gcov coverage.info coverage

test: all
	$(BUILD_DIR)/$(TARGET)

valgrind: all
	valgrind --leak-check=full --track-origins=yes -s $(BUILD_DIR)/$(TARGET) 

coverage: all
	$(BUILD_DIR)/$(TARGET) -v
	@mkdir -p coverage
	gcovr -r . 
