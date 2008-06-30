#ifndef ROSE_SAGE_INTERFACE
#define ROSE_SAGE_INTERFACE

// DQ (8/19/2004): Moved from ROSE/src/midend/astRewriteMechanism/rewrite.h
//! A global function for getting the string associated with an enum (which is defined in global scope)
std::string getVariantName (VariantT v);

// DQ (12/9/2004): Qing, Rich and Dan have decided to start this namespace within ROSE
// This namespace is specific to interface functions that operate on the Sage III AST.
// The name was chosen so as not to conflict with other classes within ROSE.
// This will become the future home of many interface functions which operate on
// the AST and which are generally useful to users.  As a namespace multiple files can be used
// to represent the compete interface and different developers may contribute interface
// functions easily.

// Constructor handling: (We have sageBuilder.h now for this purpose, Liao 2/1/2008)
//     We could add simpler layers of support for construction of IR nodes by 
// hiding many details in "makeSg***()" functions.  such functions would
// return pointers to the associated Sg*** objects and would be able to hide
// many IR specific details, including:
//      memory handling
//      optional parameter settings not often required
//      use of Sg_File_Info objects (and setting them as transformations)
//      
// namespace AST_Interface  (this name is taken already by some of Qing's work :-)

//! An alias for Sg_File_Info::generateDefaultFileInfoForTransformationNode()
#define TRANS_FILE Sg_File_Info::generateDefaultFileInfoForTransformationNode()

//------------------------------------------------------------------------
/*! \brief This namespace is to organize functions that are useful when operating on the AST.

  \defgroup frontendSageUtilityFunctions SAGE III utility functions(SageInterface)
  \ingroup ROSE_FrontEndGroup

    The Sage III IR design attempts to be minimalist.  thus additional functionality is
intended to be presented using separate higher level interfaces which work with the IR.
The namespace, SageInterface, collects functions that operate on the IR and are supportive of numerous types of routine operations required to support general analysis and transformation of the AST.

    \internal Further organization of the functions in this namespace is required.
Major AST manipulation functions are scattered in the following directories 
   - src/midend/astUtil/astInterface
   - src/roseSupport/utility_function.h,  namespace ROSE 
   - src/roseSupport/TransformationSupport.h, class TransformationSupport
   - src/midend/astInlining/inlinerSupport.C
   - src/frontend/SageIII/sageInterface
   - projects: such as outliner, OpenMP_Translator
Some other utility functions not related AST can be found in 
   - src/util/stringSupport/string_functions.h, namespace StringUtility
   - src/roseExtensions/dataStructureTraversal/helpFunctions.C
   - projects/dataStructureGraphing/helpFunctions.C


    \todo A number of additional things to do:
         - Pull scope handling out of EDG/Sage III translation so that is is made 
           available to anyone else building the Sage III IR from scratch (which 
           when it gets non-trivial, involves the manipulation of scopes).
         - Other stuff ...
 */
namespace SageInterface
{
//! An internal counter for generating unique SgName
extern int gensym_counter;

//------------------------------------------------------------------------
//@{
/*! @name Symbol tables
  \brief  utility functions for symbol tables
*/
  // Liao 1/22/2008, used for get symbols for generating variable reference nodes
  // ! Find a variable symbol in current and ancestor scopes for a given name
  SgVariableSymbol *lookupVariableSymbolInParentScopes (const SgName &	name,
							SgScopeStatement *currentScope=NULL);
  //! find a symbol in current and ancestor scopes for a given variable name, starting from top of ScopeStack if currentscope is not given or NULL.
  SgSymbol *lookupSymbolInParentScopes (const SgName &	name,
							SgScopeStatement *currentScope=NULL);

  // DQ (11/24/2007): Functions moved from the Fortran support so that they could be called from within astPostProcessing.
  //!look up the first matched function symbol in parent scopes given only a function name, starting from top of ScopeStack if currentscope is not given or NULL
  SgFunctionSymbol *lookupFunctionSymbolInParentScopes (const SgName &	functionName,
							SgScopeStatement *currentScope=NULL);

  // Liao, 1/24/2008, find exact match for a function
  //!look up function symbol in parent scopes given both name and function type, starting from top of ScopeStack if currentscope is not given or NULL
  SgFunctionSymbol *lookupFunctionSymbolInParentScopes (const SgName &  functionName, 
                                                        const SgType* t,
                                                        SgScopeStatement *currentScope=NULL);

  /*! \brief set_name of symbol in symbol table.

      This function extracts the symbol from the relavant symbol table, 
      changes the name (at the declaration) and reinserts it into the 
      symbol table.

      \internal  I think this is what this function does, I need to double check.
   */
  // DQ (12/9/2004): Moved this function (by Alin Jula) from being a member of SgInitializedName
  // to this location where it can be a part of the interface for the Sage III AST.
  int set_name (SgInitializedName * initializedNameNode, SgName new_name);

  /*! \brief Output function type symbols in global function type symbol table.
   */
  void outputGlobalFunctionTypeSymbolTable ();

  // DQ (6/27/2005):
  /*! \brief Output the local symbol tables.

      \implementation Each symbol table is output with the file infor where it is located in the source code.
   */
  void outputLocalSymbolTables (SgNode * node);

  class OutputLocalSymbolTables:public AstSimpleProcessing
        {
          public:
    void visit (SgNode * node);
        };
  /*! \brief Regenerate the symbol table.

     \implementation current symbol table must be NULL pointer before calling this 
     function (for safety, but is this a good idea?)
   */
  // DQ (9/28/2005):
  void rebuildSymbolTable (SgScopeStatement * scope);

