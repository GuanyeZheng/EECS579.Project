#include "circuit.h"

/******************Circuit Implementation********************/

Circuit::~Circuit()
{
  clear();
}

vector<Node*> Circuit::getPIs()
{
  vector<Node*> PIs;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_INPUT)
      PIs.push_back(it->second);
  }
  return PIs;
}

vector<Node*> Circuit::getPOs()
{
  vector<Node*> POs;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      POs.push_back(it->second);
  }
  return POs;
}

int Circuit::setPI(const string &input)
{
  Node *in = findNode(input);
  assert(in != NULL);
  
  in->type = PRIMARY_INPUT;
  return 0;
}

int Circuit::setPO(const string &output)
{
  Node *out = findNode(output);
  assert(out != NULL);
  
  out->type = PRIMARY_OUTPUT;
  return 0;
}

int Circuit::setPIs(const string &input, unsigned int startBit, unsigned int endBit)
{
  for (unsigned i = startBit; i < endBit; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    string name = input + "[" + sstr.str() + "]";
    assert(findNode(name) != NULL);
    setPI(name);
  }
  return 0;
}

int Circuit::setPOs(const string &output, unsigned int startBit, unsigned int endBit)
{
  for (unsigned i = startBit; i < endBit; ++i)
  {
    stringstream sstr;
    sstr << i;
    
    string name = output + "[" + sstr.str() + "]";
    assert(findNode(name) != NULL);
    setPO(name);
  }
  return 0;
}

Node* Circuit::findNode(const string &nodeName)
{
  mapIter it = nodeMap.find(nodeName);
  return (it != nodeMap.end() ? it->second : NULL);
}

Node* Circuit::createNode(const string &nodeName)
{
  Node* newNode = findNode(nodeName);
  if (newNode == NULL)
  {
    newNode = new Node(nodeName);
    nodeMap.insert(make_pair(nodeName, newNode));
  }
  
  return newNode;
}

int Circuit::print()
{
  cout << "Circuit Name: " << name << " contains " << nodeMap.size() << " nodes." << endl;
  cout << "Primary Inputs: ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_INPUT)
      cout << it->second->name << " ";
  }
  cout << endl;
  cout << "Primary Outputs: ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      cout << it->second->name << " ";
  }
  cout << endl;
  
  cout << "Nodes:" << endl;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    it->second->print();
    cout << endl;
  }

  return 0;
}

