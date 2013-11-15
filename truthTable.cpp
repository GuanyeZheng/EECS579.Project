#include "truthTable.h"

using namespace std;



const char TruthToChar[9] = {'0', '1', 'X','D','B','G','J','F','L'}; 
                             //0:0/0
                             //1:1/1
                             //X:x/x->DC
                             //D:1/0->D
                             //B:0/1->D_bar
                             //G:0/X->G0
                             //J:1/X->G1
                             //F:X/0->F0
                             //L:X/1->F1

int TruthTable::setNumVars(unsigned nV)
{
  numVars = nV;
  return 0;
}

int TruthTable::setGateType(gateType g_t)
{ 
  typeGate = g_t;
  return 0;
}


bool TruthTable::setTruthTable_in(){
  if (typeGate == NOT){
    truthTable_in.push_back("0");
    truthTable_in.push_back("1");
    truthTable_in.push_back("X");
    truthTable_in.push_back("D");
    truthTable_in.push_back("B");
    truthTable_in.push_back("G");
    truthTable_in.push_back("J");
    truthTable_in.push_back("F");
    truthTable_in.push_back("L");
  }
  else{
    truthTable_in.push_back("00");
    truthTable_in.push_back("01");
    truthTable_in.push_back("0X");
    truthTable_in.push_back("0D");
    truthTable_in.push_back("0B");
    truthTable_in.push_back("0G");
    truthTable_in.push_back("0J");
    truthTable_in.push_back("0F");
    truthTable_in.push_back("0L");
    truthTable_in.push_back("11");
    truthTable_in.push_back("1X");
    truthTable_in.push_back("1D");
    truthTable_in.push_back("1B");
    truthTable_in.push_back("1G");
    truthTable_in.push_back("1J");
    truthTable_in.push_back("1F");
    truthTable_in.push_back("1L");
    truthTable_in.push_back("XX");
    truthTable_in.push_back("XD");
    truthTable_in.push_back("XB");
    truthTable_in.push_back("XG");
    truthTable_in.push_back("XJ");
    truthTable_in.push_back("XF");
    truthTable_in.push_back("XL");
    truthTable_in.push_back("DD");
    truthTable_in.push_back("DB");
    truthTable_in.push_back("DG");
    truthTable_in.push_back("DJ");
    truthTable_in.push_back("DF");
    truthTable_in.push_back("DL");
    truthTable_in.push_back("BB");
    truthTable_in.push_back("BG");
    truthTable_in.push_back("BJ");
    truthTable_in.push_back("BF");
    truthTable_in.push_back("BL");
    truthTable_in.push_back("GG");
    truthTable_in.push_back("GJ");
    truthTable_in.push_back("GF");
    truthTable_in.push_back("GL");
    truthTable_in.push_back("JJ");
    truthTable_in.push_back("JF");
    truthTable_in.push_back("JL");
    truthTable_in.push_back("FF");
    truthTable_in.push_back("FL");
    truthTable_in.push_back("LL");
  }
  return true;
}
bool TruthTable::setTruthTable()
{
  if (typeGate == AND||typeGate == NAND )
  {
    truthTable_out.push_back('0');  //00
    truthTable_out.push_back('0');  //01
    truthTable_out.push_back('0');  //0x
    truthTable_out.push_back('0');  //0d
    truthTable_out.push_back('0');  //0b
    truthTable_out.push_back('0');  //0g
    truthTable_out.push_back('0');  //0j
    truthTable_out.push_back('0');  //0f
    truthTable_out.push_back('0');  //0l
    truthTable_out.push_back('1');  //11
    truthTable_out.push_back('X');  //1x
    truthTable_out.push_back('D');  //1d
    truthTable_out.push_back('B');  //1b
    truthTable_out.push_back('G');  //1g
    truthTable_out.push_back('J');  //1j
    truthTable_out.push_back('F');  //1f
    truthTable_out.push_back('L');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('X');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('G');  //xg
    truthTable_out.push_back('X');  //xj
    truthTable_out.push_back('F');  //xf
    truthTable_out.push_back('X');  //xl
    truthTable_out.push_back('D');  //dd
    truthTable_out.push_back('0');  //db
    truthTable_out.push_back('0');  //dg
    truthTable_out.push_back('D');  //dj
    truthTable_out.push_back('F');  //df
    truthTable_out.push_back('F');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('G');  //bg
    truthTable_out.push_back('G');  //bj
    truthTable_out.push_back('0');  //bf
    truthTable_out.push_back('L');  //bl
    truthTable_out.push_back('G');  //gg
    truthTable_out.push_back('G');  //gj
    truthTable_out.push_back('0');  //gf
    truthTable_out.push_back('F');  //gl
    truthTable_out.push_back('J');  //jj
    truthTable_out.push_back('F');  //jf
    truthTable_out.push_back('X');  //jl
    truthTable_out.push_back('F');  //ff
    truthTable_out.push_back('F');  //fl
    truthTable_out.push_back('L');  //ll
  }/*
  else if(typeGate == NAND)
  {
    truthTable_out.push_back('1');  //00
    truthTable_out.push_back('1');  //01
    truthTable_out.push_back('1');  //0x
    truthTable_out.push_back('1');  //0d
    truthTable_out.push_back('1');  //0b
    truthTable_out.push_back('1');  //0g
    truthTable_out.push_back('1');  //0j
    truthTable_out.push_back('1');  //0f
    truthTable_out.push_back('1');  //0l
    truthTable_out.push_back('0');  //11
    truthTable_out.push_back('X');  //1x
    truthTable_out.push_back('B');  //1d
    truthTable_out.push_back('D');  //1b
    truthTable_out.push_back('J');  //1g
    truthTable_out.push_back('G');  //1j
    truthTable_out.push_back('L');  //1f
    truthTable_out.push_back('F');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('X');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('J');  //xg
    truthTable_out.push_back('X');  //xj
    truthTable_out.push_back('L');  //xf
    truthTable_out.push_back('X');  //xl
    truthTable_out.push_back('B');  //dd
    truthTable_out.push_back('1');  //db
    truthTable_out.push_back('1');  //dg
    truthTable_out.push_back('B');  //dj
    truthTable_out.push_back('L');  //df
    truthTable_out.push_back('L');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('J');  //bg
    truthTable_out.push_back('J');  //bj
    truthTable_out.push_back('1');  //bf
    truthTable_out.push_back('F');  //bl
    truthTable_out.push_back('J');  //gg
    truthTable_out.push_back('J');  //gj
    truthTable_out.push_back('1');  //gf
    truthTable_out.push_back('L');  //gl
    truthTable_out.push_back('G');  //jj
    truthTable_out.push_back('L');  //jf
    truthTable_out.push_back('X');  //jl
    truthTable_out.push_back('L');  //ff
    truthTable_out.push_back('L');  //fl
    truthTable_out.push_back('F');  //ll

  }*/else if(typeGate == OR || typeGate == NOR)
  {
    truthTable_out.push_back('0');  //00
    truthTable_out.push_back('1');  //01
    truthTable_out.push_back('X');  //0x
    truthTable_out.push_back('D');  //0d
    truthTable_out.push_back('B');  //0b
    truthTable_out.push_back('G');  //0g
    truthTable_out.push_back('J');  //0j
    truthTable_out.push_back('F');  //0f
    truthTable_out.push_back('L');  //0l
    truthTable_out.push_back('1');  //11
    truthTable_out.push_back('1');  //1x
    truthTable_out.push_back('1');  //1d
    truthTable_out.push_back('1');  //1b
    truthTable_out.push_back('1');  //1g
    truthTable_out.push_back('1');  //1j
    truthTable_out.push_back('1');  //1f
    truthTable_out.push_back('1');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('J');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('X');  //xg
    truthTable_out.push_back('J');  //xj
    truthTable_out.push_back('X');  //xf
    truthTable_out.push_back('L');  //xl
    truthTable_out.push_back('D');  //dd
    truthTable_out.push_back('1');  //db
    truthTable_out.push_back('J');  //dg
    truthTable_out.push_back('J');  //dj
    truthTable_out.push_back('D');  //df
    truthTable_out.push_back('1');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('B');  //bg
    truthTable_out.push_back('1');  //bj
    truthTable_out.push_back('L');  //bf
    truthTable_out.push_back('L');  //bl
    truthTable_out.push_back('G');  //gg
    truthTable_out.push_back('J');  //gj
    truthTable_out.push_back('X');  //gf
    truthTable_out.push_back('J');  //gl
    truthTable_out.push_back('J');  //jj
    truthTable_out.push_back('J');  //jf
    truthTable_out.push_back('1');  //jl
    truthTable_out.push_back('F');  //ff
    truthTable_out.push_back('L');  //fl
    truthTable_out.push_back('L');  //ll

  }/*  
  else if(typeGate == NOR)
  {
    truthTable_out.push_back('1');  //00
    truthTable_out.push_back('0');  //01
    truthTable_out.push_back('X');  //0x
    truthTable_out.push_back('B');  //0d
    truthTable_out.push_back('D');  //0b
    truthTable_out.push_back('J');  //0g
    truthTable_out.push_back('G');  //0j
    truthTable_out.push_back('L');  //0f
    truthTable_out.push_back('F');  //0l
    truthTable_out.push_back('0');  //11
    truthTable_out.push_back('0');  //1x
    truthTable_out.push_back('0');  //1d
    truthTable_out.push_back('0');  //1b
    truthTable_out.push_back('0');  //1g
    truthTable_out.push_back('0');  //1j
    truthTable_out.push_back('0');  //1f
    truthTable_out.push_back('0');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('G');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('X');  //xg
    truthTable_out.push_back('G');  //xj
    truthTable_out.push_back('X');  //xf
    truthTable_out.push_back('F');  //xl
    truthTable_out.push_back('B');  //dd
    truthTable_out.push_back('0');  //db
    truthTable_out.push_back('G');  //dg
    truthTable_out.push_back('G');  //dj
    truthTable_out.push_back('B');  //df
    truthTable_out.push_back('0');  //dl
    truthTable_out.push_back('D');  //bb
    truthTable_out.push_back('D');  //bg
    truthTable_out.push_back('0');  //bj
    truthTable_out.push_back('F');  //bf
    truthTable_out.push_back('F');  //bl
    truthTable_out.push_back('J');  //gg
    truthTable_out.push_back('G');  //gj
    truthTable_out.push_back('X');  //gf
    truthTable_out.push_back('G');  //gl
    truthTable_out.push_back('G');  //jj
    truthTable_out.push_back('G');  //jf
    truthTable_out.push_back('0');  //jl
    truthTable_out.push_back('L');  //ff
    truthTable_out.push_back('F');  //fl
    truthTable_out.push_back('F');  //ll
  }*/
  else if (typeGate == NOT)
  {
    truthTable_out.push_back('1'); //0
    truthTable_out.push_back('0'); //1
    truthTable_out.push_back('X'); //x
    truthTable_out.push_back('B'); //d
    truthTable_out.push_back('D'); //b
    truthTable_out.push_back('J'); //g
    truthTable_out.push_back('G'); //j
    truthTable_out.push_back('L'); //f
    truthTable_out.push_back('F'); //l
  }
  else {
    return false;
  }
  return true;

}

