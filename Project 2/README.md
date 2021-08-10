# Project 2 main.cpp

This program allows the user to enter a type of wave and generate the wave of 
that type based on specific types

The main part of this program is called 'main'.

First the user enters the type of wave which they want to generate. The waves 
and their types works like this:
1 - Sine Wave
2 - Square Wave
3 - Triangle Wave
4 - Sawtooth Wave

Then the user enters the sample rate, frequency and duration of that type of 
wave. Finally, at the end, the user enters the name that they want the output 
file to be called. 

In the end, it creates a wave based on the input that the user entered and then 
prints the samples of the sound to the output file.

# Project 2 TestMain.cpp

This program allows the user to enter the following input in the following 
order:

1. wave type
2. delay
3. attenuation
4. atime
5. alevel
6. dtime
7. slevel
8. rtime
9. output file name
10. all the notes and this ends with a negative input

It will go through every note and generate the wave of the type that was 
entered. Then for every sound that is generated it puts it through adsr 
according to the values that were previously entered. Likewise, it does the 
same with reverb2 on the sample. It does that whole process for every note. 

This program handles errors that are found in reverb2 and adsr. Upon finding an 
error, it will change the length of the samples array to something negative to 
show that it should throw an error and the length of the array tells the main 
what kind of error it is. It then uses cerr to print the error message, 
return 1 and end the program. 

The notes work so that you must enter each note individually and hit 
enter in between each note. This keeps them seperate. When you enter a negative 
number the program will end and print the output to the specified file. This 
program runs at a sample rate of 8000 and if there is a negative number is 
entered first it will return an empty file with a matching name.