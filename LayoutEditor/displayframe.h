#ifndef DISPLAYFRAME_H
#define DISPLAYFRAME_H
#include "jmrijframe.h"
#include "initeventlistener.h"
#include <QColor>

class Editor;
class BufferedImage;
class DisplayFrame : public JmriJFrame
{
public:
 /*public*/ DisplayFrame(bool saveSize, bool savePosition, QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QString name, bool saveSize, bool savePosition, QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QWidget* parent = nullptr);
 /*public*/ DisplayFrame(QString name, Editor *editor, QWidget* parent = nullptr);
 /*public*/ void setPreviewBg(int index);
 /*public*/ int getPreviewBg();
 /*public*/ void setInitEventListener(InitEventListener* listener);
 /*public*/ void reSize(QWidget*container, QSize deltaDim, QSize newDim, Editor* ed);
 /*public*/ QString getClassName();
 /*public*/ BufferedImage* getPreviewBackground();
 /*public*/ void updateBackground(Editor* ed);
 /*public*/ Editor* getEditor();
 /*public*/ QColor getCurrentColor();
 /*public*/ BufferedImage* getBackground(int index);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("DisplayFrame");
 // Array of BufferedImage backgrounds loaded as background image in Preview, shared across tabs
 /*private*/ QVector<BufferedImage*>* _backgrounds = nullptr;
 /*private*/ Editor* _editor;          // current panel editor using this frame
 /*private*/ QColor _panelBackground;  // current background
 /*private*/ int previewBgIndex = 0;    // Shared index setting for preview pane background color combo choice.
 /*private*/ void makeBackgrounds();

protected:
 /**
  * Shared setting for preview pane background color combo choice.
  * Starts as 0 = use current Panel bg color.
  */
 /*protected*/ int previewBgSet;// = 0;
 /**
  * Listens for init()  = display of the frame
  */
 /*protected*/ InitEventListener* listener = nullptr;
 static QColor _grayColor;// = new Color(235, 235, 235);
 static QColor _darkGrayColor;// = new Color(150, 150, 150);
 static /*protected*/ QVector<QColor> colorChoice;// = QVector<QColor>() <<Qt::white << _grayColor _darkGrayColor; // panel bg color picked up directly

};

#endif // DISPLAYFRAME_H
