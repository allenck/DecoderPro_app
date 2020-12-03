#include "lndplxgrpinfoimpl.h"
#include "loggerfactory.h"
#include "loconetsystemconnectionmemo.h"
#include "lndplxgrpinfoimplconstants.h"
#include "lniplimplementation.h"

/**
 * Provides a low-level interface to Digitrax Duplex Group Identity information.
 * <p>
 * Implements the following "Property Change" events, which are defined as
 * static strings in {@link jmri.jmrix.loconet.duplexgroup.LnDplxGrpInfoImplConstants}:
 * <ul>
 * <li>
 *   DPLX_PC_STAT_LN_UPDATE -
 *   Indicates that a GUI status line could be updated using provided string.
 * <li>
 *   DPLX_PC_STAT_LN_UPDATE_IF_NOT_CURRENTLY_ERROR - Indicates that a GUI status
 *   line could be updated using the provided string UNLESS the status line is
 *   currently showing an error.
 * <li>
 *   NumberOfUr92sUpdate - Indicates that the class has counted the number of UR92
 *   devices
 * <li>
 *   DPLX_PC_NAME_UPDATE - Indicates that a LocoNet message has reported the
 *   Duplex Group Name
 * <li>
 *   DPLX_PC_CHANNEL_UPDATE - Indicates that a LocoNet message has reported the
 *   Duplex Group Channel
 * <li>
 *   DPLX_PC_PASSWORD_UPDATE - Indicates that a LocoNet message has reported the
 *   Duplex Group Password
 * <li>
 *   DPLX_PC_ID_UPDATE - Indicates that a LocoNet message has reported the Duplex
 *   Group Id
 * <li>
 *   DPLX_PC_NAME_VALIDITY - Indicates that the validity of GUI field showing the
 *   Duplex Group Name should be changed. NewValue() is true if a valid Duplex
 *   Group Name is available; is false if the Duplex Group Name should be
 *   considered invalid.
 * <li>
 *   DPLX_PC_CHANNEL_VALIDITY - Indicates that the validity of GUI field showing
 *   the Duplex Group Channel should be changed. NewValue() is true if a valid
 *   Duplex Group Channel is available; is false if the Duplex Group Channel
 *   should be considered invalid.
 * <li>
 *   DPLX_PC_PASSWORD_VALIDITY - Indicates that the validity of GUI field showing
 *   the Duplex Group Password should be changed. NewValue() is true if a valid
 *   Duplex Group Password is available; is false if the Duplex Group Password
 *   should be considered invalid.
 * <li>
 *   DPLX_PC_ID_VALIDITY - Indicates that the validity of GUI field showing the
 *   Duplex Group Id should be changed. NewValue() is true if a valid Duplex Group
 *   Id is available; is false if the Duplex Group Id should be considered
 *   invalid.
 * <li>
 *   DPLX_PC_RCD_DPLX_IDENTITY_QUERY - Indicates that a LocoNet message which
 *   queries the Duplex Group identity has been received.
 * <li>
 *   DPLX_PC_RCD_DPLX_IDENTITY_REPORT - Indicates that a LocoNet message which
 *   reports the Duplex Group identity has been received.
 * </ul>
 * This tool works equally well with UR92 and UR92CE devices. The UR92 and
 * UR92CE behave identically with respect to this tool. For the purpose of
 * clarity, only the term UR92 is used herein.
 *
 * @author B. Milhaupt Copyright 2011
 */
