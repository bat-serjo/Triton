#ifndef _ANALYSISPROCESSOR_H_
#define _ANALYSISPROCESSOR_H_

#include "SymbolicEngine.h"
#include "SolverEngine.h"
#include "TaintEngine.h"


class AnalysisProcessor {
  public:
    AnalysisProcessor();

    // Symbolic Engine Facade
    // ----------------------

    // Returns a symbolic element for the register (regID).
    SymbolicElement *createRegSE(std::stringstream &expr, uint64_t regID);

    // Returns a symbolic element for the memory address.
    SymbolicElement *createMemSE(std::stringstream &expr, uint64_t address);

    // Returns the ID of the symbolic element currently present in the
    // symbolic register. If there is no symbolic element, it returns UNSET.
    uint64_t getRegSymbolicID(uint64_t regID);

    // Returns the ID of the symbolic element currently present in the
    // symbolic memory. If there is no symbolic element, it returns UNSET.
    uint64_t getMemorySymbolicID(uint64_t address);

    // Returns the symbolic engine reference
    SymbolicEngine &getSymbolicEngine();

    // Taint Engine Facade
    // -------------------

    // Returns the taint engine reference
    TaintEngine &getTaintEngine();

    // Taint interface.
    // Taint the symbolic element if the taint occurs.
    bool isMemoryTainted(uint64_t addr);
    bool isRegTainted(uint64_t reg);

    /* ALU Spreading */
    void aluSpreadTaintMemImm(SymbolicElement *se, uint64_t memDst, uint32_t writeSize);
    void aluSpreadTaintMemReg(SymbolicElement *se, uint64_t memDst, uint64_t regSrc, uint32_t writeSize);
    void aluSpreadTaintRegImm(SymbolicElement *se, uint64_t regDst);
    void aluSpreadTaintRegMem(SymbolicElement *se, uint64_t regDst, uint64_t memSrc, uint32_t readSize);
    void aluSpreadTaintRegReg(SymbolicElement *se, uint64_t regDst, uint64_t regSrc);

    /* Assignment Spreading */
    void assignmentSpreadTaintMemImm(SymbolicElement *se, uint64_t memDst, uint64_t writeSize);
    void assignmentSpreadTaintMemReg(SymbolicElement *se, uint64_t memDst, uint64_t regSrc, uint64_t writeSize);
    void assignmentSpreadTaintRegImm(SymbolicElement *se, uint64_t regDst);
    void assignmentSpreadTaintRegMem(SymbolicElement *se, uint64_t regDst, uint64_t memSrc, uint32_t readSize);
    void assignmentSpreadTaintMemMem(SymbolicElement *se, uint64_t memDst, uint64_t memSrc, uint32_t readSize);
    void assignmentSpreadTaintRegReg(SymbolicElement *se, uint64_t regDst, uint64_t regSrc);

    // SolverEngine Facade

    // Returns a reference to the solver engine.
    SolverEngine &getSolverEngine();

  private:
    SymbolicEngine  symEngine;
    SolverEngine    solverEngine;
    TaintEngine     taintEngine;
};

#endif //_ANALYSISPROCESSOR_H_