#ifndef WINDOWMENU_H
#define WINDOWMENU_H

#include <QMenu>
#include <QFrame>
#include "liblayouteditor_global.h"

class JmriJFrame;
class WindowInterface;
class LIBLAYOUTEDITORSHARED_EXPORT WindowMenu : public QMenu
{
    Q_OBJECT
public:
    explicit WindowMenu(QWidget *parent = 0);
    /*public*/ WindowMenu(WindowInterface* wi, QWidget *parent);

signals:

public slots:
    void menuSelected();
private:
    /*private*/ QFrame* parentFrame;	// Keep note of the window containing the menu
    /*private*/ QList<JmriJFrame*>* framesList;	// Keep the list of windows, in order to find out which window was selected


};

#endif // WINDOWMENU_H
