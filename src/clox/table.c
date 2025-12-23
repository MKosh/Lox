#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

////////////////////////////////////////////////////////////////////////////////
///
void initTable(Table* table) {
  table->count = 0;
  table->capacity = 0;
  table->entries = NULL;
}

////////////////////////////////////////////////////////////////////////////////
///
void freeTable(Table* table) {
  FREE_ARRAY(Entry, table->entries, table->capacity);
  initTable(table);
}

////////////////////////////////////////////////////////////////////////////////
///
static Entry* findEntry(Entry* entries, i32 capacity, ObjString* key) {
  u32 index = key->hash % capacity;
  for (;;) {
    Entry* entry = &entries[index];
    if (entry->key == key || entry->key == NULL) {
      return entry;
    }

    index = (index + 1) % capacity;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// Insert an item into the hash table
bool tableSet(Table* table, ObjString* key, Value value) {
  if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
    i32 capacity = GROW_CAPACITY(table->capacity);
    adjustCapacity(table, capacity);
  }

  Entry* entry = findEntry(table->entries, table->capacity, key);
  bool is_new_key = entry->key == NULL;
  if (is_new_key) table->count++;

  entry->key = key;
  entry->value = value;

  return is_new_key;
}
