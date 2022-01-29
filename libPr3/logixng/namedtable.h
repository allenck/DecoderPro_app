#ifndef NAMEDTABLE_H
#define NAMEDTABLE_H
#include "namedbean.h"
#include "table.h"

/**
 * Represent a named table.
 * A named table is a table that is a NamedBean.
 *
 * @author Daniel Bergqvist Copyright (C) 2019
 */
/*public*/ /*interface*/class NamedTable : public NamedBean, public Table  {
  Q_OBJECT
  Q_INTERFACES(Table)
 public:
  NamedTable(QString name, QObject* parent=nullptr) : NamedBean(name, parent) {}
};
#endif // NAMEDTABLE_H
