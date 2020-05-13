#include "jmricolorchooserpanel.h"
#include "gridbaglayout.h"
#include "colorutil.h"
#include <QColor>
#include <gridbagconstraints.h>
#include "jmricolorchooser.h"
#include "bufferedimage.h"
#include <QPushButton>
#include <QtMath>
#include "colorutil.h"
#include <QSignalMapper>
#include <QGroupBox>
#include "colorselectionmodel.h"
#include <QButtonGroup>
#include "loggerfactory.h"

JmriColorChooserPanel::JmriColorChooserPanel(QWidget *parent) : AbstractColorChooserPanel(parent)
{
  colors = QList<QColor>() << QColor(Qt::black)<< QColor(Qt::darkGray) << QColor(Qt::gray) <<
    QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red)<< QColor(255,233,236) << QColor(255,170,0)<<
    QColor(Qt::yellow)<< QColor(Qt::green)<< QColor(Qt::blue)<< QColor(Qt::magenta)<< QColor(Qt::cyan)<<
    ColorUtil::BROWN;
 recentPanel = new QGroupBox();
 recentPanel->setLayout(recentPanelLayout = new GridBagLayout());
 //buildChooser();
}

/**
 * Create a custom color chooser panel.
 * The panel contains two button grids.
 * The left grid contains the 13 standard Java colors.
 * The right grid contains recently used colors.
 * <p>
 * @author Dave Sand Copyright (C) 2018
 * @since 4.13.1
 */
///*public*/ class JmriColorChooserPanel extends AbstractColorChooserPanel {


//@Override
/*public*/ void JmriColorChooserPanel::updateChooser()
{
 GridBagConstraints c = GridBagConstraints();
 c.anchor = GridBagConstraints::WEST;
 //recentPanel.removeAll();
 QList<QWidget*> widgets = recentPanel->findChildren<QWidget*>();
 foreach(QWidget* widget, widgets)
 {
  recentPanel->layout()->removeWidget(widget);
  widget->hide();
  delete widget;
 }

 QList<QColor> colors = JmriColorChooser::getRecentColors();
 int cols = qMax(3, (int) qCeil((double)colors.size() / 7));
 int idx = 0;
 for (QColor recent : colors)
 {
  c.gridx = idx % cols;
  c.gridy = idx / cols;
  recentPanelLayout->addWidget(createColorButton(recent, false), c);
  //log->debug(tr("updateChooser: idx = %1, gridx = %2, gridy = %3, cols = %4").arg(idx).arg(c.gridx).arg(c.gridy).arg(cols));
  idx++;
 }
}

//@Override
/*protected*/ void JmriColorChooserPanel::buildChooser(){
 QHBoxLayout* thisLayout;
 setLayout(thisLayout = new QHBoxLayout()); //this, BoxLayout.X_AXIS));
 signalMapper = new QSignalMapper(this);

 QGroupBox* stdColors = new QGroupBox();
 GridBagLayout* stdColorsLayout = new GridBagLayout(stdColors);
 QButtonGroup* buttonGroup = new QButtonGroup();
 //stdColors.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("StandardColorLabel")));  // NOI18N
 //stdColors->setLayout(stdColorsLayout);
 stdColors->setTitle(tr("Standard Colors"));
 ColorSelectionModel* model = getColorSelectionModel();
 GridBagConstraints c = GridBagConstraints();
 c.anchor = GridBagConstraints::WEST;
 QColor defaultColor = model->getSelectedColor();
 for (int i = 0; i < numColors; i++) {
     c.gridx = i % 2;
     c.gridy = i / 2;
     QPushButton* button;
     stdColorsLayout->addWidget(button = createColorButton(colors[i], true), c);
     button->setCheckable(true);
     if(colors[i] == defaultColor)
     {
      button->setDefault(true);
     }
     buttonGroup->addButton(button);
     signalMapper->setMapping(button, colors.at(i).name());
     connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
 }
 thisLayout->addWidget(stdColors);
 stdColors->setVisible(true);

 //recentPanel.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("RecentColorLabel")));  // NOI18N
 recentPanel->setTitle(tr("Recent Colors"));
 QList<QColor> colors = JmriColorChooser::getRecentColors();
 int cols = qMax(3, (int)qCeil((double)colors.size() / 7));
 int idx = 0;
 for (QColor recent : colors) {
     c.gridx = idx % cols;
     c.gridy = idx / cols;
     QPushButton* button;
     recentPanelLayout->addWidget(button =createColorButton(recent, false), c);
     //log->debug(tr("buildChooser: idx = %1, gridx = %2, gridy = %3, cols = %4").arg(idx).arg(c.gridx).arg(c.gridy).arg(cols));
     idx++;
     signalMapper->setMapping(button, recent.name());
     connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
 }
 thisLayout->addWidget(recentPanel);
 recentPanel->setVisible(true);
 connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onColorButton(QString)));
}

