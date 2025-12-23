#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType);

////////////////////////////////////////////////////////////////////////////////
///
static Obj* allocateObject(size_t size, ObjType type) {
  Obj* object = (Obj*)reallocate(NULL, 0, size);
  object->type = type;

  object->next = vm.objects;
  vm.objects = object;
  return object;
}

////////////////////////////////////////////////////////////////////////////////
///
static ObjString* allocateString(char* chars, i32 length, u32 hash) {
  ObjString* string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->hash = hash;
  string->chars = chars;
  return string;
}

////////////////////////////////////////////////////////////////////////////////
/// FNV-1a hash function
static u32 hashString(const char* key, i32 length) {
  u32 hash = 2166136261u;
  for (size_t i = 0; i < length; ++i) {
    hash ^= (u8)key[i];
    hash *= 16777619;
  }

  return hash;
}

////////////////////////////////////////////////////////////////////////////////
///
ObjString* takeString(char* chars, i32 length) {
  u32 hash = hashString(chars, length);
  return allocateString(chars, length, hash);
}

////////////////////////////////////////////////////////////////////////////////
///
ObjString* copyString(const char* chars, i32 length) {
  u32 hash = hashString(chars, length);
  char* heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length, hash);
}

////////////////////////////////////////////////////////////////////////////////
///
void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}
