#include <iostream> /*Reference necessary libraries and header files*/
#include "sqlite3.h" /*Program uses many APIs from standard library and boost*/
#include "Engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;


int sum1=0; /*Global variables*/
int sum2=0;
vector<int> sumholder;
FILE *f= fopen("databaseresults.xml", "w");


/*LOGIC to interface with database table and display rows and columns to STDOUT and an XML file */
static int callback(void *handle, int argc, char **argv, char **azColName){

   int i; /*Column position in SQLITE API*/


   for(int i=0; i<argc; i++){

/*Prints SQL SELECT ALL QUERY output to STDOUT and XML file*/
   switch(i){ /*Switch statement allows each database column to get a separate XML tag based on column position when its written to file*/

      case 0:
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULLx");
      fprintf(f, "<RECORD%s> \r\n", argv[i]);
      fprintf(f, "<ID>%s</ID>  \r\n",  argv[i] ? argv[i] : "NULLx");

      break;

      case 1:
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULLx");
      fprintf(f, "<TIME>%s</TIME>  \r\n",  argv[i] ? argv[i] : "NULLx");

      break;

      case 2:
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULLx");
      fprintf(f, "<MONEY>%s</MONEY>  \r\n",  argv[i] ? argv[i] : "NULLx");
      fprintf(f, "</RECORD%s> \r\n", argv[0]);

      break;


      case 3:
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULLx");
      fprintf(f, "%s = %s  \r\n", azColName[i] , argv[i] ? argv[i] : "NULLx");


      break;
   }


   }
   printf("\n");
   //fprintf(f, "\r\n");

   return 0;

}
/*LOGIC to interface with database iterates through the money (second) column and sums the values*/
static int callback1(void *NotUsed, int argc, char **argv, char **azColName){
   int i; /*References "i" column we use the second column to acquire money data*/
   int sum;


   for(i=2; i<3; i++){ /*This loop keeps the summing iteration bound to the second column*/

      sum= atoi (argv[i]); /*SQLite API outputs string data fields. So convert string values to int values and sum data*/
      sum1=+sum+sum1; /*Acquire and add money field data and store in sum1 global variable */
      printf("%i", sum1);
      sumholder.push_back(sum);


   }

   printf("\n");
   return 0;
}

/*LOGIC to interface with database, acquires count field from the first row and assigns it to sum2 */
static int callback2(void *NotUsed, int argc, char **argv2, char **azColName){
   int i;
   int cnt;
   for(i=0; i<argc; i++){ /*This function acquires the only column outputted by the API containing count data*/
      printf("%s", argv2[i] ? argv2[i] : "NULL");
      cnt=atoi(argv2[0]); /*Convert string outputted by SQLITE to int*/
      sum2=cnt; /*Assign count to sum2*/

   }
   printf("\n");
   return 0;
}






/*LOGIC to interface with database table and display rows and columns to an XML file */
/*Called by updatemoneyxml() function to write to update XML file after new data is added */
static int callback3(void *handle, int argc, char **argv, char **azColName){

    int i;
    const char *sep = "";

   for(int i=0; i<argc; i++){

/*Switch statement allows each database column to get a separate XML tag based on column position when its written to file*/
   switch(i){

      case 0:

      fprintf(f, "<RECORD%s> \r\n", argv[i]);
      fprintf(f, "<ID>%s</ID>  \r\n",  argv[i] ? argv[i] : "NULLx");
      sep= ",";
      break;

      case 1:

      fprintf(f, "<TIME>%s</TIME>  \r\n", argv[i] ? argv[i] : "NULLx");
      sep= ",";
      break;

      case 2:

      fprintf(f, "<MONEY>%s</MONEY>  \r\n", argv[i] ? argv[i] : "NULLx");
      fprintf(f, "</RECORD%s> \r\n", argv[0]);
      sep= ",";
      break;


      case 3:

      fprintf(f, "%s = %s  \r\n", azColName[i] , argv[i] ? argv[i] : "NULLx");

      sep= ",";
      break;
   }


   }
   //printf("\n");
   //fprintf(f, "\r\n");

   return 0;

}





