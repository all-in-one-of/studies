/*
TODO
add check to ensure inputs are polygons
*/


#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;

#include <limits.h>
#include <SYS/SYS_Math.h>
#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <GU/GU_RayIntersect.h>
#include <UT/UT_Matrix.h>
#include <GU/GU_Detail.h>
#include <GU/GU_PrimPoly.h>
#include <GEO/GEO_PointTree.h>
#include <CH/CH_LocalVariable.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>

#include "SOP_ah_stick_points.h"

using namespace HDK_Sample;

void newSopOperator(OP_OperatorTable *table) {
    table->addOperator(
        new OP_Operator(
                        "ah_stick_points",
                        "ah_stick_points",
                        SOP_ah_stick_points::myConstructor,
                        SOP_ah_stick_points::myTemplateList,
                        1, //Min Num Sources
                        3, //Max Num Sources
                        SOP_ah_stick_points::myVariables,
                        OP_FLAG_GENERATOR)

    );
};


//Parameters for the UI and input variables
static PRM_Name templateParm_name("templateParm", "Template Parm");
static PRM_Default templateParm_defaults(0);
static PRM_Range templateParm_range(PRM_RANGE_RESTRICTED, 0, PRM_RANGE_UI, 100);

PRM_Template
SOP_ah_stick_points::myTemplateList[] = {
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
SOP_ah_stick_points::myVariables[] = {
    { "PT", VAR_PT, 0 },
    { "NPT", VAR_NPT, 0 },
    { 0, 0, 0},
};

bool
SOP_ah_stick_points::evalVariableValue(fpreal &val, int index, int thread) {
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
SOP_ah_stick_points::myConstructor(OP_Network *net, const char *name, OP_Operator *op) {
    return new SOP_ah_stick_points(net, name, op); 
}

SOP_ah_stick_points::SOP_ah_stick_points(OP_Network *net, const char *name, OP_Operator *op)
: SOP_Node(net, name, op) {
    myCurrPoint = -1;
}

SOP_ah_stick_points::~SOP_ah_stick_points() {};

OP_ERROR SOP_ah_stick_points::cookMySop(OP_Context &context) {

    UT_Interrupt *boss;

    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT) return error();

    duplicateSource(0, context);
    const GU_Detail* gdp_rest = inputGeo(1);
    const GU_Detail* gdp_deform = inputGeo(2);
    
    if ( error() < UT_ERROR_ABORT && gdp_rest && gdp_deform){

        boss = UTgetInterrupt();
        if (boss->opStart("Cooking SOP...")) {
    
            //geometry inputs
            GA_Index rest_size = gdp_rest->getPointMap().indexSize();
            GA_Index deform_size = gdp_deform->getPointMap().indexSize();

            if(rest_size!=deform_size) {
                addError(SOP_MESSAGE, "Rest Geo and Deformed Geo do not match");
                return error();
            }

            cout << endl << "rest type :" << typeid(gdp_rest).name() << endl;
            cout << "rest info: " << gdp_rest->info(cout) << endl;

            cout << endl << "defom type :" << typeid(gdp_deform).name() << endl;
            cout << "deform info: " << gdp_deform->info(cout) << endl;

            intersect = new GU_RayIntersect;
            intersect->init(gdp_rest);
        
            const GEO_Primitive *deform_prim;
            const GEO_Primitive *rest_prim;   
     
            GA_Offset ptoff;
            GA_FOR_ALL_PTOFF(gdp, ptoff) {

                UT_Vector3 ptpos = gdp->getPos3(ptoff);
                GU_MinInfo mininfo;
                
                //Initialize Offsets and Vectors
                GA_Offset deform_pt1_off, deform_pt2_off, deform_pt3_off;
                GA_Offset rest_pt1_off, rest_pt2_off, rest_pt3_off;
                UT_Vector3 rest_pt1_pos, rest_pt2_pos, rest_pt3_pos;
                UT_Vector3 deform_pt1_pos, deform_pt2_pos, deform_pt3_pos;
                UT_Vector3 rest_b1, rest_b2, rest_b3;
                UT_Vector3 deform_b1, deform_b2, deform_b3;

                //Find closest prim on restgeo with rayIntersect
                int success = intersect->minimumPoint(ptpos, mininfo);
                if(!success) 
                    addWarning(SOP_MESSAGE, "No Polys Found in Second Input");
                rest_prim = mininfo.prim;     

                //Find cooresponding prim on deformgeo
                GA_Index rest_prim_ind = rest_prim->getMapIndex();
                deform_prim = gdp_deform->getGEOPrimitiveByIndex(rest_prim_ind);
            
                deform_pt1_off = deform_prim->getPointOffset(0);
                deform_pt2_off = deform_prim->getPointOffset(1);
                deform_pt3_off = deform_prim->getPointOffset(2);
                rest_pt1_off = rest_prim->getPointOffset(0);
                rest_pt2_off = rest_prim->getPointOffset(1);
                rest_pt3_off = rest_prim->getPointOffset(2);
                
                deform_pt1_pos = gdp_deform->getPos3(deform_pt1_off);
                deform_pt2_pos = gdp_deform->getPos3(deform_pt2_off);
                deform_pt3_pos = gdp_deform->getPos3(deform_pt3_off);
                rest_pt1_pos = gdp_rest->getPos3(rest_pt1_off);
                rest_pt2_pos = gdp_rest->getPos3(rest_pt2_off);
                rest_pt3_pos = gdp_rest->getPos3(rest_pt3_off);
                
                rest_b1 = rest_pt2_pos - rest_pt1_pos;
                rest_b1.normalize();
                rest_b2 = rest_pt3_pos - rest_pt1_pos;
                rest_b2.normalize();
                rest_b3 = cross(rest_b1, rest_b2);
                
                deform_b1 = deform_pt2_pos - deform_pt1_pos;
                deform_b1.normalize();
                deform_b2 = deform_pt3_pos - deform_pt1_pos;
                deform_b2.normalize();
                deform_b3 = cross(deform_b1, deform_b2);
                
                // Do Transformation              
                UT_Matrix4D deform_prim_xform(
                            deform_b1[0], deform_b1[1], deform_b1[2], 0,
                            deform_b2[0], deform_b2[1], deform_b2[2], 0,
                            deform_b3[0], deform_b3[1], deform_b3[2], 0,
                            deform_pt1_pos[0],deform_pt1_pos[1],deform_pt1_pos[2],1
                            );
                UT_Matrix4D rest_prim_xform(
                            rest_b1[0], rest_b1[1], rest_b1[2], 0,
                            rest_b2[0], rest_b2[1], rest_b2[2], 0,
                            rest_b3[0], rest_b3[1], rest_b3[2], 0,
                            rest_pt1_pos[0],rest_pt1_pos[1],rest_pt1_pos[2],1
                            );
                rest_prim_xform.invert();
                 
                ptpos *= rest_prim_xform;
                ptpos *= deform_prim_xform;
                gdp->setPos3(ptoff, ptpos);
            }
        }
        boss->opEnd();
    };


    cout.flush();

    //myCurrPoint = -1;

    return error();

};


