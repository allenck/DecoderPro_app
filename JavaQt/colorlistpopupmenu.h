#ifndef COLORLISTPOPUPMENU_H
#define COLORLISTPOPUPMENU_H
#include <QMenu>

class QSignalMapper;
class ColorSelectionModel;
class ColorListPopupMenu : public QMenu
{
 Q_OBJECT
public:
 ColorListPopupMenu();
 /*public*/ ColorListPopupMenu(ColorSelectionModel* m);
public slots:
 void onColorMenu(QObject *obj);

private:
 /*private*/ static /*final*/ int ICON_DIMENSION;// = 20;
 // Standard Colors
 /*private*/ QVector<QColor> colorCode;// = {Color.black, Color.darkGray, Color.gray,
//    Color.lightGray, Color.white, Color.red, Color.pink, Color.orange,
//    Color.yellow, Color.green, Color.blue, Color.magenta, Color.cyan,
//    jmri.util.ColorUtil.BROWN};
 /*private*/ int numColors = 14; //number of entries in the above arrays
 /*private*/ ColorSelectionModel* model;
 /*private*/ void addRecentColors();
 /*private*/ void addStandardColors();
 /*private*/ QAction* createMenuItem(QColor swatchColor, bool isStdColor);
 QSignalMapper* signalMapper;
};

#endif // COLORLISTPOPUPMENU_H
