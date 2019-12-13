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
/**
 * @file I2cCommunication.cpp
 * @author Philip Zellweger (philip.zellweger@hsr.ch)
 * @brief I2c communication library for master and slave
 * @version 0.1
 * @date 2019-11-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "I2cCommunication.h"


I2cCommunication::I2cCommunication(void *ReceivedMessage, void *WriteMessage, size_t writeCapacitiy, size_t readCapicity) : 
                                                            pRecievedMessage(ReceivedMessage), 
                                                            pWriteMessage(WriteMessage),
                                                            pWriteCapacity(writeCapacitiy),
                                                            pReadCapicity(readCapicity)
{
#ifdef MASTER
    Wire.begin();
#else
    Wire.begin(I2CSLAVEADDRESP);
    Wire.onRequest(RequestCallback);
    Wire.onReceive(ReadCallback);
#endif
}

#ifdef MASTER
void I2cCommunication::writeMessage()
{
    DBFUNCCALLln("I2cCommunication::writeMessage()");
    Wire.beginTransmission(I2CSLAVEADDRESP);
    Wire.write((uint8_t *) pWriteMessage, (size_t)pWriteCapacity);
    Wire.endTransmission();
    delay(50);
}

void I2cCommunication::readMessage()
{
    DBFUNCCALLln("I2cCommunication::readMessage()");
    Wire.requestFrom(I2CSLAVEADDRESP, (int)pReadCapicity);
    while(Wire.available() < (int)pReadCapicity)
    {
        delay(5);
    }
    Wire.readBytes((char *) pRecievedMessage, pReadCapicity);
}


#else

void I2cCommunication::ReadCallback(int bytes)
{
    DBFUNCCALLln("I2cCommunication::ReadCallback(int bytes)");
    while (0 < Wire.available())
    {
        Wire.readBytes( (char*) pReceivedMessage, pReadCapacity);
    }
}

void I2cCommunication::RequestCallback()
{
    DBFUNCCALLln("I2cCommunication::RequestCallback()");
    Wire.write((char*) pWriteMessage);
}
#endif

#include <Arduino.h>
#include <string.h>
#include <Wire.h>

// own files:
#include "LogConfiguration.h"
#include "MainConfiguration.h"
#include "MessageTranslation.h"

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
     * @param ReceivedMessage 
     * @param WriteMessage 
     */
    I2cCommunication(void *ReceivedMessage, void *WriteMessage, size_t writeCapacitiy, size_t readCapicity);

    

    // Functions for Master
    #ifdef MASTER

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

    #endif

    private:

    void *pRecievedMessage = nullptr;
    void *pWriteMessage = nullptr;

    size_t pWriteCapacity;
    size_t pReadCapicity;


};

#endif