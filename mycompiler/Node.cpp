#include "Node.h"

//put any class declaration. put it in the cpp file

StartNode::StartNode(ProgramNode* program)
{
	mProgramNode = program;
}

StartNode::~StartNode()
{delete mProgramNode;}

void StartNode::Interpret()
{mProgramNode -> Interpret();}

void StartNode::Code(InstructionsClass &machineCode)
{mProgramNode->Code(machineCode);}


ProgramNode::~ProgramNode(){delete mDaBlock;}

ProgramNode::ProgramNode(BlockNode* daBlock){
	mDaBlock = daBlock;
} //-> VOID MAIN LPAREN RPAREN <Block>

void ProgramNode::Interpret()
{mDaBlock->Interpret();}

void ProgramNode::Code(InstructionsClass &machineCode)
{mDaBlock->Code(machineCode);}

BlockNode::~BlockNode(){delete mSGNode;}


BlockNode::BlockNode(StatementGroupNode* ndee){
	mSGNode = ndee;}

void BlockNode::Interpret()
{mSGNode->Interpret();}

void BlockNode::Code(InstructionsClass &machineCode)
{mSGNode->Code(machineCode);}

//LCURLY <StatementGroup> RCURLY
StatementGroupNode::StatementGroupNode(){} //-> empty

StatementGroupNode::~StatementGroupNode() {
	//loop thru the size
	for (StatementNode* stmt : mListStatementNode)
	{	delete stmt;}
}

void StatementGroupNode::AddStatement(StatementNode* ptrStatementNode)
{
	mListStatementNode.push_back(ptrStatementNode);
}

StatementNode::StatementNode() {} //abstract
StatementNode::~StatementNode() {}

void StatementGroupNode::Interpret()
{	// instead of going thru jsut one, it loops thru all of them
	for (StatementNode* stmt : mListStatementNode)
	{
		stmt->Interpret();
	}
}

void StatementGroupNode::Code(InstructionsClass &machineCode)
{
	for (StatementNode* stmt : mListStatementNode)
	{
		stmt->Code(machineCode);
	}
}


DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* stuff) {
	mIDNode = stuff;
}
DeclarationStatementNode::~DeclarationStatementNode() { delete mIDNode;}

void DeclarationStatementNode::Interpret()
{	
	//mIDNode->Interpret();
	mIDNode->DeclareVariable();
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode)
{ //can't push an variable since not init yet
//mIDNode->Code(machineCode);
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* IDnode, ExpressionNode* Expressnode) {
	mIDNODE = IDnode;
	mEXPRESSNODE = Expressnode;
}

AssignmentStatementNode::~AssignmentStatementNode() { delete mIDNODE; delete mEXPRESSNODE; }

void AssignmentStatementNode::Interpret()
{
	int value = mEXPRESSNODE->Evaluate();
	mIDNODE->SetValue(value);
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode)
{	//it ask for this ... in 5.
	mEXPRESSNODE->CodeEvaluate(machineCode);
	int index = mIDNODE->GetIndex();
	machineCode.PopAndStore(index);
	//mIDNODE->Code(machineCode);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* ExpressNode) {
	mEXPRESSNODE = ExpressNode;
	//have an list of expline node like
}
CoutStatementNode::~CoutStatementNode() { delete mEXPRESSNODE; }

void CoutStatementNode::Interpret()
{
	int value = mEXPRESSNODE->Evaluate();
	//debug below?? 
	std::cout << value << std::endl;
}

void CoutStatementNode::Code(InstructionsClass &machineCode)
{ //check if goog
	mEXPRESSNODE->CodeEvaluate(machineCode);
    machineCode.PopAndWrite();
}

ExpressionNode::~ExpressionNode() {}//-> identifier or integer or expression + expression

void ExpressionNode::Code(InstructionsClass &machineCode)
{
    CodeEvaluate(machineCode);
} //add recently could be problemtic

IntegerNode::IntegerNode(int danum) {
	mNumber = danum;
}

int IntegerNode::Evaluate(){return mNumber;}

IdentifierNode::IdentifierNode(const std::string& label, SymbolTableClass* table) {
	mTable = table;
	mLabel = label;


} //-> identifier

void IntegerNode::CodeEvaluate(InstructionsClass &machineCode)
{
    machineCode.PushValue(mNumber);
}

void 
IdentifierNode::DeclareVariable() {
	mTable->AddEntry(mLabel);
	//may need to switch thisw out?? 
}

void IdentifierNode::SetValue(int v)
{
	mTable->SetValue(mLabel, v);
}

int IdentifierNode::GetIndex()
{
	return mTable->GetIndex(mLabel);
}

int IdentifierNode::Evaluate()
{
	return mTable->GetValue(mLabel);
}

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode)
{
    int index = GetIndex();
    machineCode.PushVariable(index);
}

IfStatementNode::IfStatementNode(ExpressionNode* cond, StatementNode* stmt) {
	mCondition = cond;
	mStatement = stmt;
}

void IfStatementNode::Interpret()
{
	if (mCondition->Evaluate())
	{mStatement->Interpret();}
}

void IfStatementNode::Code(InstructionsClass &machineCode)
{	//given in the book
	mCondition->CodeEvaluate(machineCode);
	unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
	unsigned char * address1 = machineCode.GetAddress();
	mStatement->Code(machineCode);
	unsigned char * address2 = machineCode.GetAddress();
	machineCode.SetOffset(InsertAddress, (int)(address2-address1));
}

IfStatementNode::~IfStatementNode()
{delete mCondition;	delete mStatement;}

