
programming Language : C++

g++ compiler will be rquired to run this cpp file.

Steps to run programme: 1. g++ Parking_Question.cpp -o Parking_Question.exe
			2. Parking_Question.exe input.txt

NOTE                 : Please pass filename in the command line arguments
		     : i.e	Parking_Question.exe input.txt

Assumptions on inputs : 1. All cars will have distict no.
			2. drivers age won't be less than 0.
			3. car_number will always be in the correct format.
			4. "input.txt" file won't be empty

What if command in input file is not correct format??
			1. If command is not in right format programe will stop executing after that line.
			2. caseinsensitivity is handled.
				i.e if instead of Park --- > park 
				there won't be any issue
			3. input filename must be passed as an comman line argument while running the cpp file.
			4.for empty data. It will print nothing.
			5. if Create_parking_lot is not in the first line. it wont process the file.
			