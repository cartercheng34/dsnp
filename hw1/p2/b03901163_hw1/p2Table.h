#ifndef P2_TABLE_H
#define P2_TABLE_H

#include <vector>
#include <string>

using namespace std;

class Row
{
public:
   Row(int);
   Row(const Row&);
   const int operator[] (size_t i) const; // TODO
   int& operator[] (size_t i); // TODO
   
private:
   int  *_data;
   int col_num;
};

class Table
{
public:
   const Row& operator[] (size_t i) const;
   Row& operator[] (size_t i);

   bool read(const string&,int&,int&);
   void print(int,int);
   void add(int,int,string);
   double ave(int,int);
   int sum(int,int);
   int max(int,int);
   int min(int,int);
   int count(int,int);
   int col;
   int row;
private:
   vector<Row>  _rows;
};

#endif // P2_TABLE_H
