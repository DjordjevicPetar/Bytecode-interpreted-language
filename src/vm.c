#include <stdio.h>
#include "../inc/common.h"
#include "../inc/compiler.h"
#include "../inc/debug.h"
#include "../inc/vm.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINATY_OPP(op) do { \
        double b = pop(); \
        double a = pop(); \
        push(a op b); \
    } while(false)

    for (;;) {
        #ifdef DEBUG_TRACE_EXECUTION
            printf("        ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            dissasebleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD: {
                BINATY_OPP(+);
                break;
            }
            case OP_SUBTRACT: {
                BINATY_OPP(-);
                break;
            }
            case OP_MULTIPLY: {
                BINATY_OPP(*);
                break;
            }
            case OP_DIVIDE: {
                BINATY_OPP(/);
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINATY_OPP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}