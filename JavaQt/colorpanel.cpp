#include "colorpanel.h"
#include "colormodel.h"
#include "gridbaglayout.h"
#include <QButtonGroup>
#include <QRadioButton>
#include "insets.h"
#include "jlabel.h"
#include "slidingspinner.h"

/*
 * Copyright (c) 2008, 2012, Oracle and/or its affiliates. All rights reserved.
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
//import java.awt.ContainerOrderFocusTraversalPolicy;
//import java.awt.GridBagConstraints;
//import java.awt.GridBagLayout;
//import java.awt.Insets;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import javax.swing.ButtonGroup;
//import javax.swing.JLabel;
//import javax.swing.JPanel;
//import javax.swing.JRadioButton;
//import javax.swing.border.EmptyBorder;
//import javax.swing.JSpinner.DefaultEditor;

///*final*/ class ColorPanel extends JPanel implements ActionListener {


ColorPanel::ColorPanel(ColorModel* model) : JPanel()
{
    //super(new GridBagLayout());
 GridBagLayout* g = new GridBagLayout(this);
 spinners = QVector<SlidingSpinner*>(5);
 values = QVector<float>(this->spinners.length());

    GridBagConstraints gbc = GridBagConstraints();
    gbc.fill = GridBagConstraints::HORIZONTAL;

    gbc.gridx = 1;
    group = new QButtonGroup();
//    EmptyBorder border = null;
    for (int i = 0; i < this->spinners.length(); i++) {
        if (i < 3) {
            QRadioButton* button = new QRadioButton();
            if (i == 0) {
//                Insets insets = button.getInsets();
//                insets.left = button.getPreferredSize().width;
//                border = new EmptyBorder(insets);
                button->setChecked(true);
//                gbc.insets.top = 5;
            }
            g->addWidget(button, gbc);
            group->addButton(button,i);
//            button.setActionCommand(Integer.toString(i));
//            button.addActionListener(this);
            connect(button, SIGNAL(clicked()), this, SLOT(actionPerformed()));
            this->spinners[i] = new SlidingSpinner(this, button);
        }
        else {
            JLabel* label = new JLabel();
            g->addWidget(label, gbc);
//            label->setBorder(border);
//            label.setFocusable(false);
            this->spinners[i] = new SlidingSpinner(this, label);
        }
    }
    gbc.gridx = 2;
    gbc.weightx = 1.0;
    gbc.insets->top = 0;
    gbc.insets->left = 5;
    for (SlidingSpinner* spinner : this->spinners) {
        g->addWidget((QWidget*)spinner->getSlider(), gbc);
        gbc.insets->top = 5;
    }
    gbc.gridx = 3;
    gbc.weightx = 0.0;
    gbc.insets->top = 0;
    for (SlidingSpinner* spinner : this->spinners) {
        g->addWidget((QWidget*)spinner->getSpinner(), gbc);
        gbc.insets->top = 5;
    }
//    setFocusTraversalPolicy(new ContainerOrderFocusTraversalPolicy());
//    setFocusTraversalPolicyProvider(true);
//    setFocusable(false);

    this->model = model;
}

/*public*/ void ColorPanel::actionPerformed(/*ActionEvent* event*/) {
//    try {
        this->z = group->checkedId();//Integer.parseInt(event.getActionCommand());
        this->y = (this->z != 2) ? 2 : 1;
        this->x = (this->z != 0) ? 0 : 1;
//        getParent().repaint();
//    }
//    catch (NumberFormatException exception) {
//    }
}

void ColorPanel::buildPanel()
{
 int count = this->model->getCount();
 this->spinners[4]->setVisible(count > 4);
 for (int i = 0; i < count; i++)
 {
  QString text = this->model->getLabel((Component*)this, i);
  QWidget* object = this->spinners[i]->getLabel();
  if (qobject_cast<QRadioButton*>(object)) {
      QRadioButton* button = (QRadioButton*) object;
      button->setText(text);
//            button.getAccessibleContext().setAccessibleDescription(text);
  }
  else if (qobject_cast<JLabel*>(object)) {
      QLabel* label = (QLabel*) object;
//      label->setText(text);
  }
  this->spinners[i]->setRange(this->model->getMinimum(i), this->model->getMaximum(i));
  this->spinners[i]->setValue(this->values[i]);
//        this->spinners[i]->getSlider().getAccessibleContext().setAccessibleName(text);
//        this->spinners[i].getSpinner().getAccessibleContext().setAccessibleName(text);
//        DefaultEditor editor = (DefaultEditor) this->spinners[i].getSpinner().getEditor();
//        editor.getTextField().getAccessibleContext().setAccessibleName(text);
//        this->spinners[i].getSlider().getAccessibleContext().setAccessibleDescription(text);
//        this->spinners[i].getSpinner().getAccessibleContext().setAccessibleDescription(text);
//        editor.getTextField().getAccessibleContext().setAccessibleDescription(text);
 }
}

void ColorPanel::colorChanged() {
#if 0
    this->color = new Color(getColor(0), true);
    Object parent = getParent();
    if (parent instanceof ColorChooserPanel) {
        ColorChooserPanel chooser = (ColorChooserPanel) parent;
        chooser.setSelectedColor(this->color);
        chooser.repaint();
    }
#endif
}

float ColorPanel::getValueX() {
    return this->spinners[this->x]->getValue();
}

float ColorPanel::getValueY() {
    return 1.0f - this->spinners[this->y]->getValue();
}

float ColorPanel::getValueZ() {
    return 1.0f - this->spinners[this->z]->getValue();
}

void ColorPanel::setValue(float z) {
    this->spinners[this->z]->setValue(1.0f - z);
    colorChanged();
}

void ColorPanel::setValue(float x, float y) {
    this->spinners[this->x]->setValue(x);
    this->spinners[this->y]->setValue(1.0f - y);
    colorChanged();
}

int ColorPanel::getColor(float z) {
    setDefaultValue(this->x);
    setDefaultValue(this->y);
    this->values[this->z] = 1.0f - z;
    return getColor(3);
}

int ColorPanel::getColor(float x, float y) {
    this->values[this->x] = x;
    this->values[this->y] = 1.0f - y;
    setValue(this->z);
    return getColor(3);
}

void ColorPanel::setColor(QColor color) {
    if (color!=(this->color)) {
        this->color = color;
        this->model->setColor(color.rgb(), this->values);
        for (int i = 0; i < this->model->getCount(); i++) {
            this->spinners[i]->setValue(this->values[i]);
        }
    }
}

/*private*/ int ColorPanel::getColor(int index) {
    while (index < this->model->getCount()) {
        setValue(index++);
    }
    return this->model->getColor(this->values);
}

/*private*/ void ColorPanel::setValue(int index) {
    this->values[index] = this->spinners[index]->getValue();
}

/*private*/ void ColorPanel::setDefaultValue(int index) {
    float value = this->model->getDefault(index);
    this->values[index] = (value < 0.0f)
            ? this->spinners[index]->getValue()
            : value;
}

