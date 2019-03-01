#include "jmricolorchooserpanel.h"
#include "gridbaglayout.h"
#include "colorutil.h"
#include <QColor>
#include <gridbagconstraints.h>
#include "jmricolorchooser.h"
#include "bufferedimage.h"
#include <QPushButton>

JmriColorChooserPanel::JmriColorChooserPanel(QWidget *parent) : AbstractColorChooserPanel(parent)
{
  colors = QList<QColor>() << QColor(Qt::black)<< QColor(Qt::darkGray) << QColor(Qt::gray) <<
    QColor(Qt::lightGray) << QColor(Qt::white) << QColor(Qt::red)<< QColor(255,233,236) << QColor(255,170,0)<<
    QColor(Qt::yellow)<< QColor(Qt::green)<< QColor(Qt::blue)<< QColor(Qt::magenta)<< QColor(Qt::cyan)<<
    ColorUtil::BROWN;

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
    /*public*/ void JmriColorChooserPanel::updateChooser(){
        GridBagConstraints c = GridBagConstraints();
        c.anchor = GridBagConstraints::WEST;
        //recentPanel.removeAll();
        QList<QWidget*> widgets = recentPanel->findChildren<QWidget*>();
        foreach(QWidget* widget, widgets)
         recentPanel->layout()->removeWidget(widget);

        QList<QColor> colors = JmriColorChooser::getRecentColors();
        int cols = qMax(3, (int) std::ceil((double)colors.size() / 7));
        int idx = 0;
        for (QColor recent : colors) {
            c.gridx = idx % cols;
            c.gridy = idx / cols;
            ((GridBagLayout*)recentPanel->layout())->addWidget(createColorButton(recent, false), c);
            idx++;
        }
    }

    //@Override
    /*protected*/ void JmriColorChooserPanel::buildChooser(){
        setLayout(new QHBoxLayout()); //this, BoxLayout.X_AXIS));
#if 0
        JPanel* stdColors = new JPanel(new GridBagLayout());
        stdColors.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("StandardColorLabel")));  // NOI18N
        GridBagConstraints c = new GridBagConstraints();
        c.anchor = java.awt.GridBagConstraints.WEST;
        for (int i = 0; i < numColors; i++) {
            c.gridx = i % 2;
            c.gridy = i / 2;
            stdColors.add(createColorButton(colors[i], true), c);
        }
        add(stdColors);
        stdColors.setVisible(true);

        recentPanel.setBorder(BorderFactory.createTitledBorder(Bundle.getMessage("RecentColorLabel")));  // NOI18N
        ArrayList<Color> colors = JmriColorChooser.getRecentColors();
        int cols = Math.max(3, (int) Math.ceil((double)colors.size() / 7));
        int idx = 0;
        for (Color recent : colors) {
            c.gridx = idx % cols;
            c.gridy = idx / cols;
            recentPanel.add(createColorButton(recent, false), c);
            idx++;
        }
        add(recentPanel);
        recentPanel.setVisible(true);
#endif
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
        String colorTip = String.format("r=%d, g=%d, b=%d, a=%d",
                color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());

        JButton colorButton = new JButton(colorName, icon);
        colorButton.setToolTipText(colorTip);
        colorButton.addActionListener((ActionEvent e) -> {
            getColorSelectionModel().setSelectedColor(color);
        });

        return colorButton;
#endif
        return new QPushButton();
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
