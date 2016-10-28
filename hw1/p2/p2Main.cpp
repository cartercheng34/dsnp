#include <iostream>
#include <string>
#include "p2Table.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

int main()
{
   Table table;

   // TODO: read in the csv file
   string csvFile;
   cout << "Please enter the file name: ";
   cin >> csvFile;
   int row = 0 , col = 1 ;
   table.row = row;
   table.col = col;
   if (table.read((csvFile),table.row,table.col))
      cout << "File \"" << csvFile << "\" was read in successfully." << endl;
   else exit(-1); // csvFile does not exist.
   char c;
   table.row--;
   ifstream file(csvFile.c_str() , ifstream::in);
      
   string tmp;
   int counter1 = 0 , counter2 = 0,count=0;
   while(file.get(c)){
     stringstream ss(tmp);
  	 if(c == ','){		
		if(tmp!=""){
	 		int num;
			ss>>num;
			table[counter1][counter2] = num;
		
		}
	 	else {
			table[counter1][counter2] = INT_MAX;
		}
 	 counter2++;
	 
	 tmp.clear();
	
	 }	
   	 else if(c == 13 ){
		
		if(count==2)
			break;
		if(tmp!=""){
			int num;
			ss>>num;
			table[counter1][counter2]=num;
		}
	 	else {
			table[counter1][counter2] = INT_MAX;
		}
	 counter1++;
	 counter2 = 0;
	
	 tmp.clear();
	 }
	else tmp+=c;
		
	}		 
   

   string command;
 
   while(true){
   cout<<"type the command"<<endl;
   cin>>command;
   if(command == "PRINT"){
	table.print(table.row,table.col);
	}
   else if(command == "ADD"){	
		table.row++;
		string str;
		getline(cin,str);
		str.erase(0,1);
	/*	cout<<str<<endl;
		cout<<"LEN="<<str.length();*/
		table.add(table.row,table.col,str);	
	}
   else if(command == "AVE"){
	int cc;
	cin>>cc;
	cout<<"The Average of data in column #"<<cc<<" is "<<table.ave(table.row,cc)<<endl;
	}
   else if(command == "SUM"){
	int cc;
	cin>>cc;
	cout<<"The Sum of data in column #"<<cc<<" is "<<table.sum(table.row,cc)<<endl;
	}
   else if(command == "MAX"){
	int cc;
	cin>>cc;
	cout<<"The Max of data in column #"<<cc<<" is "<<table.max(table.row,cc)<<endl;
	}
   else if(command == "MIN"){
	int cc;
	cin>>cc;
	cout<<"The Min of data in column #"<<cc<<" is "<<table.min(table.row,cc)<<endl;
	}
   else if(command == "COUNT"){
	int cc;
	cin>>cc;
	cout<<"The distinct count of data in column #"<<cc<<" is "<<table.count(table.row,cc)<<endl;
	}
   else if(command == "EXIT"){
        exit(-1);

   }
}
}
