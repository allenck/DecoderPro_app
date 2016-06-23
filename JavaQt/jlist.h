#ifndef JLIST_H
#define JLIST_H

#include <QListView>
#include "javaqt_global.h"
class JAVAQTSHARED_EXPORT JList : public QListView
{
public:
 JList( QWidget* parent = 0);
 QModelIndexList getSelectedValues();

private:
};

#endif // JLIST_H
