#ifndef HELPMENUPROVIDER_H
#define HELPMENUPROVIDER_H

#include <QObject>
#include "helputil.h"

class HelpMenuProvider : public QObject, public MenuProvider
{
  Q_OBJECT
  Q_INTERFACES(MenuProvider)
 public:
  explicit HelpMenuProvider(QObject *parent = nullptr);
  /*public*/ QList<JMenuItem*> getHelpMenuItems() override;

   QObject* self() override {return (QObject*)this;}
 signals:
private:
   static Logger* log;
};

#endif // HELPMENUPROVIDER_H
