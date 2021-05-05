#ifndef BLOCKCURVATUREJCOMBOBOX_H
#define BLOCKCURVATUREJCOMBOBOX_H

#include <jcombobox.h>
#include "abstractlistmodel.h"
#include "comboboxmodel.h"

class BlockCurvatureJComboBox : public JComboBox
{
  Q_OBJECT
 public:
  BlockCurvatureJComboBox();
  /*public*/ BlockCurvatureJComboBox(int curvature);
  /*public*/ void setJTableCellClientProperties();
  /*public*/ /*final*/ void setCurvature(int blockCurve);
  /*public*/ static QString getStringFromCurvature(int blockCurve);
  /*public*/ int getCurvature();
  /*public*/ static int getCurvatureFromString(QString s);
  /*public*/ static int getCurvatureFromObject(QVariant obj);

 private:
  /*private*/ static /*final*/ QString NONE_TEXT;// = Bundle.getMessage("BlockNone"); // NOI18N
  /*private*/ static /*final*/ QString GRADUAL_TEXT;// = Bundle.getMessage("BlockGradual"); // NOI18N
  /*private*/ static /*final*/ QString TIGHT_TEXT;// = Bundle.getMessage("BlockTight"); // NOI18N
  /*private*/ static /*final*/ QString SEVERE_TEXT;// = Bundle.getMessage("BlockSevere"); // NOI18N
  /*private*/ static /*final*/ QStringList CURVE_OPTIONS;// = {NONE_TEXT, GRADUAL_TEXT, TIGHT_TEXT, SEVERE_TEXT};

  friend class CurvatureComboBoxModel;
};

/*private*/ /*static*/ class CurvatureComboBoxModel : public AbstractListModel, public ComboBoxModel/*<String>*/
{
  Q_OBJECT
  Q_INTERFACES(ComboBoxModel)
    /*private*/ QString selection = QString();
public:
    //@Override
    /*public*/ QVariant getElementAt(int index) const override{
        return BlockCurvatureJComboBox::CURVE_OPTIONS[index];
    }

    //@Override
    /*public*/ int getSize() const override{
        return BlockCurvatureJComboBox::CURVE_OPTIONS.length();
    }

    //@Override
    /*public*/ void setSelectedItem(QVariant anItem) {
        selection = /*(String)*/ anItem.toString(); // to select and register an
    } // item from the pull-down list

    // Methods implemented from the interface ComboBoxModel
    //@Override
    /*public*/ QString getSelectedItem() {
        return selection; // to add the selection to the combo box
    }
  QObject* self() override {return (QObject*)this;}

 private:
  QVariant data(const QModelIndex &index, int role) const override {
   if(role == Qt::DisplayRole)
    return getElementAt(index.row());
   return QVariant();
  }
  int rowCount(const QModelIndex &parent) const override{return getSize();}
};

#endif // BLOCKCURVATUREJCOMBOBOX_H
