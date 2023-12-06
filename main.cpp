#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stddef.h>

#include "redblack.hh"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "./rbtree <file> <command file>" << endl;
      exit(1);
    }


  RBTree<string> tree;

  // cout << "HELLO" << endl;
  ifstream inStream;
  inStream.open(argv[1]);
  string word;

  while (inStream >> word)
    {
      cout << word << endl;
      tree.insert(word);
    }
  inStream.close();

  /*
  cout << "HELLO" << endl;
  
  ifstream inStream;
  string line, word;

  inStream.open(argv[2]);
  if (inStream.fail())
    {
      cout << "Failed to open file" << endl;
      exit(1);
    }


  while (getline(inStream, line))
    {
      vector<string> wordVec;
      stringstream ls(line);

      while (ls >> word)
	wordVec.push_back(word);
      cout << "OH" << endl;
    }
  **/
  tree.preOrderPrint();
  //inStream.close();
}
