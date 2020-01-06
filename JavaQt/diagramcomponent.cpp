#include "diagramcomponent.h"
#include "bufferedimage.h"
#include "colorpanel.h"
#include "insets.h"
#include <QMouseEvent>

/*
 * Copyright (c) 2008, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

//package javax.swing.colorchooser;

//import java.awt.Color;
//import java.awt.Graphics;
//import java.awt.Insets;
//import java.awt.event.MouseEvent;
//import java.awt.event.MouseListener;
//import java.awt.event.MouseMotionListener;
//import java.awt.image.BufferedImage;
//import javax.swing.JComponent;

// /*final*/ class DiagramComponent extends JComponent implements MouseListener, MouseMotionListener {


    DiagramComponent::DiagramComponent(ColorPanel* panel, bool diagram) {
     insets = new Insets(0, 0, 0, 0);;

        this->panel = panel;
        this->diagram = diagram;
//        addMouseListener(this);
//        addMouseMotionListener(this);
    }

    /*public*/ void DiagramComponent::paintEvent(QPaintEvent */*event*/)
    {
     QPainter* painter = new QPainter(this);
     paintComponent(painter);
    }


    //@Override
    /*protected*/ void DiagramComponent::paintComponent(QPainter* /*painter*/) {
        getInsets(this->insets);
        this->width = getWidth() - this->insets->left - this->insets->right;
        this->height = getHeight() - this->insets->top - this->insets->bottom;

        bool update = (this->image == nullptr)
                || (this->width != this->image->width())
                || (this->height != this->image->height());
        if (update) {
            int size = this->width * this->height;
            if ((this->array.isEmpty()) || (this->array.length() < size)) {
                this->array = QVector<int>(size);
            }
            this->image = new BufferedImage(this->width, this->height, /*BufferedImage::TYPE_INT_RGB*/QImage::Format_RGB16);
        }
        {
            float dx = 1.0f / (float) (this->width - 1);
            float dy = 1.0f / (float) (this->height - 1);

            int offset = 0;
            float y = 0.0f;
            for (int h = 0; h < this->height; h++, y += dy) {
                if (this->diagram) {
                    float x = 0.0f;
                    for (int w = 0; w < this->width; w++, x += dx, offset++) {
                        this->array[offset] = this->panel->getColor(x, y);
                    }
                }
                else {
                    int color = this->panel->getColor(y);
                    for (int w = 0; w < this->width; w++, offset++) {
                        this->array[offset] = color;
                    }
                }
            }
        }
        this->image->setRGB(0, 0, this->width, this->height, this->array, 0, this->width);
#if 0
        painter.drawImage(this->image, this->insets->left, this->insets->top, this->width, this->height, this);
        if (isEnabled()) {
            this->width--;
            this->height--;
            painter.setXORMode(Color.WHITE);
            painter.setColor(Color.BLACK);
            if (this->diagram) {
                int x = getValue(this->panel->getValueX(), this->insets->left, this->width);
                int y = getValue(this->panel->getValueY(), this->insets->top, this->height);
                painter.drawLine(x - 8, y, x + 8, y);
                painter.drawLine(x, y - 8, x, y + 8);
            }
            else {
                int z = getValue(this->panel->getValueZ(), this->insets.top, this->height);
                painter.drawLine(this->insets->left, z, this->insets->left + this->width, z);
            }
            painter.setPaintMode();
        }
#endif
    }

    /*public*/ void DiagramComponent::mousePressEvent(QMouseEvent* event) {
        mouseDragged(event);
    }

    /*public*/ void DiagramComponent::mouseReleaseEvent(QMouseEvent* /*event*/) {
    }

    /*public*/ void DiagramComponent::mouseClicked(QMouseEvent* /*event*/) {
    }

    /*public*/ void DiagramComponent::mouseEntered(QMouseEvent* /*event*/) {
    }

    /*public*/ void DiagramComponent::mouseExited(QMouseEvent* /*event*/) {
    }

    /*public*/ void DiagramComponent::mouseMoveEvent(QMouseEvent* /*event*/) {
    }

    /*public*/ void DiagramComponent::mouseDragged(QMouseEvent* event) {
        if (isEnabled()) {
            float y = getValue(event->pos().y(), this->insets->top, this->height);
            if (this->diagram) {
                float x = getValue(event->pos().y(), this->insets->left, this->width);
                this->panel->setValue(x, y);
            }
            else {
                this->panel->setValue(y);
            }
        }
    }

    /*private*/ /*static*/ int DiagramComponent::getValue(float value, int min, int max) {
        return min + (int) (value * (float) (max));
    }

    /*private*/ /*static*/ float DiagramComponent::getValue(int value, int min, int max) {
        if (min < value) {
            value -= min;
            return (value < max)
                    ? (float) value / (float) max
                    : 1.0f;
        }
        return 0.0f;
    }

    /*public*/ bool  DiagramComponent::isOpaque() {return _opaque;}

    /*public*/ QColor DiagramComponent::getBackground()
    {
     return palette().color(QWidget::backgroundRole());
    }
    /*public*/ void DiagramComponent::setBackground(QColor c){
     setStyleSheet(tr("QWidget{background-color: rgb(%1,%2,%3)").arg(c.red()).arg(c.green()).arg(c.blue()));
    }
    /*public*/ QFont DiagramComponent::getFont()
    {
     return font();
    }
    /*public*/ void DiagramComponent::setOpaque(bool b)
    {
     _opaque = b;
    }

    /*public*/ void DiagramComponent::setFont(QFont f)
    {
     QWidget::setFont(f);
    }
