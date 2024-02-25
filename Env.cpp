#include "pch.h"
#include "Env.h"

#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
using namespace env;

namespace env
{
	void loadEnv(string fileName)
	{
		Env::loadEnv(fileName);
	}

	string get(string key)
	{
		return Env::get(key);
	}
}

// Static variables must be defined outside of the class
static Env* instance;

void Env::loadEnv(string fileName)
{
	// Don't load the environment more than once
	if (instance != nullptr)
		return;

	instance = new Env();

	// ifstream is input file stream
	ifstream envFile;
	envFile.open(fileName);

	// Always check if the file is open!
	if (!envFile.is_open())
	{
		// Use cerr for errors
		cerr << "Error: File not found" << endl;
		return;
	}

	// We store it as an instance variable first
	// If we do it the other way around, it will be deleted when the scope ends
	instance->envMap = new map<string, string>();
	map<string, string>* envMap = instance->envMap;
	while (envFile)
	{
		string line;

		// Read a line from the file
		getline(envFile, line);

		// Find the position of the first '='
		// size_t is the maximum size of an object
		size_t pos = line.find('=');

		if (pos == string::npos)
		{
			// If the line does not contain an '='
			// Skip the line
			continue;
		}

		// Split line
		string key = line.substr(0, pos);
		string value = line.substr(pos + 1, line.length());

		// Count will return 1 or more if the key exists
		// Thus, it will cast to a true boolean if the key exists
		if (envMap->count(key))
		{
			// If the key already exists
			// Skip the line
			continue;
		}

		// Add the key-value pair to the map
		envMap->insert({ key, value });
	}

	// Close the file
	envFile.close();
}

string Env::get(string key)
{
	// If the instance is null, return an empty string
	if (instance == nullptr)
	{
		cerr << "Error: Environment not loaded" << endl;
		return "";
	}
	map<string, string> envMap = *(instance->envMap);

	// If the key exists, return the value
	auto iterator = envMap.find(key);
	if (iterator != envMap.end())
		return iterator->second;

	// If the key does not exist, return an empty string
	cerr << "Error: Key not found: " << key << endl;
	return "";
}