/*
int TruthTable::addEntry(const string &newEntry)
{
  if (newEntry.length() != numVars)
  {
    cout << "ERROR in truthTable::addEntry() - new entry has length "
         << newEntry.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  vector<truthType> row((newEntry.length()+1));  //add one column to store the result;
  
  for (unsigned i = 0; i < newEntry.length(); ++i)
  {
    switch(newEntry[i])setTruthTable_in(){
  if(gateType == NOT){
    truthTable_in.push_back("0");
    truthTable_in.push_back("1");
    truthTable_in.push_back("X");
    truthTable_in.push_back("D");
    truthTable_in.push_back("B");
    truthTable_in.push_back("G");
    truthTable_in.push_back("J");
    truthTable_in.push_back("F");
    truthTable_in.push_back("L");
  }
  else{
    truthTable_in.push_back("00");
    truthTable_in.push_back("01");
    truthTable_in.push_back("0X");
    truthTable_in.push_back("0D");
    truthTable_in.push_back("0B");
    truthTable_in.push_back("0G");
    truthTable_in.push_back("0J");
    truthTable_in.push_back("0F");
    truthTable_in.push_back("0L");
    truthTable_in.push_back("11");
    truthTable_in.push_back("1X");
    truthTable_in.push_back("1D");
    truthTable_in.push_back("1B");
    truthTable_in.push_back("1G");
    truthTable_in.push_back("1J");
    truthTable_in.push_back("1F");
    truthTable_in.push_back("1L");
    truthTable_in.push_back("XX");
    truthTable_in.push_back("XD");
    truthTable_in.push_back("XB");
    truthTable_in.push_back("XG");
    truthTable_in.push_back("XJ");
    truthTable_in.push_back("XF");
    truthTable_in.push_back("XL");
    truthTable_in.push_back("DD");
    truthTable_in.push_back("DB");
    truthTable_in.push_back("DG");
    truthTable_in.push_back("DJ");
    truthTable_in.push_back("DF");
    truthTable_in.push_back("DL");
    truthTable_in.push_back("BB");
    truthTable_in.push_back("BG");
    truthTable_in.push_back("BJ");
    truthTable_in.push_back("BF");
    truthTable_in.push_back("BL");
    truthTable_in.push_back("GG");
    truthTable_in.push_back("GJ");
    truthTable_in.push_back("GF");
    truthTable_in.push_back("GL");
    truthTable_in.push_back("JJ");
    truthTable_in.push_back("JF");
    truthTable_in.push_back("JL");
    truthTable_in.push_back("FF");
    truthTable_in.push_back("FL");
    truthTable_in.push_back("LL");
  }
  return true;
}
bool TruthTable::setTruthTable()
{
  if (typeGate == AND)
  {
    truthTable_out.push_back('0');  //00
    truthTable_out.push_back('0');  //01
    truthTable_out.push_back('0');  //0x
    truthTable_out.push_back('0');  //0d
    truthTable_out.push_back('0');  //0b
    truthTable_out.push_back('0');  //0g
    truthTable_out.push_back('0');  //0j
    truthTable_out.push_back('0');  //0f
    truthTable_out.push_back('0');  //0l
    truthTable_out.push_back('1');  //11
    truthTable_out.push_back('X');  //1x
    truthTable_out.push_back('D');  //1d
    truthTable_out.push_back('B');  //1b
    truthTable_out.push_back('G');  //1g
    truthTable_out.push_back('J');  //1j
    truthTable_out.push_back('F');  //1f
    truthTable_out.push_back('L');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('X');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('G');  //xg
    truthTable_out.push_back('X');  //xj
    truthTable_out.push_back('F');  //xf
    truthTable_out.push_back('X');  //xl
    truthTable_out.push_back('D');  //dd
    truthTable_out.push_back('0');  //db
    truthTable_out.push_back('0');  //dg
    truthTable_out.push_back('D');  //dj
    truthTable_out.push_back('F');  //df
    truthTable_out.push_back('F');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('G');  //bg
    truthTable_out.push_back('G');  //bj
    truthTable_out.push_back('0');  //bf
    truthTable_out.push_back('L');  //bl
    truthTable_out.push_back('G');  //gg
    truthTable_out.push_back('G');  //gj
    truthTable_out.push_back('0');  //gf
    truthTable_out.push_back('F');  //gl
    truthTable_out.push_back('J');  //jj
    truthTable_out.push_back('F');  //jf
    truthTable_out.push_back('X');  //jl
    truthTable_out.push_back('F');  //ff
    truthTable_out.push_back('F');  //fl
    truthTable_out.push_back('L');  //ll
  }
  else if(typeGate == NAND)
  {
    truthTable_out.push_back('1');  //00
    truthTable_out.push_back('1');  //01
    truthTable_out.push_back('1');  //0x
    truthTable_out.push_back('1');  //0d
    truthTable_out.push_back('1');  //0b
    truthTable_out.push_back('1');  //0g
    truthTable_out.push_back('1');  //0j
    truthTable_out.push_back('1');  //0f
    truthTable_out.push_back('1');  //0l
    truthTable_out.push_back('0');  //11
    truthTable_out.push_back('X');  //1x
    truthTable_out.push_back('B');  //1d
    truthTable_out.push_back('D');  //1b
    truthTable_out.push_back('J');  //1g
    truthTable_out.push_back('G');  //1j
    truthTable_out.push_back('L');  //1f
    truthTable_out.push_back('F');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('X');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('J');  //xg
    truthTable_out.push_back('X');  //xj
    truthTable_out.push_back('L');  //xf
    truthTable_out.push_back('X');  //xl
    truthTable_out.push_back('B');  //dd
    truthTable_out.push_back('1');  //db
    truthTable_out.push_back('1');  //dg
    truthTable_out.push_back('B');  //dj
    truthTable_out.push_back('L');  //df
    truthTable_out.push_back('L');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('J');  //bg
    truthTable_out.push_back('J');  //bj
    truthTable_out.push_back('1');  //bf
    truthTable_out.push_back('F');  //bl
    truthTable_out.push_back('J');  //gg
    truthTable_out.push_back('J');  //gj
    truthTable_out.push_back('1');  //gf
    truthTable_out.push_back('L');  //gl
    truthTable_out.push_back('G');  //jj
    truthTable_out.push_back('L');  //jf
    truthTable_out.push_back('X');  //jl
    truthTable_out.push_back('L');  //ff
    truthTable_out.push_back('L');  //fl
    truthTable_out.push_back('F');  //ll

  }else if(typeGate == OR)
  {
    truthTable_out.push_back('0');  //00
    truthTable_out.push_back('1');  //01
    truthTable_out.push_back('X');  //0x
    truthTable_out.push_back('D');  //0d
    truthTable_out.push_back('B');  //0b
    truthTable_out.push_back('G');  //0g
    truthTable_out.push_back('J');  //0j
    truthTable_out.push_back('F');  //0f
    truthTable_out.push_back('L');  //0l
    truthTable_out.push_back('1');  //11
    truthTable_out.push_back('1');  //1x
    truthTable_out.push_back('1');  //1d
    truthTable_out.push_back('1');  //1b
    truthTable_out.push_back('1');  //1g
    truthTable_out.push_back('1');  //1j
    truthTable_out.push_back('1');  //1f
    truthTable_out.push_back('1');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('J');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('X');  //xg
    truthTable_out.push_back('J');  //xj
    truthTable_out.push_back('X');  //xf
    truthTable_out.push_back('L');  //xl
    truthTable_out.push_back('D');  //dd
    truthTable_out.push_back('1');  //db
    truthTable_out.push_back('J');  //dg
    truthTable_out.push_back('J');  //dj
    truthTable_out.push_back('D');  //df
    truthTable_out.push_back('1');  //dl
    truthTable_out.push_back('B');  //bb
    truthTable_out.push_back('B');  //bg
    truthTable_out.push_back('1');  //bj
    truthTable_out.push_back('L');  //bf
    truthTable_out.push_back('L');  //bl
    truthTable_out.push_back('G');  //gg
    truthTable_out.push_back('J');  //gj
    truthTable_out.push_back('X');  //gf
    truthTable_out.push_back('J');  //gl
    truthTable_out.push_back('J');  //jj
    truthTable_out.push_back('J');  //jf
    truthTable_out.push_back('1');  //jl
    truthTable_out.push_back('F');  //ff
    truthTable_out.push_back('L');  //fl
    truthTable_out.push_back('L');  //ll

  }  
  else if(typeGate == NOR)
  {
    truthTable_out.push_back('1');  //00
    truthTable_out.push_back('0');  //01
    truthTable_out.push_back('X');  //0x
    truthTable_out.push_back('B');  //0d
    truthTable_out.push_back('D');  //0b
    truthTable_out.push_back('J');  //0g
    truthTable_out.push_back('G');  //0j
    truthTable_out.push_back('L');  //0f
    truthTable_out.push_back('F');  //0l
    truthTable_out.push_back('0');  //11
    truthTable_out.push_back('0');  //1x
    truthTable_out.push_back('0');  //1d
    truthTable_out.push_back('0');  //1b
    truthTable_out.push_back('0');  //1g
    truthTable_out.push_back('0');  //1j
    truthTable_out.push_back('0');  //1f
    truthTable_out.push_back('0');  //1l
    truthTable_out.push_back('X');  //xx
    truthTable_out.push_back('G');  //xd
    truthTable_out.push_back('X');  //xb
    truthTable_out.push_back('X');  //xg
    truthTable_out.push_back('G');  //xj
    truthTable_out.push_back('X');  //xf
    truthTable_out.push_back('F');  //xl
    truthTable_out.push_back('B');  //dd
    truthTable_out.push_back('0');  //db
    truthTable_out.push_back('G');  //dg
    truthTable_out.push_back('G');  //dj
    truthTable_out.push_back('B');  //df
    truthTable_out.push_back('0');  //dl
    truthTable_out.push_back('D');  //bb
    truthTable_out.push_back('D');  //bg
    truthTable_out.push_back('0');  //bj
    truthTable_out.push_back('F');  //bf
    truthTable_out.push_back('F');  //bl
    truthTable_out.push_back('J');  //gg
    truthTable_out.push_back('G');  //gj
    truthTable_out.push_back('X');  //gf
    truthTable_out.push_back('G');  //gl
    truthTable_out.push_back('G');  //jj
    truthTable_out.push_back('G');  //jf
    truthTable_out.push_back('0');  //jl
    truthTable_out.push_back('L');  //ff
    truthTable_out.push_back('F');  //fl
    truthTable_out.push_back('F');  //ll
  }
  else if (typeGate == NOT)
  {
    truthTable_out.push_back('1') //0
    truthTable_out.push_back('0') //1
    truthTable_out.push_back('X') //x
    truthTable_out.push_back('B') //d
    truthTable_out.push_back('D') //b
    truthTable_out.push_back('J') //g
    truthTable_out.push_back('G') //j
    truthTable_out.push_back('L') //f
    truthTable_out.push_back('F') //l
  }
  else {
    return false;
  }
  return true;

}

/*
int TruthTable::addEntry(const string &newEntry)
{
  if (newEntry.length() != numVars)
  {
    cout << "ERROR in truthTable::addEntry() - new entry has length "
         << newEntry.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  vector<truthType> row((newEntry.length()+1));  //add one column to store the result;
  
  for (unsigned i = 0; i < newEntry.length(); ++i)
  {
    switch(newEntry[i])
    {
      //transform 
      case '0': row[i] = ZERO; break;
      case '1': row[i] = ONE;  break;
      case 'X': row[i] = DC;   break;
      case 'D': row[i] = D; break;
      case 'B': row[i] = D_bar;  break;
      case 'G': row[i] = G0;   break;
      case 'J': row[i] = G1; break;
      case 'F': row[i] = F0;  break;
      case 'L': row[i] = F1;   break;
      default:
        cout << "ERROR in truthTable::addEntry() - invalid character "
             << newEntry[i] << endl;
        return -1;
    }
  }
  logic.push_back(row);
  
  return 0;
}

unsigned TruthTable::getNumEntries()
{
  return logic.size();
}
*/
unsigned TruthTable::getNumVars()
{
  return numVars;
}
/*
int TruthTable::print()
{
  for (unsigned i = 0; i < logic.size(); ++i)
  {
    for (unsigned j = 0; j < logic[i].size(); ++j)
    {
      switch(logic[i][j])
      {
        case ZERO: cout << "0"; break;
        case ONE:  cout << "1"; break;
        case DC:   cout << "-"; break;
        default:
          cout << "ERROR in truthTable::printTable() - invalid character "
               << logic[i][j] << endl;
          return -1;
      }
    }
    cout << " 1" << endl;
  }
  return 0;
}
*/


