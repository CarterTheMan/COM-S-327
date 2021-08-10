# Project 2 Part a

For this project I made sure that the make file was properly organized. In this 
case it starts off with the main make at the top. Below is the make for the 
main executable (which is the main of this project). Below that I made a all 
the .o files and they follow the order of dependencies based on the make of 
the main. Then at the very end there is the make clean which removes all the 
.o and .txt files and then removes the main executable.

Another thing I did for this project was making the the variables have very 
clear names. When something is a sample rate it is called sampleR or samplerRate 
or something else that is very easy to tell it represents samplerate. The same 
thing goes for frequency and length. 

I also went through every method and listed what class that method was for and 
how that method works so that the user can easily tell what it is for. This 
makes it super easy to go through and see how things work.

# Project 2 Part b

For this I made sure that all variables had very clear names as to what they 
were and what they did. For example, when adsr enters the various lengths such 
as atime, the number of samples that it goes for is saves as lenA since it's the 
length of A (number of samples in atime).

For adsr I was also sure to make sure that when the waves are changed for 
every different time it is clear which part is being changed and they all 
use the same format so anyone reading it can clearly see the equation that is 
used for each sample

I also have mains from both this part and the previous one so I made sure that 
the names of each was very clean. The main from part a is called main_a and 
the main from part b is called main_b.