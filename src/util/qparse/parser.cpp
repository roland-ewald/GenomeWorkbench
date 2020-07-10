/*  $Id: parser.cpp 593047 2019-09-11 15:29:02Z grichenk $
 * ===========================================================================
 *
 *                            PUBLIC DOMAIN NOTICE
 *               National Center for Biotechnology Information
 *
 *  This software/database is a "United States Government Work" under the
 *  terms of the United States Copyright Act.  It was written as part of
 *  the author's official duties as a United States Government employee and
 *  thus cannot be copyrighted.  This software/database is freely available
 *  to the public for use. The National Library of Medicine and the U.S.
 *  Government have not placed any restriction on its use or reproduction.
 *
 *  Although all reasonable efforts have been taken to ensure the accuracy
 *  and reliability of the software and data, the NLM and the U.S.
 *  Government do not and cannot warrant the performance or results that
 *  may be obtained by using this software or data. The NLM and the U.S.
 *  Government disclaim all warranties, express or implied, including
 *  warranties of performance, merchantability or fitness for any particular
 *  purpose.
 *
 *  Please cite the author in any work or product based on this material.
 *
 * ===========================================================================
 *
 * Authors: Anatoliy Kuznetsov
 *
 * File Description:
 *      Query parser entry point. 
 *    Glues together code generated by BISON, lexical tokenizer, 
 *    error processing, etc.
 *
 */

#include <ncbi_pch.hpp>
#include <corelib/ncbimtx.hpp>
#include <corelib/ncbiapp.hpp>
#include <util/qparse/query_parse.hpp>
#include <util/resource_pool.hpp>
#include <util/error_codes.hpp>

#include <stack>


#define NCBI_USE_ERRCODE_X   Util_QParse

USING_NCBI_SCOPE;

/* extern "C" */ static int ncbi_q_error (const char *s);
/* extern "C" */ static int ncbi_q_lex (CQueryParseTree::TNode** lvalp, void* param);

BEGIN_NCBI_SCOPE



/// Query tree garbage collection functor.
///
/// Finds nodes in the query tree and removes them from the 
/// memory pool. All lost nodes are deleted by the pool object.
///
/// @internal
/// @ingroup QParser
///
class CQueryTreeCleanPoolFunc
{
public:
    typedef CResourcePool<CQueryParseTree::TNode, CFastMutex> TNodePool;
    
public: 
    CQueryTreeCleanPoolFunc(TNodePool& mem_pool)
    : m_Pool(mem_pool)
    {}
  
    ETreeTraverseCode 
    operator()(CQueryParseTree::TNode& tr, int delta)
    {
        if (delta == 0 || delta == 1) {
            m_Pool.Forget(&tr);
        }
        return eTreeTraverse;
    }
private:
    TNodePool&  m_Pool;
};

/// Class passed to Lex/Bison (yylex/yyparse) functions.
/// Works as a glue to pass all the information 
/// (both parsed stream and output syntactic tree)
///
/// @internal
/// @ingroup QParser
///
class CQueryParserEnv
{
public:
    typedef CResourcePool<CQueryParseTree::TNode, CFastMutex> TNodePool;
    /// Parsing context stack
    typedef vector<CQueryParseTree::TNode*>                   TContextStack;
    
public:
    CQueryParserEnv(const char* query_str, CQueryParseTree& qtree, unsigned line = 0, unsigned linePos = 0)
    : m_QTree(qtree),
      m_Query(query_str),
      m_Ptr(query_str),
      m_QueryTree(0),
      m_Verbose(false),
      m_Case(CQueryParseTree::eCaseInsensitive),
      m_Line(line),
      m_LinePos(linePos),
      m_ParseTolerance(CQueryParseTree::eSyntaxCheck),
      m_InNode(0),
//      m_SelectNode(0),
      m_FromNode(0),
      m_Functions(0)
    {
        m_QueryLen = (unsigned)::strlen(m_Query);
    }

    ~CQueryParserEnv()
    {
        try {
            Free();
        } 
        catch (exception & ex) {
            ERR_POST_X(1, "Exception in ~CQueryParserEnv()" << ex.what());
        }
        catch (...) {
            ERR_POST_X(2, "Unknown exception in ~CQueryParserEnv()");
        }
        
    }
    