int TruthTable::clear()
{
  truthTable_in.clear();
  truthTable_out.clear();
  return 0;
}

char TruthTable::findOutput(string input)
{
  for (int i = 0; i < truthTable_in.size() ; i++)
  {
     if (input == truthTable_in[i] || (numVars != 1 && input[0]==truthTable_in[i][1] && input[1]==truthTable_in[i][0]))
     {
        return truthTable_out[i];
     }
  }


    {
      //transform 
      case '0': row[i] = ZERO; break;
      case '1': row[i] = ONE;  break;
      case 'X': row[i] = DC;   break;
      case 'D': row[i] = D; break;
      case 'B': row[i] = D_bar;  break;
      case 'G': row[i] = G0;   break;
      case 'J': row[i] = G1; break;
      case 'F': row[i] = F0;  break;
      case 'L': row[i] = F1;   break;
      default:
        cout << "ERROR in truthTable::addEntry() - invalid character "
             << newEntry[i] << endl;
        return -1;
    }
  }
  logic.push_back(row);
  
  return 0;
}

unsigned TruthTable::getNumEntries()
{
  return logic.size();
}
*/
unsigned TruthTable::getNumVars()
{
  return numVars;
}
/*
int TruthTable::print()
{
  for (unsigned i = 0; i < logic.size(); ++i)
  {
    for (unsigned j = 0; j < logic[i].size(); ++j)
    {
      switch(logic[i][j])
      {
        case ZERO: cout << "0"; break;
        case ONE:  cout << "1"; break;
        case DC:   cout << "-"; break;
        default:
          cout << "ERROR in truthTable::printTable() - invalid character "
               << logic[i][j] << endl;
          return -1;
      }
    }
    cout << " 1" << endl;
  }
  return 0;
}
*/


