#ifndef VSDECODERFRAME_H
#define VSDECODERFRAME_H
#include "jmrijframe.h"
#include "appslib_global.h"

class VSDecoderPane;
class APPSLIBSHARED_EXPORT VSDecoderFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit VSDecoderFrame(QWidget *parent = 0);
 /*public*/ void initGUI();
 /*public*/ void windowClosing(QCloseEvent* e);
 /*public*/ QList<QMenu*> getMenus();

signals:

public slots:

private:
 VSDecoderPane* decpane;
 /*private*/ QList<QMenu*> menuList;
 Logger* log;
 /*private*/ void buildMenu();

};

#endif // VSDECODERFRAME_H
