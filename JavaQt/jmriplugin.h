#ifndef JMRIPLUGIN_H
#define JMRIPLUGIN_H

#include <QObject>

class JFrame;
class QMenuBar;
class JmriPlugin : public QObject
{
  Q_OBJECT
 public:
  /*public*/ static void start(JFrame* mainFrame, QMenuBar* menuBar);

 private:
  explicit JmriPlugin() {}

 signals:

};

#endif // JMRIPLUGIN_H
