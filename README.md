
# Advenced_Exercises - UNIX only
This repo used for Advenced computing exercise 3
In this exercise we had to make KNN algorithm using cpp. KNN in a primitive ML algorithm that get as an input Data that seperate into 2 main parts: features and labels. Based on the features we want to make a prediction for a label for a new sample of data. The way KNN works is by calculating a distance function between the new sample to all the data in the training set. the label of the most fluent sampels with the smallest distance will be the prediction label of the new sample.
In this exercise we implemented a server side client side method therefore the user reach the client side and insert an input. This input is convey to the server side there the caclculation has been made and after it the result is transfering to the client side and the client side show this input to the user.

In this Excercise we have to make an implementation for 5 types of distances:
1. Euclidain Distance
2. Manheten Distance
3. Chebyshev Distance
4. Canberra Distance
5. Minkowski Distance

When you run the file you wil face an empty line for input there you will have the insert your vector input.
The insertation of the vector should be with spaces between the numbers like the following example:

![image](https://user-images.githubusercontent.com/91119719/207488828-9018edc3-73cb-4c85-8d2c-ea6d09c88ec0.png)

The code will compute the distances between the sample vector you inserted to all of the samples and will send you the following output:

![image](https://user-images.githubusercontent.com/91119719/207488348-f6a7379b-ee1b-4693-afdf-2311f77abe59.png)

The our that you will get is the class out by the KNN model

# IMPORTANT CLARIFICATION:
1. The size of iris vector must be 4, wine vectors must be 13 and beans vector must be 16
2. Each number within each vector must be seperated with spaces - Only 1 Space seperate between 2 numbers!
3. The run of the program for the client side should be from the client.out for the user (using the client side)
4. The run of the program for the server side should be from the server.out for the server
5. You can't end the input you insert with space or either start it with space
6. Every time you will insert vector and you will get result and after it you will have the option to insert new vector
7. You can stop this program by insert -1 as input
8. Notice that csv file can be called by relative path (in case you know yourself root for the location of the file / absulute path in case you know the exact location of your file and if it located in a one step lower from the root only)
9. In order that communication tunnel will be crate the port must be the same (otherwise no output will show up - you need to enforce it youself because there is no limitations due to network routing and capabillities)

# COMPILING AND RUNNING COMMANDS:
In this repo there is a makefile for compiling the program. The instruction for run this program are:
1. run the command: <code>make</code> on your terminal
2. use ls to see that indeed <code>server.out</code>, <code>client.out</code> files were created
3. run <code>./server.out \<Data.csv> \<port> </code> in order to run <code>server.out</code> file in the designated terminal resource
4. run <code>./client.out \<ip> \<port> </code> in order to run <code>client.out</code> file in the designated terminal resource
5. K = Notice K must be a number between 1 - 100 (Can be double but know that double double will be rounded - better to use int)
6. Data file must be only fro this group = {iris_classified.csv, wine_Classified.csv, beans_Classified.csv} - Other input will now accept
7. Distance function will be from the group = {AUC, MAN, CHB, CAN, MIN} - Other input will not accept

# draft
