build:
	g++ -o ./build/dataCleaner.exe ./src/data_cleaner.cpp
	g++ -o ./build/ao3Trawler.exe ./src/main.cpp ./src/FicCSV.cpp ./src/graphs/*.cpp
run:
	./build/dataCleaner.exe
	./build/ao3Trawler.exe
everything:
	g++ -o ./build/dataCleaner.exe ./src/data_cleaner.cpp
	g++ -o ./build/ao3Trawler.exe ./src/main.cpp ./src/FicCSV.cpp ./src/graphs/*.cpp
	./build/dataCleaner.exe
	./build/ao3Trawler.exe
build-graph:
	g++ -o ./build/ao3Trawler.exe ./src/main.cpp ./src/FicCSV.cpp ./src/graphs/*.cpp
run-graph:
	./build/ao3Trawler.exe
build-clean:
	g++ -o ./build/dataCleaner.exe ./src/data_cleaner.cpp
run-clean:
	./build/dataCleaner.exe
build-for-front-end:
	g++ -o ./front-end/node-stuff/ao3Trawler.exe ./src/main.cpp ./src/FicCSV.cpp ./src/graphs/*.cpp