#ifndef CONTROLLERFILTERFRAME_H
#define CONTROLLERFILTERFRAME_H
#include "jmrijframe.h"

class TableModelEvent;
class JTable;
class Logger;
class ControllerFilterFrame : public JmriJFrame
{
public:
 ControllerFilterFrame(QWidget* parent = 0);
 /*public*/ void initComponents() throw (Exception);
 /*public*/ void tableChanged(TableModelEvent* e);

public slots:
 void dispose();
 void on_save();

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ControllerFilterFrame.class.getName());
 /*private*/ static QStringList COLUMN_NAMES;// = {Bundle.getMessage("ColumnSystemName"),
//         Bundle.getMessage("ColumnUserName"),
//         Bundle.getMessage("Include")};
 /*private*/ QWidget* addTurnoutPanel();
 /*private*/ QWidget* addRoutePanel();
 /*private*/ void buildTable(JTable* table);
// /*private*/ QWidget* getIncludeButtonsPanel(/*final*/ AbstractFilterModel fm);
 /*private*/ QWidget* addCancelSavePanel();

protected:
 /*protected*/ void storeValues();

};

#endif // CONTROLLERFILTERFRAME_H
