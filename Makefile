.PHONY: lib
lib:
	cd lib && make && cd ..

.PHONY: test
test: lib
	cd test && make run

.PHONY: clean
clean:
	cd test && make clean && cd ..
	cd lib && make clean