MAKEFLAGS += --no-print-directory

.PHONY: all clean build run format

build:
	mkdir -p build && cd build && cmake .. && make -j4

bf: format build

restart: build
	sudo systemctl restart traction-control.service

clean:
	rm -rf build

run: build
	@echo "\n\n\n\n"
	./bin/traction-control

format:
	clang-format -i src/*.c inc/*.h -style=file:.clang-format

sync:
	rsync -r src inc control@control:~/traction-control-sw/ --progress
