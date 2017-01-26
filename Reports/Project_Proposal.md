#Project Proposal
##Questing Quail
###Starring: Bonnie Ishiguro, Gabe Butterick, Matthew Ruehle, Joe Sutker


##Project Goals

The minimum goal for this project is a basic HTTP server. We will begin by implementing a TCP server and get it to communicate with a client. Once that works, we will modify the server and client to use HTTP. A stretch goal would be implementing FTP on the server, allowing the client and web server to transfer files between each other.

##Product Backlog

https://trello.com/b/NEgl9TKL/softsysquestingquail

##Potential Roadblocks

Networking difficulties, especially with either (the Olin network) or (accessing hardware, with ethernet).
Current Plan: server & client on same machine.
Formatting requests, especially in C, to something which is usable outside of our server. (e.g., requests -> human language; file transfer.)
Error-checking, especially for the file transfer stretch goal.
Relatedly, ordering and re-assembly.
Avoiding packet loss.
Coordinating send() and recv(); ID’ing the client successfully.
Variation between different protocols (HTTP, TCP, FTP, UDP, …)

##Annotated Bibliography

###Griffiths, David, and Dawn Griffiths. Head First C. Beijing: O'Reilly, 2012. Print.

We are using Chapter 11 (Sockets and Networking) of this textbook to learn the basics of creating web server and client programs in C. We are also getting general C knowledge from the rest of the text to facilitate our use of the language for higher purposes.

###Hall, Brian. "Beej's Guide to Network Programming." Beej's Guide to Network Programming. N.p., 8 June 2016. Web. 21 Jan. 2017.

We are using this guide as a resource for networking concepts and implementation using the C socket libraries.

###Stevens, W. Richard. UNIX Network Programming. Englewood Cliffs, NJ: Prentice Hall, 1990. Print.

This book contains C code for a TCP server and includes an exercise for modifying the code to implement a simple HTTP server.  We plan to work through this exercise as a boilerplate for our project.
