# SoftSys HTTP Server in C

Server project for Olin College's spring 2017 class on Software Systems.

## What is this?

This project implements a rudimentary HTTP server and client, able to transfer text files from the server to the client courtesy of GET requests. The server reads the requested file, and sends it to the client via a socket; the client then writes its own “copy” of the file. Note that the server is not secure; pretty much anything on the host machine is currently, potentially grabbable by a client.

For more details, see [our website](http://matthewruehle.github.io/SoftSysQuestingQuail).

## Authors

Gabriel Butterick, Bonnie Ishiguro, Matthew Ruehle, and Joseph Sutker

#### Utilizes code from

- _Head First C_, by David Griffiths and Dawn Griffiths
- _UNIX Network Programming_, by William Richard Stevens
- [_Beej's Guide to Network Programming_](http://beej.us/guide/bgnet/output/html/multipage/index.html), by Brian "Beej Jorgensen" Hall
- [Stack Overflow](https://stackoverflow.com/questions/11952898/c-send-and-receive-file), code from user TOC

## Getting Started

Fork and/or clone this repository to get the code. There should be nothing else you need to download.

## Usage

Just run `make reset` to get your executables set up, run `./tcpserv_quails` to run the server, and run `./tcpclient <Server IP Address> <Requested File>` to download the file. Easy as that!

## Warning

Running this code for public use is a security risk. The server's file system can be accessed via carefully worded requests. If you decide to use this code to host a public facing web server, any data on the hosting computer will be accessible to any user.