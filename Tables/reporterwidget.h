#ifndef REPORTERWIDGET_H
#define REPORTERWIDGET_H

#include <QWidget>
#include "reportermanager.h"
#include "abstractreportermanager.h"
#include "proxyreportermanager.h"
#include <QSignalMapper>
#include "abstractnamedbean.h"
namespace Ui {
class ReporterWidget;
}

class ReporterWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ReporterWidget(QWidget *parent = 0);
    ~ReporterWidget();
    
private:
    Ui::ReporterWidget *ui;
    ProxyReporterManager* mgr;
    QVector<Reporter*> rows;
    void updateRow(int row, Reporter* r);
    QSignalMapper* deleteMapper;
private slots:
    void on_propertyChange(Reporter*,QString,QVariant,QVariant);
    void on_propertyChange(AbstractNamedBean* bean, QString o, QString n);
    void on_newReporterCreated(AbstractReporterManager*,Reporter*);
    void on_btnAdd_clicked();
    void on_deleteMapper_signaled(int);
};

#endif // REPORTERWIDGET_H
