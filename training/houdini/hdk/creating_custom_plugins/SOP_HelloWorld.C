// Hello world OP

#include <SOP/SOP_Node.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>

void
newSopOperator(OP_OperatorTable *table)
{
    OP_Operator *op;
    op = new OP_Operator("ah_helloWorld",                // Internal name
                         "ahHelloWorld",                    // UI name
                         SOP_Star::myConstructor,   // How to build the SOP
                         SOP_Star::myTemplateList,  // My parameters
                         0,                         // Min # of sources
                         0,                         // Max # of sources
                         SOP_Star::myVariables,     // Local variables
                         OP_FLAG_GENERATOR);        // Generates new geo
    // After addOperator(), 'table' will take ownership of 'op'
    table->addOperator(op);
}
