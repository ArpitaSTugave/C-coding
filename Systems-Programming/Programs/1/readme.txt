Project name: Read program via pipe


program codes: mapper.c reducer.c combiner.c


Description: 

1) Mapper.c : This code assigns inputs from the file to their respective key.

2) Reducer.c : This code counts number of word instances.

3) Combiner.c : This code pipes between Mapper.c and Reader.c. 
Thus Mapper.c writes into the pipe and Reducer.c reads from the pipe.




Instructions to run:

1) Run "make clean" to erase object files

2) Run the make file using "make" command on a linux terminal.

3) Run Combiner.c using "./combiner"

Results:
process 6625 exits with 0 
(cap,4)
(class,3)
(concurrency,1)

(course,4)
(culture,2)
(date,4)
(door,4)
(eraser,5)
(error,3)
(field,5)
(floor,1)
(gap,4)
(group,9)
(heat,4)
(hierarchy,1)
(hole,5)

(house,1)
(ice,4)
(inconsistency,2)
process 6626 exits with 0 




Code by: Arpita S Tugave
         arpita123@ufl.edu, arpita.subash.tugave@gmail.com
