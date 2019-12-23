#ifndef JMRICOLORCHOOSERPANEL_H
#define JMRICOLORCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class GridBagLayout;
class QGroupBox;
class QPushButton;
class QSignalMapper;
class JmriColorChooserPanel : public AbstractColorChooserPanel
{
 Q_OBJECT
public:
 JmriColorChooserPanel(QWidget* parent = nullptr);
 /*public*/ void updateChooser();
 /*public*/ QString getDisplayName();
 /*public*/ QIcon getSmallDisplayIcon();
 /*public*/ QIcon getLargeDisplayIcon();
public slots:
 void onColorButton(QWidget*);
 QString getTitle();

private:
 /*private*/ QList<QColor> colors;// = {Color.black, Color.darkGray, Color.gray,
//    Color.lightGray, Color.white, Color.red, Color.pink, Color.orange,
//    Color.yellow, Color.green, Color.blue, Color.magenta, Color.cyan,
//    jmri.util.ColorUtil.BROWN};
 /*private*/ int numColors = 14; //number of entries in the above array
 /*private*/ QGroupBox* recentPanel;// = new JPanel(new GridBagLayout());
 QPushButton* createColorButton(QColor color, bool stdcolor);
 const QIcon getColorIcon(QColor color);
 GridBagLayout* recentPanelLayout = nullptr;
 QSignalMapper* signalMapper = nullptr;

protected:
 /*protected*/ void buildChooser();

};

#endif // JMRICOLORCHOOSERPANEL_H