  //SgNode::get_globalFunctionTypeTable() ;

//@}

//------------------------------------------------------------------------
//@{
/*! @name Stringify 
  \brief Generate a useful string (name) to describe a SgNode
*/
  /*! \brief Generate a useful name to describe the SgNode

      \internal default names are used for SgNode objects that can not be associated with a name.
   */
  // DQ (9/21/2005): General function for extracting the name of declarations (when they have names)
    std::string get_name (const SgNode * node);

  /*! \brief Generate a useful name to describe the declaration

      \internal default names are used for declarations that can not be associated with a name.
   */
  // DQ (6/13/2005): General function for extracting the name of declarations (when they have names)
    std::string get_name (const SgStatement * stmt);

  /*! \brief Generate a useful name to describe the expression

      \internal default names are used for expressions that can not be associated with a name.
   */
    std::string get_name (const SgExpression * expr);

  /*! \brief Generate a useful name to describe the declaration

      \internal default names are used for declarations that can not be associated with a name.
   */
  // DQ (6/13/2005): General function for extracting the name of declarations (when they have names)
    std::string get_name (const SgDeclarationStatement * declaration);

  /*! \brief Generate a useful name to describe the scope

      \internal default names are used for scope that cannot be associated with a name.
   */
  // DQ (6/13/2005): General function for extracting the name of declarations (when they have names)
    std::string get_name (const SgScopeStatement * scope);

  /*! \brief Generate a useful name to describe the SgSymbol

      \internal default names are used for SgSymbol objects that cannot be associated with a name.
   */
  // DQ (2/11/2007): Added this function to make debugging support more complete (useful for symbol table debugging support).
    std::string get_name (const SgSymbol * symbol);

  /*! \brief Generate a useful name to describe the SgType

      \internal default names are used for SgType objects that cannot be associated with a name.
   */
    std::string get_name (const SgType * type);
      

  /*! \brief Generate a useful name to describe the SgSupport IR node
   */
    std::string get_name (const SgSupport * node);

//@}

//------------------------------------------------------------------------
//@{
/*! @name Class utilities
  \brief
*/
  /*! \brief Get the default destructor from the class declaration
   */
  // DQ (6/21/2005): Get the default destructor from the class declaration
  SgMemberFunctionDeclaration *getDefaultDestructor (SgClassDeclaration *
						     classDeclaration);

  /*! \brief Get the default constructor from the class declaration
   */
  // DQ (6/22/2005): Get the default constructor from the class declaration
  SgMemberFunctionDeclaration *getDefaultConstructor (SgClassDeclaration *
						      classDeclaration);
  /*! \brief Return true if template definition is in the class, false if outside of class.
   */
  // DQ (8/27/2005): 
  bool templateDefinitionIsInClass (SgTemplateInstantiationMemberFunctionDecl
				    * memberFunctionDeclaration);

  /*! \brief Generate a non-defining (forward) declaration from a defining function declaration.

     \internal should put into sageBuilder ?
   */
  // DQ (9/17/2005):
     SgTemplateInstantiationMemberFunctionDecl*
     buildForwardFunctionDeclaration
        (SgTemplateInstantiationMemberFunctionDecl * memberFunctionInstantiation);

  //! Check if a SgNode is a declaration for a structure
  bool isStructDeclaration(SgNode * node);
#if 0
// DQ (8/28/2005): This is already a member function of the SgFunctionDeclaration 
// (so that it can handle template functions and member functions)

  /*! \brief Return true if member function of a template member function,
             of false if a non-template member function in a templated class.
   */
   // DQ (8/27/2005):
  bool isTemplateMemberFunction (SgTemplateInstantiationMemberFunctionDecl *
				 memberFunctionDeclaration);
#endif

//@}

//------------------------------------------------------------------------
//@{
/*! @name Unsorted
  \brief Not sure the classifications right now
*/

  /*! \brief Return true if function is overloaded.
   */
  // DQ (8/27/2005):
  bool isOverloaded (SgFunctionDeclaration * functionDeclaration);

  //! Check if a SgNode is a main() function declaration
  bool isMain (const SgNode* node);
  // DQ (6/22/2005):
  /*! \brief Generate unique name from C and C++ constructs.

      This is support for the AST merge, but is generally useful as a more general mechanism than 
      name mangling which is more closely ties to the generation of names to support link-time function name 
      resolution.  This is more general than common name mangling in that it resolves more relavant differences
      between C and C++ declarations. (e.g. the type within the declaration: "struct { int:8; } foo;").

      \implementation current work does not support expressions.

   */
    std::string generateUniqueName (SgNode * node,
				    bool
				    ignoreDifferenceBetweenDefiningAndNondefiningDeclarations);

  // DQ (3/10/2007): 
  //! Generate a unique string from the source file position information
    std::string declarationPositionString (SgDeclarationStatement *
					   declaration);

  // DQ (1/20/2007): 
  //! Added mechanism to generate project name from list of file names
    std::string generateProjectName (const SgProject * project);

  /*! \brief Returns STL vector of SgFile IR node pointers. 

      Demonstrates use of restrivcted traversal over just SgFile IR nodes.
   */
    std::vector < SgFile * >generateFileList ();

  // DQ (10/6/2006): Added support for faster mangled name generation (caching avoids recomputation).
  /*! \brief Support for faster mangled name generation (caching avoids recomputation).

   */
  void clearMangledNameCache (SgGlobal * globalScope);
  void resetMangledNameCache (SgGlobal * globalScope);
  std::string getMangledNameFromCache (SgNode * astNode);
  std::string addMangledNameToCache (SgNode * astNode,
				       const std::string & mangledName);

  SgDeclarationStatement * getNonInstantiatonDeclarationForClass
    (SgTemplateInstantiationMemberFunctionDecl * memberFunctionInstantiation);


  // DQ (10/14/2006): This function tests the AST to see if for a non-defining declaration, the 
  // bool declarationPreceedsDefinition ( SgClassDeclaration* classNonDefiningDeclaration, SgClassDeclaration* classDefiningDeclaration );
  //! Check if a defining declaration comes before of after the non-defining declaration.
  bool declarationPreceedsDefinition (SgDeclarationStatement *
				      nonDefiningDeclaration,
				      SgDeclarationStatement *
				      definingDeclaration);

