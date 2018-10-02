#ifndef DISPLAYFRAME_H
#define DISPLAYFRAME_H
#include "jmrijframe.h"
#include "initeventlistener.h"

class DisplayFrame : public JmriJFrame
{
public:
 /*public*/ DisplayFrame(bool saveSize, bool savePosition, QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QString name, bool saveSize, bool savePosition, QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QString name, QWidget* parent = nullptr);
 /*public*/ void setPreviewBg(int index);
 /*public*/ int getPreviewBg();
 /*public*/ void setInitEventListener(InitEventListener* listener);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DisplayFrame");

protected:
 /**
  * Shared setting for preview pane background color combo choice.
  * Starts as 0 = use current Panel bg color.
  */
 /*protected*/ int previewBgSet;// = 0;
 /**
  * Listens for init()  = display of the frame
  */
 /*protected*/ InitEventListener* listener;

};

#endif // DISPLAYFRAME_H
