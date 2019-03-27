all: mydash-project dox


mydash-project:
	cd mydash-src; make
	cd other-progs; make


run: all
	./mydash


dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config > doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"


konq-dox: dox
	konqueror ./docs/html/index.html



valgrind: all
	valgrind --leak-check=yes ./mydash


clean:
	/bin/rm -f *.o *.d mydash a.out core *.log val.out .gitignore~
	/bin/rm -Rf ./docs
	cd mydash-src; make clean
	cd other-progs; make clean






