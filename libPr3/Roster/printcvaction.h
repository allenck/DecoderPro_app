#ifndef PRINTCVACTION_H
#define PRINTCVACTION_H

#include <QAction>
#include "logger.h"

class HardcopyWriter;
class RosterEntry;
class PaneProgFrame;
class CvTableModel;
class PrintCvAction : public QAction
{
    Q_OBJECT
public:
    //explicit PrintCvAction(QObject *parent = 0);
    /*public*/ PrintCvAction(QString actionName, CvTableModel* pModel, PaneProgFrame* pParent, bool preview, RosterEntry* pRoster);
    /*public*/ void printInfoSection(HardcopyWriter* w);
    /*public*/ static long cvSortOrderVal(QString cvName);

signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
    /*final*/ int TABLE_COLS;// = 3;
    /**
     * Frame hosting the printing
     */
    PaneProgFrame* mFrame;
    CvTableModel* mModel;
    RosterEntry* mRoster;
    /**
     * Variable to set whether this is to be printed or previewed
     */
    bool isPreview;
    Logger* log;
};

#endif // PRINTCVACTION_H
