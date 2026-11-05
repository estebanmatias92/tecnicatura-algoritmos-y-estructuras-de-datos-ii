# Drone IBag151 -- task runner over CMake.
# Every target is a thin wrapper: CMake remains the source of truth.

SHELL := /bin/bash
.DEFAULT_GOAL := help

BUILD_DIR    ?= build
BUILD_TYPE   ?= Debug
JOBS         ?= $(shell nproc 2>/dev/null || echo 2)
CMAKE        ?= cmake
CTEST        ?= ctest
CLANG_FORMAT ?= clang-format
CLANG_TIDY   ?= clang-tidy
PLANTUML     ?= plantuml
TARGET       ?= drone_ibag151
DEMO         ?= scripts/demo.txt
DIST_DIR     ?= dist
DIST_NAME    ?= drone-ibag151-src

SOURCES     := $(shell find include src tests -type f \( -name '*.cpp' -o -name '*.hpp' \) 2>/dev/null)
DIAGRAMS    := $(wildcard docs/diagrams/*.puml)
DIST_INPUTS := $(wildcard CMakeLists.txt Makefile README.md .gitignore .clang-format cmake include src tests docs scripts)

.PHONY: help configure build rebuild test run run-interactive check format format-check lint diagram clean dist

help: ## Show available targets
	@echo "Drone IBag151 -- available targets:"
	@awk 'BEGIN {FS = ":.*## "} /^[a-zA-Z0-9_-]+:.*## / {printf "  \033[36m%-18s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

configure: ## Configure the CMake build tree
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure ## Compile the library, application and tests
	$(CMAKE) --build $(BUILD_DIR) -j$(JOBS)

rebuild: ## Clean and build from scratch
	$(MAKE) clean
	$(MAKE) build

test: build ## Run the unit tests with CTest
	$(CTEST) --test-dir $(BUILD_DIR) --output-on-failure

run: build ## Run the console demo script (scripts/demo.txt)
	@if [ -f "$(DEMO)" ]; then ./$(BUILD_DIR)/$(TARGET) < "$(DEMO)"; else ./$(BUILD_DIR)/$(TARGET); fi

run-interactive: build ## Run the console interactively
	./$(BUILD_DIR)/$(TARGET)

check: format-check test ## Format check, build and tests

format: ## Apply clang-format to all C++ sources
	$(CLANG_FORMAT) -i $(SOURCES)

format-check: ## Verify formatting without modifying files
	$(CLANG_FORMAT) --dry-run --Werror $(SOURCES)

lint: build ## Run clang-tidy over the implementation sources
	$(CLANG_TIDY) -p $(BUILD_DIR) $(filter %.cpp,$(SOURCES))

diagram: ## Render PlantUML diagrams to SVG
	@if [ -n "$(DIAGRAMS)" ]; then $(PLANTUML) -tsvg $(DIAGRAMS); else echo "No .puml diagrams found."; fi

clean: ## Remove the build tree
	rm -rf $(BUILD_DIR)

dist: ## Package the sources for submission
	@mkdir -p $(DIST_DIR)
	tar -czf $(DIST_DIR)/$(DIST_NAME).tar.gz $(DIST_INPUTS)
	@echo "Created $(DIST_DIR)/$(DIST_NAME).tar.gz"