  // DQ (10/19/2006): Function calls have interesting context dependent rules to determine if 
  // they are output with a global qualifier or not.  Were this is true we have to avoid global 
  // qualifiers, since the function's scope has not been defined.  This is an example of where
  // qualification of function names in function calls are context dependent; an interesting
  // example of where the C++ language is not friendly to source-to-source processing :-).
  bool
    functionCallExpressionPreceedsDeclarationWhichAssociatesScope
    (SgFunctionCallExp * functionCall);

 /*! \brief Compute the intersection set for two ASTs.

     This is part of a test done by the copy function to compute those IR nodes in the copy that still reference the original AST.
  */
    std::vector < SgNode * >astIntersection (SgNode * original, SgNode * copy,
					     SgCopyHelp * help = NULL);
  //! Deep copy an arbitrary subtree
   SgNode* deepCopyNode (const SgNode* subtree); 

//! An internal template function for deep copying a subtree, used to create deepcopy functions with specialized parameter and return types. e.g SgExpression* copyExpression(SgExpression* e);
   template <typename NodeType>
   NodeType* deepCopy (const NodeType* subtree) {
     return dynamic_cast<NodeType*>(deepCopyNode(subtree));
   }

//! Deep copy an expression
   SgExpression* copyExpression(SgExpression* e);

//!Deep copy a statement
   SgStatement* copyStatement(SgStatement* s);

// from VarSym.cc in src/midend/astOutlining/src/ASTtools
//! Get the variable symbol for the first initialized name of a declaration stmt.
  SgVariableSymbol* getFirstVarSym (SgVariableDeclaration* decl);

//! A special purpose statement removal function, originally from inlinerSupport.h, Need Jeremiah's attention to refine it. Please don't use it for now.
void myRemoveStatement(SgStatement* stmt);

bool isConstantTrue(SgExpression* e);
bool isConstantFalse(SgExpression* e);

bool isCallToParticularFunction(SgFunctionDeclaration* decl, SgExpression* e);
bool isCallToParticularFunction(const std::string& qualifiedName, size_t arity, SgExpression* e);


//! Interface for creating a statement whose computation writes its answer into
//! a given variable.
class StatementGenerator {
  public:
  virtual ~StatementGenerator() {};
  virtual SgStatement* generate(SgExpression* where_to_write_answer) = 0;
};

//@}

//------------------------------------------------------------------------
//@{
/*! @name AST properties
  \brief version, language properties of current AST.  
*/

//  std::string version();  // utility_functions.h, version number
  /*! Brief These traverse the memory pool of SgFile IR nodes and determine what languages are in use!
   */
  bool is_C_language ();
  bool is_UPC_language ();
  //! Check if dynamic threads compilation is used for UPC programs
  bool is_UPC_dynamic_threads();
  bool is_C99_language ();
  bool is_Cxx_language ();
  bool is_Fortran_language ();
  bool is_binary_executable();
  bool is_mixed_C_and_Cxx_language ();
  bool is_mixed_Fortran_and_C_language ();
  bool is_mixed_Fortran_and_Cxx_language ();
  bool is_mixed_Fortran_and_C_and_Cxx_language ();
  
//@}

//------------------------------------------------------------------------
//@{
/*! @name Scope
  \brief 
*/

  // DQ (10/5/2006): Added support for faster (non-quadratic) computation of unique 
  // labels for scopes in a function (as required for name mangling).
  /*! \brief Assigns unique numbers to each SgScopeStatement of a function. 

      This is used to provide unique names for variables and types defined is 
      different nested scopes of a function (used in mangled name generation).
   */
  void resetScopeNumbers (SgFunctionDefinition * functionDeclaration);

  // DQ (10/5/2006): Added support for faster (non-quadratic) computation of unique 
  // labels for scopes in a function (as required for name mangling).
  /*! \brief Clears the cache of scope,integer pairs for the input function.

      This is used to clear the cache of computed unique lables for scopes in a function.
      This function should be called after any transformation on a function that might effect
      the allocation of scopes and cause the existing unique numbrs to be incorrect.
      This is part of support to provide unique names for variables and types defined is 
      different nested scopes of a function (used in mangled name generation).
   */
  void clearScopeNumbers (SgFunctionDefinition * functionDefinition);

  
  SgNamespaceDefinitionStatement * enclosingNamespaceScope (SgDeclarationStatement * declaration);
//  SgNamespaceDefinitionStatement * getEnclosingNamespaceScope (SgNode * node);

  bool isPrototypeInScope (SgScopeStatement * scope,
			   SgFunctionDeclaration * functionDeclaration,
			   SgDeclarationStatement * startingAtDeclaration);
//@}
//------------------------------------------------------------------------
//@{
/*! @name Preprocessing Information
  \brief #if-#else-#end, comments, #include, etc
*/

//! Insert  #include "filename" or #include <filename> (system header) into the global scope containing the current scope.
PreprocessingInfo* insertHeader(const std::string& filename, bool isSystemHeader=false, SgScopeStatement* scope=NULL);

//! Move preprocessing information of stmt_src to stmt_dst
void moveUpPreprocessingInfo (SgStatement* stmt_dst, SgStatement* stmt_src);

//@}


//------------------------------------------------------------------------
//@{
/*! @name Source File Position
  \brief set Sg_File_Info for a SgNode
*/
//! Build and attach comment, comment style is inferred from the language type of the target node if not provided
PreprocessingInfo* attachComment(SgLocatedNode* target, const std::string & content,
               PreprocessingInfo::RelativePositionType position=PreprocessingInfo::before,
               PreprocessingInfo::DirectiveType dtype= PreprocessingInfo::CpreprocessorUnknownDeclaration);


