#include "operationspreferencespanel.h"

namespace Operations
{
 OperationsPreferencesPanel::OperationsPreferencesPanel(QWidget *parent) :
  OperationsPanel(parent)
 {
 }
/**
 *
 * @author Randall Wood <randall.h.wood@alexandriasoftware.com>
 */
///*public*/ abstract class OperationsPreferencesPanel extends OperationsPanel implements PreferencesPanel {

 //@Override
 /*public*/ QString OperationsPreferencesPanel::getPreferencesItem() {
     return "OPERATIONS"; // NOI18N
 }

 //@Override
 /*public*/ QString OperationsPreferencesPanel::getPreferencesItemText() {
     return tr("MenuOperations"); // NOI18N
 }

 //@Override
 /*public*/ QString OperationsPreferencesPanel::getLabelKey() {
return "";
 }

 //@Override
 /*public*/ QWidget* OperationsPreferencesPanel::getPreferencesComponent() {
     return this;
 }

 //@Override
 /*public*/ bool OperationsPreferencesPanel::isPersistant() {
     return false;
 }

 //@Override
 /*public*/ bool OperationsPreferencesPanel::isRestartRequired() {
     return false;
 }

 //@Override
 /*public*/ bool OperationsPreferencesPanel::isPreferencesValid() {
     return true; // no validity checking performed
 }
}
