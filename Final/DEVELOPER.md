# COM S 327 FINAL

For this final I assumed that color must be between 1 and 9 for jelly and hard 
candies (since their color is definite) and between 0 and 9 for chocolate and 
caramel candies (Since they can be any range).

If there are two seperate entries of a candy with the same name it throws an 
error and causes the program to end. This is because it is assumed that the 
input should be correct and if there are two candies of the same name then it 
is an input error (incorrect input of the file).

There isn't a defined destructor for the classes because no extra space is 
alloced for them so the default destructor works fine for this case. 

It has a base class of "candy" and two derived classes of "pound" and "piece" 
for the seperate price types.

Most of the errors are handled in the main for the general part, but there are 
a few errors that are handled in the operator+ and operator= for the derived 
classes.

All the types of candies are stored in a vector so that it can read the the 
whole file and not run out of space.

It reads through the file by looking for the keyword of "START" and then takes 
in all the input that is needed for each candy. Then it again looks for the 
next start. It does this throughout the file. 

This next part is about how I print all the candies in a sorted order: 

I made an array for sorting that sorts so that the highest total priced items 
are in the beginning and the lowest price items are at the end. I did this by 
having an extra array that was full of 1s and 0s that were supposed to 
correlate with the candies in the vector. 0 meant the candy could be added to 
the array and a 1 meant it had already been added. When a candy was added to 
the sorted array, the corresponding element in the array of 1s and 0s changed 
to a 1 so the program would know not to use ti again. 
