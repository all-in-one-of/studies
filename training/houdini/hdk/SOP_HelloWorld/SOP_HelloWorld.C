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

#include "SOP_HelloWorld.h"

using namespace HDK_Sample;

void newSopOperator(OP_OperatorTable *table) {
    table->addOperator(
        new OP_Operator(
                        "HelloWorld",
                        "ahHelloWorld",
                        SOP_HelloWorld::myConstructor,
                        SOP_HelloWorld::myTemplateList,
                        0,
                        0,
                        SOP_HelloWorld::myVariables,
                        OP_FLAG_GENERATOR)

    );
};


//Parameters for the UI and input variables
static PRM_Name variable_name("curious", "Curious");
static PRM_Default variable_defaults(0);
static PRM_Range variable_range(PRM_RANGE_RESTRICTED, 0, PRM_RANGE_UI, 100);

PRM_Template
SOP_HelloWorld::myTemplateList[] = {
    PRM_Template(
        PRM_FLT,
        PRM_Template::PRM_EXPORT_TBX,
        1,
        &variable_name,
        &variable_defaults,
        0,
        &variable_range),
    PRM_Template()            
};

enum {
    VAR_PT,
    VAR_NPT
};

CH_LocalVariable
SOP_HelloWorld::myVariables[] = {
    { "PT", VAR_PT, 0 },
    { "NPT", VAR_NPT, 0 },
    { 0, 0, 0},
};

bool
SOP_HelloWorld::evalVariableValue(fpreal &val, int index, int thread) {
    if(myCurrPoint >= 0) {
        switch (index) {
            case VAR_PT:
                val = (fpreal) myCurrPoint;
                return true;
            case VAR_NPT:
                val = (fpreal) myTotalPoints;
                return true;
            default:
                /*do nothing*/;
        }
    }
    
    return SOP_Node::evalVariableValue(val, index, thread);
}


OP_Node * 
SOP_HelloWorld::myConstructor(OP_Network *net, const char *name, OP_Operator *op) {
    return new SOP_HelloWorld(net, name, op); 
}

SOP_HelloWorld::SOP_HelloWorld(OP_Network *net, const char *name, OP_Operator *op)
: SOP_Node(net, name, op) {
    myCurrPoint = -1;
}

SOP_HelloWorld::~SOP_HelloWorld() {};

OP_ERROR SOP_HelloWorld::cookMySop(OP_Context &context) {
    double now;
    float variable;
    UT_Interrupt *boss;

    now = context.getTime();
    variable = evalFloat("curious", 0, now);

    cout << "Hello World, from SOP_HelloWorld.so";
    cout.flush();

    //gdp, a pointer to geometry that is passed in and out of the SOP
    gdp->clearAndDestroy();
    
    if ( error() < UT_ERROR_ABORT){

        boss = UTgetInterrupt();

        if (boss->opStart("Cooking SOP...")) {
            myTotalPoints = myCurrPoint = variable;
        }
        boss->opEnd();
    };


    myCurrPoint = -1;

    return error();

};






