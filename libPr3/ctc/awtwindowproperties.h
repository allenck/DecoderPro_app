#ifndef AWTWINDOWPROPERTIES_H
#define AWTWINDOWPROPERTIES_H

#include <QObject>
#include "properties.h"

class JFrame;
class AwtWindowProperties : public QObject
{
  Q_OBJECT
 public:
  explicit AwtWindowProperties(QObject *parent = nullptr);
  /*public*/ AwtWindowProperties(JFrame* window, QString filename, QString windowName, QObject *parent=nullptr);

  /*public*/ void close();
  /*public*/ /*final*/ void setWindowState(JFrame* window, QString windowName);
  /*public*/ void saveWindowState(JFrame *window, QString windowName);
  /*public*/ void saveWindowStateAndClose(JFrame *window, QString windowName);

 signals:

 public slots:

 private:
  /*private*/ /*final*/ Properties* _mProperties;
  /*private*/ /*final*/ QString _mFilename;
  /*private*/ /*final*/ QWidget* _mMasterWindow;

};

#endif // AWTWINDOWPROPERTIES_H
