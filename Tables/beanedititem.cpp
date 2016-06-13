#include "beanedititem.h"

BeanEditItem::BeanEditItem(QObject *parent) :
  QObject(parent)
{
}
/**
 * Hold the information for each bean panel in a structured manner.
 */
// /*public*/ class BeanEditItem {


/**
 * Create the item structure to be added. If the component and description
 * are null, then the help text will be displayed across the width of the
 * panel.
 *
 * @param component   Optional Contains the item to be edited
 * @param description Optional Contains the text for the label that will be
 *                    to the left of the component
 * @param help        Optional Contains the help or hint text, that will be
 *                    displayed to the right of the component
 */
/*public*/ BeanEditItem::BeanEditItem(QWidget* component, QString description, QString help) {
    this->component = component;
    this->description = description;
    this->help = help;
}

/*public*/ QString BeanEditItem::getDescription() {
    return description;
}

/*public*/ QString BeanEditItem::getHelp() {
    return help;
}

/*public*/ QWidget* BeanEditItem::getComponent() {
    return component;
}
