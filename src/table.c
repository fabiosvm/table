//
// table.c
//

#include "table.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TOMBSTONE ((char *) -1)

#define is_empty(e)     (!(e)->key)
#define is_tombstone(e) ((e)->key == TOMBSTONE)

static inline TableEntry *alloc_entries(int cap);
static inline void grow(Table *tbl);
static inline TableEntry *alloc_entry(int cap, TableEntry *entries, const char *key);
static inline uint32_t hash(const char *str);
static inline bool equals(const char *str1, const char *str2);
static inline char *str_copy(const char *str);

static inline TableEntry *alloc_entries(int cap)
{
  TableEntry *entries = malloc(sizeof(*entries) * cap);
  for (int i = 0; i < cap; ++i)
    entries[i].key = NULL;
  return entries;
}

static inline void grow(Table *tbl)
{
  int n = tbl->len * 100 / TABLE_MAX_LOAD_FACTOR;
  if (n <= tbl->cap) return;
  int cap = tbl->cap;
  while (cap < n) cap <<= 1;
  TableEntry *entries = alloc_entries(cap);
  for (int i = 0, j = 0; i < tbl->cap && j < tbl->len; ++i)
  {
    TableEntry *entry = &tbl->entries[i];
    if (is_empty(entry) || is_tombstone(entry))
      continue;
    TableEntry *_entry = alloc_entry(cap, entries, entry->key);
    _entry->key = entry->key;
    _entry->value = entry->value;
    ++j;
  }
  free(tbl->entries);
  tbl->cap = cap;
  tbl->entries = entries;
}

static inline TableEntry *alloc_entry(int cap, TableEntry *entries, const char *key)
{
  int mask = cap - 1;
  int i = hash(key) & mask;
  TableEntry *entry = &entries[i];
  for (;;)
  {
    if (is_empty(entry)) break;
    i = (i + 1) & mask;
    entry = &entries[i];
  }
  return entry;
}

static inline uint32_t hash(const char *str)
{
  uint32_t hash = 2166136261u;
  for (int i = 0; str[i]; ++i)
  {
    hash ^= str[i];
    hash *= 16777619;
  }
  return hash;
}

static inline bool equals(const char *str1, const char *str2)
{
  if (str1 == str2) return true;
  return !strcmp(str1, str2);
}

static inline char *str_copy(const char *str)
{
  int n = (int) strlen(str) + 1;
  char *dup = malloc(n);
  memcpy(dup, str, n);
  return dup;
}

void table_init(Table *tbl)
{
  tbl->cap = TABLE_MIN_CAPACITY;
  tbl->len = 0;
  tbl->entries = alloc_entries(tbl->cap);
}

void table_deinit(Table *tbl)
{
  for (int i = 0, j = 0; i < tbl->cap && j < tbl->len; ++i)
  {
    TableEntry *entry = &tbl->entries[i];
    if (is_empty(entry) || is_tombstone(entry))
      continue;
    free(entry->key);
    ++j;
  }
  free(tbl->entries);
}

bool table_find(Table *tbl, const char *key, TableEntry **entry)
{
  int mask = tbl->cap - 1;
  int index = hash(key) & mask;
  TableEntry *entries = tbl->entries;
  bool found = false;
  for (int i = 0, j = 0; i < tbl->cap && j < tbl->len; ++i)
  {
    TableEntry *_entry = &entries[index];
    if (is_empty(_entry)) break;
    if (!is_tombstone(_entry))
    {
      if (equals(_entry->key, key))
      {
        found = true;
        break;
      }
      ++j;
    }
    index = (index + 1) & mask;
  }
  *entry = &entries[index];
  return found;
}

int table_insert(Table *tbl, const char *key, int value)
{
  TableEntry *entry;
  bool found = table_find(tbl, key, &entry);
  if (found) return ERR_KEY_ALREADY_EXISTS;
  entry->key = str_copy(key);
  entry->value = value;
  ++tbl->len;
  grow(tbl);
  return OK_INSERTED;
}

int table_update(Table *tbl, const char *key, int value)
{
  TableEntry *entry;
  bool found = table_find(tbl, key, &entry);
  if (!found) return ERR_KEY_NOT_FOUND;
  entry->value = value;
  return OK_UPDATED;
}

int table_upsert(Table *tbl, const char *key, int value)
{
  TableEntry *entry;
  bool found = table_find(tbl, key, &entry);
  if (found)
  {
    entry->value = value;
    return OK_UPDATED;
  }
  entry->key = str_copy(key);
  entry->value = value;
  ++tbl->len;
  grow(tbl);
  return OK_INSERTED;
}

int table_remove(Table *tbl, const char *key)
{
  TableEntry *entry;
  bool found = table_find(tbl, key, &entry);
  if (!found) return ERR_KEY_NOT_FOUND;
  free(entry->key);
  entry->key = TOMBSTONE;
  --tbl->len;
  return OK_REMOVED;
}

void table_clear(Table *tbl)
{
  for (int i = 0; i < tbl->cap; ++i)
  {
    TableEntry *entry = &tbl->entries[i];
    if (is_empty(entry)) continue;
    if (!is_tombstone(entry))
      free(entry->key);
    entry->key = NULL;
  }
  tbl->len = 0;
}
