#ifndef DEFAULTCONDITIONALNGSCAFFOLD_H
#define DEFAULTCONDITIONALNGSCAFFOLD_H
#include "defaultconditionalng.h"

class DefaultConditionalNGScaffold : public DefaultConditionalNG
{
 public:
  /*public*/ DefaultConditionalNGScaffold(QString sys, QString user, QObject* parent = nullptr);
  /*public*/ DefaultConditionalNGScaffold(QString sys, QString user, int threadID, QObject* parent = nullptr);
};

#endif // DEFAULTCONDITIONALNGSCAFFOLD_H
