/****************************************************************************
  FileName     [ dbTable.cpp ]
  PackageName  [ db ]
  Synopsis     [ Define database Table member functions ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2015-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#include <iomanip>
#include <string>
#include <cctype>
#include <cassert>
#include <set>
#include <algorithm>
#include "dbTable.h"
#include <cmath>
#include <climits>
#include <sstream>
using namespace std;

/*****************************************/
/*          Global Functions             */
/*****************************************/
ostream& operator << (ostream& os, const DBRow& r)
{
   // TODO: to print out a row.
   // - Data are seperated by a space. No trailing space at the end.
   // - Null cells are printed as '.'
    for(int i=0;i<r.size();i++){
      if(r[i] == INT_MAX)
        os<<".";
      else os<<r[i];
      if(i < r.size()-1)
        os<<' ';      
    }
    os<<endl;
    return os;
}

ostream& operator << (ostream& os, const DBTable& t)
{
   // TODO: to print out a table
   // - Data are seperated by setw(6) and aligned right.
   // - Null cells are printed as '.'
    for(int i=0;i<t.nRows();i++){
      for(int j=0;j<t.nCols();j++){
        if(t[i][j] == INT_MAX) os<<right<<setw(6)<<' ';
        else os<<right<<setw(6)<<t[i][j];
      }
      os<<endl;
    }
    os<<endl;
   return os;
}

ifstream& operator >> (ifstream& ifs, DBTable& t)
{
   // TODO: to read in data from csv file and store them in a table
   // - You can assume all the data of the table are in a single line.  
    char c;
    string tmp;    
    DBRow row = DBRow();
    int number;
    
    while(ifs.get(c)){
      stringstream ss(tmp);
      if(c == ','){
        if(tmp != ""){                    
          ss>>number;
          row.addData(number);          
        }
        else row.addData(INT_MAX);
        tmp.clear();
      }
      else if(c == 13 || c == 10){
        if(tmp!=""){                  
          ss>>number;
          row.addData(number);
          t.addRow(row);
          row.reset();          
        }
        else{
          row.addData(INT_MAX);
          if(row.size() == t.nCols()) 
            t.addRow(row);
          row.reset();        
        }      
        tmp.clear();
      }
      else tmp+=c;
    }

   return ifs;
}

/*****************************************/
/*   Member Functions for class DBRow    */
/*****************************************/
void
DBRow::removeCell(size_t c)
{
   // TODO
  _data.erase(_data.begin()+c);
}

/*****************************************/
/*   Member Functions for struct DBSort  */
/*****************************************/
bool
DBSort::operator() (const DBRow& r1, const DBRow& r2) const
{
   // TODO: called as a functional object that compares the data in r1 and r2
   //       based on the order defined in _sortOrder
  for(size_t i = 0; i < _sortOrder.size(); i++){
    int n = _sortOrder[i];
    if(r1[n] > r2[n]) 
      return false;
    else if(r1[n] < r2[n]) 
      return true;
  }
  return false;
}

/*****************************************/
/*   Member Functions for class DBTable  */
/*****************************************/
void
DBTable::reset()
{
   // TODO
  for(size_t i=0;i<nRows();i++)
    _table[i].reset();
}

void
DBTable::addCol(const vector<int>& d)
{
   // TODO: add a column to the right of the table. Data are in 'd'.
  for(size_t i=0;i<nRows();i++)
    _table[i].addData(d[i]);
}


void
DBTable::delRow(int c)
{
   // TODO: delete row #c. Note #0 is the first row.
  _table.erase(_table.begin()+c);
}

void
DBTable::delCol(int c)
{
   // delete col #c. Note #0 is the first row.
   for (size_t i = 0, n = _table.size(); i < n; ++i)
      _table[i].removeCell(c);
}

// For the following getXXX() functions...  (except for getCount())
// - Ignore null cells
// - If all the cells in column #c are null, return NAN
// - Return "float" because NAN is a float.
float
DBTable::getMax(size_t c) const
{
   // TODO: get the max data in column #c
  int max;
  bool judge = false;
  for(int i=0;i<nRows();i++){
    if(_table[i][c] != INT_MAX){
      max = _table[i][c];
      judge = true;
      break;
    }
  }

  for(size_t i=0;i<nRows();i++){
    if(_table[i][c] > max &&_table[i][c] != INT_MAX)
      max = _table[i][c];        
  }
  if(judge == true)
    return max;
  else return NAN;
}

float
DBTable::getMin(size_t c) const
{
   // TODO: get the min data in column #c
  int min;
  bool judge = false;
  min = _table[0][c];
  for(size_t i=0;i<nRows();i++){
    if(_table[i][c] < min)
      min = _table[i][c];
    if(_table[i][c] != INT_MAX)
      judge = true;
  }
  if(judge ==  true)
    return min;
  else return NAN;
}

float 
DBTable::getSum(size_t c) const
{
   // TODO: compute the sum of data in column #c
  if(c>=nCols())
    return NAN;
  int sum = 0;
  bool judge = false;
  for(size_t i=0;i<nRows();i++){
    if(_table[i][c] != INT_MAX){  
      sum += _table[i][c];
      judge = true;
    }
    else sum = sum;
  }
  if(judge = true)
    return sum;
  else return NAN;
}

int
DBTable::getCount(size_t c) const
{
   // TODO: compute the number of distinct data in column #c
   // - Ignore null cells

  set<int> tmp;
  for(size_t i=0;i<nRows();i++){
    if(_table[i][c] != INT_MAX)
      tmp.insert(_table[i][c]);
  }
   return tmp.size();
}

float
DBTable::getAve(size_t c) const
{
   // TODO: compute the average of data in column #c
   if(c>=nCols())
    return NAN;
   int counter = 0;
   for(size_t i=0;i<nRows();i++){
   
   if(_table[i][c] == INT_MAX)
    counter++; 
   }   
   return getSum(c) / (nRows()-counter);
}

void
DBTable::sort(const struct DBSort& s)
{
   // TODO: sort the data according to the order of columns in 's'
  std::sort(_table.begin() , _table.end() , s);
}

void
DBTable::printCol(size_t c) const
{
   // TODO: to print out a column.
   // - Data are seperated by a space. No trailing space at the end.
   // - Null cells are printed as '.'
  for(size_t i=0;i<nRows();i++){
    if(_table[i][c] == INT_MAX)
      cout<<'.';
    else cout<<_table[i][c];
    if(i<(nRows()-1))
      cout<<' ';
  }
  cout<<endl;
}

void
DBTable::printSummary() const
{
   size_t nr = nRows(), nc = nCols(), nv = 0;
   for (size_t i = 0; i < nr; ++i)
      for (size_t j = 0; j < nc; ++j)
         if (_table[i][j] != INT_MAX) ++nv;
   cout << "(#rows, #cols, #data) = (" << nr << ", " << nc << ", "
        << nv << ")" << endl;
}

