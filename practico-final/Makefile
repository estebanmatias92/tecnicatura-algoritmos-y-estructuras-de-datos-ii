SHELL := bash
PYTHON := python3
DB    ?= saca_muela.db

.PHONY: run test seed reset lint format

run:
	$(PYTHON) main.py $(DB)

test:
	PYTHONPATH=. $(PYTHON) -m pytest tests/ -v

seed:
	PYTHONPATH=. $(PYTHON) scripts/seed.py $(DB)

reset:
	rm -f $(DB)
	$(MAKE) seed

lint:
	ruff check .

format:
	black .
