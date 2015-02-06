#include "Engine.h" /*Reference header and namespace*/
#include <iostream>
using namespace std;

int main() /*Main function*/

{
     int inputone=0; /*Initialize user input variables*/
     int inputtwo=0;
     int initialrange=0;
     int finalrange=0;




    Engine *engine = new Engine();

    engine->createtable(); /*creates table in database */
    engine->displaymoneyvstime(); /*displaymoneyvstime - displays table to stdout and sumwebservice.xml*/
    cout << "Enter money amount (1-10000)" << endl;
    cin >> inputone;
    cout << "Enter time of day (0-24)" << endl;
    cin >> inputtwo;

    engine->inputmoneyvstime(inputone,inputtwo); /*inputmoneyvstime - inputs record into table */
    engine->updatemoneyvstimexml(); /*Updates XML file with newly acquired data */
    cout << "Enter initial time of day for money average:" << endl; /*Get user input to acquire avg over time*/
    cin >> initialrange;
    cout << "Enter final time for money average: " << endl;
    cin >> finalrange;


    engine->meanmoney(initialrange,finalrange);  /*meanmoney - calculates average over a specific day range*/
    engine->sorter(); /*sorts all money from least to greatest*/
    delete engine;
    return 0;
}
                            /*example: engine.inputmoneyvstime(5,10) Inputs record Day-5 Money-10*/
                            /*example: engine.meanmoney(2,4) Calculates average over days 2 to 4*/