// /*public*/ class LnDplxGrpInfoImpl extends javax.swing.JComponent implements jmri.jmrix.loconet.LocoNetListener {

    /*private*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::limitPasswordToNumericCharacters = false;
    /*public*/ LnDplxGrpInfoImpl::LnDplxGrpInfoImpl(LocoNetSystemConnectionMemo* LNCMemo, QObject* parent) : QObject(parent)
    {
        //super();
        thisone = this;

        memo = LNCMemo;

        messagesHandled = 0;

        // connect to the LnTrafficController
        connect(memo->getLnTrafficController());

        numUr92 = 0;        // assume 0 UR92 devices available
        waitingForIplReply = false;

//        swingTmrIplQuery = new javax.swing.Timer(LnDplxGrpInfoImplConstants.IPL_QUERY_DELAY, new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                swingTmrIplQuery.stop();
//                waitingForIplReply = false;
//                int oldvalue = 9999;
//                int newvalue = 0;
//                if (numUr92 > 0) {
//                    newvalue = numUr92;
//                    thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
//                    invalidateDataAndQueryDuplexInfo();
//                } else {
//                    thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
//                    thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ErrorNoUR92Found"); // NOI18N
//                }
//            }
//        });
        swingTmrIplQuery = new SwingTmrIpl02(LnDplxGrpInfoImplConstants::IPL_QUERY_DELAY, new ActionListener(), this);

//        swingTmrDuplexInfoQuery = new javax.swing.Timer(LnDplxGrpInfoImplConstants.DPLX_QUERY_DELAY, new java.awt.event.ActionListener() {
//            @Override
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                swingTmrDuplexInfoQuery.stop();
//                waitingForIplReply = false;
//                if (gotQueryReply == true) {
//                    // do not want to erase any status message other than the "Processing" message.
//                    thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE_IF_NOT_CURRENTLY_ERROR, "", " "); // NOI18N
//                    gotQueryReply = false;
//                } else {
//                    thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ErrorNoQueryResponse"); // NOI18N
//                    numUr92 = 0;
//                    int oldvalue = 9999;
//                    int newvalue = 0;
//                    thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
//                }
//            }
//        });
        swingTmrDuplexInfoQuery = new SwingTmrDuplex02(LnDplxGrpInfoImplConstants::DPLX_QUERY_DELAY, new ActionListener(), this);

        acceptedGroupName = "";
        acceptedGroupChannel = "";
        acceptedGroupPassword = "";
        acceptedGroupId = "";

    }

    /**
     * Report whether Duplex Group Password must only be numeric, or if
     * Password is allowed to include characters 'A', 'B', and/or 'C'.
     *
     * @return true if Password may only include digits.
     */
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::isPasswordLimitedToNumbers() {
        return limitPasswordToNumericCharacters;
    }

    /**
     * Validate a Duplex Group Name.
     * <p>
     * A valid Duplex Group Name is an 8 character string. The calling method
     * should append spaces or truncate to give correct length if necessary.
     *
     * @param sGroupName  string containing group name to be validated
     * @return true if and only if groupName is a valid Duplex Group Name
     */
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::validateGroupName(QString sGroupName) {
        // Digitrax seems to allow use of any 8-bit character.  So only
        // requirement seems to be that the name must be 8 characters long.
        return sGroupName.length() == 8;
    }

    /**
     * Validate a Duplex Group Password.
     * <p>
     * Note that the password must be four digits if only numeric values are
     * allowed, or must be four characters, each of pattern [0-9A-C] if
     * alphanumeric values are allowed. (See private field
     * limitPasswordToNumericCharacters.)
     *
     * @param sGroupPassword  Duplex Group Password to be validated
     * @return true if and only if sGroupPassword is a valid Duplex Group
     *         Password.
     */
    // TODO: There is no way currently to set limitPasswordToNumericCharacters to true
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::validateGroupPassword(QString sGroupPassword) {
        // force the value to uppercase
        if (sGroupPassword.length() == 0) {
            return false;
        }
        // Return whether or not the password matches
//        return (limitPasswordToNumericCharacters && sGroupPassword.matches("^[0-9][0-9][0-9][0-9]$")) // NOI18N
//                || sGroupPassword.matches("^[0-9A-C][0-9A-C][0-9A-C][0-9A-C]$"); // NOI18N
        QRegularExpression re1("^[0-9][0-9][0-9][0-9]$");
        QRegularExpression re2("^[0-9A-C][0-9A-C][0-9A-C][0-9A-C]$");
        return (limitPasswordToNumericCharacters && re1.match(sGroupPassword).hasMatch()) || re2.match(sGroupPassword).hasMatch();
    }

    /**
     * Validate a Duplex Group Channel Number.
     *
     * @param iGroupChannel  Duplex Group Channel number to be validated
     * @return true if and only if iGroupChannel is a valid Duplex Group
     *         Channel.
     */
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::validateGroupChannel(int iGroupChannel) {
        if ((iGroupChannel < LnDplxGrpInfoImplConstants::DPLX_MIN_CH)
                || (iGroupChannel > LnDplxGrpInfoImplConstants::DPLX_MAX_CH)) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * Validate the parameter as a Duplex Group ID number.
     *
     * @param iGroupId  Duplex Group ID number to be validated
     * @return true if and only if iGroupId is a valid Duplex Group ID.
     */
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::validateGroupID(int iGroupId) {

        if ((iGroupId < LnDplxGrpInfoImplConstants::DPLX_MIN_ID)
                || (iGroupId > LnDplxGrpInfoImplConstants::DPLX_MAX_ID)) {
            return false;
        } else {
            return true;
        }
    }

    /**
     * Create a LocoNet packet which queries UR92(s) for Duplex group
     * identification information. The invoking method is responsible for
     * sending the message to LocoNet.
     *
     * @return LocoNetMessage containing IPL query of UR92s
     */
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createUr92GroupIdentityQueryPacket() {
        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);
        int i;
        i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_NAME_TYPE);   // Group Name Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_QUERY);   // Query Operation
        for (; i < (LnConstants::RE_DPLX_OP_LEN - 1); i++) {
            m->setElement(i, 0);   // always 0 for duplex group name write
        }
        return m;
    }

    /**
     * Create a LocoNet packet to set the Duplex group name.
     * <p>
     * Throws an exception if s provides a 0-length group name string. If s is
     * too short, it is padded with spaces at the end of the string.
     *
     * @param sGroupName is the desired group name value as a string
     * @return The LocoNet packet which writes the Group Name to the UR92
     *         device(s)
     * @throws jmri.jmrix.loconet.LocoNetException if sGroupName is not a valid
     *                                             Duplex Group Name
     */
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createSetUr92GroupNamePacket(QString sGroupName) throw (LocoNetException) {
        int gr_msb1 = 0;
        int gr_msb2 = 0;
        int i;

        if (validateGroupName(sGroupName) == false) {
            throw LocoNetException("Invalid Duplex Group Name - must be exactly 8 characters"); // NOI18N
        }

        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);

        // update extended data storage for most-significant bits of each character
        gr_msb1 += (sGroupName.at(0) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB1_BIT : 0;
        gr_msb1 += (sGroupName.at(1) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB2_BIT : 0;
        gr_msb1 += (sGroupName.at(2) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB3_BIT : 0;
        gr_msb1 += (sGroupName.at(3) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB4_BIT : 0;
        gr_msb2 += (sGroupName.at(4) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB1_BIT : 0;
        gr_msb2 += (sGroupName.at(5) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB2_BIT : 0;
        gr_msb2 += (sGroupName.at(6) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB3_BIT : 0;
        gr_msb2 += (sGroupName.at(7) > LnConstants::RE_DPLX_7BITS_MAX) ? LnConstants::RE_DPLX_MSB4_BIT : 0;

        i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_NAME_TYPE);   // Group Name Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_WRITE);   // Write Operation
        m->setElement(i++, gr_msb1);   // MSB1
        m->setElement(i++, sGroupName.at(0).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   // 7 LSBs of leftmost character
        m->setElement(i++, sGroupName.at(1).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   // 7 LSBs of next character
        m->setElement(i++, sGroupName.at(2).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   // 7 LSBs of next character
        m->setElement(i++, sGroupName.at(3).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   //  7 LSBs of next character
        m->setElement(i++, gr_msb2);   // MSB2
        m->setElement(i++, sGroupName.at(4).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   //  7 LSBs of next character
        m->setElement(i++, sGroupName.at(5).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   //  7 LSBs of next character
        m->setElement(i++, sGroupName.at(6).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   //  7 LSBs of next character
        m->setElement(i++, sGroupName.at(7).toLatin1()
                & LnConstants::RE_DPLX_MAX_NOT_OPC);   // 7 LSBs of rightmost character
        for (; i < (LnConstants::RE_DPLX_OP_LEN - 1); i++) {
            m->setElement(i, 0);   // always 0 for duplex group name write
        }
        // Note: LocoNet send process will compute and add checksum byte in correct location

        return m;
    }

    /**
     * Create a LocoNet packet to set the Duplex group channel number.
     * <p>
     * If s provides a 0-length group name, a bogus LocoNet message is returned.
     * If s does not define an int is too short, it is padded with spaces at
     * the end of the string.
     *
     * @param iChannelNumber The desired group channel number value as an
     *                       int
     * @return The packet which writes the Group Channel Number to the UR92
     *         device(s)
     * @throws jmri.jmrix.loconet.LocoNetException if sGroupName is not a valid
     *                                             Duplex Group Name
     */
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createSetUr92GroupChannelPacket(int iChannelNumber) throw (LocoNetException) {
        int i;

        if (validateGroupChannel(iChannelNumber) == false) {
            throw  LocoNetException("Invalid Duplex Group Channel - must be between 11 and 26, inclusive"); // NOI18N
        }

        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);

        i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_CHAN_TYPE);   // Group Channel Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_WRITE);   // Write Operation
        m->setElement(i++, 0);   // always 0 for duplex group channel write
        m->setElement(i++, iChannelNumber);  // Group Channel Number
        for (; i < (LnConstants::RE_DPLX_OP_LEN - 1); i++) {
            m->setElement(i, 0);   // always 0 for duplex group channel write
        }
        // Note: LocoNet send process will compute and add checksum byte in correct location

        return m;
    }

    /**
     * Create a LocoNet packet to set the Duplex group password.
     * <p>
     * If s provides anything other than a 4 character length group password
     * which uses only valid group ID characters (0-9, A-C), a bogus
     * LocoNet message is returned.
     *
     * @param sGroupPassword The desired group password as a string
     * @return The packet which writes the Group Password to the UR92 device(s)
     * @throws jmri.jmrix.loconet.LocoNetException in case of invalid sGrooupPassword
     */
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createSetUr92GroupPasswordPacket(QString sGroupPassword) throw (LocoNetException) {

        int gr_p1 = sGroupPassword.toUpper().at(0).toLatin1();
        int gr_p2 = sGroupPassword.toUpper().at(1).toLatin1();
        int gr_p3 = sGroupPassword.toUpper().at(2).toLatin1();
        int gr_p4 = sGroupPassword.toUpper().at(3).toLatin1();
        int i;

        if (validateGroupPassword(sGroupPassword) == false) {
            if (isPasswordLimitedToNumbers() == true) {
                throw LocoNetException("Invalid Duplex Group Password - must be a 4 digit number between 0000 and 9999, inclusive"); // NOI18N
            } else {
                throw LocoNetException("Invalid Duplex Group Password - must be a 4 character value using only digits, 'A', 'B', and/or 'C'"); // NOI18N
            }
        }

        // re-code individual characters when an alphabetic character is used
        gr_p1 -= (gr_p1 > '9') ? ('A' - '9' - 1) : 0;
        gr_p2 -= (gr_p2 > '9') ? ('A' - '9' - 1) : 0;
        gr_p3 -= (gr_p3 > '9') ? ('A' - '9' - 1) : 0;
        gr_p4 -= (gr_p4 > '9') ? ('A' - '9' - 1) : 0;

        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);

        i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_PW_TYPE);   // Group password Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_WRITE);   // Write Operation
        m->setElement(i++, 0);   // always 0 for duplex group password write
        m->setElement(i++, gr_p1);   // Group password leftmost value + 0x30
        m->setElement(i++, gr_p2);   // Group password next value + 0x30
        m->setElement(i++, gr_p3);   // Group password next value + 0x30
        m->setElement(i++, gr_p4);   // Group password rightmost value + 0x30
        for (; i < (LnConstants::RE_DPLX_OP_LEN - 1); i++) {
            m->setElement(i, 0);   // always 0 for duplex group password write
        }
        // Note: LocoNet send process will compute and add checksum byte in correct location

        return m;
    }

    /**
     * Create a LocoNet packet to set the Duplex group ID number.
     * <p>
     * If s provides anything other than a numeric value between 0 and 127, a
     * LocoNetException is thrown.
     *
     * @param s The desired group ID number as a string
     * @return The packet which writes the Group ID Number to the UR92 device(s)
     * @throws jmri.jmrix.loconet.LocoNetException when an invalid id is provided
     */
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createSetUr92GroupIDPacket(QString s) throw (LocoNetException) {
        //int gr_id = int.parseInt(s, 10);
        int gr_id = s.toInt();

        if ((gr_id >= LnDplxGrpInfoImplConstants::DPLX_MIN_ID) && (gr_id <= LnDplxGrpInfoImplConstants::DPLX_MAX_ID)) {
            // format packet
            int i = 0;
            LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);

            m->setElement(i++, LnConstants::OPC_PEER_XFER);
            m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
            m->setElement(i++, LnConstants::RE_DPLX_GP_ID_TYPE);   // Group ID Operation
            m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_WRITE);   // Write Operation
            m->setElement(i++, 0);   // always 0 for duplex group ID write
            m->setElement(i++, gr_id);  // Group ID Number
            for (; i < (LnConstants::RE_DPLX_OP_LEN - 1); i++) {
                m->setElement(i, 0);   // always 0 for duplex group ID write
            }
            // Note: LocoNet send process will compute and add checksum byte in correct location
            return m;
        } else {
            /* in case param s encodes something other than a valid Duplex
             * ID number, throw an exception.
             */
            throw LocoNetException("Illegal Duplex Group ID number"); // NOI18N
        }
    }

    /**
     * Checks message m to determine if it contains a Duplex Group Identity
     * message, including queries, reports, and writes, for Name, Channel,
     * Password, and ID.
     *
     * @param m  LocoNet message to check
     * @return true if message is query, report, or write of Duplex Group Name,
     *         Channel, Password or ID
     */
    /*public*/ /*static*/ /*final*/ bool LnDplxGrpInfoImpl::isDuplexGroupMessage(LocoNetMessage* m) {
        if ((m->getOpCode() == LnConstants::OPC_PEER_XFER)
                && (m->getElement(1) == LnConstants::RE_DPLX_OP_LEN)) {
            // Message is a peer-to-peer message of appropriate length for
            // Duplex Group operations.  Check the individual message type
            int byte2 = m->getElement(2);
            if ((byte2 == LnConstants::RE_DPLX_GP_CHAN_TYPE)
                    || (byte2 == LnConstants::RE_DPLX_GP_NAME_TYPE)
                    || (byte2 == LnConstants::RE_DPLX_GP_ID_TYPE)
                    || (byte2 == LnConstants::RE_DPLX_GP_PW_TYPE)) {
                // To be sure the message is a duplex operation, check the
                // operation type.
                int byte3 = m->getElement(3);
                if ((byte3 == LnConstants::RE_DPLX_OP_TYPE_QUERY)
                        || (byte3 == LnConstants::RE_DPLX_OP_TYPE_REPORT)
                        || (byte3 == LnConstants::RE_DPLX_OP_TYPE_WRITE)) {
                    return true;
                }
            }
        }
        return false;
    }

    /**
     * Classifies a LocoNet Message to see if it is a Duplex Group Identity
     * message
     *
     * @param m a LocoNetMessage
     * @return DuplexGroupMessageType, encoded as one of the following
     *         NOT_A_DUPLEX_GROUP_MESSAGE DUPLEX_GROUP_CHANNEL_QUERY_MESSAGE
     *         DUPLEX_GROUP_CHANNEL_REPORT_MESSAGE
     *         DUPLEX_GROUP_CHANNEL_WRITE_MESSAGE
     *         DUPLEX_GROUP_NAME_QUERY_MESSAGE
     *         DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE
     *         DUPLEX_GROUP_NAME_WRITE_MESSAGE
     *         DUPLEX_GROUP_PASSWORD_QUERY_MESSAGE
     *         DUPLEX_GROUP_PASSWORD_REPORT_MESSAGE
     *         DUPLEX_GROUP_PASSWORD_WRITE_MESSAGE DUPLEX_GROUP_ID_QUERY_MESSAGE
     *         DUPLEX_GROUP_ID_REPORT_MESSAGE DUPLEX_GROUP_ID_WRITE_MESSAGE
     */
    /*public*/ /*static*/ /*final*/ DuplexGroupMessageType LnDplxGrpInfoImpl::getDuplexGroupIdentityMessageType(LocoNetMessage* m) {
        if ((m->getOpCode() == LnConstants::OPC_PEER_XFER)
                && (m->getElement(1) == LnConstants::RE_DPLX_OP_LEN)) {
            // Message is a peer-to-peer message of appropriate length for
            // Duplex Group operations.  Check the individual message type
            int byte3 = m->getElement(3);
            switch (m->getElement(2)) {
                case LnConstants::RE_DPLX_GP_CHAN_TYPE:
                    return (byte3 == LnConstants::RE_DPLX_OP_TYPE_QUERY) ? DuplexGroupMessageType::DUPLEX_GROUP_CHANNEL_QUERY_MESSAGE
                            : (byte3 == LnConstants::RE_DPLX_OP_TYPE_REPORT) ? DuplexGroupMessageType::DUPLEX_GROUP_CHANNEL_REPORT_MESSAGE
                                    : (byte3 == LnConstants::RE_DPLX_OP_TYPE_WRITE) ? DuplexGroupMessageType::DUPLEX_GROUP_CHANNEL_WRITE_MESSAGE
                                            : DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
                case LnConstants::RE_DPLX_GP_NAME_TYPE:
                    return (byte3 == LnConstants::RE_DPLX_OP_TYPE_QUERY) ? DuplexGroupMessageType::DUPLEX_GROUP_NAME_QUERY_MESSAGE
                            : (byte3 == LnConstants::RE_DPLX_OP_TYPE_REPORT) ? DuplexGroupMessageType::DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE
                                    : (byte3 == LnConstants::RE_DPLX_OP_TYPE_WRITE) ? DuplexGroupMessageType::DUPLEX_GROUP_NAME_WRITE_MESSAGE
                                            : DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
                case LnConstants::RE_DPLX_GP_PW_TYPE:
                    return (byte3 == LnConstants::RE_DPLX_OP_TYPE_QUERY) ? DuplexGroupMessageType::DUPLEX_GROUP_PASSWORD_QUERY_MESSAGE
                            : (byte3 == LnConstants::RE_DPLX_OP_TYPE_REPORT) ? DuplexGroupMessageType::DUPLEX_GROUP_PASSWORD_REPORT_MESSAGE
                                    : (byte3 == LnConstants::RE_DPLX_OP_TYPE_WRITE) ? DuplexGroupMessageType::DUPLEX_GROUP_PASSWORD_WRITE_MESSAGE
                                            : DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
                case LnConstants::RE_DPLX_GP_ID_TYPE:
                    return (byte3 == LnConstants::RE_DPLX_OP_TYPE_QUERY) ? DuplexGroupMessageType::DUPLEX_GROUP_ID_QUERY_MESSAGE
                            : (byte3 == LnConstants::RE_DPLX_OP_TYPE_REPORT) ? DuplexGroupMessageType::DUPLEX_GROUP_ID_REPORT_MESSAGE
                                    : (byte3 == LnConstants::RE_DPLX_OP_TYPE_WRITE) ? DuplexGroupMessageType::DUPLEX_GROUP_ID_WRITE_MESSAGE
                                            : DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
                default:
                    return DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
            }
        }
        return DuplexGroupMessageType::NOT_A_DUPLEX_GROUP_MESSAGE;
    }

    /**
     * Checks that m is a message with a Duplex Group Name encoded inside, then
     * extracts the Duplex Group Name. Note that the returned string is always 8
     * characters long.
     * <p>
     * If m does not contain a Duplex Group Name, returns null.
     *
     * @param m  LocoNet message from which a Duplex Group Name is to be extracted.
     * @return String containing Duplex Group Name as extracted from m
     */
    /*public*/ /*static*/ QString LnDplxGrpInfoImpl::extractDuplexGroupName(LocoNetMessage* m) {
        switch (getDuplexGroupIdentityMessageType(m)) {
            case DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE:
            case DUPLEX_GROUP_NAME_WRITE_MESSAGE:
                return extractGroupName(m);
            default:
                return QString();
        }
    }

    /**
     * Assumes that m is a message with a Duplex Group Name encoded inside.
     * Extracts the Duplex Group Name and returns it as an 8 character String.
     *
     * @return String containing Duplex Group Name as extracted from m
     */
    /*private*/ /*static*/ QString LnDplxGrpInfoImpl::extractGroupName(LocoNetMessage* m) {
        QString gr_name;// = new StringBuilder();
        int gr_msb1;
        int gr_msb2;

        gr_msb1 = m->getElement(4) & LnConstants::RE_DPLX_MAX_NOT_OPC;
        gr_msb2 = m->getElement(9) & LnConstants::RE_DPLX_MAX_NOT_OPC;
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(5) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb1 & LnConstants::RE_DPLX_MSB1_BIT) << LnConstants::RE_DPLX_BUMP_MSB1_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(6) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb1 & LnConstants::RE_DPLX_MSB2_BIT) << LnConstants::RE_DPLX_BUMP_MSB2_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(7) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb1 & LnConstants::RE_DPLX_MSB3_BIT) << LnConstants::RE_DPLX_BUMP_MSB3_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(8) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb1 & LnConstants::RE_DPLX_MSB4_BIT) << LnConstants::RE_DPLX_BUMP_MSB4_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(10) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb2 & LnConstants::RE_DPLX_MSB1_BIT) << LnConstants::RE_DPLX_BUMP_MSB1_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(11) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb2 & LnConstants::RE_DPLX_MSB2_BIT) << LnConstants::RE_DPLX_BUMP_MSB2_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(12) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb2 & LnConstants::RE_DPLX_MSB3_BIT) << LnConstants::RE_DPLX_BUMP_MSB3_BIT))));
        gr_name.append(/*Character.toString((char)*/( ((m->getElement(13) & LnConstants::RE_DPLX_MAX_NOT_OPC)
                + ((gr_msb2 & LnConstants::RE_DPLX_MSB4_BIT) << LnConstants::RE_DPLX_BUMP_MSB4_BIT))));
        return gr_name/*.toString()*/;
    }

    /**
     * Checks that m is a message with a Duplex Group Channel encoded inside,
     * then extracts and returns the Duplex Group Channel.
     * <p>
     * Returns -1 if the m does not contain a Duplex Group Channel.
     *
     * @param m  LocoNet message from which a Duplex Group Channel number will
     *          be extracted
     * @return int containing Duplex Group Name as extracted from m
     */
    /*public*/ /*static*/ int LnDplxGrpInfoImpl::extractDuplexGroupChannel(LocoNetMessage* m) {
        switch (getDuplexGroupIdentityMessageType(m)) {
            case DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE:
                return m->getElement(17)
                        + (((m->getElement(14) & 0x4) == 0x4) ? 128 : 0);
            case DUPLEX_GROUP_CHANNEL_REPORT_MESSAGE:
            case DUPLEX_GROUP_CHANNEL_WRITE_MESSAGE:
                return m->getElement(5)
                        + (((m->getElement(4) & 0x1) == 0x1) ? 128 : 0);
            default:
                return -1;
        }
    }

    /**
     * Checks that m is a message with a Duplex Group ID encoded inside, then
     * extracts and returns the Duplex Group ID.
     * <p>
     * Returns -1 if the m does not contain a Duplex Group ID.
     *
     * @param m  LocoNet message from which a Duplex Group ID will be extracted
     * @return int containing Duplex Group Name as extracted from m
     */
    /*public*/ /*static*/ int LnDplxGrpInfoImpl::extractDuplexGroupID(LocoNetMessage* m) {
        switch (getDuplexGroupIdentityMessageType(m)) {
            case DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE:
                return m->getElement(18)
                        + (((m->getElement(14) & 0x8) == 0x8) ? 128 : 0);
            case DUPLEX_GROUP_ID_REPORT_MESSAGE:
            case DUPLEX_GROUP_ID_WRITE_MESSAGE:
                return m->getElement(5)
                        + (((m->getElement(4) & 0x1) == 0x1) ? 128 : 0);
            default:
                return -1;
        }
    }

    /**
     * Checks that m is a message with a Duplex Group Password encoded inside,
     * then extracts and returns the Duplex Group Password.
     * <p>
     * Returns null if the m does not contain a Duplex Group Password.
     *
     * @param m  LocoNet message to be checked for a duplex group password message
     * @return String containing the Duplex Group Password as extracted from m
     */
    /*public*/ /*static*/ QString LnDplxGrpInfoImpl::extractDuplexGroupPassword(LocoNetMessage* m) {
        switch (getDuplexGroupIdentityMessageType(m)) {
            case DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE:
                return extractDuplexGroupPasswordSimplified(
                        (m->getElement(15) & 0x70) >> 4,
                        (m->getElement(15) & 0x0f),
                        (m->getElement(16) & 0x70) >> 4,
                        (m->getElement(16) & 0x0f),
                        (((m->getElement(14) & 0x1) == 0x1) ? true : false),
                        false,
                        (((m->getElement(14) & 0x2) == 0x2) ? true : false),
                        false);
            case DUPLEX_GROUP_PASSWORD_REPORT_MESSAGE:
            case DUPLEX_GROUP_PASSWORD_WRITE_MESSAGE:
                return extractDuplexGroupPasswordSimplified(
                        (m->getElement(5) & 0x0f),
                        (m->getElement(6) & 0x0f),
                        (m->getElement(7) & 0x0f),
                        (m->getElement(8) & 0x0f),
                        false,
                        false,
                        false,
                        false
                );
            default:
                return QString();
        }
    }

    /*private*/ /*static*/ QString LnDplxGrpInfoImpl::extractDuplexGroupPasswordSimplified(int byte1, int byte2, int byte3, int byte4,
            bool x1, bool x2, bool x3, bool x4) {
        int b1;
        int b2;
        int b3;
        int b4;
        char gr_p1;
        char gr_p2;
        char gr_p3;
        char gr_p4;

        b1 = byte1 + (x1 ? 8 : 0);
        b2 = byte2 + (x2 ? 8 : 0);
        b3 = byte3 + (x3 ? 8 : 0);
        b4 = byte4 + (x4 ? 8 : 0);

        // extract reported password characters and convert to displayable character
        gr_p1 = (char) ('0' + b1);
        gr_p1 += (gr_p1 > '9') ? ('A' - '9' - 1) : 0;

        gr_p2 = (char) ('0' + b2);
        gr_p2 += (gr_p2 > '9') ? ('A' - '9' - 1) : 0;

        gr_p3 = (char) ('0' + b3);
        gr_p3 += (gr_p3 > '9') ? ('A' - '9' - 1) : 0;

        gr_p4 = (char) ('0' + b4);
        gr_p4 += (gr_p4 > '9') ? ('A' - '9' - 1) : 0;

        return "" + gr_p1 + gr_p2 + gr_p3 + gr_p4;

    }

    /**
     * Process all incoming LocoNet messages to look for Duplex Group
     * information operations. Only pays attention to LocoNet report of Duplex
     * Group Name/password/channel/groupID, and ignores all other LocoNet
     * messages.
     * <p>
     * If tool has sent a query for Duplex group information and has not yet
     * received a Duplex group report, the method updates the GUI with the
     * received information.
     * <p>
     * If the tool is not currently waiting for a response to a query, then the
     * method compares the received information against the information
     * currently displayed in the GUI. If the received information does not
     * match, a message is displayed on the status line in the GUI, else nothing
     * is displayed in the GUI status line.
     */
    //@Override
    /*public*/ void LnDplxGrpInfoImpl::message(LocoNetMessage* m) {
        messagesHandled++;

        if (handleMessageIplResult(m)) {
            return;
        }

        if (handleMessageDuplexInfoQuery(m)) {
            gotQueryReply = true;
            thisone->pcs->firePropertyChange(DPLX_PC_RCD_DPLX_IDENTITY_QUERY, false, true);
            return;
        }

        if (handleMessageDuplexInfoReport(m)) {
            gotQueryReply = true;
            thisone->pcs->firePropertyChange(DPLX_PC_RCD_DPLX_IDENTITY_REPORT, false, true);
            return;
        }

        return;
    }

    /**
     *
     * @return String containing reported Duplex Group Name
     */
    /*public*/ QString LnDplxGrpInfoImpl::getFetchedDuplexGroupName() {
        return acceptedGroupName;
    }

    /**
     *
     * @return String containing reported Duplex Group Name
     */
    /*public*/ QString LnDplxGrpInfoImpl::getFetchedDuplexGroupChannel() {
        return acceptedGroupChannel;
    }

    /**
     *
     * @return String containing reported Duplex Group Name
     */
    /*public*/ QString LnDplxGrpInfoImpl::getFetchedDuplexGroupPassword() {
        return acceptedGroupPassword;
    }

    /**
     *
     * @return String containing reported Duplex Group Name
     */
    /*public*/ QString LnDplxGrpInfoImpl::getFetchedDuplexGroupId() {
        return acceptedGroupId;
    }

    /**
     * Interprets a received LocoNet message. If message is an IPL report of
     * attached IPL-capable equipment, check to see if it reports a UR92 device
     * as attached. If so, increment count of UR92 devices. Else ignore.
     *
     * @return true if message is an IPL device report indicating a UR92
     *         present, else return false.
     */
