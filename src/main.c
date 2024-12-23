//
// main.c
// 

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

int main(void)
{
  Table tbl;
  table_init(&tbl);

  TableEntry *entry;

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY);
  assert(!table_len(&tbl));

  assert(!table_find(&tbl, "a", &entry));
  assert(!table_find(&tbl, "b", &entry));
  assert(!table_find(&tbl, "c", &entry));
  assert(!table_find(&tbl, "d", &entry));
  assert(!table_find(&tbl, "e", &entry));
  assert(!table_find(&tbl, "f", &entry));
  assert(!table_find(&tbl, "g", &entry));
  assert(!table_find(&tbl, "h", &entry));
  assert(!table_find(&tbl, "i", &entry));
  assert(!table_find(&tbl, "j", &entry));

  assert(table_insert(&tbl, "a", 1) == OK_INSERTED);
  assert(table_insert(&tbl, "b", 2) == OK_INSERTED);
  assert(table_insert(&tbl, "c", 3) == OK_INSERTED);
  assert(table_insert(&tbl, "d", 4) == OK_INSERTED);
  assert(table_insert(&tbl, "e", 5) == OK_INSERTED);
  assert(table_insert(&tbl, "f", 6) == OK_INSERTED);
  assert(table_insert(&tbl, "g", 7) == OK_INSERTED);
  assert(table_insert(&tbl, "h", 8) == OK_INSERTED);
  assert(table_insert(&tbl, "i", 9) == OK_INSERTED);
  assert(table_insert(&tbl, "j", 10) == OK_INSERTED);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(table_len(&tbl) == 10);

  assert(table_find(&tbl, "a", &entry)); assert(entry->value == 1);
  assert(table_find(&tbl, "b", &entry)); assert(entry->value == 2);
  assert(table_find(&tbl, "c", &entry)); assert(entry->value == 3);
  assert(table_find(&tbl, "d", &entry)); assert(entry->value == 4);
  assert(table_find(&tbl, "e", &entry)); assert(entry->value == 5);
  assert(table_find(&tbl, "f", &entry)); assert(entry->value == 6);
  assert(table_find(&tbl, "g", &entry)); assert(entry->value == 7);
  assert(table_find(&tbl, "h", &entry)); assert(entry->value == 8);
  assert(table_find(&tbl, "i", &entry)); assert(entry->value == 9);
  assert(table_find(&tbl, "j", &entry)); assert(entry->value == 10);

  assert(table_insert(&tbl, "a", 1) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "b", 2) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "c", 3) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "d", 4) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "e", 5) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "f", 6) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "g", 7) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "h", 8) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "i", 9) == ERR_KEY_ALREADY_EXISTS);
  assert(table_insert(&tbl, "j", 10) == ERR_KEY_ALREADY_EXISTS);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(table_len(&tbl) == 10);

  assert(table_update(&tbl, "a", 11) == OK_UPDATED);
  assert(table_update(&tbl, "b", 12) == OK_UPDATED);
  assert(table_update(&tbl, "c", 13) == OK_UPDATED);
  assert(table_update(&tbl, "d", 14) == OK_UPDATED);
  assert(table_update(&tbl, "e", 15) == OK_UPDATED);
  assert(table_update(&tbl, "f", 16) == OK_UPDATED);
  assert(table_update(&tbl, "g", 17) == OK_UPDATED);
  assert(table_update(&tbl, "h", 18) == OK_UPDATED);
  assert(table_update(&tbl, "i", 19) == OK_UPDATED);
  assert(table_update(&tbl, "j", 20) == OK_UPDATED);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(table_len(&tbl) == 10);

  assert(table_find(&tbl, "a", &entry)); assert(entry->value == 11);
  assert(table_find(&tbl, "b", &entry)); assert(entry->value == 12);
  assert(table_find(&tbl, "c", &entry)); assert(entry->value == 13);
  assert(table_find(&tbl, "d", &entry)); assert(entry->value == 14);
  assert(table_find(&tbl, "e", &entry)); assert(entry->value == 15);
  assert(table_find(&tbl, "f", &entry)); assert(entry->value == 16);
  assert(table_find(&tbl, "g", &entry)); assert(entry->value == 17);
  assert(table_find(&tbl, "h", &entry)); assert(entry->value == 18);
  assert(table_find(&tbl, "i", &entry)); assert(entry->value == 19);
  assert(table_find(&tbl, "j", &entry)); assert(entry->value == 20);

  assert(table_upsert(&tbl, "a", 21) == OK_UPDATED);
  assert(table_upsert(&tbl, "b", 22) == OK_UPDATED);
  assert(table_upsert(&tbl, "c", 23) == OK_UPDATED);
  assert(table_upsert(&tbl, "d", 24) == OK_UPDATED);
  assert(table_upsert(&tbl, "e", 25) == OK_UPDATED);
  assert(table_upsert(&tbl, "f", 26) == OK_UPDATED);
  assert(table_upsert(&tbl, "g", 27) == OK_UPDATED);
  assert(table_upsert(&tbl, "h", 28) == OK_UPDATED);
  assert(table_upsert(&tbl, "i", 29) == OK_UPDATED);
  assert(table_upsert(&tbl, "j", 30) == OK_UPDATED);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(table_len(&tbl) == 10);

  assert(table_find(&tbl, "a", &entry)); assert(entry->value == 21);
  assert(table_find(&tbl, "b", &entry)); assert(entry->value == 22);
  assert(table_find(&tbl, "c", &entry)); assert(entry->value == 23);
  assert(table_find(&tbl, "d", &entry)); assert(entry->value == 24);
  assert(table_find(&tbl, "e", &entry)); assert(entry->value == 25);
  assert(table_find(&tbl, "f", &entry)); assert(entry->value == 26);
  assert(table_find(&tbl, "g", &entry)); assert(entry->value == 27);
  assert(table_find(&tbl, "h", &entry)); assert(entry->value == 28);
  assert(table_find(&tbl, "i", &entry)); assert(entry->value == 29);
  assert(table_find(&tbl, "j", &entry)); assert(entry->value == 30);

  assert(table_remove(&tbl, "a") == OK_REMOVED);
  assert(table_remove(&tbl, "b") == OK_REMOVED);
  assert(table_remove(&tbl, "c") == OK_REMOVED);
  assert(table_remove(&tbl, "d") == OK_REMOVED);
  assert(table_remove(&tbl, "e") == OK_REMOVED);
  assert(table_remove(&tbl, "f") == OK_REMOVED);
  assert(table_remove(&tbl, "g") == OK_REMOVED);
  assert(table_remove(&tbl, "h") == OK_REMOVED);
  assert(table_remove(&tbl, "i") == OK_REMOVED);
  assert(table_remove(&tbl, "j") == OK_REMOVED);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(!table_len(&tbl));

  assert(!table_find(&tbl, "a", &entry));
  assert(!table_find(&tbl, "b", &entry));
  assert(!table_find(&tbl, "c", &entry));
  assert(!table_find(&tbl, "d", &entry));
  assert(!table_find(&tbl, "e", &entry));
  assert(!table_find(&tbl, "f", &entry));
  assert(!table_find(&tbl, "g", &entry));
  assert(!table_find(&tbl, "h", &entry));
  assert(!table_find(&tbl, "i", &entry));
  assert(!table_find(&tbl, "j", &entry));

  assert(table_upsert(&tbl, "a", 31) == OK_INSERTED);
  assert(table_upsert(&tbl, "b", 32) == OK_INSERTED);
  assert(table_upsert(&tbl, "c", 33) == OK_INSERTED);
  assert(table_upsert(&tbl, "d", 34) == OK_INSERTED);
  assert(table_upsert(&tbl, "e", 35) == OK_INSERTED);
  assert(table_upsert(&tbl, "f", 36) == OK_INSERTED);
  assert(table_upsert(&tbl, "g", 37) == OK_INSERTED);
  assert(table_upsert(&tbl, "h", 38) == OK_INSERTED);
  assert(table_upsert(&tbl, "i", 39) == OK_INSERTED);
  assert(table_upsert(&tbl, "j", 40) == OK_INSERTED);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(table_len(&tbl) == 10);

  assert(table_find(&tbl, "a", &entry)); assert(entry->value == 31);
  assert(table_find(&tbl, "b", &entry)); assert(entry->value == 32);
  assert(table_find(&tbl, "c", &entry)); assert(entry->value == 33);
  assert(table_find(&tbl, "d", &entry)); assert(entry->value == 34);
  assert(table_find(&tbl, "e", &entry)); assert(entry->value == 35);
  assert(table_find(&tbl, "f", &entry)); assert(entry->value == 36);
  assert(table_find(&tbl, "g", &entry)); assert(entry->value == 37);
  assert(table_find(&tbl, "h", &entry)); assert(entry->value == 38);
  assert(table_find(&tbl, "i", &entry)); assert(entry->value == 39);
  assert(table_find(&tbl, "j", &entry)); assert(entry->value == 40);

  table_clear(&tbl);

  assert(table_cap(&tbl) == TABLE_MIN_CAPACITY * 2);
  assert(!table_len(&tbl));

  assert(!table_find(&tbl, "a", &entry));
  assert(!table_find(&tbl, "b", &entry));
  assert(!table_find(&tbl, "c", &entry));
  assert(!table_find(&tbl, "d", &entry));
  assert(!table_find(&tbl, "e", &entry));
  assert(!table_find(&tbl, "f", &entry));
  assert(!table_find(&tbl, "g", &entry));
  assert(!table_find(&tbl, "h", &entry));
  assert(!table_find(&tbl, "i", &entry));
  assert(!table_find(&tbl, "j", &entry));

  table_deinit(&tbl);

  printf("All tests passed!\n");
  return EXIT_SUCCESS;
}
