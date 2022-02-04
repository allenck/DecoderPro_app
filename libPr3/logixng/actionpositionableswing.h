#ifndef ACTIONPOSITIONABLESWING_H
#define ACTIONPOSITIONABLESWING_H

#include "abstractdigitalactionswing.h"
#include "jcombobox.h"
#include "jtabbedpane.h"
#include "editor.h"

class ActionPositionableSwing : public AbstractDigitalActionSwing
{
 public:
  ActionPositionableSwing();
  /*public*/  bool validate(/*@Nonnull*/ QList<QString> errorMessages)override;
  /*public*/  MaleSocket* createNewObject(/*@Nonnull*/ QString systemName, /*@CheckForNull*/ QString userName)override;
  /*public*/  void updateObject(/*@Nonnull*/ Base* object)override;
  /*public*/  QString toString()override;
  /*public*/  void dispose();

 private:
  /*private*/ QString _selectedEditor;

  /*private*/ JComboBox/*<EditorItem>*/* _editorComboBox;
  /*private*/ JTabbedPane* _tabbedPanePositionable;
  /*private*/ JComboBox/*<String>*/* _positionableComboBox;
  /*private*/ JPanel* _panelPositionableDirect;
  /*private*/ JPanel* _panelPositionableReference;
  /*private*/ JPanel* _panelPositionableLocalVariable;
  /*private*/ JPanel* _panelPositionableFormula;
  /*private*/ JTextField* _positionableReferenceTextField;
  /*private*/ JTextField* _positionableLocalVariableTextField;
  /*private*/ JTextField* _positionableFormulaTextField;

  /*private*/ JTabbedPane* _tabbedPanePositionableState;
  /*private*/ JComboBox/*<Operation>*/* _isControllingComboBox;
  /*private*/ JPanel* _panelPositionableStateDirect;
  /*private*/ JPanel* _panelPositionableStateReference;
  /*private*/ JPanel* _panelPositionableStateLocalVariable;
  /*private*/ JPanel* _panelPositionableStateFormula;
  /*private*/ JTextField* _positionableStateReferenceTextField;
  /*private*/ JTextField* _positionableStateLocalVariableTextField;
  /*private*/ JTextField* _positionableStateFormulaTextField;
  /*private*/ /*static*/ class EditorItem {

   /*private*/ /*final*/ Editor* _editor;
   public:
   /*public*/ EditorItem(Editor* editor) {
       this->_editor = editor;
   }

   //@Override
   /*public*/ QString toString() {
       return _editor->getName();
   }
   friend class ActionPositionableSwing;
  };
#if 0
  /*public*/ class Operation {
//          Disable(Bundle.getMessage("ActionPositionable_Disable")),
//          Enable(Bundle.getMessage("ActionPositionable_Enable")),
//          Hide(Bundle.getMessage("ActionPositionable_Hide")),
//          Show(Bundle.getMessage("ActionPositionable_Show"));
   public:
    enum TYPE {Disable, Enable, Hide, Show, None};
          //@Override
    /*public*/ static QString toString(TYPE t) {
        switch(t)
        {
        case Disable:
         return tr("Disable");
        case Enable:
         return tr("Enable");
        case Hide:
         return tr("Hide");
        case Show:
         return tr("Show");
        default:
         return tr("None");
        }
    }
    /*public*/ static QList<TYPE> values()
    {
     QList<TYPE> val = {Disable, Enable, Hide, Show};
     return val;
    }
    /*public*/ static TYPE toType(QString s)
    {
     if(s == "Disable") return Disable;
     if(s == "Enable") return Enable;
     if(s == "Hide") return Hide;
     if(s == "Show") return Show;
     return None;
    }
  };
#endif
  /*private*/ void updatePositionables(JActionEvent* e=0);


 protected:
  /*protected*/ void createPanel(/*@CheckForNull*/ Base* object, /*@Nonnull*/ JPanel* buttonPanel)override;

};

#endif // ACTIONPOSITIONABLESWING_H
