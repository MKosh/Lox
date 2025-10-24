#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

/////////////////////////////////////////////////////////////////////
///
void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

/////////////////////////////////////////////////////////////////////
///
void freeChunk(Chunk* chunk) {
  FREE_ARRAY(u8, chunk->code, chunk->capacity);
  FREE_ARRAY(i32, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

/////////////////////////////////////////////////////////////////////
///
void writeChunk(Chunk *chunk, u8 byte, i32 line) {
  if (chunk->capacity  < chunk->count + 1) {
    i32 oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(u8, chunk->code, oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(i32, chunk->lines, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

/////////////////////////////////////////////////////////////////////
///
i32 addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
