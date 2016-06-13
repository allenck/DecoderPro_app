#ifndef REPORTERWIDGET_H
#define REPORTERWIDGET_H

#include <QWidget>
#include "reportermanager.h"
#include "abstractreportermanager.h"
#include "proxyreportermanager.h"
#include <QSignalMapper>

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
    QVector<AbstractReporter*> rows;
    void updateRow(int row, AbstractReporter* r);
    QSignalMapper* deleteMapper;
private slots:
    void on_propertyChange(AbstractReporter*,QString,QVariant,QVariant);
    void on_propertyChange(AbstractNamedBean* bean, QString o, QString n);
    void on_newReporterCreated(AbstractReporterManager*,AbstractReporter*);
    void on_btnAdd_clicked();
    void on_deleteMapper_signaled(int);
};

#endif // REPORTERWIDGET_H
