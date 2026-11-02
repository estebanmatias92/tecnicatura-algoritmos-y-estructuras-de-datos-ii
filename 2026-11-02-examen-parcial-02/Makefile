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
# DX: make orquesta, CMake genera, GTest verifica.

.PHONY: all build run test test-integration coverage clean

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

# Cobertura de líneas sobre src/ con gcov + gcovr. Recompila con
# -fprofile-arcs -ftest-coverage, ejecuta las pruebas unitarias y reporta.
# Se excluyen: main.cpp (no está vinculado a los tests), los adaptadores
# MariaDB (se cubren con make test-integration, que necesita Docker) y el
# bucle del menú Console::run (marcado con GCOVR_EXCL en src/console.cpp).
# Umbral exigido por RNF-011: >= 80 %.
coverage:
	# Reconfigura y compila con instrumentación de cobertura (gcov)
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug \
	    -DCMAKE_CXX_FLAGS="-Wall -Wextra -fprofile-arcs -ftest-coverage" \
	    -DCMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage"
	cmake --build $(BUILD_DIR) -j$$(nproc 2>/dev/null || echo 4) --target parcial02_tests
	# Ejecuta las pruebas unitarias para generar los ficheros .gcda
	cd $(BUILD_DIR) && ctest --output-on-failure
	# Reporte de cobertura sobre src/ (gcovr solo disponible vía nix-shell)
	nix-shell -p gcovr --run 'gcovr --root . --filter ".*src/.*" --exclude ".*main.cpp" --exclude ".*maria_db_.*" --print-summary $(BUILD_DIR)'

clean:
	rm -rf $(BUILD_DIR)
