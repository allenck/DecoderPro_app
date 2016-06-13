#ifndef OBJECTVIEWERDIALOG_H
#define OBJECTVIEWERDIALOG_H

#include <QDialog>
#include "ObjectViewer/ovtablemodel.h"
#include "namedbean.h"

namespace Ui {
class ObjectViewerDialog;
}

class ObjectViewerDialog : public QDialog
{
 Q_OBJECT
    
public:
 explicit ObjectViewerDialog(QWidget *parent = 0);
 void setData(QList<ItemData>* list);
 void clearData();
 ~ObjectViewerDialog();
    
private:
 Ui::ObjectViewerDialog *ui;
 OVTableModel* model;
};

#endif // OBJECTVIEWERDIALOG_H
