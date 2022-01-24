#include "signalmastaddpane.h"
#include "dccsignalmastaddpane.h"
#include "turnoutsignalmastaddpane.h"
#include "virtualsignalmastaddpane.h"
#include "signalheadsignalmastaddpane.h"
#include "matrixsignalmastaddpane.h"

SignalMastAddPane::SignalMastAddPane(QWidget *parent) : JPanel(parent)
{
}
/**
 * Definition of JPanel used to configure a specific SignalMast type
 *
 * Implementing classes <em>must</em> be registered as service providers of this
 * type to be recognized and usable.
 * <p>
 * General design documentation is available on the
 * <a href="http://jmri.org/help/en/html/doc/Technical/SystemStructure.shtml">Structure of External System Connections page</a>.
 *
 * The general sequence is:
 * <ul>
 * <li>Find one or more object of this type that have {@link SignalMastAddPaneProvider#isAvailable} true.
 * <li>Invoke {@link #setAspectNames} from the selected signal system
 * <li>If you're showing a mast that exists, invoke {@link #setMast} to load the contents
 * <li>To eventually create or update a mast from the entered data, invoke {@link #createMast}
 * </ul>
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2003, 2018
 * @see java.util.ServiceLoader
 * @see AddSignalMastPanel
 * @since 4.11.3
 */
//  /*public*/ abstract class SignalMastAddPane extends JPanel implements JmriServiceProviderInterface {

 /**
  * Provide a new list of aspects in the signal system.
  * Must be done at startup before the pane is shown.
  * May be done later, to update to a new system.
  */
 /*abstract*/ /*public*/ void SignalMastAddPane::setAspectNames(/*@Nonnull*/ SignalAppearanceMap* /*map*/,  /*@Nonnull*/ SignalSystem* /*sigSystem*/) {}

 /**
  * Can this pane edit a specific mast object, i.e. an object of its type?
  * @param mast the SignalMast to possibly display
  * @return true if this pane can handle that mast type; false if can't
  */
/*abstract*/ /*public*/ bool SignalMastAddPane::canHandleMast(/*@Nonnull*/ SignalMast* mast) {return false;}

 /**
  * Load this pane with information from a mast.
  * Do not invoke this is {@link #canHandleMast(SignalMast)} on that mast returns false.
  *
  * @param mast the SignalMast to display or null to reset a previous setting
  */
/*abstract*/ /*public*/ void SignalMastAddPane::setMast(SignalMast* mast) {}

 /**
  * Called to either "create and register" or update an existing mast from the given information.
  * @param sigsysname the name of the signal system in use
  * @param mastname the mast type name
  * @param username user name value
  * @return false if the operation failed, in which case the user should have already been notified
  */
 /*abstract*/ /*public*/ bool SignalMastAddPane::createMast(/*@Nonnull*/
         QString sigsysname, /*@Nonnull*/QString mastname, /*@Nonnull*/QString username) {return false;}

 /**
  * @return Human-prefered name for type of signal mast, in local language
  */
/*@Nonnull*/ /*abstract*/ /*public*/ QString SignalMastAddPane::getPaneName() {return "";}

 /*final*/ /*protected*/ /*static*/ int SignalMastAddPane::NOTIONAL_ASPECT_COUNT = 12;  // size of maps, not critical

// static /*public*/ abstract class SignalMastAddPaneProvider implements JmriServiceProviderInterface {
     /**
      * Is this pane available, given the current configuration of the program?
      * In other words, are all necessary managers and other objects present?
      */
     /*public*/ bool SignalMastAddPaneProvider::isAvailable() { return true; }

     /**
      * @return Human-prefered name for type of signal mast, in local language
      */
     /*@Nonnull*/ /*abstract*/ /*public*/ QString SignalMastAddPaneProvider::getPaneName() {return "";}

     /**
      * @return A new instance of this SignalMastAddPane class
      */
     /*@Nonnull*/ /*abstract*/ /*public*/ SignalMastAddPane* SignalMastAddPaneProvider::getNewPane() {return nullptr;}

     /**
      * Get all available instances as an {@link Collections#unmodifiableMap}
      * between the (localized) name and the pane. Note that this is a SortedMap in
      * name order.
      */
     /*final*/ /*static*/ /*public*/ QMap<QString, SignalMastAddPaneProvider*>* SignalMastAddPaneProvider::getInstancesMap() {
         if (instanceMap == nullptr) loadInstances();
         //return Collections.unmodifiableMap(instanceMap);
         return new QMap<QString, SignalMastAddPaneProvider*>(*instanceMap);
     }

     /**
      * Get all available instances as an {@link Collections#unmodifiableCollection}
      * between the (localized) name and the pane.
      */
     /*final*/ /*static*/ /*public*/ QList<SignalMastAddPaneProvider*> SignalMastAddPaneProvider::getInstancesCollection() {
         if (instanceMap == nullptr) loadInstances();
         return QList<SignalMastAddPaneProvider*> (instanceMap->values());
     }

     /**
      * Load all the available instances. Note this only runs
      * once; there's no reloading once the program is running.
      */
     /*final*/ /*static*/ /*public*/ void SignalMastAddPaneProvider::loadInstances() {
         if (instanceMap != nullptr) return;

         instanceMap = new QMap<QString, SignalMastAddPaneProvider*>();  // sorted map, in string order on key
     #if 0
         ServiceLoader.load(SignalMastAddPaneProvider.class).forEach((pane) -> {
              if (pane.isAvailable()) {
                 instanceMap.put(pane.getPaneName(), pane);
             }
         });
 #endif
         VirtualSignalMastAddPaneProvider* provider = new VirtualSignalMastAddPaneProvider();
         instanceMap->insert(provider->getPaneName(), provider);
         TurnoutSignalMastAddPaneProvider* provider1 = new TurnoutSignalMastAddPaneProvider();
         instanceMap->insert(provider1->getPaneName(), provider1);
         SignalMastAddPaneProvider* provider2 = new SignalMastAddPaneProvider();
         instanceMap->insert(provider2->getPaneName(), provider2);
         SignalHeadSignalHeadSignalMastAddPaneProvider* provider3 = new SignalHeadSignalHeadSignalMastAddPaneProvider();
         instanceMap->insert(provider3->getPaneName(), provider3);
         MatrixSignalMastAddPaneProvider* provider4 = new MatrixSignalMastAddPaneProvider();
         instanceMap->insert(provider4->getPaneName(), provider4);

     }

     /*static*/ /*volatile*/ QMap<QString, SignalMastAddPaneProvider*>* SignalMastAddPaneProvider::instanceMap = nullptr;
 //};
