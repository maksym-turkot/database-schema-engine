all:
	cd build; make all

run:
	./build/src/db-project1_run

test:
	./build/tst/db-project1_tst

debug:
	lldb ./build/src/db-project1_run

debug-tst:
	lldb ./build/tst/db-project1_tst

clean:
	cd build; make clean
	