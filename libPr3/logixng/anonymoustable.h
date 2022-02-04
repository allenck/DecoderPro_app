#ifndef ANONYMOUSTABLE_H
#define ANONYMOUSTABLE_H
#include "table.h"

/**
 * Represent an anonymous table.
 * An anonymous table has no name. It can be assigned to a Memory or to a cell
 * in a table but cannot be stored in an xml file. It's used as a temporary
 * storage during execution of JMRI.
 *
 * @author Daniel Bergqvist Copyright (C) 2019
 */
/*public*/ /*interface*/class AnonymousTable : public Table {
  Q_OBJECT
 public:
  AnonymousTable(QObject* parent = nullptr) : Table("Anonymous", "", parent){}

    /*public*/ virtual void insertColumn(int col)=0;

    /*public*/ virtual void deleteColumn(int col)=0;

    /*public*/ virtual void insertRow(int row)=0;

    /*public*/ virtual void deleteRow(int row)=0;

};
Q_DECLARE_INTERFACE(AnonymousTable, "AnonymousTable")
#endif // ANONYMOUSTABLE_H