int TruthTable::clear()
{
  truthTable_in.clear();
  truthTable_out.clear();
  return 0;
}

char findOutput(string input)
{
  for (int i = 0; i < truthTable_in.size() ; i++)
  {
     if (input == truthTable_in[i] || (numVars != 1 && input[0]==truthTable_in[i][1] && input[1]==truthTable_in[i][0]))
     {
        return truthTable_out[i];
     }
  }

}

char TruthTable::evaluate_helper(const string &input)
{
  if (input.length() != numVars)
  {
    cout << "ERROR in truthTable::evaluate() - input has length "
         << input.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  if (input.length() == 2 || input.length() == 1)
  {
    return TruthTable::findOutput(input); //it will return the 
  } 
  else if (input.length()%2 == 0)
  {
    
    unsigned halfLength = input.length()/2;
    string halfInput1, halfInput2;
    char halfReturn1, halfReturn2;
    halfInput1 = input.substr(0,halfLength-1);
    halfInput2 = input.substr(halfLength,input.length()-1);
    halfReturn1 = TruthTable::evaluate_helper(halfInput1);
    halfReturn2 = TruthTable::evaluate_helper(halfInput2);
    string newInput;
    newInput.push_back(halfReturn1);
    newInput.push_back(halfReturn2);
    return TruthTable::evaluate_helper(newInput);
  }
  else
  {
    string halfInput1;
    char   halfInput2; //last character
    char halfReturn; //for return
    halfInput1 = input.substr(0,input.length()-2);
    halfInput2 = input[input.length()-1];
    halfReturn = TruthTable::evaluate_helper(halfInput1);
    string newInput;
    newInput.push_back(halfReturn);
    newInput.push_back(halfInput2);
    return TruthTable::evaluate_helper(newInput);
  }
  
  /*
  // input length must match the number of variables in truth table
  if (input.length() != numVars)
  {
    cout << "ERROR in truthTable::evaluate() - input has length "
         << input.length() << " vs. numVars = " << numVars << endl;
    return -1;
  }
  
  vector<truthType> row(input.length());
  
  // convert the input string to a vector of TruthType
  for (unsigned i = 0; i < input.length(); ++i)
  {
    switch(input[i])
    {
      case '0': row[i] = ZERO; break;
      case '1': row[i] = ONE;  break;
      case '-': row[i] = DC;   break;
      default:
        cout << "ERROR in truthTable::evaluate() - invalid character "
             << input[i] << endl;
        return -1;
    }
  }

  // search the truth table for the input pattern entry by entry
  for (unsigned j = 0; j < logic.size(); ++j)
  {
    bool match = true;
    // compare each variable 
    for (unsigned k = 0; k < numVars; ++k)
    {
      if (logic[j][k] != row[k])
      {
        match = false;
      }
    }
    // truth table here only store the entry with result "true", so output 1 if match
    if (match)
    {
      return '1';
    }
  }
  
  // no match, output 0
  return '0';
  */
}

char TruthTable::evaluate(const string &input){
  char result = evaluate_helper(input);
  if( typeGate == NAND || typeGate == NOR )
  {
    switch (result)
    {
      case '0': result = '1'; break;
      case '1': result = '0'; break;
      case 'X': result = 'X'; break;
      case 'D': result = 'B'; break;
      case 'B': result = 'D'; break;
      case 'G': result = 'J'; break;
      case 'J': result = 'G'; break;
      case 'F': result = 'L'; break;
      case 'L': result = 'F'; break;
      default:   
          cout<<"ERROR IN THE RETURN Value" << result << endl;
          return -1 ;
    }
  
  }
  return result;
}