WhileStatementNode::WhileStatementNode(ExpressionNode* cond, StatementNode* stmt)
{	mCondition = cond;
	mStatement = stmt;}

WhileStatementNode::~WhileStatementNode()
{
	delete mCondition;	delete mStatement;
}

void WhileStatementNode::Interpret()
{
	while (mCondition->Evaluate())
	{
		mStatement->Interpret();
	}
}

void WhileStatementNode::Code(InstructionsClass &machineCode)
{	    // Address1: start of loop (condition check)
    unsigned char * address1 = machineCode.GetAddress();

    // Evaluate condition
    mCondition->CodeEvaluate(machineCode);

    // If false → skip loop body
    unsigned char * insertAddressToSkip = machineCode.SkipIfZeroStack();

    // Address2: start of body
    unsigned char * address2 = machineCode.GetAddress();

    // Loop body
    mStatement->Code(machineCode);

    // Jump back to condition
    unsigned char * insertAddressToJump = machineCode.Jump();

    // Address3: after loop
    unsigned char * address3 = machineCode.GetAddress();

    // Fix offsets
    machineCode.SetOffset(insertAddressToSkip, (int)(address3 - address2));
    machineCode.SetOffset(insertAddressToJump, (int)(address1 - address3));
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left,
	ExpressionNode* right)
	: mLeft(left),
	mRight(right)
{}

BinaryOperatorNode::~BinaryOperatorNode() {	delete mLeft;	delete mRight;}


PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right){}


int PlusNode::Evaluate()
{
	return mLeft->Evaluate() + mRight->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

PlusEqualNode::PlusEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {}

int PlusEqualNode::Evaluate()
{	//should take Left and add right to left and evaluate
	return mLeft->Evaluate() + mRight->Evaluate();
}


// [][][][][][][][][][][][][][][][][][][][][][][][]
// [][][][][][][][][][][][][][][][][][][][][][][][]
// [][][][][][][][][][][][][][][][][][][][][][][][]



//almost got Evaluate for += to work then -= logic should work
void PlusEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{	
	/*
	int index = indentNode.GetIndex(machineCode);
	C.pushvariable(index);
	ExpressionNode* ->CodeEvaluate(machineCode); 
    machineCode.PopPopAddPush();
	machineCode.PopAndStore(index);
	*/
}


MinusNode::MinusNode(ExpressionNode* left,
	ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int MinusNode::Evaluate()
{
	return mLeft->Evaluate() - mRight->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

MinusEqualNode::MinusEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right) {
}

int MinusEqualNode::Evaluate()
{	//should take Left and add right to left and evaluate
	return mLeft->Evaluate() - mRight->Evaluate();
}

void MinusEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
	/*
	int index = indentNode.GetIndex(machineCode);
	C.pushvariable(index);
	ExpressionNode* ->CodeEvaluate(machineCode); 
    machineCode.PopPopAddPush();
	machineCode.PopAndStore(index);
	*/
}

TimesNode::TimesNode(ExpressionNode* left,
	ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{}

int TimesNode::Evaluate()
{
	return mLeft->Evaluate() * mRight->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush(); //double
}

DivideNode::DivideNode(ExpressionNode* left,ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{}

int DivideNode::Evaluate()
{
	int rightValue = mRight->Evaluate();

	// Optional safety check
	if (rightValue == 0)
	{
		std::cerr << "Runtime Error: Division by zero\n";
		exit(1);
	}

	return mLeft->Evaluate() / rightValue;}


void DivideNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush(); 
}

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int LessNode::Evaluate()
{
	int rightValue = mRight->Evaluate();

	// Optional safety check

	/*
	if (rightValue == NULL)
	{
		std::cerr << "Runtime Error: Division by zero\n";
		exit(1);
	}
		*/

	return mLeft->Evaluate() < rightValue;
}

void LessNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int LessEqualNode::Evaluate()
{
	int rightValue = mRight->Evaluate();

	return mLeft->Evaluate() <= rightValue;
}

void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopLessEQPush();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int GreaterNode::Evaluate()
{
	int rightValue = mRight->Evaluate();

	return mLeft->Evaluate() > rightValue;
}

void GreaterNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopGrePush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int GreaterEqualNode::Evaluate()
{
	int rightValue = mRight->Evaluate();
	return mLeft->Evaluate() >= rightValue;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopGreEQPush();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int EqualNode::Evaluate()
{
	int rightValue = mRight->Evaluate();

	/*
	if (rightValue == NULL)
	{
		std::cerr << "Runtime Error: Division by zero\n";
		exit(1);
	} */

	return mLeft->Evaluate() == rightValue;
}

void EqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopEQPush();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int NotEqualNode::Evaluate()
{
	int rightValue = mRight->Evaluate();
	return mLeft->Evaluate() != rightValue;
}

void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopNEQPush();
}

/*
// InsertionNode (<<)
InsertionNode::InsertionNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int InsertionNode::Evaluate()
{
	return mLeft->Evaluate() << mRight->Evaluate();
}

void InsertionNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);

    // You DON'T have a PopPopShiftPush(), so either:
    // Option A: skip for now
    // Option B: implement custom behavior

    std::cerr << "InsertionNode CodeEvaluate not implemented\n";
    exit(1);
}
*/
// OrNode (||)
OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{
}

int OrNode::Evaluate()
{
	return mLeft->Evaluate() || mRight->Evaluate();
}

void OrNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}
// AndNode (&&)
AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
	: BinaryOperatorNode(left, right)
{}

//should this return BOOLEAN
int AndNode::Evaluate()
{
	return mLeft->Evaluate() && mRight->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass &machineCode)
{
    mLeft->CodeEvaluate(machineCode);
    mRight->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

