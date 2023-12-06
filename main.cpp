#include <iostream>
#include <sstream>
#include <string>
#include "redblack.hh"
#include "node.hh"

using namespace std;
int main(int argc, char** argv)
{
  if (argc < 3)
    {
      cout << "./rbtree <file> <command file>" << endl;
      exit(1);
    }

  string file(argv[2]);

  RBTree tree();

  istringstream file_stream(file);
  do
    {
      string word;
      file_stream >> word;

      tree.insert(word);
    }
  while(file_stream);

  
  ifstream inStream;
  string line, word;

  inStream.open(argv[3]);
  if (inStream.fail())
    {
      cout << "Failed to open file" << endl;
      exit(1);
    }

  while (getline(inStream, line))
    {
      vector <string> wordVec;
      stringstream ls(line);

      while (ls >> word)
	wordVec.push_back(word);

      if (wordVec.size() > 0)
	{
	  // The only thing that matters in the command is the first letter and its case
	  switch(wordVec[0].at(0))
	    {
	    case 'i':
	      if (wordVec.size() == 2)
		tree.insert(wordVec[1]);
	    }
	}
 
    }
}
