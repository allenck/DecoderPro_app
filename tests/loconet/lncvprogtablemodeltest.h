#ifndef LNCVPROGTABLEMODELTEST_H
#define LNCVPROGTABLEMODELTEST_H

#include <QObject>
#include "lncvprogtablemodel.h"

class LncvProgTableModelTest : public QObject
{
  Q_OBJECT
 public:
  explicit LncvProgTableModelTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 signals:

 public slots:
      void testCTor();
      void testInitTable();
      void testGetColumnName();
      void testGetColumnClass();
      void tastIsCellEditable();
      void testGetColumnCount();
      void testGetSetValueAt();
 private:
  LocoNetSystemConnectionMemo* memo;
  LncvProgTableModel* lptm;

};

#endif // LNCVPROGTABLEMODELTEST_H