  // Liao, 1/8/2007, set file info. for a whole subtree as transformation generated
//! set current node's source position as transformation generated
  void setOneSourcePositionForTransformation(SgNode *node);

//! recursively set source position info(Sg_File_Info) as transformation generated
  void setSourcePositionForTransformation (SgNode * root);

//! set source position info(Sg_File_Info) as transformation generated for all SgNodes in memory pool
  void setSourcePositionForTransformation_memoryPool();

//! Set the source position of SgLocatedNode to Sg_File_Info::generateDefaultFileInfo(). These nodes WILL be unparsed. Not for transformation usage.
  void setSourcePosition (SgLocatedNode * locatedNode);

//@}


//------------------------------------------------------------------------
//@{
/*! @name Data type
  \brief
*/

// from src/midend/astInlining/typeTraits.h
// src/midend/astUtil/astInterface/AstInterface.h

//! get the right bool type according to C or C++ language input
SgType* getBoolType(SgNode* n);

//! Is a type default constructible?  This may not quite work properly.
bool isDefaultConstructible(SgType* type);

//! Is a type copy constructible?  This may not quite work properly.
bool isCopyConstructible(SgType* type);

//! Does a type have a trivial (built-in) destructor?
bool hasTrivialDestructor(SgType* t);

//! Is this type a non-constant reference type?
bool isNonconstReference(SgType* t);

//! Is this type a const or non-const reference type?
bool isReferenceType(SgType* t);

//! Is this a const type?
bool isConstType(SgType* t);

//! Is this a scalar type?
bool isScalarType(SgType* t);

//! Lookup a named type based on its name, bottomup searching from a specified scope. Note name collison might be allowed for c (not C++) between typedef and enum/struct. Only the first matched named type will be returned in this case. typedef is returned as it is, not the base type it actually refers to.
SgType* lookupNamedTypeInParentScopes(const std::string& type_name, SgScopeStatement* scope=NULL);

//@}

//------------------------------------------------------------------------
//@{
/*! @name Loop handling
  \brief
*/

// by Jeremiah
//! Add a step statement to the end of a loop body
//! Add a new label to the end of the loop, with the step statement after
//! it; then change all continue statements in the old loop body into
//! jumps to the label
//!
//! For example:
//! while (a < 5) {if (a < -3) continue;} (adding "a++" to end) becomes
//! while (a < 5) {if (a < -3) goto label; label: a++;}
void addStepToLoopBody(SgScopeStatement* loopStmt, SgStatement* step);

void moveForStatementIncrementIntoBody(SgForStatement* f);
void convertForToWhile(SgForStatement* f);
void convertAllForsToWhiles(SgNode* top);
//! change continue statements in a given block of code to gotos to a label
void changeContinuesToGotos(SgStatement* stmt, SgLabelStatement* label);
 
//! Routines to get and set the body of a loop
SgStatement* getLoopBody(SgScopeStatement* loop);
void setLoopBody(SgScopeStatement* loop, SgStatement* body);

//! Routines to get and set the condition of a loop
SgStatement* getLoopCondition(SgScopeStatement* loop);
void setLoopCondition(SgScopeStatement* loop, SgStatement* cond);

//@}

//------------------------------------------------------------------------
//@{
/*! @name Topdown search
  \brief Top-down traversal from current node to find a node of a specified type
*/

//! query a subtree to get all nodes of a given type.
template <typename NodeType>
std::vector<NodeType*> querySubTree(SgNode* top, VariantT variant);

/*! \brief top-down traversal from current node to find the main() function declaration
*/
SgFunctionDeclaration* findMain(SgNode* currentNode);  

	  //midend/programTransformation/partialRedundancyElimination/pre.h
//! find referenced symbols within an expression
std::vector<SgVariableSymbol*> getSymbolsUsedInExpression(SgExpression* expr);

//! Find break statements inside a particular statement, stopping at nested loops or switches
/*! loops or switch statements defines their own contexts for break
 statements.  The function will stop immediately if run on a loop or switch
 statement.  If fortranLabel is non-empty, breaks (EXITs) to that label within
 nested loops are included in the returned list.
*/
std::vector<SgBreakStmt*> findBreakStmts(SgStatement* code, const std::string& fortranLabel = ""); 

//! Find all continue statements inside a particular statement, stopping at nested loops
/*! Nested loops define their own contexts for continue statements.  The
 function will stop immediately if run on a loop
 statement.  If fortranLabel is non-empty, continues (CYCLEs) to that label
 within nested loops are included in the returned list.
*/
  std::vector<SgContinueStmt*> findContinueStmts(SgStatement* code, const std::string& fortranLabel = "");
  std::vector<SgGotoStatement*> findGotoStmts(SgStatement* scope, SgLabelStatement* l);
  std::vector<SgReturnStmt*> findReturnStmts(SgStatement* scope);
  std::vector<SgStatement*> getSwitchCases(SgSwitchStatement* sw); 
#if 0 //TODO
  // 1. preorder traversal from current SgNode till find next SgNode of type V_SgXXX
  //    until reach the end node
  SgNode* getNextSgNode( const SgNode* astSourceNode, VariantT=V_SgNode, SgNode* astEndNode=NULL);

  // 2. return all nodes of type VariantT following the source node
  std::vector<SgNode*> getAllNextSgNode( const SgNode* astSourceNode, VariantT=V_SgNode, SgNode* astEndNode=NULL);

#endif

//@}

//------------------------------------------------------------------------
//@{
/*! @name Bottom up search 
  \brief Backwards traverse through the AST to find a node, findEnclosingXXX()
*/
// remember to put const to all arguments.
//! traverse back through a node's parents to find the first node matching the desired type, includingSelf specifies if the current node is checked.
SgNode * getEnclosingNode(const SgNode*, const VariantT, const bool includingSelf=false);

//! get the closest scope 
SgScopeStatement* getScope(const SgNode* astNode); 