//    @edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "DLS_DEAD_LOCAL_STORE",
//                justification = "False positive on the implied local variable in numUr92++")
    /*private*/ bool LnDplxGrpInfoImpl::handleMessageIplResult(LocoNetMessage* m) {
        if (LnIPLImplementation::isIplUr92IdentityReportMessage(m)) {
            numUr92++;
            thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, "", " ");
            waitingForIplReply = false;

            return true;
        } else {
            return false;
        }
    }

    /*private*/ bool LnDplxGrpInfoImpl::handleMessageDuplexInfoQuery(LocoNetMessage* m) {
        return (getDuplexGroupIdentityMessageType(m) == DuplexGroupMessageType::DUPLEX_GROUP_NAME_QUERY_MESSAGE);
    }

    /**
     * Interprets a received LocoNet message. If message is a report of Duplex
     * Group Identity information, extract it to local variables. Else ignore.
     *
     * @return true if message is a Duplex Group Identity Report, else return
     *         false.
     */
    /*private*/ bool LnDplxGrpInfoImpl::handleMessageDuplexInfoReport(LocoNetMessage* m) {

        QString gr_name = "";
        QString gr_password = "";
        int gr_ch;
        int gr_id;
        int i;
        if (getDuplexGroupIdentityMessageType(m) == DuplexGroupMessageType::DUPLEX_GROUP_NAME_ETC_REPORT_MESSAGE) {
            gr_name = extractDuplexGroupName(m);
            // remove trailing spaces from name
            i = (gr_name.length() - 1);
            while ((gr_name.at(i) == ' ') && (i > 0)) {
                gr_name = gr_name.mid(0, i);
                i--;
            }
            gr_password = extractDuplexGroupPassword(m);
            gr_ch = extractDuplexGroupChannel(m);
            gr_id = extractDuplexGroupID(m);

            if (awaitingGroupReadReport) {
                awaitingGroupReadReport = false;
                acceptedGroupName = gr_name;
                acceptedGroupChannel = QString::number(gr_ch, LnDplxGrpInfoImplConstants::GENERAL_DECIMAL_RADIX);
                acceptedGroupPassword = gr_password;
                acceptedGroupId = QString::number(gr_id, LnDplxGrpInfoImplConstants::GENERAL_DECIMAL_RADIX);

                thisone->pcs->firePropertyChange(DPLX_PC_NAME_UPDATE, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_CHANNEL_UPDATE, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_PASSWORD_UPDATE, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_ID_UPDATE, false, true);

                thisone->pcs->firePropertyChange(DPLX_PC_NAME_VALIDITY, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_CHANNEL_VALIDITY, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_PASSWORD_VALIDITY, false, true);
                thisone->pcs->firePropertyChange(DPLX_PC_ID_VALIDITY, false, true);

                thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, "", " ");
            } else {
                // if not expecting a group read, compare new read data
                // versus first returned data
                QString c = "" + QString::number(gr_ch, LnDplxGrpInfoImplConstants::GENERAL_DECIMAL_RADIX);
                QString p = "" + gr_password;
                QString d = "" + QString::number(gr_id, LnDplxGrpInfoImplConstants::GENERAL_DECIMAL_RADIX);

                if ((acceptedGroupName !=(gr_name))
                        || (acceptedGroupChannel !=(c))
                        || (acceptedGroupPassword!=(p))
                        || (acceptedGroupId!=(d))) {
                    // show that a Duplex Group Identification information hapened.
                    // Show message as as red text on status line
                    thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ErrorGroupMismatch");
                }
            }
            return true;
        }
        return false;
    }

    /**
     * Sends a LocoNet Message to query the Duplex Group Identity. Starts a
     * timer to monitor completion.
     *
     */
    /*public*/ void LnDplxGrpInfoImpl::queryDuplexGroupIdentity() {

        awaitingGroupReadReport = true;
        gotQueryReply = false;

        memo->getLnTrafficController()->sendLocoNetMessage(createUr92GroupIdentityQueryPacket());
        invalidateDuplexGroupIdentityInfo();

        if (swingTmrDuplexInfoQuery != nullptr) {
            if (swingTmrDuplexInfoQuery->isRunning()) {
                swingTmrDuplexInfoQuery->reStart();
            } else {
                swingTmrDuplexInfoQuery->start();
            }
        }
    }

    /**
     * Creates and sends a LocoNet message which sets the Duplex Group Name.
     *
     * @param dgn  String containing the new Duplex Group Name
     * @throws jmri.jmrix.loconet.LocoNetException if dgn is not a valid Duplex
     *                                             Group Name.
     */
    /*public*/ void LnDplxGrpInfoImpl::setDuplexGroupName(QString dgn) throw (LocoNetException) {
        memo->getLnTrafficController()->sendLocoNetMessage(
                createSetUr92GroupNamePacket(
                        dgn));
    }

    /**
     * Creates and sends a LocoNet message which sets the Duplex Group Channel.
     *
     * @param dgc  int containing the new Duplex Group Channel
     * @throws jmri.jmrix.loconet.LocoNetException if dgc is not a valid Duplex
     *                                             Group Channel number.
     */
    /*public*/ void LnDplxGrpInfoImpl::setDuplexGroupChannel(int dgc) throw (LocoNetException) {
        memo->getLnTrafficController()->sendLocoNetMessage(createSetUr92GroupChannelPacket(
                dgc));
    }

    /**
     * Creates and sends a LocoNet message which sets the Duplex Group Password.
     *
     * @param dgp  String containing the new Duplex Group Password
     * @throws jmri.jmrix.loconet.LocoNetException if dgp is not a valid Duplex
     *                                             Group Password.
     */
    /*public*/ void LnDplxGrpInfoImpl::setDuplexGroupPassword(QString dgp) throw (LocoNetException) {
        memo->getLnTrafficController()->sendLocoNetMessage(createSetUr92GroupPasswordPacket(
                dgp));
    }

    /**
     * Creates and sends a LocoNet message which sets the Duplex Group Id.
     *
     * @param dgi  String containing the new Duplex Group Id
     * @throws jmri.jmrix.loconet.LocoNetException if dgi is not a valid Duplex
     *                                             Group Id.
     */
    /*public*/ void LnDplxGrpInfoImpl::setDuplexGroupId(QString dgi) throw (LocoNetException) {
        memo->getLnTrafficController()->sendLocoNetMessage(createSetUr92GroupIDPacket(
                dgi));
    }

    /*private*/ void LnDplxGrpInfoImpl::invalidateDataAndQueryDuplexInfo() {
        if (numUr92 > 0) {
            thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ProcessingReadingInfo");
            thisone->queryDuplexGroupIdentity();
        }
    }

    /*private*/ void LnDplxGrpInfoImpl::sendUr92IplQuery() {
        waitingForIplReply = true;
        memo->getLnTrafficController()->sendLocoNetMessage(
                LnIPLImplementation::createIplSpecificHostQueryPacket(
                        LnConstants::RE_IPL_DIGITRAX_HOST_ALL,
                        LnConstants::RE_IPL_DIGITRAX_HOST_UR92));
        int oldvalue = 9999;
        int newvalue = 0;
        thisone->pcs->firePropertyChange("NumberOfUr92sUpdate", oldvalue, newvalue); // NOI18N
        invalidateDuplexGroupIdentityInfo();
        if (swingTmrIplQuery != nullptr) {
            if (swingTmrIplQuery->isRunning()) {
                swingTmrIplQuery->reStart();
            } else {
                swingTmrIplQuery->start();
            }
        }
    }

    /*private*/ void LnDplxGrpInfoImpl::invalidateDuplexGroupIdentityInfo() {
        acceptedGroupName = "";
        acceptedGroupChannel = "";
        acceptedGroupPassword = "";
        acceptedGroupId = "";
        thisone->pcs->firePropertyChange(DPLX_PC_NAME_UPDATE, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_CHANNEL_UPDATE, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_PASSWORD_UPDATE, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_ID_UPDATE, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_NAME_VALIDITY, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_CHANNEL_VALIDITY, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_PASSWORD_VALIDITY, true, false);
        thisone->pcs->firePropertyChange(DPLX_PC_ID_VALIDITY, true, false);
    }

    /**
     * Begins a sequence which includes counting available UR92s and, if at
     * least one UR92 is present, reads the Duplex Group Identity Info.
     */
    /*public*/ void LnDplxGrpInfoImpl::countUr92sAndQueryDuplexIdentityInfo() {
        if (thisone == nullptr) {
            log->error("called countUR92sAndQueryDuplexInfo before thisone is initialized");
            return;
        }
        if ((waitingForIplReply == true)
                || (swingTmrIplQuery == nullptr)
                || (swingTmrDuplexInfoQuery == nullptr)
                || (swingTmrIplQuery->isRunning())
                || (swingTmrDuplexInfoQuery->isRunning())) {
            thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ErrorReadingTooSoon");
            return;
        }
        invalidateDuplexGroupIdentityInfo();
        numUr92 = 0;

        // configure timer for delay between UR92 query request and begin of duplex info query
        sendUr92IplQuery();
        thisone->pcs->firePropertyChange(DPLX_PC_STAT_LN_UPDATE, " ", "ProcessingInitialStatusMessage");
        swingTmrIplQuery->stop();
        swingTmrIplQuery->setInitialDelay(LnDplxGrpInfoImplConstants::IPL_QUERY_DELAY);
        swingTmrIplQuery->setRepeats(false);
        swingTmrIplQuery->reStart();
    }

    // the following code may be used to create a LocoNet message that follows the
    // form of the message sent by a UR92 in response to a Duplex Group Name query
    // LocoNet message.
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createUr92GroupNameReportPacket(
            QString dupName,
            QString dupPass,
            int dupChan,
            int dupId) {
        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);
        int i = 0;
        dupName += "        ";
        dupName = dupName.mid(0, 8); // get first 8 chars of space-padded name
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_NAME_TYPE);   // Group Name Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_REPORT);   // Report Operation

        m->setElement(i++,
                (((dupName.at(0).toLatin1() & 0x80) == 0x80) ? 1 : 0)
                + (((dupName.at(1).toLatin1() & 0x80) == 0x80) ? 2 : 0)
                + (((dupName.at(2).toLatin1() & 0x80) == 0x80) ? 4 : 0)
                + (((dupName.at(3).toLatin1() & 0x80) == 0x80) ? 8 : 0));
        m->setElement(i++, dupName.at(0).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(1).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(2).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(3).toLatin1() & 0x7f);

        m->setElement(i++,
                (((dupName.at(4).toLatin1() & 0x80) == 0x80) ? 1 : 0)
                + (((dupName.at(5).toLatin1() & 0x80) == 0x80) ? 2 : 0)
                + (((dupName.at(6).toLatin1() & 0x80) == 0x80) ? 4 : 0)
                + (((dupName.at(7).toLatin1() & 0x80) == 0x80) ? 8 : 0));
        m->setElement(i++, dupName.at(4).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(5).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(6).toLatin1() & 0x7f);
        m->setElement(i++, dupName.at(7).toLatin1() & 0x7f);
        dupPass += "0000"; // NOI18N
        dupPass = dupPass.mid(0, 4);
        int gr_p1 = dupPass.at(0).toLatin1();
        int gr_p2 = dupPass.at(1).toLatin1();
        int gr_p3 = dupPass.at(2).toLatin1();
        int gr_p4 = dupPass.at(3).toLatin1();

        // re-code individual characters when an alphabetic character is used
        gr_p1 -= (gr_p1 > '9') ? ('A' - '9' - 1) : 0;
        gr_p2 -= (gr_p2 > '9') ? ('A' - '9' - 1) : 0;
        gr_p3 -= (gr_p3 > '9') ? ('A' - '9' - 1) : 0;
        gr_p4 -= (gr_p4 > '9') ? ('A' - '9' - 1) : 0;
        int passLo = ((gr_p1 & 0x0f) << 4) + (gr_p2 & 0x0f);
        int passHi = ((gr_p3 & 0x0f) << 4) + (gr_p4 & 0x0f);
        m->setElement(i++,
                (((passLo & 0x80) == 0x80) ? 1 : 0)
                + (((passHi & 0x80) == 0x80) ? 2 : 0)
                + (((dupChan & 0x80) == 0x80) ? 4 : 0)
                + (((dupId & 0x80) == 0x80) ? 8 : 0));
        m->setElement(i++, passLo & 0x7f);
        m->setElement(i++, passHi & 0x7f);
        m->setElement(i++, dupChan & 0x7f);
        m->setElement(i++, dupId & 0x7f);

        return m;
    }

    // the following code may be used to create a LocoNet message that follows the
    // form of the message sent by a UR92 in response to a Duplex Group Channel query
    // LocoNet message.
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createUr92GroupChannelReportPacket(
            int dupChan) {
        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);
        int i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_CHAN_TYPE);   // Group Channel Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_REPORT);   // Report Operation

        m->setElement(i++, (dupChan & 0x80) >> 7);
        m->setElement(i++, dupChan & 0x7f);

        for (; i < LnConstants::RE_DPLX_OP_LEN; i++) {
            m->setElement(i, 0);
        }

        return m;
    }

    // the following code may be used to create a LocoNet message that follows the
    // form of the message sent by a UR92 in response to a Duplex Group Password query
    // LocoNet message.
    // No attempt is made to check the validity of the dupPass argument.
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createUr92GroupPasswordReportPacket(
            QString dupPass) {
        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);
        int i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_PW_TYPE);   // Group Password Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_REPORT);   // Report Operation

        dupPass += "0000"; // NOI18N

        m->setElement(i++,
                ((dupPass.at(0).toLatin1() & 0x80) == 0x80 ? 8 : 0)
                + ((dupPass.at(1).toLatin1() & 0x80) == 0x80 ? 4 : 0)
                + ((dupPass.at(2).toLatin1() & 0x80) == 0x80 ? 2 : 0)
                + ((dupPass.at(3).toLatin1() & 0x80) == 0x80 ? 1 : 0)
        );
        m->setElement(i++, dupPass.at(0).toLatin1() & 0x7f);
        m->setElement(i++, dupPass.at(1).toLatin1() & 0x7f);
        m->setElement(i++, dupPass.at(2).toLatin1() & 0x7f);
        m->setElement(i++, dupPass.at(3).toLatin1() & 0x7f);

        for (; i < LnConstants::RE_DPLX_OP_LEN; i++) {
            m->setElement(i, 0);
        }

        return m;
    }

    // the following code may be used to create a LocoNet message that follows the
    // form of the message sent by a UR92 in response to a Duplex Group Id query
    // LocoNet message.
    /*public*/ /*static*/ /*final*/ LocoNetMessage* LnDplxGrpInfoImpl::createUr92GroupIdReportPacket(
            int dupId) {
        // format packet
        LocoNetMessage* m = new LocoNetMessage(LnConstants::RE_DPLX_OP_LEN);
        int i = 0;
        m->setElement(i++, LnConstants::OPC_PEER_XFER);
        m->setElement(i++, LnConstants::RE_DPLX_OP_LEN);   // 20-byte message
        m->setElement(i++, LnConstants::RE_DPLX_GP_ID_TYPE);   // Group Id Operation
        m->setElement(i++, LnConstants::RE_DPLX_OP_TYPE_REPORT);   // Report Operation

        m->setElement(i++, (dupId & 0x80) >> 7);
        m->setElement(i++, dupId & 0x7f);

        for (; i < LnConstants::RE_DPLX_OP_LEN; i++) {
            m->setElement(i, 0);
        }

        return m;
    }

    /**
     * Reports the number of UR92 devices which responded to the most-recent
     * LocoNet IPL query of UR92 devices.
     * <p>
     * Note that code should ignore the value returned by this method
     * if isWaitingForUr92DeviceReports() is true;
     *
     * @return the number of UR92 devices which reported in response to the
     *      LocoNet IPL device query which is sent by this class.
     */
    /*public*/ int LnDplxGrpInfoImpl::getNumUr92s() {
        return numUr92;
    }

    /**
     * Reports whether this class is currently waiting for the first UR92 LocoNet
     * IPL Device Report messages in response to a LocoNet IPL Device Query for
     * UR92s sent by this class.
     *
     * @return true if the class is waiting for LocoNet IPL reply messages, else
     *      false.
     */
    /*public*/ bool LnDplxGrpInfoImpl::isWaitingForFirstUr92IPLReport() {
        return waitingForIplReply;
    }


    /**
     * Reports the number of LocoNet messages handled since object construction.
     *
     * @return the number of LocoNet messages since this object was constructed.
     */
    /*public*/ int LnDplxGrpInfoImpl::getMessagesHandled() {
        return messagesHandled;
    }

    /**
     * Reports whether the IPL query timer is running.
     *
     * @return true if the timer is running, else false.
     */
    /*public*/ bool LnDplxGrpInfoImpl::isIplQueryTimerRunning() {
        return swingTmrIplQuery->isRunning();
    }

    /**
     * Reports whether the Duplex Group Info query timer is running.
     *
     * @return true if the timer is running, else false.
     */
    /*public*/ bool LnDplxGrpInfoImpl::isDuplexGroupQueryRunning() {
        return swingTmrDuplexInfoQuery->isRunning();
    }

    /**
     * Reports whether this object is currently waiting for
     * Duplex Group Name, etc. Report message.
     *
     * @return true if currently waiting, else false
     */
    /*public*/ bool LnDplxGrpInfoImpl::isAwaitingDuplexGroupReportMessage() {
        return awaitingGroupReadReport;
    }

    // Property Change keys relating to GUI status line
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_STAT_LN_UPDATE = "DPLXPCK_STAT_LN_UPDATE"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_STAT_LN_UPDATE_IF_NOT_CURRENTLY_ERROR = "DPLXPCK_STAT_LN_ON_OVER_UPDATE"; // NOI18N

    // Property Change keys relating to validity of identity info
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_NAME_VALIDITY = "DPLXPCK_NAME_VALID"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_CHANNEL_VALIDITY = "DPLXPCK_CH_VALID"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_PASSWORD_VALIDITY = "DPLXPCK_PW_VALID"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_ID_VALIDITY = "DPLXPCK_ID_VALID"; // NOI18N

    // Property Change keys relating to identity info value changes
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_NAME_UPDATE = "DPLXPCK_NAME_UPDATE"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_CHANNEL_UPDATE = "DPLXPCK_CH_UPDATE"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_PASSWORD_UPDATE = "DPLXPCK_PW_UPDATE"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_ID_UPDATE = "DPLXPCK_ID_UPDATE"; // NOI18N

    // Property Change keys relating to Duplex Group Identity LocoNet messages
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_RCD_DPLX_IDENTITY_QUERY = "DPLXPCK_IDENTITY_QUERY"; // NOI18N
    /*public*/ /*final*/ /*static */QString LnDplxGrpInfoImpl::DPLX_PC_RCD_DPLX_IDENTITY_REPORT = "DPLXPCK_IDENTITY_REPORT"; // NOI18N

    /**
     * Connect this instance's LocoNetListener to the LocoNet Traffic Controller
     *
     * @param t  LocoNet traffic controller
     */
    /*public*/ void LnDplxGrpInfoImpl::connect(LnTrafficController* t) {
        if (t != nullptr) {
            // connect to the LnTrafficController
            t->addLocoNetListener(~0, this);
        }
    }

    /**
     * Break connection with the LnTrafficController and stop timers.
     */
    /*public*/ void LnDplxGrpInfoImpl::dispose() {
        if (swingTmrIplQuery != nullptr) {
            swingTmrIplQuery->stop();
        }
        if (swingTmrDuplexInfoQuery != nullptr) {
            swingTmrDuplexInfoQuery->stop();
        }
        if (memo->getLnTrafficController() != nullptr) {
            memo->getLnTrafficController()->removeLocoNetListener(~0, this);
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LnDplxGrpInfoImpl::log = LoggerFactory::getLogger("LnDplxGrpInfoImpl");

