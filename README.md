![Typing SVG](https://readme-typing-svg.demolab.com?font=ARIEL&weight=500&size=30&duration=3000&pause=200&color=F7AE6C&background=FF51F800&multiline=true&repeat=false&&width=600&height=100&lines=Advance++Programming+Project;+By+Amit+%26+Simon)

The Project is written in CPP <p align="left">  <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> </p>
Advanced Programming  project by Amit Hazan and Simon Fraiberg
to compile follow this simple steps:
1. clone the project.
2. extract the zip to a folder.
3. open your terminal in the folder destination using cd command.
4. run the "make" command on the planet server to compile.
now you have the server.out file and client.out file.
first run the server. the command is ./server.out [port].
now run the client. the command is ./client.out  [server ip] [port that server is listening to].

a menu like this will appear:
[![Typing SVG](https://readme-typing-svg.demolab.com?font=ARIEL&weight=200&duration=500&pause=200&color=38F740&background=050D2F&multiline=true&&repeat=false&&width=1000&height=200&lines=Welcome+to+the+KNN+Classifier+Server.+Please+choose+an+option%3A;1.+upload+an+unclassified+csv+data+file;2.+algorithm+settings;3.+classify+data;4.+display+result;5.+download+results;8.+exit)](https://git.io/typing-svg)

here is a summary of each option:
1. first upload a train csv file of classified vectors and then a test csv file of unclassified vectors.
2. this will show you the current settings for KNN algorithem that (distance method and k). pressing enter will keep them. if you would like to change them use this format <K for KNN> <string of distance func as written below>
***********************************************************
the string representation of the formulas are as follows:
1. AUC - auclidian distance.
2. MAN - manhattan distance.
3. CHB - chebyshev distance.
4. CAN - canberra distance.
5. MIN - minkowski distance.
***********************************************************
3. classify the test csv using the KNN algorithm with the train file.
4. show the classification of the test file to the screen.
5. writes the classification of the test file to the file path you provide.
8. exit the server.


*the K is for the KNN fucntion that indicates the number of neighbors in the function.

wrong input will print invalid input. (wrong input like none positive K, wrong length of vector, wrong string representation of the distance formula).
note that if you provide us a k of a large number that is leagal for the current file but then upload a file smaller then the k, the k will be the size of the smaller file.
please make sure that that after you upload new files to classify them again for the desired result.
you can input a file with as much vectors as you would like.
the server will keep running making a thread for each new clinet.

//info on the distance formulas//
the functions used the similarity of the Euclidean and Manhattan that are based on the Minkowski formula.
when p = 1 we get Euclidean distance and for p = 2 we get Manhattan distance so we have a general function to calculate the formula.
all of the 5 different distance function are in Distance class that has static functions for each distance method.
its a static method so it would not be necessary to make an Distance object to use them. just like the known math class.

##the minikowski function was calculated as p = 2 in the formula##
