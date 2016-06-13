#ifndef PRINTACTION_H
#define PRINTACTION_H

#include <QAction>

class PaneProgFrame;
class PrintAction : public QAction
{
    Q_OBJECT
public:
    //explicit PrintAction(QObject *parent = 0);
    /*public*/ PrintAction(QString actionName, PaneProgFrame* frame, bool preview);
signals:

public slots:
    /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
    /**
     * Variable to set whether this is to be printed or previewed
     */
    bool isPreview;
    /**
     * Frame hosting the printing
     */
    PaneProgFrame* mFrame;

};

#endif // PRINTACTION_H
