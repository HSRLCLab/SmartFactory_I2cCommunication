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
#include <string.h>
#include <Wire.h>

// own files:
#include "LogConfiguration.h"

#define MASTER

#ifdef MASTER

/**
*  Received I2c message struct to store message for master
* 
*/
#pragma pack(1)
struct ReceivedI2cMessage
{
    char event[12] = "-1";
    uint8_t packageId = 0;
    uint16_t targetDest = 0;
    int8_t position = -1;
    uint8_t state = 0;
    bool error = false;
    bool token = false;
    /*
    char cargo[12] = "-1";
    */
};


/**
*  Write I2c message struct to store answer message for master
* 
*/
#pragma pack(1)
struct WriteI2cMessage
{
    char event[12] = "-1";
    uint8_t targetLine = -1;
};


#else
/**
*  Received I2c message struct to store message for slave
* 
*/
#pragma pack(1)
struct ReceivedI2cMessage
{
    char event[12] = "-2";
    uint8_t targetLine = -1;
};


/**
*  Write I2c message struct to store answer message for slave
* 
*/
#pragma pack(1)
struct WriteI2cMessage
{
    char event[12] = "-1";
    uint8_t packageId = 0;
    uint16_t targetDest = 0;
    int8_t position = -1;
    uint8_t state = 0;
    bool error = false;
    bool token = false;
    /*
    char cargo[12] = "-1";
    */
};


#endif

/**
 * @brief Class to communicate with I2c
 * 
 */
class I2cCommunication
{
    public:

    #ifdef MASTER
    /**
     * @brief Construct a new I2cCommunication object
     * 
     * @param ReceivedMessage 
     * @param WriteMessage 
     */
    I2cCommunication(int adress, ReceivedI2cMessage *receivedMessage, WriteI2cMessage *writeMessage);

    // Functions for Master

    /**
     * @brief Write function to write message to slave
     * 
     */
    void writeMessage();

    /**
     * @brief Read function to read message from slave
     * 
     */
    void readMessage();

    ReceivedI2cMessage *pReceivedMessage = nullptr;

    WriteI2cMessage *pWriteMessage = nullptr;


    #else

    /**
     * @brief Construct a new I2cCommunication object
     * 
     */
    I2cCommunication(int adress, void (*receiveCallback)(int bytes), void (*requestCallback)());
    
    void (*receiveCallbackFuncPointer)(int bytes) = nullptr;  ///< functionpointer to callback-function

    void (*requestCallbackFuncPointer)() = nullptr;  ///< functionpointer to callback-function
    #endif

    private:

    int pAdress;

    

    



};

#endif