#ifndef PREVIEWPANEL_H
#define PREVIEWPANEL_H
#include "jpanel.h"

class ImagePanel;
class Logger;
class DisplayFrame;
class QComboBox;
class PreviewPanel : public JPanel
{
 Q_OBJECT
public:
 PreviewPanel();
 /*public*/ PreviewPanel(DisplayFrame* parent, ImagePanel* panel1, ImagePanel* panel2, bool hasComboBox);
 /*public*/ void setBackgroundSelection(int index);
 /*public*/ DisplayFrame* getParent();

private:
 static Logger* log;
 DisplayFrame* _parent;
 QComboBox/*<String>*/* _bgColorBox;
 /*private*/ JPanel* makeBgButtonPanel(ImagePanel* preview1, ImagePanel* preview2);

};

#endif // PREVIEWPANEL_H
