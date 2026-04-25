#include "Symbol.h"
#include <cstdlib> 

bool SymbolTableClass::Exists(const std::string& s) {
	
	int start = mScopeStarts.back();
	
	bool yainside = false;
	for (int i = start; i < mVariables.size(); i++)
    {
        if (mVariables[i].mLabel == s)
            return true;
    }
	//an lookup function to see if insde the data structure SymbolTable class
	return yainside; // returns true if <s> is already in the symbol table.
}

void SymbolTableClass::AddEntry(const std::string& s) {
	MSG("[SYMTABLE] Adding: " << s << " at scope depth " << mScopeStarts.size());

	if (Exists(s)) {
		std::cerr << "Variable already declared -> " << s << std::endl;
		throw std::runtime_error("Already Declared Variable");

		//return; // or quits if it was already there
	}
	Variable entry;
	entry.mLabel = s;
	entry.mValue = 0;
	
	mVariables.push_back(entry);  // adds <s> to the symbol table
	 MSG("[SYMTABLE] Table size now: " << GetCount());
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

int SymbolTableClass::GetIndex(const std::string& s)
{	MSG("[SYMTABLE] Lookup: " << s);

    // walk scopes from inner → outer
    for (int scope = (int)mScopeStarts.size() - 1; scope >= 0; scope--)
    {
        int start = mScopeStarts[scope];

        int end;
        if (scope == (int)mScopeStarts.size() - 1)
            end = (int)mVariables.size();
        else
            end = mScopeStarts[scope + 1];

        // search ONLY inside this scope
        for (int i = end - 1; i >= start; i--)
        {
            if (mVariables[i].mLabel == s)
                return i;
        }
    }
	MSG("[SYMTABLE] FAILED lookup: " << s);
    std::cerr << "ERROR: Variable not found: " << s << std::endl;
    return -1;
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
 
SymbolTableClass::SymbolTableClass(){
	EnterScope(); 
}

void SymbolTableClass::EnterScope()
{	
	MSG(">>> ENTER SCOPE (depth=" << mScopeStarts.size() << ", size=" << mVariables.size() << ")");
    mScopeStarts.push_back(mVariables.size());
}

void SymbolTableClass::ExitScope()
{ //sanity check if size is one 
    int start = mScopeStarts.back();
    mScopeStarts.pop_back();
	 MSG("<<< EXIT SCOPE → resizing to " << start);
    mVariables.resize(start);
}