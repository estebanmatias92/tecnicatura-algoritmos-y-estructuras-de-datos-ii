# Task runner para el Examen Parcial 02 (Productos de Goma)
#
# Targets:
#   all               -> build
#   build             -> configura y compila con CMake
#   run               -> ejecuta la app (necesita MariaDB arriba: docker compose up -d)
#   test              -> pruebas unitarias (sin Docker)
#   test-integration  -> pruebas de integración (requiere MariaDB arriba)
#   clean             -> borra el directorio build/
#
# DX: make orquesta, CMapake genera, GTest verifica.

.PHONY: all build run test test-integration clean

BUILD_DIR := build
COMPOSE := docker compose

all: build

build:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DIR) -j$$(nproc 2>/dev/null || echo 4)

run: build
	@if ! $(COMPOSE) ps --services --filter "status=running" 2>/dev/null | grep -q mariadb; then \
		echo "Error: MariaDB no está corriendo."; \
		echo "Levantá el contenedor con: docker compose up -d"; \
		exit 1; \
	fi
	$(BUILD_DIR)/parcial02

test: build
	cd $(BUILD_DIR) && ctest --output-on-failure

test-integration: build
	@if ! $(COMPOSE) ps --services --filter "status=running" 2>/dev/null | grep -q mariadb; then \
		echo "Error: MariaDB no está corriendo."; \
		echo "Levantá el contenedor con: docker compose up -d"; \
		exit 1; \
	fi
	cd $(BUILD_DIR) && ctest --output-on-failure -L integration

clean:
	rm -rf $(BUILD_DIR)