int Circuit::readBLIF(const string &filename)
{
  cout << "reading file " << filename << "..." << endl;
  ifstream inFile(filename.c_str());
  if (!inFile.good())
  {
    cout << "ERROR in readBLIF() - cannot open "
         << filename << " for reading." << endl;
  }
  
  // clear circuit's contents
  clear();
  
  string line;

  getline(inFile,line);
  string fistLine, secondLine;
  line >> firstLine; 
  int num_gate = atoi(firstLine.c_str()); //number of gates in the circuit;
  getline(inFile,line); // to pass the second line, which is of no use.

  //start fetch from the third line;
  while (getline(inFile, line))
  {
//    cout << "processing line: " << line << endl;
    stringstream sstr;
    // skip empty lines
    if (line.length() == 0) continue;
    
    sstr << line;
    string word;
    vector<string> words; //modified to a vector of string type;
    
    // parse each line
    while (sstr >> word)
    {
      words.push_back(word);
    }
    
    // parse non-empty lines only
    if (!words.empty())
    {
      //words[0] node name
      Node* node = findNode(words[0]);
      if (node == !NULL){
        Node* levelNode = createNode(words[0]);
      }
      else {
        Node* levelNode = node; 
      }
      //words[1] gate type node type;
      levelNode.type =  INTERNAL;//  is this correct?
      switch(words[1])
      {
        case "1": levelNode.type = PRIMARY_INPUT; break;
        case "2": levelNode.type = PRIMARY_OUTPUT; break;
        case "6": levelNode.gate = "AND"; break;
        case "6": levelNode.gate = "AND"; break;
        case "7": levelNode.gate = "NAND"; break;
        case "8": levelNode.gate = "OR"; break;
        case "9": levelNode.gate = "NOR"; break;
        case "10": levelNode.gate = "NOT"; break;
      }

      
      //word[2] level;
      levelNode.level = atoi(words[2].c_str());
      
      //word[3] numFanin;
      levelNode.numfanin =  atoi(words[3].c_str());
      //word[4] faninlist...
      int count = 4;
      int j;
      for (j = 0; j<levelNode.numFanin;++j)
      {
        Node* node = findNode(words[count+j]);
        if (node == NULL) Node* node_fanin_c0 = createNode(words[count+j]);
        else Node* node_fanin_c0 = node;
        
        levelNode.fanin_c0.push_back(node_fanin_c0);
      }
      count = count + j;//6

      //words[4+numFanin]
      for (j = 0; j<levelNode.numFanin; ++j)
      { 
        string name = words[count+j];
        Node*node = findNode(name);
        if (node == NULL) Node * node_fanin_c1 = createNode(name);
        else Node* node_fanin_c1 = node;
        levelNode.fanin_c1.push_back(node_fanin_c1);
      }

      count = count + j;//8
      //words[4+numFanin*2]
      levelNode.numFanout =  atoi(words[count].c_str());
      count = count + 1;//9
      //words[4+numFanin*2+1,4+numFanin*2+1+numFanout];
      for (j = 0; j< levelNode.numFanout; ++j)
      {
        string name = words[count+j];
        Node*node = findNode(name);
        if (node == NULL) Node * node_fanout = createNode(name);
        else Node* node_fanout = node;
        levelNode.fanout.push_back(node_fanout);
      }
      count = count + j;//11
      
      //words[count] oberservabitlity
      levelNode.obs_value = atoi(words[count].c_str());
      count = count + 2;//13
      for (j = 0; j < levelNode.numFanin; ++j)
      {
        levelNode.control_value.push_back(atoi(words[count+j].c_str()));
      }
    }
  }
  
  cout << "file " << filename << " successfully read." << endl;
  inFile.close();
  return 0;
}

int Circuit::writeBLIF(const string &filename)
{
  ofstream outFile(filename.c_str());
  if (!outFile.good())
  {
    cout << "ERROR in writeBLIF() - cannot open "
         << filename << " for writing." << endl;
    return -1;
  }
  
  // print model name
  outFile << ".model " << name << endl << endl;
  
  // print primary inputs
  outFile << ".inputs ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_INPUT)
      outFile << it->first << " ";
  }
  outFile << endl << endl;
  
  // print primary outputs
  outFile << ".outputs ";
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second->type == PRIMARY_OUTPUT)
      outFile << it->first << " ";
  }
  outFile << endl << endl;
  
  // print nodes
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    // must explicitly write 0 node
    if (it->second->type == ZERO_NODE)
    {
      outFile << ".names " << it->second->name << endl;
      outFile << endl;
    }
    // must explicitly write 1 node
    else if (it->second->type == ONE_NODE)
    {
      outFile << ".names " << it->second->name << endl;
      outFile << "1" << endl << endl;
    }
    else if (it->second->type != PRIMARY_INPUT)
    {
      outFile << ".names ";
      for (unsigned i = 0; i < it->second->getNumFanin(); ++i)
        outFile << it->second->getFanin()[i]->name << " ";
      outFile << it->second->name << endl;
      
      const TruthTable &theTT = it->second->tt;
      for (unsigned i = 0; i < theTT.logic.size(); ++i)
      {
        for (unsigned j = 0; j < theTT.logic[i].size(); ++j)
        {
          switch(theTT.logic[i][j])
          {
            case ZERO: outFile << "0"; break;
            case ONE:  outFile << "1"; break;
            case DC:   outFile << "-"; break;
          }
        }
        outFile << " 1" << endl;
      }
      outFile << endl;
    }
  }
  
  outFile << ".end" << endl;
  outFile.close();
  
  cout << "File " << filename << " successfully written." << endl;
  
  return 0;
}

int Circuit::clear()
{
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second != NULL)
      delete it->second;
  }
  nodeMap.clear();
  return 0;
}

