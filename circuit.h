#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <stdlib.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>
#include <stack>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#include "node.h"

typedef map<string,Node*>::iterator mapIter;

class Circuit
{
  private:
    map<string,Node*> nodeMap;
    string name;
    vector<Node*> sortNode;
		pair<Node*, char> fault;
		pair<Node*, char> cur_obj;

    int circuitGate;//in one frame;

    		Node* nearest_decision;
    map<string, Node*> d_frontier;
		vector<Node*> PIs;
		vector<Node*> POs;
    vector<Node*> dff_node; //map of dff;
  public:
    // constructors
    Circuit() {};
    
    Circuit(const string &filename,int n)
    { clear(); 
      if (readBLIF(filename,n)) cout << "error in reading " << filename << endl; }
    
    // destructor
    ~Circuit();
    
    // get number of nodes in the circuit
    unsigned getNumNodes() { return nodeMap.size(); }
    
    // get and set the name of the circuit
    string getName() { return name; }
    int setName(const string &modelName) { name = modelName; return 0; }
    
    // get primary inputs and outputs
    vector<Node*> getPIs();
    vector<Node*> getPOs();
    
    // sets the node of <string> as primary input and output
    int setPI(const string &input);
    int setPO(const string &output);
    
    // set (assign) nodes in specific format as primary inputs and outputs from [startBit,endBit)
    // for a given string <string> and numBits, format is <string>[startBit] ... <string[endBit-1]
    int setPIs(const string &input, unsigned int startBit, unsigned int endBit);
    int setPOs(const string &output, unsigned int startBit, unsigned int endBit);
    
    // check to see if a node is there
    Node* findNode(const string &nodeName);
    
    // create an empty node - will return NULL if node already exists
    Node* createNode(const string &nodeName);
    
    // prints out the contents of the circuit
    int print();
    
    // reads in circuit from BLIF format
    int readBLIF(const string &filename,int n);//n->framenumber;
    
    // writes circuit in BLIF format
    int writeBLIF(const string &filename);
    
    // erases the contents of the entire circuit
    int clear();

		int clearsig();

    // print the topologically sorted nodes of the circuit
    int printSortNode();    

    // topologically sort the nodes of the circuit
    int topoSort();
  
    // Help function to add the sorted node to the result vector recursively
    int visit(Node* node);
 
    // read the inputs into the circuit
    int readInput(const string &filename);
    
    // compute the outputs according the current input
    int compute();

    // Help function to compute the node recursively
    char computeNode(Node* node);

		// add for 579
		// find an objective
		bool objective();
   
		// add for 579
		// backtrace current objective to find next PI to assign a value
		Node* backtrace();
		Node* backtrace_help(Node *cur_node, char cur_val);

		// add for 579
		// find the reverse of a val
		char invert_val(char val);

		// add for 579
		void imply(Node *cur_node);

		bool is_fault_found();

		bool backtrack(); 
    
    
    string cal_node_number(int n, int gateNo, string cur_number);
    string calc_psedo_input_name( int gateNo, string cur_number);
    string calc_psedo_output_name( int gateNo, string cur_number);

		bool podem(Node *faulty_node, char fault_value);
    // expand one timeframe forward;
    int add_timeframe(const string &filename, int n);  

    int site_fault(string node_name, char stuck_value, int cur_frame);

};

#endif

