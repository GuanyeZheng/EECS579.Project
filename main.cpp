#include "circuit.h"
#include <math.h>

#include <utility>

using namespace std;

#define MAXFRAME 10

void usage(const char* exename);

int main(int argc, char **argv)
{
  // parsing inputs
  if (argc < 2)
  {
    usage(argv[0]);
  }
  
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i] == string("-h") || argv[i] == string("-help"))
    {
      usage(argv[0]);
    }
    /*else if (argv[i] == string("-buildsc"))
    {
      if (i + 1 < argc)
      {
        string inFilename = string(argvp
      }
    }*/
    else if (argv[i] == string("-build"))
    {
      if (i + 1 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename,0);
        //c.readBLIF(inFilename,1);

        // your code here
        // print the result of topologically sorted nodes of the circuit, support functions implemented in circuit.cpp
        c.print();
      }
      else
      {
        cout << "option -build requires an additional argument." << endl;
        usage(argv[0]);
      }
    }
		else if (argv[i] == string("-gentest"))
    {
      if (i + 1 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename,0);
        // your code here
        // print the result of topologically sorted nodes of the circuit, support functions implemented in circuit.cpp
				/*
				vector<Node*> Nodes = c.getNodes();
				int framecount;
				for (int i = 0; i < Nodes.size(); i++) {
					Node *faulty_node = Nodes[i];
					framecount = 0;
					while 
					if (c.podem(faulty_node, '0')) {
					cout << "test found" << endl;
					vector<Node*> test = c.getPIs();
					for (i = 0; i < test.size(); i++) {
						cout << "node: " << test[i]->getName() << " = " << test[i]->getValue() << endl;
					}
				}
				else {
					cout << "test failed" << endl;
				}
				*/
				Node* faulty_node = c.findNode();
				int framecount = 1;
				bool test_found = false;
				char fault_val = '0';
				while (framecount <= MAXFRAME && !test_found) {
					c.clearsig();
					c.setfault(faulty_node, fault_val);
					test_found = c.podem(faulty_node, fault_val);
					if (test_found) {
						cout << "test found with " << framecount << " frames" << endl;
						vector<Node*> test = c.getPIs();
						for (i = 0; i < test.size(); i++) {
							cout << "node: " << test[i]->getName() << " = " << test[i]->getValue() << endl;
						}
					}
					else {
						c.addtimeframe(inFilename, framecount);
						framecount++;
					}
				}


        //c.print();

      }
      else
      {
        cout << "option -testobj requires an additional argument." << endl;
        usage(argv[0]);
      }
    }
    else if (argv[i] == string("-simulate"))
    {
      if (i + 2 < argc)
      {
        string inFilename = string(argv[++i]);
        Circuit c(inFilename,0);
        string inputFile = string(argv[++i]);
        // your code here
        // support functions implemented in circuit.cpp and truthtable.cpp
        // read the inputs in the inputFile into the circuit
        c.readInput(inputFile);
        // compute and print the outputs
        c.compute();
      } 
      else
      {
        cout << "option -simulate requires two additional arguments." << endl;
        usage(argv[0]);
      }
    }
    
  }
  
  return 0;
}

void usage(const char* exename)
{
  cout << "Usage: " << exename << " <options> " << endl;
  cout << "-h or -help                     prints out this help message. " << endl;
  cout << "-topoSort <inFile>              prints a topological ordering of the circuit in <inFile>. " << endl;
  cout << "-simulate <inFile> <inputs>     simulates the circuit in <inFile> with the inputs in <inputs>." << endl;
  cout << endl;
  
  exit(0);
}

