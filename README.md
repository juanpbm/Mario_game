## Walter Galdamez and Juan Pablo Bernal 

## Title: NEU Super Mario

## Description:

This porject consisted of replicating the first level of Super Mario using ACSII art to make the design for the map and the all the characters involved. For example, Mario is represented using an "m" and the monsters represented using an "X". The game has basic movement option; as an extra feature fot the game, we decided to use the wiimote to control the movement of the character. The remote was programmed so that we could use the the arrows in the remote to move Marion up,down,left, and right. Another feature that we decided to add is a celebratory animation at the end of the game which is shown in the youtube video. Also, we added the feature to interact with the user with the command windown. The user gets to choose if they want to play, read the instructions on how to play the game, ect. Lastly, we wanted to mimic the original game as much as possible, so we decided that instead of having one to fit in the canvas of the screen, we would stead didvie the map into many parts. Once the user got to the end of the first part, the second would be displayed and so on.  

## Revelance:

The parts of the course material that we are excersing in the design of the project are functions, pass-down by reference, and OOP. For every action performed by the character, we created a fuction that updates the movemnt to keep track of where Mario is on the board to check if he is near monsters or standing on a monster. We also desing fucntions to add the next stages of the map and functions that create the map. In other words, the whole program has fcutions to track the movement of the character that determined whatv the program will do next. We used pass by reference because each parameter gigving to a fucntion needed to be modified so we pass down the memory location of the variable and modified its content in the fuction. Lastly, the last part that we implemented in the course are objects and classes. We did not necessarly used classes for the actual game but we used classes for the wiimote. We had a wiimote.h and wiimote.cc that allowed to connect the wiimote to the zebboard. The we gather the values of each button and use a swicth-case statment for each button to tell the program what to do.


Youtube Link:

https://www.youtube.com/watch?v=3c0uHj5n-Rg

In this video, we show the functionality of the game controlled by the wiimote. In the two minutes of the footage, we showed the stages of the game, how Mario interacts with the monsters, how mario interacts with the map, and lastly the celebartory event at the end.

