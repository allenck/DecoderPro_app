#include "nullprofile.h"

//NullProfile::NullProfile()
//{

//}
/**
 * An empty JMRI application profile. Profiles allow a JMRI application to load
 * completely separate set of preferences at each launch without relying on host
 * OS-specific tricks to ensure this happens.
 * <p>
 * A NullProfile allows an application using JMRI as a library to set the active
 * JMRI profile to an identity set by that application, if the use of a standard
 * JMRI profile is not acceptable.
 * <p>
 * This class deliberately overrides all methods of {@link jmri.profile.Profile}
 * that access the {@code name} and {@code id} fields to remove protections
 * and restrictions on those fields.
 *
 * @author Randall Wood Copyright (C) 2014
 * @see jmri.profile.ProfileManager#setActiveProfile(jmri.profile.Profile)
 */
// /*public*/ class NullProfile extends Profile {

    /**
     * Create a NullProfile object given just a path to it. The Profile must
     * exist in storage on the computer. Uses a random identity for the Profile.
     *
     * @param path The Profile's directory
     * @throws java.io.IOException If path is not readable
     */
    /*public*/ NullProfile::NullProfile(/*@Nonnull*/ File* path, QObject* parent) throw (IOException) : Profile(path, false,parent) {
        //super(path, false);
    }

    /**
     * Create a NullProfile object given just a path to it. The Profile must
     * exist in storage on the computer.
     *
     * @param path The Profile's directory
     * @param id   The Profile's id
     * @throws java.io.IOException If path is not readable
     */
    /*public*/ NullProfile::NullProfile(/*@Nonnull*/ File* path, /*@Nonnull*/ QString id, QObject* parent) throw (IOException)
    : Profile(path, id,false, parent)
    {
        //super(path, id, false);
    }

    /**
     * Create a Profile object and a profile in storage. A Profile cannot exist
     * in storage on the computer at the path given. Since this is a new
     * profile, the id must match the last element in the path.
     * <p>
     * This is the only time the id can be set on a Profile, as the id becomes a
     * read-only property of the Profile. The {@link ProfileManager} will only
     * load a single profile with a given id.
     *
     * @param name The name of the profile.
     * @param id   If null, {@link jmri.profile.ProfileManager#createUniqueId()}
     *             will be used to generate the id.
     * @param path The path where the profile is stored.
     * @throws java.io.IOException If path is not readable.
     * @throws IllegalArgumentException If a profile already exists at or within path
     */
    /*public*/ NullProfile::NullProfile(QString name, QString id, /*@Nonnull*/ File* path, QObject* parent) throw (IOException, IllegalArgumentException)
    : Profile(path, parent)
    {
//        this(path, (null != id) ? id : ProfileManager.createUniqueId());
//        this.setNameInConstructor(name);
    }

    //@Override
    /*public*/ QString NullProfile::toString() {
        return this->getName();
    }

    //@Override
//    /*public*/ int NullProfile::hashCode() {
//        int hash = 7;
//        hash = 71 * hash + this->getId().hashCode();
//        return hash;
//    }

    //@Override
    /*public*/ bool NullProfile::equals(QObject* obj) {
        if (obj == nullptr) {
            return false;
        }
        //if (getClass() != obj.getClass()) {
        if(this->metaObject()->className() != obj->metaObject()->className()){
            return false;
        }
        /*final*/ NullProfile* other = (NullProfile*) obj;
        return this->getId() == (other->getId());
    }

    /**
     * Test if the profile is complete.
     *
     * @return always true for a NullProfile.
     */
    //@Override
    /*public*/ bool NullProfile::isComplete() {
        return true;
    }

    /**
     * Return the uniqueness portion of the Profile Id.
     *
     * @return The complete Id of a NullProfile.
     */
    //@Override
    /*public*/ QString NullProfile::getUniqueId() {
        return this->getId(); // NOI18N
    }

