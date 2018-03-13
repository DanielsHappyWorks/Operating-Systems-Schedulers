Project_Name = simulate
Compiler = g++
Job_Generator = ca1_jobs.pl 11 20 10 

$(Project_Name): $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	$(Compiler) -o $(Project_Name) $^

%.o: %.cpp $(wildcard *.hpp)
	$(Compiler) -c $<

demo:
	make demo1
	make demo2
	make demo3

demo1: demo1_input.txt
	./$(Project_Name) < $@_input.txt | tee $@_output.txt

demo2: demo2_input.txt
	./$(Project_Name) < $@_input.txt | tee $@_output.txt

demo3: demo3_input.txt
	./$(Project_Name) < $@_input.txt | tee $@_output.txt

demo1_input.txt:
	$(Job_Generator) > $@

demo2_input.txt:
	$(Job_Generator) > $@

demo3_input.txt:
	$(Job_Generator) > $@
