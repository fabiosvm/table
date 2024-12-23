//
// table.h
//

#ifndef TABLE_H
#define TABLE_H

#include <stdbool.h>

#define TABLE_MIN_CAPACITY    (1 << 3)
#define TABLE_MAX_CAPACITY    (1 << 30)
#define TABLE_MAX_LOAD_FACTOR (75)

#define OK                     (0)
#define OK_INSERTED            (1)
#define OK_UPDATED             (2)
#define OK_REMOVED             (3)
#define ERR_KEY_NOT_FOUND      (-1)
#define ERR_KEY_ALREADY_EXISTS (-2)

#define table_cap(t) ((t)->cap)
#define table_len(t) ((t)->len)

typedef struct
{
  char *key;
  int  value;
} TableEntry;

typedef struct
{
  int        cap;
  int        len;
  TableEntry *entries;
} Table;

void table_init(Table *tbl);
void table_deinit(Table *tbl);
bool table_find(Table *tbl, const char *key, TableEntry **entry);
int table_insert(Table *tbl, const char *key, int value);
int table_update(Table *tbl, const char *key, int value);
int table_upsert(Table *tbl, const char *key, int value);
int table_remove(Table *tbl, const char *key);
void table_clear(Table *tbl);

#endif // TABLE_H
