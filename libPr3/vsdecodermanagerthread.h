#ifndef VSDECODERMANAGERTHREAD_H
#define VSDECODERMANAGERTHREAD_H

#include <QThread>

class VSDecoderManager;
class VSDecoderManagerThread : public QThread
{
 Q_OBJECT
public:
 explicit VSDecoderManagerThread(QObject *parent = 0);
 /*public*/ static VSDecoderManagerThread* instance(bool create);
 /*public*/ static VSDecoderManagerThread* instance();
 /*public*/ static VSDecoderManager* manager();
 /*public*/ void run();
 /*public*/ void kill();

signals:

public slots:

private:
 /*private*/ static VSDecoderManagerThread* _instance;// = NULL;
 /*private*/ static VSDecoderManager* _manager;// = NULL;
 bool is_running;

};

#endif // VSDECODERMANAGERTHREAD_H
