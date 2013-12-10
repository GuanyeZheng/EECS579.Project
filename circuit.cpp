#include "circuit.h"
using namespace std;
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
  string firstLine, secondLine;
  firstLine = line; 
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
      Node* levelNode;
      if (node == NULL){
        levelNode = createNode(words[0]);
      }
      else {
        levelNode = node; 
      }
      //words[1] gate type node type;
      int gateType_value = atoi((words[1].c_str()));
      switch(gateType_value)
      {
        case 1:		levelNode->gate = PI;		levelNode->tt.typeGate= PI;		break;
        case 2:		levelNode->gate = PO;		levelNode->tt.typeGate = PI;		break;
        case 5: levelNode->gate = DFF;    levelNode->tt.typeGate = DFF;   break;//for dff
        case 6:		levelNode->gate = AND;	levelNode->tt.typeGate = AND;		break;
        case 7:		levelNode->gate = NAND;	levelNode->tt.typeGate = NAND;	break;
        case 8:		levelNode->gate = OR;		levelNode->tt.typeGate = OR;		break;
        case 9:		levelNode->gate = NOR;	levelNode->tt.typeGate = NOR;		break;
        case 10:	levelNode->gate = NOT;	levelNode->tt.typeGate = NOT;		break;
        case 11:  levelNode->gate = BUF;  levelNode->tt.typeGate = BUF;   break;
        default : 
            cout << "ERROR: Gate type not recognized" << endl;
      }
      if (levelNode->gate == PI)
      {
        levelNode->type = PRIMARY_INPUT;
				PIs.push_back(levelNode);
      }
      else if (levelNode->gate == PO)
      {
        levelNode->type = PRIMARY_OUTPUT;
				POs.push_back(levelNode);
      }
      else 
      {
        levelNode->type = INTERNAL;
      }
      
      //word[2] level;
      levelNode->level = atoi(words[2].c_str());
      
      //word[3] numFanin;
      levelNode->numFanin =  atoi(words[3].c_str());
			levelNode->tt.numVars = atoi(words[3].c_str());
      //word[4] faninlist...
      int count = 4;

      for (unsigned j = 0; j<levelNode->numFanin;++j)
      {
        Node* node = findNode(words[count+j]);
        Node* node_fanin_c0;
        if (node == NULL) node_fanin_c0 = createNode(words[count+j]);
        else node_fanin_c0 = node;
        
        levelNode->fanin_c0.push_back(node_fanin_c0);
      }
      count = count + levelNode->numFanin;//6

      //words[4+numFanin]
      for (unsigned k = 0; k < levelNode->numFanin; ++k)
      { 
        string name = words[count+k];
        Node* node = findNode(name);
        Node* node_fanin_c1; 
        if (node == NULL)node_fanin_c1 = createNode(name);
        else node_fanin_c1 = node;
        levelNode->fanin_c1.push_back(node_fanin_c1);
      }

      count = count + levelNode->numFanin;//8
      //words[4+numFanin*2]
      levelNode->numFanout =  atoi(words[count].c_str());
      count++;//9
      //words[4+numFanin*2+1,4+numFanin*2+1+numFanout];
      for (unsigned l = 0; l < levelNode->numFanout; ++l)
      {
        string name = words[count+l];
        Node *node = findNode(name);
        Node * node_fanout;
        if (node == NULL) node_fanout = createNode(name);
        else node_fanout = node;
        levelNode->fanout.push_back(node_fanout);
      }
      count = count + levelNode->numFanout;//11
      
      //words[count] oberservabitlity
      levelNode->obs_value = atoi(words[count].c_str());
      count = count + 2;//13
			levelNode->c0 = atoi(words[count].c_str());
			count++;
			levelNode->c1 = atoi(words[count].c_str());
    }
  }
  
  cout << "file " << filename << " successfully read." << endl;
  inFile.close();
  return 0;
}

int Circuit::writeBLIF(const string &filename)
{/*
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
*/
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

int Circuit::clearsig()
{
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    if (it->second != NULL)
      it->second->setValue('X');
  }
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
  //if (!node->getMark())
  //{
    vector<Node*> fanin = node->getFanin();
    string input;
    // recursively compute the nodes it depends on
    for (unsigned int i = 0; i < fanin.size(); i++)
    {
      input.push_back(computeNode(fanin[i]));
    }
    // mark the current node as computed
    //node->setMark();
    node->setValue(node->tt.evaluate(input));
  //}
  return node->getValue();
}

bool Circuit::objective() {
	// if fault location unassigned
	if (fault.first->getValue() == 'X') {
		cur_obj = make_pair(fault.first, invert_val(fault.second));
		cout << "cur_obj = <" << cur_obj.first->getName() << ", " << cur_obj.second << ">" << endl;
		return true;
	}
	
	//TODO: recheck the logic here, especially for the NOT gate
	for (int i = 0; i < d_frontier.size(); i++) {
		Node *d_front = d_frontier[i];
		for (int j = 0; j < d_front->getFanout().size(); j++) {
			Node *prop_gate = d_front->getFanout()[j];
			if (prop_gate->getValue() == 'X') {
				for (int k = 0; k < prop_gate->getFanin().size(); k++) {
					Node *obj_sig = prop_gate->getFanin()[k];
					if (obj_sig->getValue() == 'X') {
						cur_obj = make_pair(obj_sig, prop_gate->non_ctr_val());
						cout << "cur_obj = <" << cur_obj.first->getName() << ", " << cur_obj.second << ">" << endl;    
						return true;
					}
				}
			}
		}
	}

	return false;
}


