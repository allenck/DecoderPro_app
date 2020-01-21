#ifndef POWERPANELFRAME_H
#define POWERPANELFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class PowerPane;
class LIBLAYOUTEDITORSHARED_EXPORT PowerPanelFrame : public JmriJFrame
{
    Q_OBJECT
public:
    explicit PowerPanelFrame(QWidget *parent = 0);
    /*public*/ void dispose();
    /*public*/ QString getClassName();

signals:

public slots:
private:
    // GUI member declarations
    PowerPane* pane;//	= new PowerPane();

};

#endif // POWERPANELFRAME_H