  //! traverse back through a node's parents to find the enclosing global scope
  SgGlobal* getGlobalScope( const SgNode* astNode);

  //! find the function definition
  SgFunctionDefinition* getEnclosingProcedure(SgNode* n, const bool includingSelf=false);

  SgFunctionDefinition* getEnclosingFunctionDefinition(SgNode* astNode, const bool includingSelf=false);

  //! Find the closest enclosing statement, including the given node
  SgStatement* getEnclosingStatement(SgNode* n);

  //! Find the closest switch outside a given statement (normally used for case and default statements)
  SgSwitchStatement* findEnclosingSwitch(SgStatement* s);

  //! Find the closest loop outside the given statement; if fortranLabel is not empty, the Fortran label of the loop must be equal to it
  SgScopeStatement* findEnclosingLoop(SgStatement* s, const std::string& fortranLabel = "", bool stopOnSwitches = false);

  SgFunctionDeclaration * getEnclosingFunctionDeclaration (SgNode * astNode, const bool includingSelf=false);

   //roseSupport/utility_functions.h
  //! get the SgFile node from current node
  SgFile* getEnclosingFileNode (SgNode* astNode );

  //! Get the initializer containing an expression if it is within an initializer.
  SgInitializer* getInitializerOfExpression(SgExpression* n);

  //! Get the closest class definition enclosing the specified AST node, 
  SgClassDefinition* getEnclosingClassDefinition(SgNode* astnode, const bool includingSelf=false); 

// TODO
#if 0
   SgNode * getEnclosingSgNode(SgNode* source,VariantT, SgNode* endNode=NULL);
   std::vector<SgNode *>  getAllEnclosingSgNode(SgNode* source,VariantT, SgNode* endNode=NULL);
   SgVariableDeclaration* findVariableDeclaratin( const string& varname)

   SgClassDeclaration* getEnclosingClassDeclaration( const SgNode* astNode);
   SgClassDefinition* getEnclosingClassDefinition( const SgNode* astNode);

   // e.g. for some expression, find its parent statement
   SgStatement* getEnclosingStatement(const SgNode* astNode);

   SgSwitchStatement* getEnclosingSwitch(SgStatement* s); 
   SgModuleStatement* getEnclosingModuleStatement( const SgNode* astNode);
  
  // used to build a variable reference for compiler generated code in current scope
   SgSymbol * findReachingDefinition (SgScopeStatement* startScope, SgName &name);
#endif
//@}

//------------------------------------------------------------------------
//@{
/*! @name AST Walk and Traversal
  \brief 
*/
  // Liao, 1/9/2008
  /*! 
  	\brief return the first global scope under current project
  */
  SgGlobal * getFirstGlobalScope(SgProject *project);

  /*!
	\brief get the last statement within a scope, return NULL if it does not exit
  */
  SgStatement* getLastStatement(SgScopeStatement *scope);

  //! Get the first statement within a scope, return NULL if it does not exist. Skip compiler-generated statement by default
  SgStatement* getFirstStatement(SgScopeStatement *scope,bool includingCompilerGenerated=false);

//! Get next statement within the same scope of current statement 
  SgStatement* getNextStatement(SgStatement * currentStmt);

//! Get previous statement within the same scope of current statement 
  SgStatement* getPreviousStatement(SgStatement * currentStmt);
#if 0 //TODO
  // preorder traversal from current SgNode till find next SgNode of type V_SgXXX
  SgNode* getNextSgNode( const SgNode* currentNode, VariantT=V_SgNode);
#endif 
//@}

//------------------------------------------------------------------------
//@{
/*! @name AST comparison
  \brief Compare AST nodes, subtree, etc
*/
  //! Check if a SgIntVal node has a given value 
 bool isEqualToIntConst(SgExpression* e, int value); 
//@}

//------------------------------------------------------------------------
//@{
/*! @name AST insert, removal, and replacement
  \brief Add, remove,and replace AST
 
  scope->append_statement(), exprListExp->append_expression() etc. are not enough to handle side effect of parent pointers, symbol tables, preprocessing info, defining/nondefining pointers etc.
*/

//! append a statement to the end of the current scope, handle side effect of appending statements, e.g. preprocessing info, defining/nondefining pointers etc.
void appendStatement(SgStatement *stmt, SgScopeStatement* scope=NULL);

//! append a list of statements to the end of the current scope, handle side effect of appending statements, e.g. preprocessing info, defining/nondefining pointers etc.
void appendStatementList(const std::vector<SgStatement*>& stmt, SgScopeStatement* scope=NULL);

//! prepend a statement to the beginning of the current scope, handling side
//! effects as appropriate
void prependStatement(SgStatement *stmt, SgScopeStatement* scope=NULL);

//! prepend a list of statements to the beginning of the current scope,
//! handling side effects as appropriate
void prependStatementList(const std::vector<SgStatement*>& stmt, SgScopeStatement* scope=NULL);

//! insert a statement before or after the target statement within the target's scope
void insertStatement(SgStatement *targetStmt, SgStatement* newStmt, bool insertBefore= true);

//! insert a list of statements before or after the target statement within the
//target's scope
void insertStatementList(SgStatement *targetStmt, const std::vector<SgStatement*>& newStmts, bool insertBefore= true);

//! insert a statement before a target statement
void insertStatementBefore(SgStatement *targetStmt, SgStatement* newStmt);

//! insert a list of statements before a target statement
void insertStatementListBefore(SgStatement *targetStmt, const std::vector<SgStatement*>& newStmts);

//! insert a statement after a target statement
void insertStatementAfter(SgStatement *targetStmt, SgStatement* newStmt);

//! insert a list of statements after a target statement
void insertStatementListAfter(SgStatement *targetStmt, const std::vector<SgStatement*>& newStmt);

//! Replace a statement with another
void replaceStatement(SgStatement* oldStmt, SgStatement* newStmt);

//! append an argument to SgFunctionParameterList, transparently set parent,scope, and symbols for arguments when possible
/*! we recommend to build SgFunctionParameterList before building a function declaration
 However, it is still allowed to append new arguments for existing function declarations.
 \todo function type , function symbol also need attention.
*/
SgVariableSymbol* appendArg(SgFunctionParameterList *, SgInitializedName*);

//! append an expression to a SgExprListExp, set the parent pointer also
void appendExpression(SgExprListExp *, SgExpression*);

//! set parameter list for a function declaration, considering existing parameter list etc.
void setParameterList(SgFunctionDeclaration *func,SgFunctionParameterList *paralist);

//! set a pragma of a pragma declaration. handle memory release for preexisting pragma, and set parent pointer.
void setPragma(SgPragmaDeclaration* decl, SgPragma *pragma);