/*CREATES table in SQLite */
void Engine::createtable(){

 sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE IF NOT EXISTS TIMEANDMONEYd("  \
         "ID INTEGER PRIMARY KEY NOT NULL," \
         "TIME           INT    NOT NULL," \
         "MONEY            INT     NOT NULL);";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);

}





void Engine::displaymoneyvstime(){ /*Displays TIMEANDMONEY table from SQLITE */

   sqlite3 *db; /*Initialization of local variables for SQLITE API CALLBACK FUNCTION */
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";


   char *errs = NULL;
   string all;
   string replacer= "*";

   /* Open database */
   rc = sqlite3_open("test.db", &db); /*Opens test.db file in SQLITE API */
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
       fprintf(f, "<xml>\n");
   }

   /* Create SQL statement */

   all = "SELECT * from TIMEANDMONEYd";

    boost::replace_all(all, "*", replacer); /*Replace * with fields specified by replacer variable */

    char * c = new char[all.size() + 1]; /*Convert all string variable into char pointer so SQL API can use */
    std::copy(all.begin(), all.end(), c);
    c[all.size()] = '\0';

    sql=c;

   /* Execute SELECT SQL statement and display results */
   rc = sqlite3_exec(db, sql, callback, 0, &errs);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
    fprintf(f, "</xml>\n");
   }
                                    /*Close database and filepointer */
   sqlite3_close(db);
   fclose(f);

}



void Engine::inputmoneyvstime(int money, int time){ /*Input money and time into TIMEANDMONEY table*/

   stringstream ss; /*Convert money integer to string to inject into SQL statement*/
   ss << money;
   string strmoney = ss.str();

   stringstream qq; /*Convert date integer to string to inject into SQL statement*/
   qq << time;
   string strtime = qq.str();

   sqlite3 *db; /*Initialize local variables to be used in callback function */
   char *zErrMsg = 0;
   int rc;
   char *sql;
   string allx;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }




   /* Create SQL statement to INSERT RECORD INTO TIMEANDMONEY*/
   allx = "INSERT INTO TIMEANDMONEYd (TIME, MONEY) "  \
         "VALUES (?time, ?money); ";


    /*Boost library binds time and money string variables to SQL INSERT query*/
        boost::replace_all(allx, "?time", strtime);
        boost::replace_all(allx, "?money", strmoney);


    /*Converting SQL string into a char pointer to be a usable parameter by SQLITE API*/
    char * d = new char[allx.size() + 1];
    std::copy(allx.begin(), allx.end(), d);
    d[allx.size()] = '\0';

    sql=d;

   /* Execute SQL INSERT statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
}


void Engine::meanmoney(int first, int last){ /*Function to calculate mean over a given day range*/

    ofstream outFile;

    float avg=0;

    string outputFileName= "sumwebservice.xml";
    outFile.open(outputFileName.c_str());

    stringstream ss; /*Convert first date integer to string to inject into SQL statement*/
    ss << first;
    string strfirst = ss.str();

    stringstream qq; /*Convert last date integer to string to inject into SQL statement*/
    qq << last;
    string strlast = qq.str();

    sqlite3 *db; /*Initialize local variables to be used as parameters in callback function */
    char *zErrMsg = 0;
    int rc;
    char *sql;
    char *sql2;
    const char* data = "Callback function called";
    string ally;
    string allz;



   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SELECT SQL statement that displays information in a user specify range */
   ally = "SELECT * from TIMEANDMONEYd WHERE TIME >= ?first AND TIME <= ?last";
   allz = "SELECT COUNT(*) from TIMEANDMONEYd WHERE TIME >= ?first AND TIME <= ?last";


    /* Again the boost library to bind parameters to the FIRST SQL query above*/
    boost::replace_all(ally, "?first", strfirst);
    boost::replace_all(ally, "?last", strlast);

    /*SQLITE API requires a char pointer as a parameter so we convert SQL string to char* */
    char * e = new char[ally.size() + 1];
    std::copy(ally.begin(), ally.end(), e);
    e[ally.size()] = '\0';

    sql=e;

    /*Again the boost library to bind parameters to the SECOND SQL query above*/
    boost::replace_all(allz, "?first", strfirst);
    boost::replace_all(allz, "?last", strlast);

    /*SQLITE API requires a char pointer as a parameter so we convert SQL string to char* */
    char * f = new char[allz.size() + 1];
    std::copy(allz.begin(), allz.end(), f);
    f[allz.size()] = '\0';

    sql2=f;



   /* Execute SQL statement to AVERAGE the numbers.*/
   rc = sqlite3_exec(db, sql, callback1, (void*)data, &zErrMsg); /*SUMMING IS ACCOMPLISHED in the CALLBACK1 FUNCTION */
   rc = sqlite3_exec(db, sql2, callback2, (void*)data, &zErrMsg); /*COUNT  IS ACCOMPLISHED in the CALLBACK2 FUNCTION */
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");


    stringstream xxx; /*Convert sum1, sum2, count integers to strings*/
    xxx << sum1;
    string sum1s = xxx.str();

    stringstream yyy;
    yyy << sum2;
    string sum2s = yyy.str();

    stringstream zzz;
    zzz << avg;
    string avgs = zzz.str();

    string sum1tagb="<SUM>"; /*Adds tags to sum1,sum2,count variables for XML processing */
    string sum1tage="</SUM>";

    string sum2tagb="<COUNT>";
    string sum2tage="</COUNT>";

    string avgtagb="<AVG>";
    string avgtage="</AVG>";


      if(outFile.is_open()){ /*Sends sum and count data to console and an XML file */
      printf("The sum is %i\n", sum1);
      outFile << "<SUMCOUNTAVG>" << endl;
      outFile << sum1tagb+sum1s+sum1tage << endl;
      printf("The count is %i\n", sum2);
      outFile << sum2tagb+sum2s+sum2tage << endl;
      avg=(float)sum1/ (float)sum2;

    stringstream zzz; /*Convert avg integer to string*/
    zzz << avg;
    string avgs = zzz.str();


      printf("The avg is %f\n", avg); /*Sends avg data to console and to sumwebservices XML file*/
      outFile << avgtagb+avgs+avgtage << endl;
      outFile << ("</SUMCOUNTAVG>") << endl;
      }
        else{
            cout << "Could not create outfile" << endl;
        }
                            /*Close filepointer and database*/
        outFile.close();

   sqlite3_close(db);

}
}


