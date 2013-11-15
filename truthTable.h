#ifndef __TRUTHTABLE_H__
#define __TRUTHTABLE_H__

#include <vector>
#include <string>
#include <iostream>
/*
using std::vector;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
*/
using namespace std;
class Node;
class Circuit;

//Defne possible values inside truth table
enum truthType {ZERO, ONE, DC, D, D_bar, G0,G1,F0,F1};  //add for 579
enum gateType {AND, OR, NOT, NAND, NOR};
class TruthTable
{
  friend class Node;
  friend class Circuit;
  
  private:
    // number of columns per entry
    unsigned numVars;               //In 579, numVars is the number of inputs. 
    gateType typeGate;              //in 579, it indicates the gate type. 
    vector<string> truthTable_in;       
    vector<char>   truthTable_out;
    /*
    // stores the truth table logic
    vector<vector<truthType> > logic;
    */
  public:
    // constructors
    TruthTable():numVars(0) {} 
    
    TruthTable(unsigned nV): numVars(nV) {}
    
    //TruthTable(unsigned nV, gateType g, const vector<string> &t_in, const vector<string> &t_out ): numVars(0),typeGate(g),truthTable_in(t_in),truthTable_out(t_out) {} 
    
    // destructor
    ~TruthTable() {};
    
    // sets the number of variables
    int setNumVars(unsigned nV);
   
    //set the gateType;
    int setGateType(gateType g_t); 
    char findOutput(string input);//just calculate 2-input gate output;

    bool setTruthTable_in();
    bool setTruthTable();

    /*
    // adds an emtry (row) to the truth table
    int addEntry(const string &newEntry);
    
    // returns the number of entries (rows)
    unsigned getNumEntries();
    */
    // returns number of variables (columns)
    unsigned getNumVars();
    
    // prints the contents of the table
    //int print();
    
    // clears all entries
    int clear();

 // evaluate the result of a node by comparing the input to the truth table entry by entry
    char evaluate(const string &input);
    char evaluate_helper(const string &input);//helper function for evaluate ;

};

#endif

