.SECONDARY

Project_Name = simulate
Compiler = g++

$(Project_Name): $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(Compiler) -o $(Project_Name) $^

%.o: %.cpp $(wildcard *.hpp)
	$(Compiler) -c $<

demo: demo1 demo2 demo3

demo1: demo_output1.txt
	./simulate < demo_input1.txt > $@

demo_input1.txt:
	ca1_jobs.pl 11 20 10 > $@

demo2: demo_output1.txt
	./simulate < demo_input1.txt > $@

demo_input2.txt:
	ca1_jobs.pl 11 20 10 > $@

demo3: demo_output1.txt
	./simulate < demo_input1.txt > $@

demo_input3.txt:
	ca1_jobs.pl 11 20 10 > $@