#ifndef PR4SELECTPANE_H
#define PR4SELECTPANE_H
#include "pr3selectpane.h"

class Pr4SelectPane : public Pr3SelectPane
{
 Q_OBJECT
public:
 Pr4SelectPane(QWidget *parent = nullptr);
 /*public*/ QString getHelpTarget();
 /*public*/ QString getTitle();

};

#endif // PR4SELECTPANE_H
