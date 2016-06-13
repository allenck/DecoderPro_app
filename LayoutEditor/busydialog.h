#ifndef BUSYDIALOG_H
#define BUSYDIALOG_H
#include "jdialog.h"

class JFrame;
class QProgressBar;
class BusyDialog : public JDialog
{
 Q_OBJECT
public:
 //explicit BusyDialog(QWidget *parent = 0);
 /*public*/ BusyDialog(JFrame* frame, QString title, bool modal,QWidget *parent=0) ;
 /*public*/ void initComponents();
 /*public*/ void start() ;
 /*public*/ void finish();

signals:

public slots:
private:
 JFrame* frame;
 QProgressBar* pbar;

};

#endif // BUSYDIALOG_H
