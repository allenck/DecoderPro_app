#ifndef CATEGORYDISPLAY_H
#define CATEGORYDISPLAY_H

#include "category.h"

class CategoryDisplay : public Category
{
 public:
  CategoryDisplay();
  /*public*/ static /*final*/ CategoryDisplay DISPLAY;// = new CategoryDisplay();
  /*public*/ static void registerCategory();

};

#endif // CATEGORYDISPLAY_H
