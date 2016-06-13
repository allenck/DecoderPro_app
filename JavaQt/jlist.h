#ifndef JLIST_H
#define JLIST_H

#include <QListView>

class JList : public QListView
{
public:
 JList( QWidget* parent = 0);
 QModelIndexList getSelectedValues();

private:
};

#endif // JLIST_H
