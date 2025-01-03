/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include "reader.h"
#include "codegen.h"  

#define CODE_SIZE 10000
extern SymTab* symtab;

extern Object* readiFunction;
extern Object* readcFunction;
extern Object* writeiProcedure;
extern Object* writecProcedure;
extern Object* writelnProcedure;

CodeBlock* codeBlock;

int computeNestedLevel(Scope* scope) {
  int level = 0;
  Scope* tmp = symtab->currentScope;
  while (tmp != scope) {
    tmp = tmp->outer;
    level ++;
  }
  return level;
}
 
void genVariableAddress(Object* var) {
  int level = computeNestedLevel(VARIABLE_SCOPE(var));
  int offset = VARIABLE_OFFSET(var);
  genLA(level, offset);
}
 //Sinh giá trị của biến bằng cách trỏ đến địa chỉ.
void genVariableValue(Object* var) {
  int level = computeNestedLevel(VARIABLE_SCOPE(var));
  int offset = VARIABLE_OFFSET(var);
  genLV(level, offset);
}

void genParameterAddress(Object* param) {
  int level = computeNestedLevel(PARAMETER_SCOPE(param));
  int offset = PARAMETER_OFFSET(param);
  genLA(level, offset);
}

void genParameterValue(Object* param) {
  int level = computeNestedLevel(PARAMETER_SCOPE(param));
  int offset = PARAMETER_OFFSET(param);
  genLV(level, offset);
}

void genReturnValueAddress(Object* func) {
  int level = computeNestedLevel(FUNCTION_SCOPE(func));
  int offset = RETURN_VALUE_OFFSET;
  genLA(level, offset);
}

void genReturnValueValue(Object* func) {
  int level = computeNestedLevel(FUNCTION_SCOPE(func));
  int offset = RETURN_VALUE_OFFSET;
  genLV(level, offset);
}
//Xử lý các thủ tục được định nghĩa trước như writei, writec, writeln.

void genPredefinedProcedureCall(Object* proc) {
  if (proc == writeiProcedure)
    genWRI();
  else if (proc == writecProcedure)
    genWRC();
  else if (proc == writelnProcedure)
    genWLN();
}

//Gọi các hàm/ thủ tục do người dùng định nghĩa.
void genProcedureCall(Object* proc) {
  int level = computeNestedLevel(proc->procAttrs->scope->outer);
  genCALL(level, proc->procAttrs->codeAddress);
}


//Xử lý các hàm được định nghĩa trước như readi, readc.
void genPredefinedFunctionCall(Object* func) {
  if (func == readiFunction)
    genRI();
  else if (func == readcFunction)
    genRC();
}
 //Gọi các hàm/ thủ tục do người dùng định nghĩa.
void genFunctionCall(Object* func) {
  int level = computeNestedLevel(func->funcAttrs->scope->outer);
  genCALL(level, func->funcAttrs->codeAddress);
}
//Sinh chỉ thị nạp địa chỉ (Load Address).
void genLA(int level, int offset) {
  emitLA(codeBlock, level, offset);
}
//Sinh chỉ thị nạp giá trị biến (Load Value).
void genLV(int level, int offset) {
  emitLV(codeBlock, level, offset);
}

void genLC(WORD constant) {
  emitLC(codeBlock, constant);
}
//Nạp giá trị từ bộ nhớ (Load Indirect).
void genLI(void) {
  emitLI(codeBlock);
}

void genINT(int delta) {
  emitINT(codeBlock,delta);
}

void genDCT(int delta) {
  emitDCT(codeBlock,delta);
}
//Sinh chỉ thị nhảy không điều kiện.
Instruction* genJ(CodeAddress label) {
  Instruction* inst = codeBlock->code + codeBlock->codeSize;
  emitJ(codeBlock,label);
  return inst;
}
//Sinh chỉ thị nhảy có điều kiện (False Jump).
Instruction* genFJ(CodeAddress label) {
  Instruction* inst = codeBlock->code + codeBlock->codeSize;
  emitFJ(codeBlock, label);
  return inst;
}

void genHL(void) {
  emitHL(codeBlock);
}
//Lưu giá trị vào bộ nhớ (Store).
void genST(void) {
  emitST(codeBlock);
}

void genCALL(int level, CodeAddress label) {
  emitCALL(codeBlock, level, label);
}

void genEP(void) {
  emitEP(codeBlock);
}

void genEF(void) {
  emitEF(codeBlock);
}

void genRC(void) {
  emitRC(codeBlock);
}

void genRI(void) {
  emitRI(codeBlock);
}

void genWRC(void) {
  emitWRC(codeBlock);
}

void genWRI(void) {
  emitWRI(codeBlock);
}

void genWLN(void) {
  emitWLN(codeBlock);
}

void genAD(void) {
  emitAD(codeBlock);
}

void genSB(void) {
  emitSB(codeBlock);
}

void genML(void) {
  emitML(codeBlock);
}

void genDV(void) {
  emitDV(codeBlock);
}

void genNEG(void) {
  emitNEG(codeBlock);
}

void genCV(void) {
  emitCV(codeBlock);
}

void genEQ(void) {
  emitEQ(codeBlock);
}

void genNE(void) {
  emitNE(codeBlock);
}

void genGT(void) {
  emitGT(codeBlock);
}

void genGE(void) {
  emitGE(codeBlock);
}

void genLT(void) {
  emitLT(codeBlock);
}

void genLE(void) {
  emitLE(codeBlock);
}

void updateJ(Instruction* jmp, CodeAddress label) {
  jmp->q = label;
}
//Cập nhật địa chỉ đích của câu lệnh nhảy.
void updateFJ(Instruction* jmp, CodeAddress label) {
  jmp->q = label;
}

CodeAddress getCurrentCodeAddress(void) {
  return codeBlock->codeSize;
}

int isPredefinedFunction(Object* func) {
  return ((func == readiFunction) || (func == readcFunction));
}

int isPredefinedProcedure(Object* proc) {
  return ((proc == writeiProcedure) || (proc == writecProcedure) || (proc == writelnProcedure));
}

void initCodeBuffer(void) {
  codeBlock = createCodeBlock(CODE_SIZE);
}

void printCodeBuffer(void) {
  printCodeBlock(codeBlock);
}

void cleanCodeBuffer(void) {
  freeCodeBlock(codeBlock);
}

int serialize(char* fileName) {
  FILE* f;

  f = fopen(fileName, "wb");
  if (f == NULL) return IO_ERROR;
  saveCode(codeBlock, f);
  fclose(f);
  return IO_SUCCESS;
}
