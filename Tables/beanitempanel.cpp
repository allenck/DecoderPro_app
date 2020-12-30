#include "beanitempanel.h"
#include "actionlistener.h"

BeanItemPanel::BeanItemPanel(QWidget* parent ) : QWidget(parent)
{
 reset = NULL;
 save = NULL;
 items =  QList<BeanEditItem*>();
}

BeanItemPanel::~BeanItemPanel() {}

/**
 * Hold the information for each bean panel in a structured mannor.
 */
// /*public*/ class BeanItemPanel extends JPanel{

    /**
  *
  */
 // private static final long serialVersionUID = -5160179371427193315L;

///*public*/ BeanItemPanel(){
//       super();
//   }

/*public*/ void BeanItemPanel::saveItem()
{
 if(save!=NULL)
  save->actionPerformed(NULL);
}

/*public*/ void BeanItemPanel::resetField()
{
 if(reset!=NULL)
  reset->actionPerformed(NULL);
}

/**
 *  Set the action to be performed when the save button is pressed
 */
/*public*/ void BeanItemPanel::setSaveItem(AbstractAction* save)
{
 this->save = save;
}

/**
 *  Set the action to be performed when the cancel button is pressed
 */
/*public*/ void BeanItemPanel::setResetItem(AbstractAction* reset){
    this->reset = reset;
}


/*public*/ void BeanItemPanel::addItem(BeanEditItem* bei){
    items.append(bei);
}

/*public*/ QList<BeanEditItem*> BeanItemPanel::getListOfItems(){
    return items;
}

/*public*/ void BeanItemPanel::setName(QString name){ this->name = name; }
/*public*/ QString BeanItemPanel::getName() { return name; }

