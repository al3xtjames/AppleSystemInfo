CC := clang
CFLAGS := -Os -std=c99

INCLUDE_DIR := include
OBJECT_DIR := obj
OUTPUT_DIR := out
SOURCE_DIR := src
TEST_DIR := test

FRAMEWORK_DIRS := /System/Library/PrivateFrameworks
FRAMEWORKS := -framework CoreFoundation -framework IOKit
FRAMEWORKS_ASI := -framework AppleSystemInfo $(FRAMEWORKS)


TEST_FEAT_DEPS := $(OBJECT_DIR)/asi.o
TESTER_DEPS := $(OBJECT_DIR)/asi_test.o $(OBJECT_DIR)/test_platformfeature.o

all: clean dump_features test_features

$(OBJECT_DIR)/asi.o: $(SOURCE_DIR)/AppleSystemInfo.c
	$(CC) -o $@ -c $< $(CFLAGS) -D TEST_FEATURES -I $(INCLUDE_DIR)

$(OBJECT_DIR)/asi_test.o: $(SOURCE_DIR)/AppleSystemInfo.c
	$(CC) -o $@ -c $< $(CFLAGS) -D TEST -I $(INCLUDE_DIR)

$(OBJECT_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE_DIR)

dump_features: $(SOURCE_DIR)/util/dump_features.c
	$(CC) -o $(OUTPUT_DIR)/$@ $< $(CFLAGS) -F $(FRAMEWORK_DIRS) $(FRAMEWORKS_ASI) -I $(INCLUDE_DIR)

test_features: $(TEST_FEAT_DEPS) $(SOURCE_DIR)/util/dump_features.c
	$(CC) -o $(OUTPUT_DIR)/$@ $^ $(CFLAGS) -D TEST_FEATURES $(FRAMEWORKS) -I $(INCLUDE_DIR)

test_impl: $(TESTER_DEPS) $(TEST_DIR)/test.c
	$(CC) -o $(OUTPUT_DIR)/$@ $^ $(CFLAGS) -F $(FRAMEWORK_DIRS) $(FRAMEWORKS_ASI) -I $(INCLUDE_DIR)
	@$(OUTPUT_DIR)/test_impl

.PHONY: clean
clean:
	rm -rf out/* obj/*