  //! Replace an expression with another, used for variable reference substitution and others. the old expression can be deleted (default case)  or kept.
void replaceExpression(SgExpression* oldExp, SgExpression* newExp, bool keepOldExp=false);

//! Replace a given expression with a list of statements produced by a generator
void replaceExpressionWithStatement(SgExpression* from,
				    SageInterface::StatementGenerator* to);
//! Similar to replaceExpressionWithStatement, but with more restrictions.
//! Assumptions: from is not within the test of a loop or ifStmt,  not currently traversing from or the statement it is in
void replaceSubexpressionWithStatement(SgExpression* from,
				      SageInterface::StatementGenerator* to);

//! Set operands for expressions with single operand, such as unary expressions. handle file info, lvalue, pointer downcasting, parent pointer etc.
void setOperand(SgExpression* target, SgExpression* operand);

//!set left hand operand for binary expressions, transparently downcasting target expressions when necessary
void setLhsOperand(SgExpression* target, SgExpression* lhs);

//!set left hand operand for binary expression
void setRhsOperand(SgExpression* target, SgExpression* rhs);

//! Set original expression trees to NULL for SgValueExp or SgCastExp expressions, so you can change the value and have it unparsed correctly.
void removeAllOriginalExpressionTrees(SgNode* top);

//@}
//------------------------------------------------------------------------
//@{
/*! @name AST repair, fixup, and postprocessing.
  \brief 
*/
//! Connect variable reference to the right variable symbols when feasible, return the number of references being fixed.
/*! In AST translation, it is possible to build a variable reference before the variable
 is being declared. buildVarRefExp() will use fake initialized name and symbol as placeholders
 to get the work done. Users should call fixVariableReference() when AST is complete and all
 variable declarations are in place.
*/
int fixVariableReferences(SgNode* root);

//!Patch up symbol, scope, and parent information when a SgVariableDeclaration's scope is known.
/*!
It is possible to build a variable declaration without knowing its scope information during bottom-up construction of AST, though top-down construction is recommended in general. 
In this case, we have to patch up symbol table, scope and parent information when the scope is known. This function is usually used internally within appendStatment(), insertStatement().
*/
void fixVariableDeclaration(SgVariableDeclaration* varDecl, SgScopeStatement* scope);

//! fixup symobls, parent and scope pointers. Used internally within appendStatment(), insertStatement() etc when a struct declaration was built without knowing its target scope.
void fixStructDeclaration(SgClassDeclaration* structDecl, SgScopeStatement* scope);

//@}

//------------------------------------------------------------------------
//@{
/*! @name Advanced AST transformations and optimizations
  \brief Some complex but commonly used AST transformations. 
  */

//!Instrument(Add a statement, often a function call) into a function right before the return points, handle multiple return statements and return expressions with side effects. Return the number of statements inserted. 
/*! Useful when adding a runtime library call to terminate the runtime system right before the end of a program, especially for OpenMP and UPC runtime systems. Return with complex expressions with side effects are rewritten using an additional assignment statement. 
 */
int instrumentEndOfFunction(SgFunctionDeclaration * func, SgStatement* s);

//! Remove jumps whose label is immediately after the jump.  Used to clean up inlined code fragments.
void removeJumpsToNextStatement(SgNode*);

//! Remove labels which are not targets of any goto statements
void removeUnusedLabels(SgNode* top);

//! Remove consecutive labels
void removeConsecutiveLabels(SgNode* top);

//! Replace an expression with a temporary variable and an assignment statement
/*!
 Add a new temporary variable to contain the value of 'from'
 Change reference to 'from' to use this new variable
 Assumptions: 'from' is not within the test of a loop or 'if'
              not currently traversing 'from' or the statement it is in

 */
 SgAssignInitializer* splitExpression(SgExpression* from, std::string newName = "");

//! Split long expressions into blocks of statements
void splitExpressionIntoBasicBlock(SgExpression* expr);

//! Remove labeled goto statements
void removeLabeledGotos(SgNode* top);

//! If the given statement contains any break statements in its body, add a new label below the statement and change the breaks into gotos to that new label.
void changeBreakStatementsToGotos(SgStatement* loopOrSwitch);

//! Check if the body of a 'for' statement is a SgBasicBlcok, create one if not. 
SgBasicBlock* ensureBasicBlockAsBodyOfFor(SgForStatement* fs);
//! Check if the body of a 'while' statement is a SgBasicBlcok, create one if not. 
SgBasicBlock* ensureBasicBlockAsBodyOfWhile(SgWhileStmt* ws);
//! Check if the body of a 'do .. while' statement is a SgBasicBlcok, create one if not. 
SgBasicBlock* ensureBasicBlockAsBodyOfDoWhile(SgDoWhileStmt* ws);
//! Check if the true body of a 'if' statement is a SgBasicBlcok, create one if not. 
SgBasicBlock* ensureBasicBlockAsTrueBodyOfIf(SgIfStmt* ifs);
//! Check if the false body of a 'if' statement is a SgBasicBlcok, create one if not. 
SgBasicBlock* ensureBasicBlockAsFalseBodyOfIf(SgIfStmt* ifs);
SgBasicBlock* ensureBasicBlockAsBodyOfCatch(SgCatchOptionStmt* cos);
SgBasicBlock* ensureBasicBlockAsParent(SgStatement* s);

//! Fix up ifs, loops, etc. to have blocks as all components and add dummy else
//! clauses to if statements that don't have them
void changeAllLoopBodiesToBlocks(SgNode* top);

//@}


#if 0

//------------------------AST dump, stringify-----------------------------
//------------------------------------------------------------------------
  std::string buildOperatorString ( SgNode* astNode ); //transformationSupport.h