Node* Circuit::backtrace() {
	return backtrace_help(cur_obj.first, cur_obj.second);
}

Node* Circuit::backtrace_help(Node *cur_node, char cur_val) {
	if (cur_node->getType() == PRIMARY_INPUT) {
		cur_node->setValue(cur_val);
		cur_node->lastdecision = nearest_decision;
		nearest_decision = cur_node;
		cout << "current decision: " << nearest_decision->getName() << " = " << cur_val << endl;
		return cur_node;
	}
	else {
		char next_val;
		gateType cur_gate = cur_node->getGateType();
		//if G is NOR/NOT/NAND, value is opposite
		if (cur_gate == AND || cur_gate == OR) {
			next_val = cur_val;
		}
		else {
			next_val = invert_val(cur_val);
		}
		//find an unassigned input, here I ignore controllbility mentioned
		//in the paper, should be fine, correct?
		//TODO: .lev file has controllability value which can be used
		for (int i = 0; i < cur_node->getFanin().size(); i++) {
			Node *next_node = cur_node->getFanin()[i];
			if (next_node->getValue() == 'X') {				
				return backtrace_help(next_node, next_val);
			}
		}
		//Assume the for loop above must find one unassigned input, or this node		//will not be selected, correct?
	}
	return NULL;
}

char Circuit::invert_val(char val) {
	char inv_val;
	switch(val) {
		case	'0'	: inv_val = '1';	break;
		case	'1'	: inv_val = '0';	break;
		case	'X'	: inv_val = 'X';	break;
		case	'D'	: inv_val = 'B';	break;
		case	'B'	: inv_val = 'D';	break;
		case	'G'	: inv_val = 'J';	break;
		case	'J'	: inv_val = 'G';	break;
		case	'F'	: inv_val = 'L';	break;
		case	'L'	: inv_val = 'F';	break;
		default		:	inv_val = 'X';	break;
	}
	return inv_val;
}

void Circuit::imply(Node *cur_node) {
	//assume new value of a node will not lead a contradiction when imply
	//correct?
	Node *next_node;
	vector<Node*> fanout = cur_node->getFanout();
	int fanout_size = fanout.size();
	for (int i = 0; i < fanout_size; i++) {
		next_node = fanout[i];
		if (next_node->getValue() == 'X') {
			string next_node_input = next_node->getInput();
			char next_node_val = next_node->tt.evaluate(next_node_input);
			if (next_node_val != 'X') {
				if (next_node != fault.first) {
					next_node->setValue(next_node_val);
					nearest_decision->implications.push_back(next_node);
					imply(next_node);
				}
				else {
					if (next_node_val == fault.second) {
						cout << "fault cannot be generated" << endl;
						cout << "Error!!!" << endl;
						exit(1);
					}
					else {
						if (next_node_val == '1') {
							next_node->setValue('D');
							nearest_decision->implications.push_back(next_node);
							imply(next_node);
						}
						else if (next_node_val == '0') {
							next_node->setValue('B');
							nearest_decision->implications.push_back(next_node);
							imply(next_node);
						}
						else {
							cout << "Error!!!" << endl;
							exit(1);
						}
					}
				}
			}
		}
	}
}

bool Circuit::is_fault_found() {
  for (unsigned i = 0; i < POs.size(); i++)
  {
    if (POs[i]->value == 'D' || POs[i]->value == 'B') {
      return true;
		}
  }
	return false;
}

bool Circuit::backtrack() {
	bool success = false;
	while (1) {
		unsigned numimplications = nearest_decision->implications.size();
		for (unsigned i = 0; i < numimplications; i++) {
			nearest_decision->implications[i]->value == 'X';
		}
		nearest_decision->implications.clear();
		if (nearest_decision->isbacktracked) {
			if (nearest_decision->lastdecision != NULL) {
				nearest_decision = nearest_decision->lastdecision;
				continue;
			}
			else {
				break;
			}
		}
		else {
			nearest_decision->value == invert_val(nearest_decision->value);
			nearest_decision->isbacktracked = true;
			success = true;
			break;
		}
	}
	return success;
}
	

bool Circuit::podem(Node *faulty_node, char fault_value) {
	bool is_test_found = false;
	//clearall
	fault = make_pair(faulty_node, fault_value);
	cout << "fault = <" << faulty_node->getName() << ", " << fault_value << ">" << endl; 
	while (1) {
		if(objective()) {
			Node* decision_node = backtrace();
			imply(decision_node);
			if (is_fault_found()) {
				is_test_found = true;
				break;
			}
		}
		else {
			if (backtrack()) {
				imply(nearest_decision);
				if (is_fault_found()) {
				is_test_found = true;
				break;
				}
			}
			else {
				break;
			}
		}
	}
	return is_test_found;
}
			






		
