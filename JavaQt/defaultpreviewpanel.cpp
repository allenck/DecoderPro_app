#include "defaultpreviewpanel.h"
#include "jcolorchooser.h"
#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>

DefaultPreviewPanel::DefaultPreviewPanel(QWidget *parent) : JPanel(parent)
{

}
/*
 * Copyright (c) 1998, 2013, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

//package javax.swing.colorchooser;

//import javax.swing.*;
//import javax.swing.border.*;
//import javax.swing.event.*;
//import javax.swing.text.*;
//import java.awt.*;
//import java.awt.image.*;
//import java.awt.event.*;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//import java.io.Serializable;
//import sun.swing.SwingUtilities2;


/**
 * The standard preview panel for the color chooser.
 * <p>
 * <strong>Warning:
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans™
 * has been added to the <code>java.beans package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Steve Wilson
 * @see JColorChooser
 */
// class DefaultPreviewPanel extends JPanel {


/*private*/ JColorChooser* DefaultPreviewPanel::getColorChooser() {
//        return (JColorChooser)SwingUtilities.getAncestorOfClass(
//                                   JColorChooser.class, this);
 QObject* obj = this;
 while(true)
 {
  obj = obj->parent();
  if(obj== nullptr)
   return nullptr;
  if(qobject_cast<JColorChooser*>(obj))
   return (JColorChooser*)obj;
 }
 return (JColorChooser*) metaObject()->superClass();
}

/*public*/ QSize DefaultPreviewPanel::getPreferredSize() {
    QWidget* host = getColorChooser();
    if (host == nullptr) {
        host = this;
    }
    //FontMetrics fm = host.getFontMetrics(getFont());
    QFontMetrics fm = host->fontMetrics();

    int ascent = fm.ascent();
    int height = fm.height();
    int width = fm.width(getSampleText());//SwingUtilities2.stringWidth(host, fm, getSampleText());


    int y = height*3 + textGap*3;
    int x = squareSize * 3 + squareGap*2 + swatchWidth + width + textGap*3;
    return QSize( x,y );
}

// /*public*/ void paintComponent(Graphics g)
/*public*/ void DefaultPreviewPanel::paintEvent(QPaintEvent* evt)
{
 QPainter g(this);
 QRect rect = evt->rect();
    if (!oldColor.isValid())
        oldColor = getForeground();

//    g.setColor(getBackground());
    g.fillRect(0,0,width(), height(), /*getBackground()*/QColor(Qt::lightGray));

//    if (this.getComponentOrientation().isLeftToRight()) {
//        int squareWidth = paintSquares(g, 0);
//        int textWidth = paintText(g, squareWidth);
//        paintSwatch(g, squareWidth + textWidth);
//    } else
    {
        int swatchWidth = paintSwatch(&g, 0);
        int textWidth = paintText(&g, swatchWidth);
        paintSquares(&g , swatchWidth + textWidth);

    }
}

/*private*/ int DefaultPreviewPanel::paintSwatch(QPainter *g, int offsetX) {
    int swatchX = offsetX;
    //g.setColor(oldColor);
    g->fillRect(swatchX, 0, swatchWidth, (squareSize) + (squareGap/2), oldColor);
    //g.setColor(getForeground());
    g->fillRect(swatchX, (squareSize) + (squareGap/2), swatchWidth, (squareSize) + (squareGap/2), getForeground() );
    return (swatchX+swatchWidth);
}

/*private*/ int DefaultPreviewPanel::paintText(QPainter* g, int offsetX) {
    g->setFont(getFont());
    QWidget* host = getColorChooser();
    if (host == nullptr) {
        host = this;
    }
    //FontMetrics fm = SwingUtilities2.getFontMetrics(host, g);
    QFontMetrics fm = host->fontMetrics();

    int ascent = fm.ascent();
    int height = fm.height();
    int width = fm.width(getSampleText());//SwingUtilities2.stringWidth(host, fm, getSampleText());

    int textXOffset = offsetX + textGap;

    QColor color = getForeground();

    //g.setColor(color);

//    SwingUtilities2.drawString(host, g, getSampleText(),textXOffset+(textGap/2),
//                               ascent+2);
    g->drawText(textXOffset+(textGap/2), ascent+2,  getSampleText());

    g->fillRect(textXOffset,
               ( height) + textGap,
               width + (textGap),
               height +2, color);

    //g.setColor(Color.black);
    g->setBrush(color);
//    SwingUtilities2.drawString(host, g, getSampleText(),
//                 textXOffset+(textGap/2),
//                 height+ascent+textGap+2);
    g->drawText(textXOffset+(textGap/2), height+ascent+textGap+2, getSampleText());


    //g.setColor(Color.white);

    g->fillRect(textXOffset,
               ( height + textGap) * 2,
               width + (textGap),
               height +2, QColor(Qt::white));

    //g.setColor(color);
    g->setBrush(QColor(Qt::black));
//    SwingUtilities2.drawString(host, g, getSampleText(),
//                 textXOffset+(textGap/2),
//                 ((height+textGap) * 2)+ascent+2);
    g->drawText(textXOffset+(textGap/2), ((height+textGap) * 2)+ascent+2, getSampleText());

    return width + textGap*3;

}

