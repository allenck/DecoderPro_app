#ifndef DECODERPRO3WINDOW_H
#define DECODERPRO3WINDOW_H
#include "rosterframe.h"

class DecoderPro3Window : public RosterFrame
{
 Q_OBJECT
public:
 explicit DecoderPro3Window(QWidget *parent = 0);
 /*public*/  DecoderPro3Window(QString menuFile, QString toolbarFile, QWidget *parent = 0);
 /*public*/  void remoteCalls(QStringList args)override;

signals:

public slots:
private:
    void buildWindow() override;

 protected:
    /*protected*/ void additionsToToolBar()override;

};

#endif // DECODERPRO3WINDOW_H
