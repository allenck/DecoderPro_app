#include "signallingguitools.h"
#include "instancemanager.h"
#include <QMessageBox>
#include "signalmastlogicmanager.h"
#include "signalmast.h"

//SignallingGuiTools::SignallingGuiTools(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Kevin Dickerson Copyright (C) 2011
 * @version			$Revision: 19571 $
 */
///*public*/ class SignallingGuiTools {

//    static final ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrit.signalling.SignallingGuiTools");

/*private*/ SignallingGuiTools::SignallingGuiTools() : QObject(){}

    /**
    * This provides a method to display a message to the user asking them to confirm if they wish to update
    * the signal mast logic from the old signal mast to the new one..
    */
    /*static*/ /*public*/ void SignallingGuiTools::updateSignalMastLogic(JmriJFrame *frame, SignalMast* oldMast, SignalMast* newMast){
//        Object[] options = {rb.getString("UpdateButton"),
//            rb.getString("LeaveButton")};
//        int n = JOptionPane.showOptionDialog(frame,
//            java.text.MessageFormat.format(rb.getString("UpdateLogic"),
//                new Object[]{oldMast.getDisplayName(),newMast.getDisplayName()}),
//            "Update Logic",
//            JOptionPane.YES_NO_CANCEL_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            null,
//            options,
//            options[0]);
//         if(n==0)
//           InstanceManager::getDefault("SignalMastLogicManager").replaceSignalMast(oldMast, newMast);
    switch(QMessageBox::question((QWidget*)frame, tr("Update Logic"), tr("SignalMast %1 has been replaced with %2\ndo you want to update all the logics to reflect this?").arg(oldMast->getDisplayName()).arg(newMast->getDisplayName()), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
     {
     case QMessageBox::Yes:
             ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->replaceSignalMast(oldMast, newMast);
         return;
     default:
      break;
     }
    }

    /**
    * This provides a method to display a message to the user asking them to confirm if they wish to update
    * the signal mast logic for swapping two signal masts over.
    */
    /*static*/ /*public*/ void SignallingGuiTools::swapSignalMastLogic(JmriJFrame* frame, SignalMast* oldMast, SignalMast* newMast){
//        Object[] options = {rb.getString("UpdateButton"),
//            rb.getString("LeaveButton")};
//        int n = JOptionPane.showOptionDialog(frame,
//            java.text.MessageFormat.format(rb.getString("SwapLogic"),
//                new Object[]{oldMast.getDisplayName(),newMast.getDisplayName()}),
//            rb.getString("UpdateLogicTitle"),
//            JOptionPane.YES_NO_CANCEL_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            null,
//            options,
//            options[0]);
//         if(n==0)
//           InstanceManager.signalMastLogicManagerInstance().swapSignalMasts(oldMast, newMast);
    switch(QMessageBox::question((QWidget*)frame, tr("Remove Logic"), tr("SignalMast %1 and %2\n                                                                                have been swapped\ndo you want to update all the logics to reflect this?").arg(oldMast->getDisplayName()).arg(newMast->getDisplayName()), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
     {
     case QMessageBox::Yes:
             ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->swapSignalMasts(oldMast, newMast);
         return;
     default:
      break;
     }
    }

    /**
    * This provides a method to display a message to the user asking them to confirm if they wish to remove
    * the signal mast logic for a given signal.
    */
    /*static*/ /*public*/ bool SignallingGuiTools::removeSignalMastLogic(JmriJFrame* frame, SignalMast* mast){
//        Object[] options = {rb.getString("RemoveButton"),
//            rb.getString("LeaveButton")};
//        int n = JOptionPane.showOptionDialog(frame,
//        java.text.MessageFormat.format(rb.getString("RemoveLogic"),
//                new Object[]{mast.getDisplayName()}),
//            rb.getString("RemoveLogicTitle"),
//            JOptionPane.YES_NO_CANCEL_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            null,
//            options,
//            options[0]);
//         if(n==0){
//           InstanceManager.signalMastLogicManagerInstance().removeSignalMast(mast);
//            return true;
//        }
    switch(QMessageBox::question((QWidget*)frame, tr("Remove Logic"), tr("SignalMast %1 has been removed,\ndo you want to remove the logic associated with it?").arg(mast->getDisplayName()), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
     {
     case QMessageBox::Yes:
             ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->removeSignalMast(mast);
         return true;
     default:
      break;
     }
     return false;
    }

    /**
    * This provides a method to display a message to the user asking them to confirm if they wish to remove
    * the signal mast logic for a given signal, this is the same as removeSignalMastLogic, but with altered text
    */
    /*static*/ /*public*/ void SignallingGuiTools::removeAlreadyAssignedSignalMastLogic(JmriJFrame *frame, SignalMast* mast){
//            Object[] options = {rb.getString("RemoveButton"),
//            rb.getString("LeaveButton")};
//        int n = JOptionPane.showOptionDialog(frame,
//            java.text.MessageFormat.format(rb.getString("RemoveAlreadyLogic"),
//                new Object[]{mast.getDisplayName()}),
//            rb.getString("RemoveLogicTitle"),
//            JOptionPane.YES_NO_CANCEL_OPTION,
//            JOptionPane.QUESTION_MESSAGE,
//            null,
//            options,
//            options[0]);
//         if(n==0)
//           InstanceManager.signalMastLogicManagerInstance().removeSignalMast(mast);
    switch(QMessageBox::question((QWidget*)frame, tr("Remove Already Logic"), tr("SignalMast %1 is already assigned within logics,\ndo you want to remove the logic associated with it?").arg(mast->getDisplayName()), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel))
     {
     case QMessageBox::Yes:
             ((SignalMastLogicManager*)InstanceManager::getDefault("SignalMastLogicManager"))->removeSignalMast(mast);
         return ;
     default:
      break;
     }
    }
