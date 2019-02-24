/*
 * Sam Glendenning
 * Assignment 4
 * AC21008 Multi-Paradigm
 *
 * N-gram Frequency Tool
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cmath>
#include "HashTable.h"

using namespace std;

typedef HashTable<string,int> Table;
Table table(1000);

void calculate(int k)
{
	size_t tableSize = table.size();
	int num = 0;

	for (unsigned i=0; i<tableSize; i++)
	{
		if (table.getKey(i).length() > 0)
		{
			num++;
		}
	}

	vector<string> keys (num, "");
	vector<int> values (num, 0);
	int arrayIndex = 0;

	for (unsigned i=0; i<tableSize; i++)
	{
		if (table.getKey(i).length() > 0)
		{
			keys[arrayIndex] = table.getKey(i);
			values[arrayIndex] = table.getValue(table.getKey(i));
			arrayIndex++;
		}
	}

	int i, j, flag = 1;    // set flag to 1 to start first pass
	int temp;             // holding variable
	string tmp;
	int valuesLength = values.size();
	for(i=1; (i<=valuesLength) && flag; i++)
	{
		flag = 0;
	    for (j=0; j < (valuesLength -1); j++)
	    {
	    	if (values[j+1] > values[j])      // ascending order simply changes to <
	        {
	    		temp = values[j];             // swap elements
	    		tmp = keys[j];
	    		values[j] = values[j+1];
	    		keys[j] = keys[j+1];
	    		values[j+1] = temp;
	    		keys[j+1] = tmp;
	            flag = 1;               // indicates that a swap occurred.
	        }
	     }
	}

	float numberOfngrams = 0;

	for (unsigned i=0; i<values.size(); i++)
	{
		numberOfngrams += values[i];
	}

	if (k > num)
	{
		k = num;
	}

	for (int i=0; i<k; i++)
	{
		float percentage = roundf((values[i] / numberOfngrams) * 10000) / 100;
		cout << percentage << "%" <<  " : " << keys[i] << endl;
	}
}

void ngram(string filename, int n)
{
	string line;
	stringstream stream;
	n = n-1;

	ifstream input(filename);

	while (getline(input, line))
	{
		for (unsigned i=0; i+n<line.length(); i++)
		{
			string ngram = "";
			int temp = i;
			n = n+i;
			while (temp <= n)
			{
				ngram += line[n-(n-temp)];
				temp++;
			}

			try
			{
				table.insert(ngram, 1);
			}
			catch (...)
			{
				size_t index = table.hash_function(ngram);
				int numberOfApps = table.getValue(ngram);

				table.setValue(index, ++numberOfApps);
			}
			n = n-i;
		}
	}

	input.close();
}

int main(int argc, char* argv[])
{
	string *args = new string[argc]();

	for (int i=0; i<argc; i++)
	{
		args[i] = argv[i];
	}

	string filename = "inputfile.txt";
	int n = 3;
	int k = 10;

	if (argc > 1)
	{
		filename = args[1];

		if (argc == 4)
		{
			try
			{
				k = stoi(args[3]);
			}
			catch (...)
			{
				cerr << "Error. Candidates are ngram filename[string] n-gram-size[integer] top-results[integer]" << endl;
				return 1;
			}

			if (k <= 0)
			{
				cerr << "Error. Candidates are ngram filename[string] n-gram-size[integer] top-results[integer]" << endl;
				return 1;
			}
		}

		if (argc >= 3)
		{
			try
			{
				n = (unsigned)stoi(args[2]);

				if (n <= 0)
				{
					cerr << "Error. Candidates are ngram filename[string] n-gram-size[integer] top-results[integer]" << endl;
					return 1;
				}
			}
			catch (...)
			{
				cerr << "Error. Candidates are ngram filename[string] n-gram-size[integer] top-results[integer]" << endl;
				return 1;
			}

			if (n <= 0)
			{
				cerr << "Error. Candidates are ngram filename[string] n-gram-size[integer] top-results[integer]" << endl;
				return 1;
			}
		}
	}

	ifstream input(filename);

	if (!input)
	{
		cerr << "File " << filename << " not found!" << endl;
		input.close();
		return 1;
	}

	input.close();

	ngram(filename, n);
	calculate(k);

	return 0;
}
