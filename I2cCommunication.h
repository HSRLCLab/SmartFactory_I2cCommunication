/**
 * @file I2cCommunication.h
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief I2c communication library for master and slave
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef I2CCOMMUNICAITON_H__
#define I2CCOMMUNICAITON_H__

#include <Arduino.h>
#include <Wire.h>

// own files:
#include "LogConfiguration.h"
#include "MainConfiguration.h"
#include "Message.h"

#define MASTER


/**
 * @brief Class to communicate with I2c
 * 
 */
class I2cCommunication
{
    public:

    /**
     * @brief Construct a new I2cCommunication object
     * 
     */
    I2cCommunication();

    /**
     * @brief Get the Received Event object
     * 
     * @return String 
     */
    String getReceivedEvent();

    /**
     * @brief Get the ReadFlag I2c object
     * 
     * @return true 
     * @return false 
     */
    bool getReadFlag_I2c();

    /**
     * @brief Set the Write Event object
     * 
     * @param s - String
     */
    void setWriteEvent(String s);

    /**
     * @brief Set the ReadFlag I2c object
     * 
     * @param flag - bool
     */
    void setReadFlag_I2c(bool flag);

    // Functions for Master
    #ifdef MASTER

    /**
     * @brief Write function to write message to slave
     * 
     */
    void writeMessage(WriteI2cMessage &message);

    /**
     * @brief Read function to read message from slave
     * 
     */
    ReceivedI2cMessage readMessage();
    
    /**
     * @brief Get the Received Information object
     * 
     * @return String 
     */
    String getReceivedInformation();

    /**
     * @brief Set the Write Package Information object
     * 
     * @param p - PackageMessage
     */
    void setWritePackageInformation(PackageMessage p);

    /**
     * @brief Set the Write State object
     * 
     * @param s - String
     */
    void setWriteState(String s);

    /**
     * @brief Set the Write Position object
     * 
     * @param pos - String
     */
    void setWritePosition(String pos);

    // Functions for Slave
    #else
    
    /**
     * @brief I2c request callback function to request on call from master
     * 
     */
    static void RequestCallback();
    
    /**
     * @brief I2c read callback function to read message from master
     * 
     * @param bytes - int
     */
    static void ReadCallback(int bytes);

    /**
     * @brief Get the Received State object
     * 
     * @return String 
     */
    String getReceivedState();

    /**
     * @brief Get the Received Position object
     * 
     * @return String 
     */
    String getReceivedPosition();

    /**
     * @brief Get the Received Package Information object
     * 
     * @return PackageMessage 
     */
    PackageMessage getReceivedPackageInformation();

    /**
     * @brief Set the Write Information object
     * 
     * @param s - String
     */
    void setWriteInformation(String s);
    #endif

    /**
     * @brief Reset function to reset all received message
     * 
     */
    void resetReceivedMessages();
    
    /**
     * @brief Reset function to reset I2c write message
     * 
     */
    void resetWriteMessages();

    private:

    static WriteI2cMessage pWriteMessage;               ///< private instance of write i2c message struct
    static ReceivedI2cMessage pReceivedMessage[2];      ///< private instance of received i2c message struct
    static bool READFLAG_I2C;                           ///< readflag for i2c messages
};

#endif