    void Free()
    {
        if (m_QueryTree) {
            // Sync the memory pool not to delete the in-tree nodes
            CQueryTreeCleanPoolFunc func(m_NodePool);
            TreeDepthFirstTraverse(*m_QueryTree, func);

            delete m_QueryTree; m_QueryTree = 0;
        }
    }
    
    /// Register pointer on function names (no ownership transfer)
    void SetFunctions(const CQueryParseTree::TFunctionNames* func) { m_Functions = func; }
    /// Get list of registered functions
    const CQueryParseTree::TFunctionNames* GetFunctions() const { return m_Functions; }
    

    const char*  GetQueryBuffer() const { return m_Query; }
    const char*  GetBufPtr() const { return m_Ptr; }
    const char*  GetBufEnd() const { return m_Query + m_QueryLen; }
    void SetBufPtr(const char* ptr) { m_Ptr = ptr; }

    int GetChar()
    {
        int r = *m_Ptr++;
        if (r == '\n') {
            ++m_Line; m_LinePos = 0;
            return r;
        }
        ++m_LinePos;
        return r;
    }

    /// Skip number of characters
    void Skip(int num)
    {
        for (int i = 0; i < num; ++i) {
            GetChar();
        }
    }
/*
    void UnGetChar() 
    { 
        --m_Ptr; 
    }
*/
    void AttachToPool(CQueryParseTree::TNode* qt)
    {
//cerr << "AttachToPool was:" <<  m_QueryTree << " new: " << qt << endl;
//        m_QueryTree = qt;
        m_NodePool.Put(qt);
    }

    void AttachQueryTree(CQueryParseTree::TNode* qt)
    {
//cerr << "AttachQueryTree was:" <<  m_QueryTree << " new: " << qt << endl;
        m_QueryTree = qt;
    }

    CQueryParseTree::TNode* GetQueryTree() { return m_QueryTree; }

    /// Return query clause.
    ///
    /// Caller is responsible for deleteion
    ///
    CQueryParseTree::TNode* DetachQueryTree() 
    { 
        if (m_QueryTree) {
            // Sync the memory pool
            CQueryTreeCleanPoolFunc func(m_NodePool);
            TreeDepthFirstTraverse(*m_QueryTree, func);

            CQueryParseTree::TNode* qc = m_QueryTree;
            m_QueryTree = 0;

            return qc; 
        }
        return 0;
    }

    void AddNodeToPool(CQueryParseTree::TNode* qnode)
    {
        m_NodePool.Put(qnode);
    }

    TNodePool& GetPool()
    {
        return m_NodePool;
    }

    void ForgetPoolNode(CQueryParseTree::TNode* qnode)
    {
        if (qnode) m_NodePool.Forget(qnode);
    }
    
    void ForgetPoolNodes(CQueryParseTree::TNode* qnode1, 
                         CQueryParseTree::TNode* qnode2)
    {
        if (qnode1) m_NodePool.Forget(qnode1);
        if (qnode2) m_NodePool.Forget(qnode2);
    }
    
    bool IsVerbose() const { return m_Verbose; }
    void SetVerbose(bool verbose=true) { m_Verbose = verbose; }

    CQueryParseTree::ECase GetCase() const { return m_Case; }
    void SetCase(CQueryParseTree::ECase case_sense) { m_Case = case_sense; }
    
    CQueryParseTree& QTree() { return m_QTree; }
    
    /// Src line number
    unsigned GetLine() const { return m_Line; }    
    /// Get position in line
    unsigned GetLinePos() const { return m_LinePos; }
    
    void SetParserTolerance(CQueryParseTree::ESyntaxCheck  syntax_check)
    {
        m_ParseTolerance = syntax_check;
    }
    CQueryParseTree::ESyntaxCheck GetParserTolerance() const 
    {
        return m_ParseTolerance;
    }   
    void SetIN_Context(CQueryParseTree::TNode* in_node)
    {
        if(m_InNode != 0) _ASSERT(in_node == 0);
        m_InNode = in_node;
    }
    CQueryParseTree::TNode* GetIN_Context() { return m_InNode; }

    void SetSELECT_Context(CQueryParseTree::TNode* node)
    {
        if (node) {
            m_SelectCtxStack.push_back(node);
        } else {
            m_SelectCtxStack.pop_back();
        }
    }
    CQueryParseTree::TNode* GetSELECT_Context() 
    { 
        if (m_SelectCtxStack.size() == 0) {
            return 0;
        }
        return m_SelectCtxStack[m_SelectCtxStack.size()-1];
    }