/*private*/ int DefaultPreviewPanel::paintSquares(QPainter *g, int offsetX) {

    int squareXOffset = offsetX;
    QColor color = getForeground();

    //g.setColor(Color.white);
    g->fillRect(squareXOffset,0,squareSize,squareSize, QColor(Qt::white));
    //g.setColor(color);
    g->fillRect(squareXOffset+innerGap,
               innerGap,
               squareSize - (innerGap*2),
               squareSize - (innerGap*2), color);
    //g.setColor(Color.white);
    g->fillRect(squareXOffset+innerGap*2,
               innerGap*2,
               squareSize - (innerGap*4),
               squareSize - (innerGap*4), QColor(Qt::white));

    //g.setColor(color);
    g->fillRect(squareXOffset,squareSize+squareGap,squareSize,squareSize, color);

    g->translate(squareSize+squareGap, 0);
    //g.setColor(Color.black);
    g->fillRect(squareXOffset,0,squareSize,squareSize, QColor(Qt::black));
    //g.setColor(color);
    g->fillRect(squareXOffset+innerGap,
               innerGap,
               squareSize - (innerGap*2),
               squareSize - (innerGap*2), color);
    //g.setColor(Color.white);
    g->fillRect(squareXOffset+innerGap*2,
               innerGap*2,
               squareSize - (innerGap*4),
               squareSize - (innerGap*4),QColor(Qt::white));
    g->translate(-(squareSize+squareGap), 0);

    g->translate(squareSize+squareGap, squareSize+squareGap);
    //g.setColor(Color.white);
    g->fillRect(squareXOffset,0,squareSize,squareSize,QColor(Qt::white));
    //g.setColor(color);
    g->fillRect(squareXOffset+innerGap,
               innerGap,
               squareSize - (innerGap*2),
               squareSize - (innerGap*2), color);
    g->translate(-(squareSize+squareGap), -(squareSize+squareGap));



    g->translate((squareSize+squareGap)*2, 0);
    //g.setColor(Color.white);
    g->fillRect(squareXOffset,0,squareSize,squareSize,QColor(Qt::white));
    //g.setColor(color);
    g->fillRect(squareXOffset+innerGap,
               innerGap,
               squareSize - (innerGap*2),
               squareSize - (innerGap*2), color);
    //g.setColor(Color.black);
    g->fillRect(squareXOffset+innerGap*2,
               innerGap*2,
               squareSize - (innerGap*4),
               squareSize - (innerGap*4), QColor(Qt::black));
    g->translate(-((squareSize+squareGap)*2), 0);

    g->translate((squareSize+squareGap)*2, (squareSize+squareGap));
    //g.setColor(Color.black);
    g->fillRect(squareXOffset,0,squareSize,squareSize, QColor(Qt::black));
    //g.setColor(color);
    g->fillRect(squareXOffset+innerGap,
               innerGap,
               squareSize - (innerGap*2),
               squareSize - (innerGap*2), color);
    g->translate(-((squareSize+squareGap)*2), -(squareSize+squareGap));

    return (squareSize*3+squareGap*2);
}

/*private*/ QString DefaultPreviewPanel::getSampleText() {
    if (this->sampleText == "") {
        //this.sampleText = UIManager.getString("ColorChooser.sampleText", getLocale());
     this->sampleText = "Sample text";
    }
    return this->sampleText;
}

/*public*/ QColor DefaultPreviewPanel::getForeground() {return fg;}

/*public*/ QFont DefaultPreviewPanel::getFont() {return JPanel::font();}
