#ifndef DECODERPRO3_H
#define DECODERPRO3_H
#include "apps3.h"
#include "runnable.h"

class DecoderPro3 : public Apps3
{
    Q_OBJECT
public:
    //explicit DecoderPro3(QObject *parent = 0);
 /*public*/  DecoderPro3(QStringList args, QObject *parent = 0);
 /*public*/  /*synchronized*/ static QString getMenuFile();
 /*public*/  /*synchronized*/ static QString getToolbarFile();
 /*public*/  static void main(QStringList args);
 static /*public*/  void preInit(QStringList args);

signals:

public slots:
private:
    /*private*/ static QString menuFile;// = NULL;
    /*private*/ static QString toolbarFile;// = null;
    /*private*/ static /*final*/ QString applicationName;// = "DecoderPro";
    Logger* log;

protected:
    /*protected*/ void createMainFrame();
    virtual /*protected*/ void start();
    virtual /*protected*/ void displayMainFrame(QSize d);

    friend class LoadDecoders;
};

class LoadDecoders : public QObject
{
 Q_OBJECT
public:
 LoadDecoders(QObject* parent = 0);
 ~LoadDecoders() {}
public slots:
 void process();
 //void run();
signals:
 void finished();
 void error(QString err);

};
#endif // DECODERPRO3_H
