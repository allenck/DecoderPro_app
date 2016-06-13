#ifndef DUALDECODERSELECTPANE_H
#define DUALDECODERSELECTPANE_H

#include <QWidget>
#include "appslib_global.h"

class Logger;
class ProgModePane;
class JLabel;
class QRadioButton;
class JToggleButton;
class APPSLIBSHARED_EXPORT DualDecoderSelectPane : public QWidget
{
 Q_OBJECT
public:
 explicit DualDecoderSelectPane(QWidget *parent = 0);
 /*public*/ void dispose();

signals:

public slots:
 /*public*/ void programmingOpReply(int value, int retcode);

private:
 bool scanning;// = false;
 int next;// = 0;

 int NENTRIES;// = 8;

 QVector<JLabel*>* labels;// = new JLabel[NENTRIES];
 QVector<QRadioButton*>* buttons;// = new JRadioButton[NENTRIES];

 JLabel* status;// = new JLabel("Idle");
 JToggleButton* searchButton;// = new JToggleButton("Search");
 ProgModePane* modePane;// = new ProgModePane(BoxLayout.Y_AXIS);
 void writeCV15(int value) ;
 void writeCV16(int value);
 void writeCV(int cv, int value);
 void readCV16();
 // modes
 enum MODES
 {
 SEARCH = 10,
 INIT = 20
 };
 int mode;// = SEARCH;

 // search, select operation states
 enum STATES
 {
 IDLE = 0,
 WROTECV15 = 1,
 READCV16 = 2,
 FIRSTCV16 = 11,
 FIRSTCV15 = 12,
 SECONDCV16 = 13
 };
 int state;// = IDLE;
 void searchReply(int value, int retcode);
 void initReply(int value, int retcode);
 Logger* log;

private slots:
 void search();
 void reset();
 void doInit();
 void select(int number);

};

#endif // DUALDECODERSELECTPANE_H