    void SetFROM_Context(CQueryParseTree::TNode* from_node)
    {
        m_FromNode = from_node;
    }
    CQueryParseTree::TNode* GetFROM_Context() { return m_FromNode; }
    
    void SetContext(CQueryParseTree::TNode* node)
    {
        if (node) {
            m_CtxStack.push_back(node);
        } else {
            m_CtxStack.pop_back();
        }
    }
        
    CQueryParseTree::TNode* GetContext() 
    { 
        if (m_CtxStack.size() == 0) {
            return 0;
        }
        return m_CtxStack[m_CtxStack.size()-1];
    }

private:
    CQueryParseTree& m_QTree;   ///< Base query tree reference
    const char*      m_Query;   ///< Request buffer. (Source for the scanner)
    unsigned         m_QueryLen;///< Query length
    const char*      m_Ptr;     ///< Current position in the request buffer

    /// Query clause tree. This is the result of the statement parsing.
    CQueryParseTree::TNode*                 m_QueryTree;
    
    /// Memory pool of query clause tree nodes. 
    /// Used to avoid memory leaks when BISON shifts stack and calls
    /// yyerror (or othewise throws a C++ exception)
    TNodePool m_NodePool;
    /// Debug trace when parsing
    bool      m_Verbose;
    /// Case sensitivity switch
    CQueryParseTree::ECase  m_Case;
    
    unsigned   m_Line;
    unsigned   m_LinePos;
    
    CQueryParseTree::ESyntaxCheck  m_ParseTolerance;
    
    /// operator "IN" context pointer
    CQueryParseTree::TNode*             m_InNode;

    /// "SELECT" parsing context 
    //CQueryParseTree::TNode*             m_SelectNode;
    TContextStack                       m_SelectCtxStack;

    /// "FROM" context pointer
    CQueryParseTree::TNode*             m_FromNode;
    
    /// Common parsing context
    TContextStack                       m_CtxStack;

    /// Function names 
    const CQueryParseTree::TFunctionNames*    m_Functions;

};




END_NCBI_SCOPE

#ifdef IN
#undef IN
#endif

#include "query_parser_bison.tab.c"
#include "lexer.inc"

/// Called by yyparse on error 
static
int ncbi_q_error (const char *) 
{
    _TRACE("Parsing error!!!");
//    NCBI_THROW(CQueryParseException, eParserError, "Syntax error!");
    return 1;
}


BEGIN_NCBI_SCOPE


void CQueryParseTree::Parse(const char*           query_str, 
                            ECase                 case_sense,
                            ESyntaxCheck          syntax_check,
                            bool                  verbose,
                            const TFunctionNames& functions,
                            unsigned              line,
                            unsigned              linePos)
{
    CQueryParserEnv env(query_str, *this, line, linePos);

#ifdef _DEBUG
    CNcbiApplicationGuard app = CNcbiApplication::InstanceGuard();
    if (app  &&  app->GetEnvironment().Get("DIAG_TRACE") == "1") {
        yydebug = 1;
        verbose = true;
    }
#endif
    env.SetCase(case_sense);
    env.SetVerbose(verbose);
    env.SetParserTolerance(syntax_check);
    if (functions.size()) {
        env.SetFunctions(&functions);
    }

    int res = ncbi_q_parse((void*) &env);
    if (res != 0) {
        NCBI_THROW(CQueryParseException, eParserError, "Parsing error.");
    }
    
    CQueryParseTree::TNode* qt = env.GetQueryTree();

    if (qt) {
        qt = env.DetachQueryTree();
        this->SetQueryTree(qt);
    } else {

        // Check if we have only one token node created by the tokenizer
        // means it's just a single word request (perfectly legal)

        CQueryParserEnv::TNodePool& pool = env.GetPool();
        CQueryParserEnv::TNodePool::TPoolList& vec = pool.GetFreeList();

        // the only node in pool
        if (vec.size() == 1) {
            CQueryParseTree::TNode* qcl = vec[0];
            this->SetQueryTree(qcl);
            pool.ForgetAll();
        }
    }
    env.Free();
}


END_NCBI_SCOPE