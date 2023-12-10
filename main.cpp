#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <stddef.h>

#include "redblack.hh"

using namespace std;

void clean_and_insert_all_words(string, RBTree<string>*);
void cleanup_string(string &);

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      cout << "./RBTree <command file>" << endl;
      exit(1);
    }


  RBTree<string> *tree = new RBTree<string>();

  /**
  // cout << "HELLO" << endl;
  ifstream inStream;
  inStream.open(argv[1]);
  string word;

  while (inStream >> word)
    {
      tree.insert(word);
    }
  inStream.close();


  tree.preOrderPrint();
  */


  ifstream commandStream;

  commandStream.open(argv[1]);

  if (commandStream.fail()) {
    cout << "Failed to open command file\n";
    exit(1);
  }

  // iterate through file line by line assuming no syntax errors
  
  string line, s_command, s_arg;
  
  while (getline(commandStream, line)) {

    stringstream ls(line);

    ls >> s_command;
    ls >> s_arg;

    // Insert all words into tree
    
    if (s_command == "TEXT")
      {
	clean_and_insert_all_words(s_arg, tree);
	cout << "Size: " << tree->getSize() << endl;
      }


    // insert word into tree
    
    else if (s_command == "INSERT")
      {
	tree->insert(s_arg);
	cout << tree->getSize() << endl;
      }

    // remove word from tree

    /*
    else if (s_command == "REMOVE") {
      HT->remove(s_arg);
      cout << HT->num_entries << " " << HT->table_size << endl;
    }
    */

    else if (s_command == "PREORDER")
      {
	tree->preOrderPrint();
      }
    else if (s_command == "POSTORDER")
      {
	tree->postOrderPrint();
      }
    else if (s_command == "INORDER")
      {
	tree->inOrderPrint();
      }

    // garbage
    
    else {
      cout << "Unknown command " << s_command << endl;
      exit(1);
    }
  }
  
  commandStream.close();

  return 1;
}

/**
 * Created by Professor from Hashing Project
 */
void cleanup_string(string & s)
{
  int i;

  while (s.size() > 0 && ispunct(s[0]))
    s.erase(0, 1);

  while (s.size() > 0 && ispunct(s[s.size() - 1]))
    s.erase(s.size() - 1, 1);

  for (i = 0; i < s.size(); i++)
    if (isalpha(s[i]))
      s[i] = tolower(s[i]);

  // possessive checker
  
  if (s[s.length() - 2] == '\'' && s[s.length() - 1] == 's') 
    s = s.substr(0, s.length() - 2);
}

/**
 * Created by Professor from Hashing Project. Modified to fit Red Black Tree
 */
void clean_and_insert_all_words(string filename, RBTree<string> *tree)
{
  // try to open file 

  ifstream inStream;
  string s;

  inStream.open(filename.c_str());

  if (inStream.fail()) {
    cout << "Failed to open file\n";
    exit(1);
  }
  
  while (!inStream.eof()) {

    inStream >> s;

    if (!inStream.eof()) {

      cleanup_string(s); 

      if (s.size())
	tree->insert(s);
    }
  }

  inStream.close();
}
