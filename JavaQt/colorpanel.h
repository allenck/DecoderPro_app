#ifndef COLORPANEL_H
#define COLORPANEL_H
#include "jpanel.h"

class QButtonGroup;
class SlidingSpinner;
class JActionEvent;
class ColorModel;
class ColorPanel : public JPanel
{
 Q_OBJECT
public:
 ColorPanel(ColorModel* model);
public slots:
 /*public*/ void actionPerformed(/*ActionEvent* event = 0*/);

private:
 /*private*/ /*final*/ QVector<SlidingSpinner*> spinners;// = new SlidingSpinner[5];
 /*private*/ /*final*/ QVector<float> values;// = QVector<float>(this->spinners.length());

 /*private*/ /*final*/ ColorModel* model;
 /*private*/ QColor color;
 /*private*/ int x = 1;
 /*private*/ int y = 2;
 /*private*/ int z = 0;
 void buildPanel();
 void colorChanged();
 float getValueX();
 float getValueY();
 float getValueZ();
 void setValue(float z);
 void setValue(float x, float y);
 int getColor(float z);
 int getColor(float x, float y);
 void setColor(QColor color);
 /*private*/ int getColor(int index);
 /*private*/ void setValue(int index);
 /*private*/ void setDefaultValue(int index);
 QButtonGroup* group;

 friend class ColorChooserPanel;
 friend class SlidingSpinner;
 friend class DiagramComponent;
 friend class ColorChooserPanelTest;
};

#endif // COLORPANEL_H
