#ifndef UNPARSER_PYTHON_H_
#define UNPARSER_PYTHON_H_

#include "unparser.h"

class SgStatement;
class SgBasicBlock;
class SgClassDefinition;
class SgNamespaceDefinitionStatement;

#include "unparseLanguageIndependentConstructs.h"

class Unparse_Python : public UnparseLanguageIndependentConstructs
   {
     public:
          Unparse_Python(Unparser* unp, std::string fname);
          virtual ~Unparse_Python();
          virtual void unparseLanguageSpecificStatement(SgStatement*, SgUnparse_Info&);
          virtual void unparseLanguageSpecificExpression(SgExpression*, SgUnparse_Info&);
          virtual void unparseStringVal(SgExpression*, SgUnparse_Info&);

       // DQ (9/6/2010): Mark the derived class to support debugging.
          virtual std::string languageName() const { return "Python Unparser"; }

     protected:
          virtual void unparseAssignInitializer(SgAssignInitializer*, SgUnparse_Info&);
          virtual void unparseBasicBlock(SgBasicBlock*, SgUnparse_Info&);
          virtual void unparseBinaryOp(SgBinaryOp*, SgUnparse_Info&);
          virtual void unparseExprStatement(SgExprStatement*, SgUnparse_Info&);
          virtual void unparseFunctionCallExp(SgFunctionCallExp*, SgUnparse_Info&);
          virtual void unparseFunctionDeclaration(SgFunctionDeclaration*, SgUnparse_Info&);
          virtual void unparseFunctionDefinition(SgFunctionDefinition*, SgUnparse_Info&);
          virtual void unparseFunctionParameterList(SgFunctionParameterList*, SgUnparse_Info&);
          virtual void unparseIfStmt(SgIfStmt*, SgUnparse_Info&);
          virtual void unparseInitializedName(SgInitializedName*, SgUnparse_Info&);
          virtual void unparseLongIntVal(SgLongIntVal*, SgUnparse_Info&);
          virtual void unparseReturnStmt(SgReturnStmt*, SgUnparse_Info&);
          virtual void unparseStringVal(SgStringVal*, SgUnparse_Info&);
          virtual void unparseVarRefExp(SgVarRefExp*, SgUnparse_Info&);

          virtual std::string ws_prefix(int nesting_level);
   };

#define ROSE_PYTHON_ADD_OP      "+"
#define ROSE_PYTHON_ASSIGN_OP   "="
#define ROSE_PYTHON_BITAND_OP   "&"
#define ROSE_PYTHON_BITOR_OP    "|"
#define ROSE_PYTHON_BITXOR_OP   "^"
#define ROSE_PYTHON_DIV_OP      "/"
#define ROSE_PYTHON_EXP_OP      "**"
#define ROSE_PYTHON_IDIV_OP     "//"
#define ROSE_PYTHON_LSHIFT_OP   "<<"
#define ROSE_PYTHON_RSHIFT_OP   ">>"
#define ROSE_PYTHON_MOD_OP      "%"
#define ROSE_PYTHON_MULT_OP     "*"
#define ROSE_PYTHON_SUB_OP      "-"

#endif /* UNPARSER_PYTHON_H_ */



