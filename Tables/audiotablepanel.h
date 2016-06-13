#ifndef AUDIOTABLEPANEL_H
#define AUDIOTABLEPANEL_H

#include <QWidget>

class FlowLayout;
class AudioTableDataModel;
class JTable;
class QTabWidget;
class QGroupBox;
class AudioTablePanel : public QWidget
{
 Q_OBJECT
public:
 //explicit AudioTablePanel(QWidget *parent = 0);
 /*public*/ AudioTablePanel(AudioTableDataModel* listenerModel,
         AudioTableDataModel* bufferModel,
         AudioTableDataModel* sourceModel,
         QString helpTarget, QWidget *parent = 0);
 /*public*/ QAction* getPrintItem();
 /*public*/ void dispose();

signals:

public slots:
 void On_printItemTriggered();

private:
 /*private*/ AudioTableDataModel* listenerDataModel;
 /*private*/ AudioTableDataModel* bufferDataModel;
 /*private*/ AudioTableDataModel* sourceDataModel;
 /*private*/ JTable* listenerDataTable;
 /*private*/ JTable* bufferDataTable;
 /*private*/ JTable* sourceDataTable;
// /*private*/ JScrollPane listenerDataScroll;
// /*private*/ JScrollPane bufferDataScroll;
// /*private*/ JScrollPane sourceDataScroll;
 /*private*/ QTabWidget* audioTabs;
 QGroupBox* bottomBox;                  // panel at bottom for extra buttons etc
 int bottomBoxIndex;             // index to insert extra stuff
 static /*final*/ int bottomStrutWidth;// = 20;
 void extras();
 FlowLayout* bottomBoxLayout;
 QString helpTarget;
protected:
 /*protected*/ QGroupBox* getBottomBox();
 /*protected*/ void addToBottomBox(QWidget* comp);
 friend class AudioTableAction;
};

#endif // AUDIOTABLEPANEL_H
