#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

/**
 * @brief LLVM FunctionPass to detect implicit constructor calls within functions.
 *
 * This pass iterates over all instructions in each function, searching for call instructions
 * to functions whose names contain "C1" (a common LLVM mangling for constructors).
 * When such a call is found, it prints the constructor's name and attempts to classify
 * the constructor type as default, copy, or parameterized based on the number and type of arguments.
 *
 * - Default Constructor: No arguments.
 * - Copy Constructor: Single pointer argument.
 * - Parameterized Constructor: Any other argument pattern.
 *
 * The pass does not modify the IR.
 */
namespace {
struct ImplicitCtorPass : public FunctionPass {
    static char ID;
    ImplicitCtorPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
        for (auto &BB : F) {
            for (auto &I : BB) {
                if (auto *Call = dyn_cast<CallInst>(&I)) {
                    Function *CalledFunc = Call->getCalledFunction();
                    if (CalledFunc && CalledFunc->hasName() && CalledFunc->getName().contains("C1")) {
                        errs() << "Implicit constructor detected: " << CalledFunc->getName() << "\n";
                        // Analyze constructor type based on parameters
                        if (CalledFunc->arg_size() == 0)
                            errs() << "Type: Default Constructor\n";
                        else if (CalledFunc->arg_size() == 1 && CalledFunc->getArg(0)->getType()->isPointerTy())
                            errs() << "Type: Copy Constructor\n";
                        else
                            errs() << "Type: Parameterized Constructor\n";                        
                    }
                }
            }
        }   
        return false;
    }
};
} // namespace

char ImplicitCtorPass::ID = 0;
static RegisterPass<ImplicitCtorPass> X("implicit-ctor", "Detect Implicit Constructor Calls",false,false);