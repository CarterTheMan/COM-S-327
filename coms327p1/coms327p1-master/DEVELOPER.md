# Project 1 Part C

First for this program I made sure the make file was organized. It started with 
the all function, then the playsong and then it went to the .o parts and lastly 
was the clean part of the make file. This keeps it organized and easy to read. 

Another formatting thing I did was to make the structures read like a pyramid. 
This made them easy to read and nevigate between. When I say they are put 
together like a pyramid, the structure goes like this. First it reads the 
'WAVE' part and stores those. Then ir reads the 'SOUND' part and stores those 
with all the pointers to the proper 'WAVE's. Then it reads the 'SONG' part and 
stores the info for that with a pointer to the proper 'SOUND' parts. So 'WAVE' 
at the bottom, 'SOUND' in the middle and 'SONG' at the top.

I also made the variables easy to read and to understand. For example, the 
delay part of a 'WAVE' structure accounts for its delay of reverb. Most 
variables follow this structure.

I also have every file commented so it's easy to understand what every part is 
for. Even in the structure files.