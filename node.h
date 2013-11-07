#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "truthTable.h"

// define node type
enum nodeType {PRIMARY_INPUT, PRIMARY_OUTPUT, INTERNAL, ZERO_NODE, ONE_NODE};
enum gateType {AND, OR, NOT};

// define value type
class Circuit;

class Node
{
  friend class Circuit;
  
  private:
    string name;
    nodeType type;
		gateType gate;
    vector<Node*> fanin;
		// add for 579
		vector<Node*> fanout;
    TruthTable tt;
    // add two private variables in support of topoSort and simulate
    bool marked;
    char value;
    
  public:
    // constructors
    Node():type(INTERNAL) {}
    
    Node(const string &nodeName):name(nodeName), type(INTERNAL) {}
    
    // destructor
    ~Node() {};
    
    // returns and sets the name of the node
    string getName() { return name; }
    int setName(const string &n) { name = n; return 0; }
    
    // returns and sets the type of the node
    nodeType getType() { return type; }
    int setType(nodeType t) { type = t; return 0; }
    
    // returns the vector of fanin nodes
    vector<Node*> getFanin() { return fanin; }

		// add for 579
		// returns the vector of fainout nodes
		vector<Node*> getFanout() { return fanout; }
    
    // adds a fanin node
    int addFanin(Node* &inNode) { fanin.push_back(inNode); return 0; }

		// add for 579
		// adds a fanout node
		int addFanout(Node* &inNode) { fanout.push_back(inNode); return 0; }
    
    // returns the number of fanin nodes (variables)
    unsigned getNumFanin() { return fanin.size(); }

		// add for 579
		// returns the number of fanout nodes (variables)
		unsigned getNumFanout() { return fanout.size(); }
    
    // clear functions
    int clearName() { name = ""; return 0; }
    int clearFanin() { fanin.clear(); return 0; }
		// add for 579
		int clearFanout() { fanout.clear(); return 0; }
    int clearTT() { tt.clear(); return 0; }
    int clear() { name = ""; clearFanin(); clearFanout(); clearTT(); return 0; }
    
    // prints node information
    int print()
    {
      cout << "Name: " << name << " [TYPE = ";
      switch(type)
      {
        case PRIMARY_INPUT : cout << "PRIMARY_INPUT";  break;
        case PRIMARY_OUTPUT: cout << "PRIMARY_OUTPUT"; break;
        case INTERNAL      : cout << "INTERNAL";       break;
        case ZERO_NODE     : cout << "ZERO_NODE";      break;
        case ONE_NODE      : cout << "ONE_NODE";       break;
      }
      cout << "]" << endl;
      
      if (type == PRIMARY_OUTPUT || type == INTERNAL)
      {
        cout << "Fanin nodes: ";
        for (unsigned i = 0; i < fanin.size(); ++i)
          cout << fanin[i]->name << " ";
        cout << endl;
        tt.print();
      }

			// add for 579
			if (type == PRIMARY_INPUT || type == INTERNAL)
			{
				cout << "Fanout nodes: ";
				for (unsigned i = 0; i < fanout.size(); ++i)
					cout << fanout[i]->name << " ";
				cout << endl;
			}
      
      return 0;
    }
    
    // get, set and reset function of mark, which indicates if a node has been visited (when topoSort) or computed (when simulate)
    bool getMark() { return marked; }
    int setMark() { marked = true; return 0; }
    int resetMark() { marked = false; return 0; }

    // get and set function of value, which indicates the value of a node (1 or 0)
    char getValue() { return value; }
    int setValue(char inVal) { value = inVal; return 0; }

		// add for 579
		// returns a non controlling value for the gate
		char non_ctr_val() {
			char value;
			switch(gate) {
				case	AND	: char = '1';	break;
				case	OR	:	char = '0';	break;
				default		:	char = '0';	break;
			}
			return value;
		}			
};

#endif