  // do we need these?
  std::string dump_node(const SgNode* astNode);
  std::string dump_tree(const SgNode* astNode);

  // or a friendly version of  unparseToString(), as a memeber function
  std::string SgNode::toString(bool asSubTree=true); // dump node or subtree

//----------------------------AST comparison------------------------------
//------------------------------------------------------------------------
// How to get generic functions for comparison? 
  bool isNodeEqual(SgNode* node1, SgNode* node2); //?
  bool isTreeEqual(SgNode* tree1, SgNode* tree2);

	//! Are two expressions equal (using a deep comparison)?
  bool expressionTreeEqual(SgExpression*, SgExpression*);
	//! Are corresponding expressions in two lists equal (using a deep comparison)?
  bool expressionTreeEqualStar(const SgExpressionPtrList&,
                             const SgExpressionPtrList&);

//----------------------AST verfication/repair----------------------------
//------------------------------------------------------------------------
// sanity check of AST subtree, any suggestions?
//  TODO
    verifySgNode(SgNode* node, bool subTree=true);
  //src/midend/astDiagnostics/AstConsistencyTests.h
  // AstTests::runAllTests(SgProject * )

  //src/midend/astUtil/astInterface/AstInterface.h.C
  //FixSgProject(SgProject &project) 
  //FixSgTree(SgNode* r)

  //src/frontend/SageIII/astPostProcessing
  //AstPostProcessing(SgNode * node)

//--------------------------AST modification------------------------------
//------------------------------------------------------------------------
// any operations changing AST tree, including
// insert, copy, delete(remove), replace

  // insert before or after some point, argument list is consistent with LowLevelRewrite
  void insertAst(SgNode* targetPosition, SgNode* newNode, bool insertBefore=true);

  // previous examples
  //void myStatementInsert(SgStatement* target,...)
  // void AstInterfaceBase::InsertStmt(AstNodePtr const & orig, AstNodePtr const &n, bool insertbefore, bool extractfromBasicBlock)

  // copy
  // copy children of one basic block to another basic block 
  //void appendStatementCopy (const SgBasicBlock* a, SgBasicBlock* b);
  void copyStatements (const SgBasicBlock* src, SgBasicBlock* dst);

  // delete (remove) a node or a whole subtree
  void removeSgNode(SgNode* targetNode); // need this?
  void removeSgNodeTree(SgNode* subtree); // need this?

  void removeStatement( SgStatement* targetStmt);

  //Move = delete + insert
  void moveAst (SgNode* src, SgNode* target); // need this?
      // similar to  
  void moveStatements (SgBasicBlock* src, SgBasicBlock* target);

  // replace= delete old + insert new (via building or copying)

  void replaceAst(SgNode* oldNode, SgNode* newNode);

   //void replaceChild(SgNode* parent, SgNode* from, SgNode* to);
   //bool AstInterface::ReplaceAst( const AstNodePtr& orig, const AstNodePtr& n)

//--------------------------AST transformations---------------------------
//------------------------------------------------------------------------
// Advanced AST modifications through basic AST modifications
// Might not be included in AST utitlity list, but listed here for the record.

  // extract statements/content from a scope
  void flattenBlocks(SgNode* n);

  //src/midend/astInlining/inlinerSupport.h
  void renameVariables(SgNode* n);
  void renameLabels(SgNode* n, SgFunctionDefinition* enclosingFunctionDefinition);

  void simpleCopyAndConstantPropagation(SgNode* top);
  void changeAllMembersToPublic(SgNode* n);

  void removeVariableDeclaration(SgInitializedName* initname);

  //! Convert something like "int a = foo();" into "int a; a = foo();"
  SgAssignOp* convertInitializerIntoAssignment(SgAssignInitializer* init);

  //! Rewrites a while or for loop so that the official test is changed to
  //! "true" and what had previously been the test is now an if-break
  //! combination (with an inverted condition) at the beginning of the loop
  //! body
  void pushTestIntoBody(LoopStatement* loopStmt);

  //programTransformation/finiteDifferencing/finiteDifferencing.h
  //! Move variables declared in a for statement to just outside that statement.
  void moveForDeclaredVariables(SgNode* root);

//------------------------ Is/Has functions ------------------------------
//------------------------------------------------------------------------
// misc. boolean functions
// some of them could moved to SgXXX class as a member function

  bool isOverloaded (SgFunctionDeclaration * functionDeclaration);

  bool isSwitchCond (const SgStatement* s);
  bool isIfCond (const SgStatement* s);
  bool isWhileCond (const SgStatement* s);
  bool isStdNamespace (const SgScopeStatement* scope);
  bool isTemplateInst (const SgDeclarationStatement* decl);


  bool isCtor (const SgFunctionDeclaration* func);
  bool isDtor (const SgFunctionDeclaration* func);

   // src/midend/astInlining/typeTraits.h
  bool isDefaultConstructible(SgType* type);
  bool isCopyConstructible(SgType* type);
  bool hasTrivialDestructor(SgType* t);
  bool isNonconstReference(SgType* t);
  bool isReferenceType(SgType* t);

