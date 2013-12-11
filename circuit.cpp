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

vector<Node*> Circuit::getNodes()
{
  vector<Node*> Nodes;
  for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
  {
    Nodes.push_back(it->second);
  }
  return Nodes;
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
    newNode->type = INTERNAL;
    newNode->gate = PI;
    newNode->timeframe = 0;
    newNode->level = 0;
    newNode->numFanin = 0;
    newNode->numFanout = 0;
    newNode->obs_value = 0;
    newNode->c0 = 0;
    newNode->c1 = 0;
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

string Circuit::cal_node_number(int n, int gateNo, string cur_number)
{
  int new_node_number = atoi(cur_number.c_str())+n*gateNo;
  stringstream ss;
  ss << new_node_number;
  return ss.str();
}

string Circuit::calc_psedo_output_name( int gateNo, string cur_number)
{
  int new_node_number = atoi(cur_number.c_str()) - gateNo;
  stringstream ss;
  ss << new_node_number;
  return ss.str();
}
string Circuit::calc_psedo_input_name( int gateNo, string cur_number)
{
  int new_node_number = atoi(cur_number.c_str()) + gateNo;
  stringstream ss;
  ss << new_node_number;
  return ss.str();
}



int Circuit::readBLIF(const string &filename, int n)
{
  cout << "reading file " << filename << "..." << endl;
  ifstream inFile(filename.c_str());
  if (!inFile.good())
  {
    cout << "ERROR in readBLIF() - cannot open "
         << filename << " for reading." << endl;
  }
  
  // clear circuit's contents
  //clear();
	framecount = n+1;
  string line;

  getline(inFile,line);
  string firstLine, secondLine;
  firstLine = line; 
  int num_gate = atoi(firstLine.c_str())-1; //number of gates in the circuit;
	nodeNum = num_gate;
  getline(inFile,line); // to pass the second line, which is of no use.
  
  circuitGate = num_gate;
  
  int count_line = 1;
  //start fetch from the third line;
  while (getline(inFile, line))
  {
     cout<<count_line<<endl;
     count_line++;

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
      //for frame n node_name = words[0]+n*gateNumber;
      string cur_node_name = cal_node_number(n, num_gate, words[0]);
      cout<<"cur_node_name:"<<cur_node_name<<endl;
      Node* node = findNode(cur_node_name);
      Node* levelNode;
      if (node == NULL){
        levelNode = createNode(cur_node_name);
      }
      else {
        levelNode = node; 
      }
      
      levelNode->timeframe = n;
      //cout<<"pass words 0"<<endl;
      //words[1] gate type node type;
      int gateType_value = atoi((words[1].c_str()));
      switch(gateType_value)
      {

        case 1:		levelNode->gate = PI;		levelNode->tt.typeGate= PI;		  break;
        case 2:		levelNode->gate = PO;		levelNode->tt.typeGate = PO;		break;
        case 5:   levelNode->gate = DFF;  levelNode->tt.typeGate = DFF;   break;//for dff
        case 6:		levelNode->gate = AND;	levelNode->tt.typeGate = AND;		break;
        case 7:		levelNode->gate = NAND;	levelNode->tt.typeGate = NAND;	break;
        case 8:		levelNode->gate = OR;		levelNode->tt.typeGate = OR;		break;
        case 9:		levelNode->gate = NOR;	levelNode->tt.typeGate = NOR;		break;
        case 10:	levelNode->gate = NOT;	levelNode->tt.typeGate = NOT;		break;
        case 11:  levelNode->gate = BUF;  levelNode->tt.typeGate = BUF;   break;

        default : 
            cout << "ERROR: Gate type not recognized" << endl;
      }
      if(levelNode->type != PSEUDO_OUTPUT) //if the node is defined as pseudo+output previously
      {
        if (levelNode->gate == PI)
        {
          levelNode->type = PRIMARY_INPUT;
        }
        else if (levelNode->gate == PO)
        {
          levelNode->type = PRIMARY_OUTPUT;
        }
        else if (levelNode->gate == DFF)
        {
          levelNode->type = PSEUDO_INPUT;
        }
        else
        {
          levelNode->type = INTERNAL;
        }
      }
      
      
     //cout<<"pass words [1]"<<endl; 

      //word[2] level;
      levelNode->level = atoi(words[2].c_str());
      
      //word[3] numFanin;
      levelNode->numFanin =  atoi(words[3].c_str());
			levelNode->tt.numVars = atoi(words[3].c_str());
			levelNode->tt.setTruthTable_in();
			levelNode->tt.setTruthTable();



      //word[4] faninlist...
      int count = 4;

      for (unsigned j = 0; j<levelNode->numFanin;++j)
      {
        string node_name = cal_node_number(n, num_gate, words[count+j]);
        node = findNode(node_name);
        Node* node_fanin_c0;
        if (node == NULL) node_fanin_c0 = createNode(node_name);
        else node_fanin_c0 = node;
        levelNode->fanin_c0.push_back(node_fanin_c0);
        //cout<<cur_node_name <<"'s fanin is "<<node_fanin_c0->name<<endl;

      }
      count = count + levelNode->numFanin;//6

      //words[4+numFanin]
      for (unsigned k = 0; k < levelNode->numFanin; ++k)
      { 
        string node_name = cal_node_number(n, num_gate, words[count+k]);
        node = findNode(node_name);
        //if (node == NULL)node_fanin_c1 = createNode(name);
        //else
        levelNode->fanin_c1.push_back(node);
      }
      //if this node is dff, we have to replace it's fanin to previous pseudooutput from last frame; or create a new node if it is the first frame; 
      if (levelNode->gate == DFF)
      {
        (levelNode->fanin_c0.front())->type = PSEUDO_OUTPUT;
      //  cout<<"fanin to dff = "<<levelNode->fanin_c0.front()->name<<endl;
        string psedo_out_name =calc_psedo_output_name(num_gate,levelNode->fanin_c0.front()->name); 
       // cout<<"fanin to dff after cal= "<<psedo_out_name<<endl;
        node = findNode(psedo_out_name);
        Node* node_fanin_c0;
        if (node == NULL)  node_fanin_c0 = createNode(psedo_out_name);
        else node_fanin_c0 = node;
        //cout<<"new fanin to dff is "<<node_fanin_c0->name<<endl;
        node_fanin_c0->type = PSEUDO_OUTPUT;
        node_fanin_c0->timeframe = n-1;
        levelNode->fanin_c0.pop_back();
        levelNode->fanin_c0.push_back(node_fanin_c0);
       // cout<<"fanin_c0 size = "<<levelNode->fanin_c0.size()<<endl;
       // cout<<"fanin_c0 front = "<<levelNode->fanin_c0.front()->name<<endl;
        levelNode->fanin_c1.pop_back();
        levelNode->fanin_c1.push_back(node_fanin_c0);
      }    
     // cout<<"number of fanin"<<levelNode->numFanin<<endl;
      count = count + levelNode->numFanin;//8
      //words[4+numFanin*2]
      //cout<<"count = "<<count<<endl;
      levelNode->numFanout =  atoi(words[count].c_str());
     // cout<<cur_node_name<<"'s number_of_fanout = "<<levelNode->numFanout<<endl;
      count++;//9
      //words[4+numFanin*2+1,4+numFanin*2+1+numFanout];
      for (unsigned l = 0; l < levelNode->numFanout; ++l)
      {
       // cout<<l<<endl;  
        string words_l = words[count+l];
        string node_name = cal_node_number(n,num_gate, words_l);
      //  cout<<cur_node_name<<"'s fanout l"<<l<<" is"<< node_name<<endl;
        node = findNode(node_name);
        Node * node_fanout;
        if (node == NULL) node_fanout = createNode(node_name);
        else node_fanout = node;
        levelNode->fanout.push_back(node_fanout);
      }
      
      if (levelNode->type == PSEUDO_OUTPUT)
      {
        //cout<<"leveNode is a pseudo_output"<<endl;
        for (unsigned l = 0; l < levelNode->numFanout; ++l)
        {
          

          if(levelNode->fanout[l]->gate == DFF)
          {
            //cout<<"levelnode fanout [l] "<<l<< "'s gate is a dff"<<endl;
            string fout_name = levelNode->fanout[l]->name;
            string node_name = calc_psedo_input_name(num_gate,fout_name);
            //cout<<"this fantou l replaced" <<fout_name<<" by<<"<<node_name<<endl;
            node = findNode(node_name);
            Node * node_fanout;
            if (node == NULL) node_fanout = createNode(node_name);
            else node_fanout = node;
            //node_fanout->fanin_c0.push_back(levelNode);
            node_fanout->type = PSEUDO_INPUT;
            //node_fanout->level = levelNode->fanout[l]->level;
            node_fanout->gate = DFF;
            //node_fanout->numFanin =1;
            //node_fanout->fanin_c0.push_back(levelNode);
            //node_fanout->c0 = 0;
            //node_fanout->c1 = 0;
            //node_fanout->obs_value = 0;
            //node_fanout->fanin_c1.push_back(levelNode);
            //node_fanout->numFanout = 0;
            //node_fanout->timeframe = n+1;
            levelNode->fanout[l]=(node_fanout);
          }
        }

      }
      //cout<<"pass fanout"<<endl;

      count = count + levelNode->numFanout;//11
      
      //words[count] oberservabitlity
      levelNode->obs_value = atoi(words[count].c_str());
      count = count + 2;//13a
      
			levelNode->c0 = atoi(words[count].c_str());
      //cout<<"pass here"<<endl;
			count++;
			levelNode->c1 = atoi(words[count].c_str());

      if (n == 0)
      {
        if (levelNode->gate == DFF)
        {
          levelNode->type = PRIMARY_INPUT;
        }
      }
    }
      /*
      cout << "Nodes:" << endl;
      for (mapIter it = nodeMap.begin(); it != nodeMap.end(); it++)
      {
        it->second->print();
        cout << endl;
      } */
  }

  cout << "file " << filename << " successflly read." << endl;
  //cout<<" find node 3"<<findNode("3")->name;
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
    if (it->second != NULL) {
      it->second->setValue('X');
			it->second->fault_target = false;
		}
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


int Circuit::add_timeframe(const string &filename,int n) //n:frame number;
{
  return readBLIF(filename,n);
}

int Circuit::site_fault(string node_name, char stuck_value, int cur_frame)
{

  cout<<"fautl node is "<<node_name;
  Node* node = findNode(node_name);
  if(node == NULL)
  {
    cout<<"the node does not exits"<<endl;
  }else
  {
    for (int i = 0; i <cur_frame;++i)
    {
        string node_name_s = cal_node_number(i,circuitGate, node_name);
        node = findNode(node_name_s);
        if (node == NULL)
        {
          cout<<"we have a problem finding this node in the circuit"<<node_name_s<<endl;
        }
        else {
          node->sal_value = stuck_value;
          node->fault_target = true;
        }
    }
  }
}


bool Circuit::objective() {
	// if fault location unassigned
	if (fault.first->getValue() == 'X') {
		cur_obj = make_pair(fault.first, invert_val(fault.second));
		cout << "cur_obj = <" << cur_obj.first->getName() << ", " << cur_obj.second << ">" << endl;
		return true;
	}
	bool is_d_frontier = false;	
	//TODO: recheck the logic here, especially for the NOT gate
	//TODO: choose d_frontier according to level
	//TODO: the way I move out d_frontiers can be improved
	for (mapIter it = d_frontier.begin(); it != d_frontier.end(); it++) {
		is_d_frontier = false;
		cout << "looking for d_frontiers" << endl;
		Node *d_front = it->second;
		cout << "current d_frontier: " << d_front->getName() << endl;
		for (int j = 0; j < d_front->getFanout().size(); j++) {
			cout << "checkpoint1" << endl;
			Node *prop_gate = d_front->getFanout()[j];
			if (prop_gate->getValue() == 'X' || prop_gate->getValue() == 'G' || prop_gate->getValue() == 'J' || prop_gate->getValue() == 'F' || prop_gate->getValue() == 'L') {
				cout << "checkpoint2" << endl;
				is_d_frontier = true;
				for (int k = 0; k < prop_gate->getFanin().size(); k++) {
					cout << "checkpoint3" << endl;
					Node *obj_sig = prop_gate->getFanin()[k];
					cout << obj_sig->getValue() << endl;
					if (obj_sig->getValue() == 'X') {
						cout << "checkpoint4" << endl;
						cur_obj = make_pair(obj_sig, prop_gate->non_ctr_val());
						cout << "cur_obj = <" << cur_obj.first->getName() << ", " << cur_obj.second << ">" << endl;    
						return true;
					}
				}
			}
		}
		if (!is_d_frontier) {
			d_frontier.erase(d_front->getName());
			cout << "check" << endl;
		}
	}
	cout << "chec!!!!!!!!!!" << endl;
	return false;
}


Node* Circuit::backtrace() {
	return backtrace_help(cur_obj.first, cur_obj.second);
}

Node* Circuit::backtrace_help(Node *cur_node, char cur_val) {
	if (cur_node->getType() == PRIMARY_INPUT) {
		if (!cur_node->fault_target) {
			cur_node->setValue(cur_val);
		}
		else {
			if (cur_val == '0') {
				cur_node->setValue('B');
				if (d_frontier.find(cur_node->getName()) == d_frontier.end()) {
					d_frontier[cur_node->getName()] = cur_node;
				}
			}
			else if (cur_val == '1') {
				cur_node->setValue('D');
				if (d_frontier.find(cur_node->getName()) == d_frontier.end()) {
					d_frontier[cur_node->getName()] = cur_node;
				}
			}
			else { 
				cout << "error in backtrace helper" << endl;
			}
		}
		cur_node->lastdecision = nearest_decision;
		nearest_decision = cur_node;
		cout << "current decision: " << nearest_decision->getName() << " = " << cur_node->getValue() << endl;
		return cur_node;
	}
	else {
		char next_val;
		gateType cur_gate = cur_node->getGateType();
		//if G is NOR/NOT/NAND, value is opposite
		if (cur_gate == AND || cur_gate == OR || cur_gate == BUF || cur_gate == PO) {
			next_val = cur_val;
		}
		else {
			cout << "inverval?" << endl;
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
	bool is_d_frontier = false;
	for (int i = 0; i < fanout_size; i++) {
		next_node = fanout[i];
			if ((next_node->getValue() == 'X' || next_node->getValue() == 'G' || next_node->getValue() == 'J' || next_node->getValue() == 'F' || next_node->getValue() == 'L') && (atoi(next_node->getName().c_str()) <= framecount*nodeNum)) {
			string next_node_input = next_node->getInput();
			cout << "next_node_input: " << next_node_input << " node name is " << next_node->getName() << endl;
			char next_node_val = next_node->tt.evaluate(next_node_input);
			cout << "next_node_val: " << next_node_val << endl;
			if (next_node_val != 'X') {
				if (!next_node->fault_target) {
					next_node->setValue(next_node_val);
					nearest_decision->implications.push_back(next_node);
					imply(next_node);
				}
				else {
					if (next_node_val == next_node->sal_value) {
						cout << "fault cannot be generated" << endl;
						cout << "Error!!!" << endl;
						exit(1);
					}
					else {
						cout << "here?" << endl;
						cout << next_node_val << endl;
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
			} // if (next_node_val != 'X') 
			else {
				//TODO: may add additional d_frontiers, but should be fine, check!!!
				is_d_frontier = true;
			}
				
		}
	}
	if (is_d_frontier && (cur_node->getValue() == 'D' || cur_node->getValue() == 'B')) {
		if (d_frontier.find(cur_node->getName()) == d_frontier.end()) {
			d_frontier[cur_node->getName()] = cur_node;
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
		cout << "now in backtrack" << endl;
		cout << "nearest decision is " << nearest_decision->getName() << "and isbacktracked = " << nearest_decision->isbacktracked << endl;
		unsigned numimplications = nearest_decision->implications.size();
		for (unsigned i = 0; i < numimplications; i++) {
			//TODO: not necessarity set to 'X', should set back to the value before
			nearest_decision->implications[i]->value == 'X';
		}
		nearest_decision->implications.clear();
		if (nearest_decision->isbacktracked) {
			cout << "c1" << endl;
			if (nearest_decision->lastdecision != NULL) {
				cout << "c2" << endl;
				nearest_decision = nearest_decision->lastdecision;
				continue;
			}
			else {
				cout << "c3" << endl;
				break;
			}
		}
		else {
			cout << "c4" << endl;
			cout << "backtrack succ" << endl;
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


		
