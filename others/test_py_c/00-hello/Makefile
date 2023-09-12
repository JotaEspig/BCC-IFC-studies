ENV_DIR=env

all: | $(ENV_DIR)
	python3 setup.py install

ext:
	python3 setup.py build_ext --inplace

test: all
	python3 tests/testc.py

$(ENV_DIR):
	python3 -m venv $(ENV_DIR)
	. $(ENV_DIR)/bin/activate

.PHONY: clean
clean:
	@rm -rf *.out *.so build
	@rm -rf hellomod/*.out hellomod/*.so
