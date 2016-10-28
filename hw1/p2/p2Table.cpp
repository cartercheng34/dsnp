#include "p2Table.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <climits>
#include <sstream>
#include <cstdlib>
using namespace std;

// Implement member functions of class Row and Table here

Row::Row(int col)
{
	_data = new int[col];
	col_num = col;
}

Row::Row(const Row& row)
{
	col_num = row.col_num;
	_data = new int[row.col_num]; 
	for(int i=0;i<row.col_num;i++){
		_data[i] = row._data[i];
	}
}

const int Row::operator[]( size_t i ) const
{
	return _data[i];
}



int& Row::operator[]( size_t i ) 
{
	return _data[i];
}

const Row& Table::operator[]( size_t i ) const
{
	return _rows[i];
}


Row& Table::operator[]( size_t i)
{
	return _rows[i];
}

bool Table::read(const string& csvFile,int &row_sub,int &col_sub)
{ 
	ifstream myfile (csvFile.c_str() , ifstream::in);
	int count=0;
	char c;
	while(myfile.get(c)){
             if(c == ',' && count == 0)
                 col_sub++;
             else if(c == 13){
                 row_sub++;
                 count++;
          }
        }
   Row rows(col_sub);
   for(int i=0;i<row_sub;i++)
        _rows.push_back(rows);
	if( myfile.is_open() )
		return true; // TODO
	else return false;
}

void Table::print(int row , int col)
{
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(_rows[i][j] == INT_MAX)
				cout<<right<<setw(4)<<"";
			else cout<<right<<setw(4)<<_rows[i][j];		
		}
		cout<<endl;
	}	



}
double Table::ave(int row, int tar_col)
{
	int sum=0,counter=0;
	for(int i=0;i<row;i++){
		if(_rows[i][tar_col] == INT_MAX){
			sum=sum;
			counter++;
		}
		else	sum+=_rows[i][tar_col];
	}
	return (sum/(row-counter));
}

int Table::max(int row ,int tar_col)
{	
	int max=-101;
	for(int i=0;i<row;i++){
		int tmp=_rows[i][tar_col];
		if(tmp>max && tmp!=INT_MAX)
			max=tmp;
	}
	return max;
}
int Table::min(int row ,int tar_col)
{
	int min=101;
	for(int i=0;i<row;i++){
		int tmp=_rows[i][tar_col];
		if(tmp<min && tmp!=INT_MAX)
			min=tmp;
	}
	return min;
}
int Table::sum(int row ,int tar_col)
{
	int sum=0;
	for(int i=0;i<row;i++){
		if(_rows[i][tar_col] == INT_MAX)
			sum=sum;
		else sum+=_rows[i][tar_col];
	}
	return sum;	 	
}
int Table::count(int row,int tar_col)
{
	vector<int> modified;
	
	for(int i=0;i<row;i++){
		if(_rows[i][tar_col]!=INT_MAX)
			modified.push_back(_rows[i][tar_col]);
	}
	for(int i=0;i<modified.size();i++){
		for(int j=i+1 ; j<modified.size() ; j++){
			if(modified[i]==modified[j] ){
				modified.erase(modified.begin()+i);
				i--;
			}
		}
	}
	return modified.size();
}
void Table::add(int row_num,int col_num,string str)
{		
	string tmp;
	int counter = 0;
	stringstream ss(tmp);
	_rows.push_back(Row(col_num));
	
	for(int i=0;i<str.length();i++){
		if(str[i] == '-' ){
			tmp+=str[i];		
		}
		else if(int(str[i])==32){
			if(tmp=="-"){
				_rows[row_num][counter] = INT_MAX;
				tmp.clear();
			}
			else
			{	ss.str("");
				ss.str(tmp);
				cout<<"tmp="<<tmp<<endl;		
				int num;	
				ss>>num;
				cout<<"num="<<num<<endl;
				_rows[row_num][counter] = num;
				counter++;
				tmp.clear();
			}
		}
		else if(str[i]!='-' && int(str[i])!=32){
			tmp+=str[i];
		}
	}
	if(tmp!="-"){
	cout<<"tmp="<<tmp<<endl;
	int num2;
	num2=atoi(tmp.c_str());
	_rows[row_num][counter] = num2;
	tmp.clear();
	}
}	




