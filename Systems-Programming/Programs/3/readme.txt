Project name: Use semaphores and mmap for shared memory access to implement dining philosophers.


program codes: host.c philosophers.c philosophers.h



Description: 
1) Host.c : This code assigns input from the file. Specify input as Number_of_philosophers Number_of_times_each_eat 

2) Philosopher.h : initializes common struct for barrier and philosophers.

3) Philosopher.c : implements philosophers.



Instructions to run:

1) Run "make clean" to erase object file

2) Run the make file using "make" command on a linux terminal.

3) Run Host.c using "./Host FileName Number_of_philosophers Number_of_times_each_eat "

Results: (sample) run ./Host 2 3
barrier sink, wait a while

process  0 hungry 
process 0 eating for 1 time
process 1 hungry 
process 0 thinking 
process 1 thinking 
process 0 hungry 
process 0 eating for 2 time
process 
1 hungry 
process 0 thinking 
process 1 thinking 
process 0 hungry 
process 0 eating for 3 time
process 1 hungry 
process 0 thinking 
end of process 0

process 1 thinking 
process 1 hungry 
process 1 eating for 1 time
process 1 thinking 
process 1 hungry 
process 1 eating for 2 time
process 1 thinking 
process 
1 hungry 
process 1 eating for 3 time
process 1 thinking 
end of process 1



Code by: Arpita S Tugave
         arpita123@ufl.edu, arpita.subash.tugave@gmail.com
