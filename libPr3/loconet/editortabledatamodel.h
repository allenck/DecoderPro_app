#ifndef EDITORTABLEDATAMODEL_H
#define EDITORTABLEDATAMODEL_H
#include "abstracttablemodel.h"

class HardcopyWriter;
class QPushButton;
class QTableView;
class Logger;
class SpjFile;
class EditorTableDataModel : public AbstractTableModel
{
 Q_OBJECT
public:
 //explicit EditorTableDataModel(QObject *parent = 0);
 enum COLUMNS
 {
  HEADERCOL = 0,
  TYPECOL = 1,
  MAPCOL = 2,
  HANDLECOL = 3,
  FILENAMECOL = 4,
  LENGTHCOL = 5,
  PLAYBUTTONCOL = 6,
  REPLACEBUTTONCOL = 7,

  NUMCOLUMN = 8
 };
 /*public*/ EditorTableDataModel(SpjFile* file, QObject *parent = 0);
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ int getPreferredWidth(int col);
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
 /*public*/ void configureTable(QTableView* table);
  /*public*/ QPushButton* largestWidthButton(int col);
 /*synchronized*/ /*public*/ void dispose();
 /*public*/ void printTable(HardcopyWriter* w);

signals:

public slots:
private:
 SpjFile* file;
 Logger* log;
 void playButtonPressed(QVariant value, int row, int col);
 void viewTxtButtonPressed(QVariant value, int row, int col);
 void viewSdfButtonPressed(QVariant value, int row, int col);
 void editSdfButtonPressed(QVariant value, int row, int col);
 void replWavButtonPressed(QVariant value, int row, int col);
protected:
 /*protected*/ void printColumns(HardcopyWriter* w, QStringList columnStrings, int columnSize);

};

#endif // EDITORTABLEDATAMODEL_H
