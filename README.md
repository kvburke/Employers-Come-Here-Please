# Employers-Come-Here-Please
C++ Interface to SQL database. Takes user input. Displays database table. Calculates average over interval. 
Sorts stored money data from least to greatest deposit amount.





Interfacing SQLite and C++ code. View Table, Insert Record, Find Avg over Interval, Sort data from least to greatest.
Write data from program to XML file for webservice consumption.

The program that interfaces with SQLite database. I choose SQLite over a traditional database to be user friendly
on more machines. Displays records, inserts records, finds average over a range, sorts data in database column.

REQUIRES BOOST AND SQLITE3 LIBRARIES!!!

This program is a C++ interface to SQLite database. main.cpp(main class), include\Engine.h(header), 
and src\Engine.cpp(implementation) are the main files that went into developing this program. 
The purpose of this program is to show how one can implement C++ code with a SQLite backend. 


In this program I have implemented 6 functions. 

*The first function [createtable()] will create a table in the SQLite database.
If a table exists this function will be passed over. 

*The second function [displaymoneyvstime()] displays all the records stored in the database.

*The third function [inputmoneyvstime(int, int)] allows a user to input a record
into the database.

*The fourth function [meanmoney(int, int)] allows a user to specify a start and end 
date to find the average of money data over a specify interval.

*The fifth function [sorter()] sorts money data from least to greatest. The purpose of this
is to show how to pass an array of data to an external library.

*The sixth function [updatemoneyvstimexml()] goes back and updates the XML webservices if new data
is inserted into the database by the inputmoneyvstime(int, int) function.




Any additional questions I can be reached at kvburke@ncsu.edu