/**
 * Create a button that contains a color swatch and
 * the translated color name.  Use the RGB values if a name is not
 * available.
 * @param color The color object
 * @param stdcolor If true, the color name is used otherwise the RGB values.
 * @return a button item with the listener.
 */
QPushButton* JmriColorChooserPanel::createColorButton(QColor color, bool stdcolor) {
#if 0
    BufferedImage* image = new BufferedImage(40, 15,
            BufferedImage::TYPE_INT_ARGB);

    Graphics g = image.getGraphics();
    // fill it with its representative color
    g.setColor(new Color(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha()));
    g.fillRect(0, 0, 40, 15);
    // draw a black border around it
    g.setColor(Color.black);
    g.drawRect(0, 0, 40 - 1, 15 - 1);
    ImageIcon icon = new ImageIcon(image);

    String colorName = "";
    if (stdcolor) {
        colorName = jmri.util.ColorUtil.colorToLocalizedName(color);
    }
#endif
    QString colorTip = ColorUtil::colorToString(color);
    QString colorName = ColorUtil::colorToColorName(color);
    QString colorHexName = color.name();
    QPushButton* colorButton = new QPushButton(getColorIcon(color), colorName);
    colorButton->setToolTip(colorTip);
    colorButton->setCheckable(true);
//        colorButton.addActionListener((ActionEvent e) -> {
//            getColorSelectionModel().setSelectedColor(color);
//        });
    signalMapper->setMapping(colorButton, colorButton);
    connect(colorButton, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    return colorButton;
}

void JmriColorChooserPanel::onColorButton(QString s)
{
 getColorSelectionModel()->setSelectedColor(QColor(s));
}

const QIcon JmriColorChooserPanel::getColorIcon(QColor color)
{
 //Q_ASSERT(color.isValid());
 int ICON_DIMENSION = 10;
 // BufferedImage image = new BufferedImage(ICON_DIMENSION,  ICON_DIMENSION,
 // BufferedImage.TYPE_INT_RGB);
 QImage resultImage =  QImage(ICON_DIMENSION,ICON_DIMENSION,QImage::Format_ARGB32_Premultiplied);

 // Graphics g = image.getGraphics();
 QPainter painter(&resultImage);
//   // set completely transparent
// g.setColor(color);
// g.fillRect(0,0, ICON_DIMENSION,ICON_DIMENSION);
QBrush brBkgnd = QBrush(QColor(color), Qt::SolidPattern);
//eRect.adjust(0, -3.0, 0, 0);
painter.fillRect(resultImage.rect(), brBkgnd);
painter.end();
// ImageIcon icon = new ImageIcon(image);
QIcon icon =  QIcon(QPixmap::fromImage(resultImage));
return icon;
}

//@Override
/*public*/ QString JmriColorChooserPanel::getDisplayName() {
    return "JMRI";  // NOI18N
}

//@Override
/*public*/ QIcon JmriColorChooserPanel::getSmallDisplayIcon(){
   return QIcon();
}

//@Override
/*public*/ QIcon JmriColorChooserPanel::getLargeDisplayIcon(){
   return QIcon();
}

/*public*/ QString JmriColorChooserPanel::getTitle() {return "JMRI";}

Logger* JmriColorChooserPanel::log = LoggerFactory::getLogger("JmriColorChooserPanel");
