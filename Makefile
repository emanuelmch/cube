
CXX := g++

# Code dependencies are not necessary for these these targets
NODEPS := clean

SRC_DIR := ./src
BUILD_DIR := ./build
DBG_DIR := $(BUILD_DIR)/debug
DBG_DEP_DIR := $(DBG_DIR)/deps

FLAGS_DEBUG := -march=k8 -mtune=k8 -O0 -g
LIBS := -lallegro{,_dialog}
#LIBS := -lallegro-5.0.7-monolith-md-debug

SRCS := $(shell find $(SRC_DIR) -type f -name \*.cpp)
DBG_OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(DBG_DIR)/%.o, $(SRCS))
DBG_DEPS := $(patsubst $(SRC_DIR)/%.cpp, $(DBG_DEP_DIR)/%.d, $(SRCS))

WARNINGS := -Wall -Wextra -pedantic -std=c++0x

all: debug

gdb: debug
	gdb ./debug

valgrind: debug
	valgrind --log-file=val.log ./debug
run: debug
	./debug

debug: $(DBG_OBJS)
	$(CXX) -o $@ $^ $(LIBS)

$(DBG_DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -E -M -MM -MF $@ $<
# Gambiarras...
	@mv $@ $@.tmp
	@echo -n "$(DBG_DIR)/" > $@
	@cat $@.tmp >> $@
	@rm $@.tmp

$(DBG_DIR)/%.o: $(DBG_DEP_DIR)/%.d

$(DBG_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(WARNINGS) $(INCLUDES) $(FLAGS_DEBUG) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR) release{,.exe} debug{,.exe}

.PHONY: all clean run

#ifneq "$(MAKECMDGOALS)" "clean"
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
-include $(DBG_DEPS)
endif
