#include "colorlistpopupmenu.h"
#include "colorselectionmodel.h"
#include "colorutil.h"
#include "jmricolorchooser.h"
#include "jlabel.h"
#include "bufferedimage.h"
#include <QPainter>
#include "colorutil.h"
#include "imageicon.h"
#include <QSignalMapper>

ColorListPopupMenu::ColorListPopupMenu()
{

}
/**
 * Popup menu for displaying recently selected colors along with standard
 * java colors.
 *
 * @author Paul Bender Copyright (C) 2018
 * @since 4.13.1
 */
// /*public*/ class ColorListPopupMenu extends JPopupMenu {

/*private*/ /*static*/ /*final*/ int ColorListPopupMenu::ICON_DIMENSION = 20;


/*public*/ ColorListPopupMenu::ColorListPopupMenu(ColorSelectionModel* m){
    //super();
    colorCode = QVector<QColor>() << QColor(Qt::black) << QColor(Qt::darkGray) << QColor(Qt::gray) <<
       QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red) << QColor(255,233,236) << QColor(255,165,0) <<
       QColor(Qt::yellow) << QColor(Qt::green) << QColor(Qt::blue) << QColor(Qt::magenta) << QColor(Qt::cyan)<<
       ColorUtil::BROWN;

    model = m;
    signalMapper = new QSignalMapper(this);
    connect(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(onColorMenu(QObject*)));
    addRecentColors();
    addSeparator();
    addStandardColors();
}

/*private*/ void ColorListPopupMenu::addRecentColors(){
    // build the menu.
    addSection( tr("Recent Color"));
    for (QColor color : JmriColorChooser::getRecentColors())
    {
        addAction(createMenuItem(color, false));
    }
}

/*private*/ void ColorListPopupMenu::addStandardColors(){
    // build the menu.
    addSection(tr("Standard Color"));
    for (int i = 0; i < numColors; i++)
    {
        addAction(createMenuItem(colorCode[i], true));
    }
}

/*private*/ QAction* ColorListPopupMenu::createMenuItem(QColor swatchColor, bool isStdColor){
    // update the Swatch to have the right color showing.
    QImage image =  QImage(ICON_DIMENSION, ICON_DIMENSION,
         QImage::Format_ARGB32_Premultiplied);

    //Graphics g = image.getGraphics();
    QPainter g(&image);
    // fill it with its representative color
    //g.setColor(
    //QColor c = QColor(swatchColor.red(), swatchColor.green(), swatchColor.blue(), swatchColor.alpha());
    QBrush brBkgnd = QBrush(QColor(swatchColor), Qt::SolidPattern);
    g.fillRect(0, 0, ICON_DIMENSION, ICON_DIMENSION, brBkgnd);
    // draw a black border around it
//    g.setBrush(QColor(Qt::black));
//    g.drawRect(0, 0, ICON_DIMENSION - 1, ICON_DIMENSION - 1);
    g.end();
    //ImageIcon* icon = new ImageIcon(image);
    QIcon icon = QIcon(QPixmap::fromImage(image));

    //g.dispose();

    QString colorName = "";
    QString colorTip = tr("r=%1, g=%2, b=%3, a=%4").arg(
            swatchColor.red()).arg(swatchColor.green()).arg(swatchColor.blue()).arg(swatchColor.alpha());
    if (isStdColor) {
        colorName = ColorUtil::colorToColorName(swatchColor);
    } else {
        colorName = colorTip;
    }

    QAction* colorMenuItem = new QAction(icon, colorName, this);
    if (isStdColor) colorMenuItem->setToolTip(colorTip);
//    colorMenuItem.addActionListener((ActionEvent e) -> {
//       model.setSelectedColor(swatchColor);
//    });
    colorMenuItem->setData(swatchColor);
    signalMapper->setMapping(colorMenuItem, colorMenuItem);
    connect(colorMenuItem, SIGNAL(triggered(bool)), signalMapper, SLOT(map()));
    return colorMenuItem;
}

void ColorListPopupMenu::onColorMenu(QObject* obj)
{
 QAction* act = (QAction*)obj;
 QColor swatchColor = act->data().value<QColor>();
 model->setSelectedColor(swatchColor);
}
