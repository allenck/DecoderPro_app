#ifndef JMRICOLORCHOOSERPANEL_H
#define JMRICOLORCHOOSERPANEL_H
#include "abstractcolorchooserpanel.h"

class Logger;
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
 QColor getForeground();
public slots:
 void onColorButton(QString s);
 QString getTitle();
 void setEnabled(bool b) override {QWidget::setEnabled(b);}

private:
 /*private*/ QList<QColor> colors;// = {Color.black, Color.darkGray, Color.gray,
//    Color.lightGray, Color.white, Color.red, Color.pink, Color.orange,
//    Color.yellow, Color.green, Color.blue, Color.magenta, Color.cyan,
//    jmri.util.ColorUtil.BROWN};
 /*private*/ int numColors = 14; //number of entries in the above array
 /*private*/ JPanel* recentPanel;// = new JPanel(new GridBagLayout());
 QPushButton* createColorButton(QColor color, bool stdcolor);
 const QIcon getColorIcon(QColor color);
 GridBagLayout* recentPanelLayout = nullptr;
 QSignalMapper* signalMapper = nullptr;
 static Logger* log;

protected:
 /*protected*/ void buildChooser();

};

#endif // JMRICOLORCHOOSERPANEL_H
