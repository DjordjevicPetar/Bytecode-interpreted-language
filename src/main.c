#include "../inc/common.h"
#include "../inc/chunk.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);
    freeChunk(&chunk);
    return 0;
}