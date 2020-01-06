#ifndef DEFAULTPREVIEWPANEL_H
#define DEFAULTPREVIEWPANEL_H
#include "jpanel.h"

class JColorChooser;
class DefaultPreviewPanel : public JPanel
{
 Q_OBJECT
public:
 DefaultPreviewPanel(QWidget* parent = nullptr);
 /*public*/ QSize getPreferredSize();
 /*public*/ void paintEvent(QPaintEvent *);
 /*public*/ QColor getForeground();
 /*public*/ QFont getFont();

private:
 /*private*/ int squareSize = 25;
 /*private*/ int squareGap = 5;
 /*private*/ int innerGap = 5;


 /*private*/ int textGap = 5;
 /*private*/ QFont font;// = new Font(Font.DIALOG, Font.PLAIN, 12);
 /*private*/ QString sampleText;

 /*private*/ int swatchWidth = 50;

 /*private*/ QColor oldColor;// = null;
 /*private*/ JColorChooser* getColorChooser();
 /*private*/ QString getSampleText();
 /*private*/ int paintSwatch(QPainter *g, int offsetX);
 /*private*/ int paintText(QPainter* g, int offsetX);
 /*private*/ int paintSquares(QPainter* g, int offsetX);
 QColor fg;
};

#endif // DEFAULTPREVIEWPANEL_H
