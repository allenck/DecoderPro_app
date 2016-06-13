#ifndef AUTOMATTABLEFRAME_H
#define AUTOMATTABLEFRAME_H

#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class AutomatTableDataModel;
class JTable;
class LIBLAYOUTEDITORSHARED_EXPORT AutomatTableFrame : public JmriJFrame
{
 Q_OBJECT
public:
 //explicit AutomatTableFrame(QWidget *parent = 0);
 /*public*/ AutomatTableFrame(AutomatTableDataModel* model, QWidget *parent = 0);
 /*public*/ void dispose();

signals:

public slots:
private:
 AutomatTableDataModel* dataModel;
 JTable* dataTable;
 //ScrollPane dataScroll;

};

#endif // AUTOMATTABLEFRAME_H
