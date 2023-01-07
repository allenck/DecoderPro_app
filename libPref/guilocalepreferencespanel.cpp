#include "guilocalepreferencespanel.h"
#include "guilafconfigpane.h"

GuiLocalePreferencesPanel::GuiLocalePreferencesPanel(QWidget *parent) :
    QWidget(parent)
{
 parent = nullptr;
 setObjectName("GuiLocalePreferencesPanel");
}
/**
 * Provide PreferencesPanel information for the JPanel provided by
 * {@link apps.GuiLafConfigPane#doLocale()}.
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
// /*public*/ class GuiLocalePreferencesPanel implements PreferencesSubPanel {

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getParentClassName() {
    return "apps.GuiLafConfigPane";
}

//@Override
/*public*/ void GuiLocalePreferencesPanel::setParent(PreferencesPanel* parent)
{
 //if (parent instanceof GuiLafConfigPane) {
 if(qobject_cast<GuiLafConfigPane*>(parent->ppself())!=nullptr)
 {
  this->parent = (GuiLafConfigPane*) parent->ppself();
 }
}

//@Override
/*public*/ PreferencesPanel* GuiLocalePreferencesPanel::getParent() {
    return this->parent;
}

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getPreferencesItem() {
 if(this->getParent())
    return this->getParent()->getPreferencesItem();
 else
  return "";
}

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getPreferencesItemText() {
 if(this->getParent())
    return this->getParent()->getPreferencesItemText();
 else
  return "";
}

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getTabbedPreferencesTitle() {
    return tr("Locale"); // NOI18N
}

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getLabelKey() {
    return tr("Locale"); // NOI18N
}

//@Override
/*public*/ QWidget* GuiLocalePreferencesPanel::getPreferencesComponent() {
 if(this->getParent())
    return ((GuiLafConfigPane*) this->getParent())->doLocale();
 else
  return nullptr;
}

//@Override
/*public*/ bool GuiLocalePreferencesPanel::isPersistant() {
    return false;
}

//@Override
/*public*/ QString GuiLocalePreferencesPanel::getPreferencesTooltip() {
    return "";
}

//@Override
/*public*/ void GuiLocalePreferencesPanel::savePreferences() {
    this->getParent()->savePreferences();
}

//@Override
/*public*/ bool GuiLocalePreferencesPanel::isDirty() {
    return this->getParent()->isDirty();
}

//@Override
/*public*/ bool GuiLocalePreferencesPanel::isRestartRequired() {
    return this->getParent()->isRestartRequired();
}

//@Override
/*public*/ bool GuiLocalePreferencesPanel::isPreferencesValid() {
    return this->getParent()->isPreferencesValid();
}
/*public*/ QString GuiLocalePreferencesPanel::className() {return "apps.GuiLocalePreferencesPanel";}
