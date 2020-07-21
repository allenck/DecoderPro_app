#ifndef LAYOUTEDITORVIEWCONTEXT_H
#define LAYOUTEDITORVIEWCONTEXT_H

#include <QObject>

class LayoutEditorViewContext : public QObject
{
    Q_OBJECT
public:
    explicit LayoutEditorViewContext(QObject *parent = nullptr);
    /*final*/ /*public*/ void setLayoutWidth(int width);
    /*final*/ /*public*/ int getLayoutWidth();
    /*final*/ /*public*/ void setLayoutHeight(int height);
    /*final*/ /*public*/ int getLayoutHeight();
    /*final*/ /*public*/ void setWindowWidth(int width);
    /*final*/ /*public*/ int getWindowWidth();
    /*final*/ /*public*/ void setWindowHeight(int height);
    /*final*/ /*public*/ int getWindowHeight();
    /*final*/ /*public*/ int getUpperLeftX();
    /*final*/ /*public*/ void setUpperLeftX(int x);
    /*final*/ /*public*/ int getUpperLeftY();
    /*final*/ /*public*/ void setUpperLeftY(int y);
    /*final*/ /*public*/ int setGridSize(int newSize);
    /*final*/ /*public*/ int getGridSize();
    /*final*/ /*public*/ int setGridSize2nd(int newSize);
    /*final*/ /*public*/ int getGridSize2nd();
    /*final*/ /*public*/ void setMainlineTrackWidth(float width);
    /*final*/ /*public*/ int getMainlineTrackWidth();
    /*final*/ /*public*/ void setSidelineTrackWidth(float width);
    /*final*/ /*public*/ int getSidelineTrackWidth();
    /*final*/ /*public*/ double getXScale();
    /*final*/ /*public*/ void setXScale(double scale);
    /*final*/ /*public*/ double getYScale();
    /*final*/ /*public*/ void setYScale(double scale);
signals:

private:
    /*private*/ int panelWidth = 0;
    /*private*/ int panelHeight = 0;
    /*private*/ int windowWidth = 0;
    /*private*/ int windowHeight = 0;
    /*private*/ int upperLeftX = 0;
    /*private*/ int upperLeftY = 0; // (not panel)
    /*private*/ int gridSize1st = 10;
    /*private*/ int gridSize2nd = 10;
    /*private*/ float mainlineTrackWidth = 4.0F;
    /*private*/ float sidelineTrackWidth = 2.0F;
    /*private*/ double xScale = 1.0;
    /*private*/ double yScale = 1.0;


};

#endif // LAYOUTEDITORVIEWCONTEXT_H
