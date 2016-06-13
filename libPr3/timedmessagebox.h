#ifndef TIMEDMESSAGEBOX_H
#define TIMEDMESSAGEBOX_H

#include <QMessageBox>

class TimedMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    //explicit TimedMessageBox(QWidget *parent = 0);
 StandardButton critical(QWidget *parent, const QString &title, const QString &text, const QString &button0Text, const QString &button1Text, const QString &button2Text, int defaultButtonNumber, int escapeButtonNumber, int timeout = 15000);
signals:

public slots:

};

#endif // TIMEDMESSAGEBOX_H
