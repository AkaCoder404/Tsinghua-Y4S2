#include <cstdio>
#include <cstring>
// #define ORIGINAL 0
#define TESTING 0

const int TABLE_SIZE = 499883; // = 124970 * 4 + 3
struct hash_entry {
  char *my_string;
  int my_data;
  hash_entry() {
    my_string = NULL;
    my_data = 0;
  }
  hash_entry(char *str, int data) : my_data(data) {
    my_string = new char[strlen(str) + 1];
    strcpy(my_string, str);
  }
};
struct hashing_strategy {
  virtual int operator()(char *str, int N) = 0;
};
struct naive_hashing : public hashing_strategy {
  int operator()(char *str, int N) override;
};
struct ascii_hashing : public hashing_strategy {
  int operator()(char *str, int N) override;
};
struct utf8_hashing : public hashing_strategy {
  int operator()(char *str, int N) override;
};

struct collision_strategy {
  virtual void init() = 0; // pure virtual function
  virtual int operator()(hash_entry *Table, int table_size, int last_choice) = 0;
};
struct linear_probe : public collision_strategy {
  void init();
  int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
struct quadratic_probe : public collision_strategy {
  int square;
  bool negative;
  void init();
  int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
struct overflow_probe : public collision_strategy {
  int counter;
  void init();
  int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

struct hashtable {
  hash_entry *Table;
  int table_size;
  int insert_collision_count = 0;
  int query_collision_count = 0;
  float overflow_area = 0.8;
  hashing_strategy *my_hashing; // 如果改为hashing_strategy my_hashing, 即不是用指针作为hashtable的成员, 而是让hashing_strategy结构体直接作为hashtable的成员. 会发生什么bug?
  collision_strategy *my_collision;
  hashtable(int size, hashing_strategy *hashing, collision_strategy *collision)
      : table_size(size), my_hashing(hashing), my_collision(collision) {
    Table = new hash_entry[table_size];
  }
  bool insert(hash_entry entry) {
#ifdef ORIGINAL
    int last_choice = (*my_hashing)(entry.my_string, table_size);
    my_collision->init();
    while (Table[last_choice].my_string != NULL) { // loop infinitely? return false when no more space?
      insert_collision_count++;
      last_choice = (*my_collision)(Table, table_size, last_choice);
    }
    Table[last_choice] = entry;
    return true;
#endif
#ifdef TESTING
    int last_choice;
    // collision_strategy is of type overflow_prob
    if (dynamic_cast<overflow_probe *>(my_collision) != NULL) {
      last_choice = (*my_hashing)(entry.my_string, table_size * overflow_area);
      my_collision->init();
      while (Table[last_choice].my_string != NULL) { // loop infinitely? return false when no more space?
        insert_collision_count++;
        last_choice = (*my_collision)(Table, table_size * overflow_area, last_choice);
      }
      Table[last_choice] = entry;
      return true;
    } else {
      last_choice = (*my_hashing)(entry.my_string, table_size);
      my_collision->init();
      while (Table[last_choice].my_string != NULL) { // loop infinitely? return false when no more space?
        insert_collision_count++;
        last_choice = (*my_collision)(Table, table_size * overflow_area, last_choice);
      }
      Table[last_choice] = entry;
      return true;
    }
#endif
  }

  int query(char *query_string) {
#ifdef ORIGINAL
    int last_choice = (*my_hashing)(query_string, table_size);
    my_collision->init();
    while (Table[last_choice].my_string != NULL &&
           strcmp(Table[last_choice].my_string, query_string) != 0) { // 未处理的情况: 哈希表已满?
      query_collision_count++;
      last_choice = (*my_collision)(Table, table_size, last_choice);
    }
    if (Table[last_choice].my_string == NULL) {
      return -1;
    } else {
      return Table[last_choice].my_data;
    }
#endif
#ifdef TESTING
    int last_choice;
    // collision_strategy is of type overflow_prob
    if (dynamic_cast<overflow_probe *>(my_collision) != NULL) {
      last_choice = (*my_hashing)(query_string, table_size * overflow_area);
      my_collision->init();
      while (Table[last_choice].my_string != NULL &&
             strcmp(Table[last_choice].my_string, query_string) != 0) { // 未处理的情况: 哈希表已满?
        query_collision_count++;
        last_choice = (*my_collision)(Table, table_size * overflow_area, last_choice);
      }
      if (Table[last_choice].my_string == NULL) {
        return -1;
      } else {
        return Table[last_choice].my_data;
      }
    } else {
      last_choice = (*my_hashing)(query_string, table_size);
      my_collision->init();
      while (Table[last_choice].my_string != NULL &&
             strcmp(Table[last_choice].my_string, query_string) != 0) { // 未处理的情况: 哈希表已满?
        query_collision_count++;
        last_choice = (*my_collision)(Table, table_size, last_choice);
      }
      if (Table[last_choice].my_string == NULL) {
        return -1;
      } else {
        return Table[last_choice].my_data;
      }
    }
#endif
  }
};
