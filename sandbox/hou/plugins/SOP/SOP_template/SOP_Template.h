#define __SOP_Template__

#include <SOP/SOP_Node.h>

namespace HDK_Sample {

class SOP_Template : public SOP_Node {

    public:
        static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
        static PRM_Template myTemplateList[];
        static CH_LocalVariable myVariables[];

    protected:
        SOP_Template(OP_Network *net, const char *name, OP_Operator * op);
        virtual ~SOP_Template();
        virtual OP_ERROR cookMySop(OP_Context &context);
        virtual bool evalVariableValue( fpreal &val, int index, int thread);
        virtual bool evalVariableValue( UT_String &v, int i, int thread) {
            return evalVariableValue(v, i, thread);
        }

    private:
        int myCurrPoint;
        int myTotalPoints;

};

} // End HDK_Sample Namespace