int Circuit::printSortNode()
{
  topoSort();
  // print sorted nodes
  cout << "*** Topological order:" << endl;
  if (sortNode.size() != 0)
  {
    string curNodeName = sortNode[0]->getName();
    cout << curNodeName;
  }
  for (unsigned int j = 1; j < sortNode.size(); j++)
  {
    string curNodeName = sortNode[j]->getName();
    cout << " " << curNodeName;
  }
  cout << endl;
  return 0;
} 

int Circuit::visit(Node* node)
{
  // if not visited before
  if (!node->getMark())
  {
    vector<Node*> fanin = node->getFanin();
    // recursively visit the fanin nodes
    for (unsigned int i = 0; i < fanin.size(); i++)
    {
      visit(fanin[i]);
    }
    // mark the current node and put it into the result vector, 
    // all nodes it depends on must already be in the result vector
    node->setMark();
    sortNode.push_back(node);
  }
  return 0;
} 

int Circuit::topoSort()
{
  // clear previous result, make sure begin with empty result vector
  sortNode.clear();
  // reset marks of all nodes to be unmarked
  for (mapIter mit = nodeMap.begin(); mit != nodeMap.end(); mit++)
  {
    mit->second->resetMark();
  }
  // get all POs and start recursion with them
  vector<Node*> POs = getPOs();
  for (unsigned int i = 0; i < POs.size(); i++)
  {
    visit(POs[i]);
  }
  return 0;
}

int Circuit::readInput(const string &filename)
{
  string nodeName;
  char value;

  ifstream inFile(filename.c_str());
  if (!inFile.good())
  {
    cout << "ERROR in readInput() - cannot open "
         << filename << " for reading." << endl;
  }

  string line;

  // reset marks of all nodes to be unmarked
  for (mapIter mit = nodeMap.begin(); mit != nodeMap.end(); mit++)
  {
    mit->second->resetMark();
  }

  while (getline(inFile, line))
  {
    stringstream sstr;
    // skip empty lines
    if (line.length() == 0) continue;

    // no error checking    
    sstr << line;
    sstr >> nodeName;
    sstr >> value;
    // all PIs are marked as computed 
    Node* inNode = findNode(nodeName);
    inNode->setMark();
    inNode->setValue(value);
  }
  inFile.close();

  return 0;
}
  
int Circuit::compute()
{
  cout << "*** Outputs:" << endl;
  vector<Node*> POs = getPOs();
  // start the recursions with POs and print out the result
  if (POs.size() != 0)
  {
    cout << POs[0]->getName() << " = " << computeNode(POs[0]) ;
  }
  for (unsigned int i = 1; i < POs.size(); i++)
  {
    cout << ", " << POs[i]->getName() << " = " << computeNode(POs[i]);
  }
  cout << endl;
  return 0;
}

char Circuit::computeNode(Node* node)
{
  // only compute when the node is not computed before
  if (!node->getMark())
  {
    vector<Node*> fanin = node->getFanin();
    string input;
    // recursively compute the nodes it depends on
    for (unsigned int i = 0; i < fanin.size(); i++)
    {
      input.push_back(computeNode(fanin[i]));
    }
    // mark the current node as computed
    node->setMark();
    node->setValue(node->tt.evaluate(input));
  }
  return node->getValue();
}

bool Circuit::objective() {
	// if fault location unassigned
	if (fault.first->getValue() = 'u') {
		cur_obj = fault;
		return true;
	}
	
	for (int i = 0; i < d_frontier.size(); i++) {
		Node *d_front = d_frontier[i];
		for (int j = 0; j < d_front->getFanout.size(); j++) {
			Node *prop_gate = d_front->getFanout[j];
			if (prop_gate->getValue() = 'u') {
				for (int k = 0; k < prop_gate->getFanin.size(); k++) {
					Node *obj_sig = prop_gate->getFanin[k];
					if (obj_sig->getValue = 'u') {
						cur_obj = (obj_sig, prop_gate->non_ctr_val());
						return true;
					}
				}
			}
		}
	}

	return false;
}
		
