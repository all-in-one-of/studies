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
#include <OP/OP_AutoLockInputs.h>

#include "SOP_Template.h"

using namespace HDK_Sample;

void newSopOperator(OP_OperatorTable *table) {
    table->addOperator(
        new OP_Operator(
                        "Template",
                        "Template",
                        SOP_Template::myConstructor,
                        SOP_Template::myTemplateList,
                        1, //Min Num Sources
                        1, //Max Num Sources
                        SOP_Template::myVariables,
                        OP_FLAG_GENERATOR)

    );
};


//Parameters for the UI and input variables
static PRM_Name templateParm_name("templateParm", "Template Parm");
static PRM_Default templateParm_defaults(0);
static PRM_Range templateParm_range(PRM_RANGE_RESTRICTED, 0, PRM_RANGE_UI, 100);

PRM_Template
SOP_Template::myTemplateList[] = {
    PRM_Template(
        PRM_INT,
        PRM_Template::PRM_EXPORT_TBX,
        1,
        &templateParm_name,
        &templateParm_defaults,
        0,
        &templateParm_range),
    PRM_Template()            
};

enum {
    VAR_PT,
    VAR_NPT
};

CH_LocalVariable
SOP_Template::myVariables[] = {
    { "PT", VAR_PT, 0 },
    { "NPT", VAR_NPT, 0 },
    { 0, 0, 0},
};

bool
SOP_Template::evalVariableValue(fpreal &val, int index, int thread) {
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
SOP_Template::myConstructor(OP_Network *net, const char *name, OP_Operator *op) {
    return new SOP_Template(net, name, op); 
}

SOP_Template::SOP_Template(OP_Network *net, const char *name, OP_Operator *op)
: SOP_Node(net, name, op) {
    myCurrPoint = -1;
}

SOP_Template::~SOP_Template() {};

OP_ERROR SOP_Template::cookMySop(OP_Context &context) {
    double now;
    int variable;
    UT_Interrupt *boss;

    now = context.getTime();
    variable = evalFloat("templateParm", 0, now);

    cout << "Hello World, from SOP_Template.so" << endl;
    cout << "Template Parm Value is: " << variable << endl;
    cout.flush();

    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
        return error();

    // Duplicate input geometry
    duplicateSource(0, context);

    //gdp, a pointer to geometry that is passed in and out of the SOP
    //gdp->clearAndDestroy();
    
    if ( error() < UT_ERROR_ABORT){

        boss = UTgetInterrupt();

        if (boss->opStart("Cooking SOP...")) {
         /*
            Do Stuff
        */

        }
        boss->opEnd();
    };


    myCurrPoint = -1;

    return error();

};






