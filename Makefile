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

demo1: demo_input1.txt
        ./$(Project_Name) < demo_input1.txt | tee $@_output.txt

demo2: demo_input2.txt
        ./$(Project_Name) < demo_input2.txt | tee $@_output.txt

demo3: demo_input2.txt
        ./$(Project_Name) < demo_input3.txt | tee $@_output.txt

demo_input1.txt:
        $(Job_Generator) > $@

demo_input2.txt:
        $(Job_Generator) > $@

demo_input3.txt:
        $(Job_Generator) > $@