void Engine::sorter(){ /*Function that sorts money values listed in database from least to greatest */

/*After money values are placed into vector by callback3 function
use the boost library to sort the vector least to greatest*/
std::sort(boost::begin(sumholder), boost::end(sumholder));

cout << "Sorting entire money distribution from least to greatest:" << endl;
/*Prints values from sumholder vector to stdout*/
for(int i=0; i<sumholder.size(); i++) {
    printf("%i ", sumholder[i]);
   }

}

void Engine::updatemoneyvstimexml(){ /*Displays TIMEANDMONEY table from SQLITE */
FILE *f= fopen("databaseresults.xml", "w"); /*open filepointer to write SELECT QUERY TO XML FILE for UPDATED INFO*/
   sqlite3 *db; /*Initialization of local variables for SQLITE API CALLBACK FUNCTION */
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   char *errs = NULL;
   string all;
   string replacer= "*";

   /* Open database */
   rc = sqlite3_open("test.db", &db); /*Opens test.db file in SQLITE API */
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
       fprintf(f, "<xml>\n");
   }

   /* Create SQL statement */
   all = "SELECT * from TIMEANDMONEYd";

    boost::replace_all(all, "*", replacer); /*Replace * with fields specified by replacer variable */

    char * c = new char[all.size() + 1]; /*Convert all string variable into char pointer so SQL API can use */
    std::copy(all.begin(), all.end(), c);
    c[all.size()] = '\0';

    sql=c;

   /* Execute SELECT SQL statement and display results */
   rc = sqlite3_exec(db, sql, callback3, 0, &errs);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
    fprintf(f, "</xml>\n");

   }
   sqlite3_close(db); /*Close database and filepointer */
     fclose(f);

}