  //  generic ones, or move to the SgXXX class as a member function

  bool isConst(SgNode* node); // const type, variable, function, etc.
  bool isStatic(SgNode* node); // const type, variable, function, etc.
  // .... and more

  bool isConstType (const SgType* type);
  bool isConstFunction (const SgFunctionDeclaration* decl);

  bool isStaticFunction (const SgFunctionDeclaration* func);
  bool isExternC (const SgFunctionDeclaration* func);

  bool isMemberVariable(const SgInitializedName & var);
  //bool isMemberVariable(const SgNode& in);

  bool isPrototypeInScope (SgScopeStatement * scope,
			   SgFunctionDeclaration * functionDeclaration,
			   SgDeclarationStatement * startingAtDeclaration);

  bool MayRedefined(SgExpression* expr, SgNode* root);
  // bool isPotentiallyModified(SgExpression* expr, SgNode* root); // inlinderSupport.h
  bool hasAddressTaken(SgExpression* expr, SgNode* root);

  //src/midend/astInlining/inlinerSupport.C
     // can also classified as topdown search
  bool containsVariableReference(SgNode* root, SgInitializedName* var);

  bool isDeclarationOf(SgVariableDeclaration* decl, SgInitializedName* var);
  bool isPotentiallyModifiedDuringLifeOf(SgBasicBlock* sc,
                                       SgInitializedName* toCheck,
                                       SgInitializedName* lifetime)
  //src/midend/programTransformation/partialRedundancyElimination/pre.h
  bool anyOfListPotentiallyModifiedIn(const std::vector<SgVariableSymbol*>& syms, SgNode* n);

//------------------------ loop handling ---------------------------------
//------------------------------------------------------------------------
  //get and set loop control expressions 
  // 0: init expr, 1: condition expr, 2: stride expr

  SgExpression* getForLoopTripleValues(int valuetype,SgForStatement* forstmt );
  int setForLoopTripleValues(int valuetype,SgForStatement* forstmt, SgExpression* exp);

  bool isLoopIndexVarRef(SgForStatement* forstmt, SgVarRefExp *varref);
  SgInitializedName * getLoopIndexVar(SgForStatement* forstmt);

//------------------------expressions-------------------------------------
//------------------------------------------------------------------------
  //src/midend/programTransformation/partialRedundancyElimination/pre.h
  int countComputationsOfExpressionIn(SgExpression* expr, SgNode* root);

  	//src/midend/astInlining/replaceExpressionWithStatement.h
  void replaceAssignmentStmtWithStatement(SgExprStatement* from,                                        StatementGenerator* to);

  void replaceSubexpressionWithStatement(SgExpression* from,
                                       StatementGenerator* to);
  SgExpression* getRootOfExpression(SgExpression* n);

//--------------------------preprocessing info. -------------------------
//------------------------------------------------------------------------
  //! Removes all preprocessing information at a given position.
  void cutPreprocInfo (SgBasicBlock* b,
                       PreprocessingInfo::RelativePositionType pos,
                       AttachedPreprocessingInfoType& save_buf);
  //! Pastes preprocessing information at the front of a statement.
  void pastePreprocInfoFront (AttachedPreprocessingInfoType& save_buf,
                              SgStatement* s);
  //! Pastes preprocessing information at the back of a statement.
  void pastePreprocInfoBack (AttachedPreprocessingInfoType& save_buf,
                             SgStatement* s);

  /*!
   *  \brief Moves 'before' preprocessing information.
   *  Moves all preprocessing information attached 'before' the source
   *  statement to the front of the destination statement.
   */
  // a generic one for all  
  /// void movePreprocessingInfo(src, dest, RelativePositionType);
  void moveBeforePreprocInfo (SgStatement* src, SgStatement* dest);
  void moveInsidePreprocInfo (SgBasicBlock* src, SgBasicBlock* dest);
  void moveAfterPreprocInfo (SgStatement* src, SgStatement* dest);

  //! Dumps a statement's preprocessing information.
  void dumpPreprocInfo (const SgStatement* s, std::ostream& o);

//--------------------------------opeartor--------------------------------
//------------------------------------------------------------------------
  from transformationSupport.h, not sure if they should be included here
  /* return enum code for SAGE operators */
  operatorCodeType classifyOverloadedOperator(); // transformationSupport.h

 /*! \brief generates a source code string from operator name.
    This function returns a string representing the elementwise operator (for primative types)
    that would be match that associated with the overloaded operator for a user-defined
    abstractions (e.g. identifyOperator("operator+()") returns "+").
  */
  std::string stringifyOperator (std::string name);

//--------------------------------macro ----------------------------------
//------------------------------------------------------------------------
  std::string buildMacro ( std::string s ); //transformationSupport.h

//--------------------------------access functions---------------------------
//----------------------------------get/set sth.-----------------------------
// several categories: 
* get/set a direct child/grandchild node or fields 
* get/set a property flag value
* get a descendent child node using preorder searching
* get an ancestor node using bottomup/reverse searching

  	// SgName or string?
  std::string getFunctionName (SgFunctionCallExp* functionCallExp);
  std::string getFunctionTypeName ( SgFunctionCallExp* functionCallExpression );

    // do we need them anymore? or existing member functions are enought?
    // a generic one:
   std::string get_name (const SgNode* node);
   std::string get_name (const SgDeclarationStatement * declaration);

  // get/set some property: should moved to SgXXX as an inherent memeber function?
  // access modifier
  void  setExtern (SgFunctionDeclartion*)
  bool  isExtern()
  void  clearExtern()

   // similarly for other declarations and other properties
  void setExtern (SgVariableDeclaration*)
  void setPublic()
  void setPrivate()


#endif 
}// end of namespace

#endif
