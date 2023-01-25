#ifndef CATEGORYLOCONET_H
#define CATEGORYLOCONET_H

#include "category.h"

class CategoryLocoNet : public Category
{
 public:
  explicit CategoryLocoNet();
  /*public*/ static /*final*/ CategoryLocoNet LOCONET;// = new CategoryLocoNet();
  /*public*/ static void registerCategory();
  /*public*/ static bool hasLocoNet();

};

#endif // CATEGORYLOCONET_H
