#include "Symbol.h"
#include <cstdlib> 

bool SymbolTableClass::Exists(const std::string& s) {
	bool yainside = false;
	for (const auto& variable : mVariables)
	{
		if (variable.mLabel == s)
			return true;
	}
	//an lookup function to see if insde the data structure SymbolTable class
	return yainside; // returns true if <s> is already in the symbol table.
}

void SymbolTableClass::AddEntry(const std::string& s) {
	if (Exists(s)) {
		std::cerr << "Variable already declared -> " << s << std::endl;
		return; // or quits if it was already there
	}
	Variable entry;
	entry.mLabel = s;
	entry.mValue = 0;
	
	//mVariables.push_back({ s, 0 });
	mVariables.push_back(entry);  // adds <s> to the symbol table
}


int SymbolTableClass::GetValue(const std::string& s) {
		int index = GetIndex(s);
		if (index == -1)
		{
			std::cerr << "Variable not found: " << s << std::endl;
			return -1;
		}

		return mVariables[index].mValue;
}
// returns the current value of variable <s>, when
// interpreting. Meaningless for Coding and Executing.
// Prints a message and quits if variable s does not exist.
void SymbolTableClass::SetValue(const std::string& s, int v) {
	int index = GetIndex(s);
	if (index == -1)
	{
		std::cerr << "Variable not found: " << s << std::endl;
		return;
	}
	
	mVariables[index].mValue = v;
}

int SymbolTableClass::GetIndex(const std::string& s) {
	for (int i = 0; i < mVariables.size(); i++)
	{
		if (mVariables[i].mLabel == s)
			return i; // returns a unique index of where variable <s> is.
	}
	return -1; // returns -1 if variable <s> is not there.
}


size_t SymbolTableClass::GetCount() const{
	return mVariables.size(); // returns the current number of variables in the symbol
}

void SymbolTableClass::Print()
{
	std::cout << "----- Symbol Table -----\n";

	for (int i = 0; i < mVariables.size(); i++)
	{
		std::cout << i << ": " << mVariables[i].mLabel << std::endl;
	}
}
 
