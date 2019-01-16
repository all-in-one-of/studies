#define __SOP_ah_stick_points__

#include <SOP/SOP_Node.h>
#include <GU/GU_RayIntersect.h>

namespace HDK_Sample {

class SOP_ah_stick_points : public SOP_Node {

    public:
        static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
        static PRM_Template myTemplateList[];
        static CH_LocalVariable myVariables[];

    protected:
        SOP_ah_stick_points(OP_Network *net, const char *name, OP_Operator * op);
        virtual ~SOP_ah_stick_points();
        virtual OP_ERROR cookMySop(OP_Context &context);
        virtual bool evalVariableValue( fpreal &val, int index, int thread);
        virtual bool evalVariableValue( UT_String &v, int i, int thread) {
            return evalVariableValue(v, i, thread);
        }

    private:
        int myCurrPoint;
        int myTotalPoints;
        const GA_PointGroup *myGroup;

       GU_RayIntersect *intersect;
};

} // End HDK_Sample Namespace

