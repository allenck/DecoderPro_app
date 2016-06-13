#ifndef ROSTERGROUPTABLEFRAME_H
#define ROSTERGROUPTABLEFRAME_H
#include "jmrijframe.h"

class QTableView;
class QGroupBox;
class RosterGroupTableModel;
class RosterGroupTableFrame : public JmriJFrame
{
 Q_OBJECT

public:
 /*public*/ RosterGroupTableFrame(RosterGroupTableModel* model, QString helpTarget, QWidget* parent = 0);
 /*public*/ void dispose();


private:
 RosterGroupTableModel* dataModel;
 QTableView* dataTable;
 //JScrollPane dataScroll;
 QGroupBox* bottomBox;		// panel at bottom for extra buttons etc
 int bottomBoxIndex;	// index to insert extra stuff
 static /*final*/ int bottomStrutWidth;// = 20;
 QGroupBox* topBox;		// panel at bottom for extra buttons etc
 int topBoxIndex;	// index to insert extra stuff
 static /*final*/ int topStrutWidth;// = 20;
 void extras();

protected:
 /*protected*/ QGroupBox* getBottomBox();
 /*protected*/ void addToBottomBox(QWidget* comp);
 /*protected*/ QGroupBox* getTopBox();
 /*protected*/ void addToTopBox(QWidget* comp);

};

#endif // ROSTERGROUPTABLEFRAME_H
