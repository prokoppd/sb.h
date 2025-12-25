TARGET = sb_test

CFLAGS = -std=c23 -O3 -Wall -Wextra -ggdb -fdiagnostics-color=always -fprofile-arcs -ftest-coverage 
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
	rm -rf $(BUILD_DIR) *.gcda *.gcno *.gcov coverage.info coverage_report

test: all
	$(BUILD_DIR)/$(TARGET) -v | ./greenest

valgrind: all
	valgrind --leak-check=full --track-origins=yes -s $(BUILD_DIR)/$(TARGET) -v | ./greenest

coverage_report: all
	$(BUILD_DIR)/$(TARGET) -v
	@mkdir -p coverage_report
	gcovr -r . --html --html-details -o coverage_report/coverage.html
