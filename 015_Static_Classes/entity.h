#ifndef _entity_h
#define _entity_h

#include <iostream>

struct Entity
{
  static int a;
  int b;
  static inline int c;
  void Print();
  void add_to_a(int num);
  static void add_to_b(Entity& e, int num);
  static void add_to_c(int num);
};

#endif