#ifndef CATEGORYDISPLAY_H
#define CATEGORYDISPLAY_H

#include "category.h"

class CategoryDisplay : public Category
{
  Q_OBJECT
 public:
  CategoryDisplay(QObject* parent = nullptr);
  /*public*/ static /*final*/ CategoryDisplay* DISPLAY;// = new CategoryDisplay();
  /*public*/ static void registerCategory();

};

#endif // CATEGORYDISPLAY_H
