#Preliminary Report

###Questing Quail: Bonnie Ishiguro, Gabe Butterick, Matthew Ruehle, Joe Sutker

##Revised Project Goals

The minimum goal for this project is an FTP (File Transfer Protocol) server. We will begin by implementing a TCP server, based on code from the *Unix Network Programming* textbook, and get it to communicate with a client. Once that works, we will modify the server and client to use FTP, allowing the server to transfer a file to a client. A stretch goal would be implementing HTTP on the server (GET and POST requests for html files).

##Sprints 1-2 Tasks

Product Backlog: https://trello.com/b/NEgl9TKL/softsysquestingquail
- ThinkOS Chapters 1 & 2: See individual repositories for Exercises in C reading questions (matthewruehle, bishiguro, jsutker, buttegab)
- Reflection 0: See individual ExercisesInC repositories in reflections folder
- Web_server exercise @ meeting: Pushed to group repository a version of tcpclient01 that is thoroughly commented and understood by team.
- Head First C Chapters 1 & 2: See individual ExercisesInC repositories in exercises folder
- Read/Follow Socket Programming Guide: We read this and implemented pieces in our project code
- Determine and set coding tasks: See this section of the preliminary report
- Project Proposal: https://github.com/matthewruehle/SoftSysQuestingQuail/blob/master/Reports/Project_Proposal.md
- Reading questions: (Exercises in C)
- HFC Chapter 11 - Sockets: See individual ExercisesinC repositories in exercises folder
- Talk to profs about clear definition for what kind of server to write: we had a conversation with Allen in which we stepped through the web_server code.
- View pre-written server code and step through it: done and integrated into our server and client code for ftp.

##Preliminary Code Results

**Server**
```
>> ./tcpserv_quails
Listening on port 9877 (AKA ntohs(38182))
Accepted
Forked
File Size: 
5 bytes
Server sent 256 bytes for the size
1. Server sent 5 bytes from file's data, offset is now : 5 and remaining data = 5
2. Server sent 5 bytes from file's data, offset is now : 5 and remaining data = 0
```

**Telnet**
```
>> telnet 127.0.0.1 9877
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
5ę3 6��3�*��N\��V̙3�G��3�*w�3w�3�ę3&�h��3�&@hello
Connection closed by foreign host.
```

**Comments**

We used Telnet to test our server before writing a corresponding client.  The response received by Telnet contains the first message we send - the 5, for the size of the file, and the “hello” (the contents of the text file we try to send); parsing that into something writeable into a file has proved a bit trickier, but the basic function of the server is there.

We have successfully transferred the contents of a text file from server to client.  We are currently working on the FTP client, which can receive data from the server, but we are having issues parsing the actual contents of the file from it.  We are currently not clear on exactly what is being sent by the server, but we know that it includes the file size.

##Potential Roadblocks
Our present, most pressing roadblock is getting the client to intelligibly parse information, or get multi-part files successfully. We’ve been bashing our heads against this problem for a while now, and haven’t had an overabundance of progress -- we know that what we’re trying to do is possible, but our attempts at implementation have mostly failed in some respect.

Error-checking now seems like more of a stretch, at least given our current capabilities.

##Annotated Bibliography

###Griffiths, David, and Dawn Griffiths. Head First C. Beijing: O'Reilly, 2012. Print.

We are using Chapter 11 (Sockets and Networking) of this textbook to learn the basics of creating web server and client programs in C. We are also getting general C knowledge from the rest of the text to facilitate our use of the language for higher purposes.

###Hall, Brian. "Beej's Guide to Network Programming." Beej's Guide to Network Programming. N.p., 8 June 2016. Web. 21 Jan. 2017.

We are using this guide as a resource for networking concepts and implementation using the C socket libraries.

###Stevens, W. Richard. UNIX Network Programming. Englewood Cliffs, NJ: Prentice Hall, 1990. Print.

This book contains C code for a TCP server and includes an exercise for modifying the code to implement a simple HTTP server.  We plan to work through this exercise as a boilerplate for our project.
