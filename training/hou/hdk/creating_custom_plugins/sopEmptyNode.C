#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include <limits.h>
#include <SYS/SYS_Math.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <GU/GU_Detail.h>
#include <GU/GU_PrimPoly.h>
#include <CH/CH_LocalVariable.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>

#include "sopEmptyNode.h"

using namespace HDK_Sample;

void
newSopOperator(OP_OperatorTable *table) {
    table->addOperator(		
        new OP_Operator(
                        "EmptyNode",                	
                      	"EmptyNodeHDK",            		
                        sopEmptyNode::myConstructor,  
                        sopEmptyNode::myTemplateList, 
	                    0,
                        0, 
                        sopEmptyNode::myVariables,
                        OP_FLAG_GENERATOR)
    );
};



static PRM_Name         variable_name("curious", "Curious");
static PRM_Default      variable_defaults(0);
static PRM_Range		variable_range(PRM_RANGE_RESTRICTED, 0, PRM_RANGE_UI, 100);

PRM_Template 
sopEmptyNode::myTemplateList[] = {	
		PRM_Template( 
            PRM_FLT, 
    		PRM_Template::PRM_EXPORT_TBX,
	    	1, 
		    &variable_name, 	
    		&variable_defaults,	
	    	0,	
		    &variable_range ),								
		PRM_Template()
};


enum {
	VAR_PT,
	VAR_NPT
};

CH_LocalVariable
sopEmptyNode::myVariables[] = {
    { "PT",	VAR_PT, 0 },
    { "NPT",	VAR_NPT, 0 },
    { 0, 0, 0 },
};

bool
sopEmptyNode::evalVariableValue(fpreal &val, int index, int thread)
{
    if (myCurrPoint >= 0)
    {
	switch (index)
	{
	    case VAR_PT:
		val = (fpreal) myCurrPoint;
		return true;
	    case VAR_NPT:
		val = (fpreal) myTotalPoints;
		return true;
	    default:
		/* do nothing */;
	}
    }
    return SOP_Node::evalVariableValue(val, index, thread);
}

OP_Node *
sopEmptyNode::myConstructor(OP_Network *net, const char *name, OP_Operator *op) {
    return new sopEmptyNode(net, name, op);
}

sopEmptyNode::sopEmptyNode(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net, name, op)
{
    myCurrPoint = -1;	
}

sopEmptyNode::~sopEmptyNode()
{
};


OP_ERROR sopEmptyNode::cookMySop(OP_Context &context)
{

    double              now;
    float               variable;
    UT_Interrupt        *boss;

    now 				= context.getTime();
	variable 			= evalFloat  ("curious", 0, now);
	cout << "Test Message: Version 1 for H13";
	cout.flush(); 

	gdp->clearAndDestroy();

    if (error() < UT_ERROR_ABORT)
    {
        boss = UTgetInterrupt();

        if (boss->opStart("Cooking SOP..."))
        {
        	myTotalPoints = myCurrPoint = variable;
        }
        boss->opEnd();
    };

    myCurrPoint = -1;
    return error();
};

