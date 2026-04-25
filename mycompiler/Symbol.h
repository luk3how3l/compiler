#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "Debug.h"

int unittest();


class SymbolTableClass
{
public:
	SymbolTableClass();

	bool Exists(const std::string& s);
	
	void AddEntry(const std::string& s);
	
	int GetValue(const std::string& s);
	
	void SetValue(const std::string& s, int v);
	
	int GetIndex(const std::string& s);
	
	size_t GetCount() const;

	void Print();

	void EnterScope();

	void ExitScope();

private:
	
	struct  Variable
	{
		std::string mLabel{};
		int mValue{ 0 };
	};
	
	std::vector<Variable>mVariables;

	std::vector<int> mScopeStarts;
};
