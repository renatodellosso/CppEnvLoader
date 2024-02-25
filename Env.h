#pragma once

#include <string>
#include <map>

using namespace std;

namespace env
{
	void loadEnv(string fileName);
	string get(string key);
}

class Env
{
public:
	static void loadEnv(string fileName);
	static string get(string key);

private:
	map<string, string>* envMap;
};
