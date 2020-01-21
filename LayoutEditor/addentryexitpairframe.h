#ifndef ADDENTRYEXITPAIRFRAME_H
#define ADDENTRYEXITPAIRFRAME_H
#include "jmrijframe.h"
#include "liblayouteditor_global.h"

class LayoutEditor;
class AddEntryExitPairPanel;
class QPushButton;
class LIBLAYOUTEDITORSHARED_EXPORT AddEntryExitPairFrame : public JmriJFrame
{
 Q_OBJECT
public:
 explicit AddEntryExitPairFrame(QWidget *parent = 0);
 /*public*/ void initComponents(LayoutEditor* panel); //throws Exception
 /*public*/ QString getClassName();

signals:

public slots:
 void on_options();
private:
 QPushButton* sendButton;
 AddEntryExitPairPanel* nxPanel;


};

#endif // ADDENTRYEXITPAIRFRAME_H
