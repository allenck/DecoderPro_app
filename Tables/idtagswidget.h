#ifndef IDTAGSWIDGET_H
#define IDTAGSWIDGET_H

#include <QWidget>
#include "defaultidtagmanager.h"
#include "abstractidtag.h"
#include "defaultidtag.h"

namespace Ui {
class IdTagsWidget;
}

class TablesFrame;
class IdTagsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit IdTagsWidget(QWidget *parent = 0);
    ~IdTagsWidget();
    
private:
 Ui::IdTagsWidget *ui;
 DefaultIdTagManager* mgr;
 void updateRow(int row, AbstractIdTag* t);
 TablesFrame* parent;
 QVector<AbstractIdTag*> rows;
 QSignalMapper* deleteMapper;
 QSignalMapper* clearMapper;

private slots:
  void on_btnAdd_clicked();
  void on_propertyChange(DefaultIdTag*,QString pName, QObject* o, QObject* n);
  void on_propertyChange(AbstractNamedBean*, QString pName, QString o, QString n);
  void on_tableWidget_cellChanged(int,int);
  void on_newIdTagCreated(IdTag* tag);
  void on_deleteMapper_clicked(QObject*);
  void on_clearMapper_clicked(QObject*);
  void on_chkSaveWhen_toggled(bool b);
  void on_chkFastClock_toggled(bool b);
  void propertyChange(PropertyChangeEvent* e);

};

#endif // IDTAGSWIDGET_H
