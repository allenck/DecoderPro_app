#ifndef CATALOGPANE_H
#define CATALOGPANE_H

#include <QWidget>
//#include <QFileSystemModel>
#include "namedicon.h"
#include "catalogtreemodel.h"

namespace Ui {
class CatalogPane;
}
class CatalogPane : public QWidget
{
    Q_OBJECT

public:
    /*explicit*/ CatalogPane(bool bShowFiles=false, QWidget *parent = 0);
    ~CatalogPane();
    NamedIcon* getSelectedIcon();
    //QFileSystemModel* model;
    CatalogTreeModel* model;

public slots:
    void on_tree_clicked(QModelIndex);
signals:
    void newDirectorySelected(QString path);

private:
    Ui::CatalogPane *ui;
    bool bShowFiles;
};

#endif // CATALOGPANE_H
