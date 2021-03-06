/*  Copyright (C) 2012,2013 Renier Yves
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
    
#include "protocol.h"


// Constructor is dependant of the protocol.
/* This is a template constructor. 
    It should initialize all arrays of messages to NULL.*/
protocol::protocol(uint8_t pins[],uint8_t npin)
{
/*//Initialize array of messages to NULL here.  There should be 1 message array per pin acquirring binary data
    this->mosi_mess=NULL;*/
//Call init_acquisition if paramaters are given.
    if(pins!=NULL && npin>0)
        this->init_acquisition(pins,npin);
}

// Destructor is dependant of the protocol
/* This is a template destructor. 
    It should delete all arrays of messages if they are not NULL.
protocol::~protocol()
{
//delete[] array of message here if not NULL
    if(mosi_mess!=NULL)
        delete[] mosi_mess;
//reinitialize all arrays of messages to NULL here.
    mosi_mess=NULL;
 }*/
 
//! init_acquisition() does not have to be reimplemented, this is the default behaviour:
void protocol::init_acquisition(uint8_t pins[],uint8_t npin)
{
    pmesg(DEBUG,"protocol::init_acquisition().\n");
    //! 1. Clean everything
//test disable destructors
//    this->~protocol();
    //! 2. Call binary::init_acquisition() if paramaters are given
    if(pins!=NULL && npin>0)
        this->capture.init_acquisition(pins,npin);
}

//! acquire() does not have to be reimplemented, this is the default behaviour:
void protocol::acquire(uint32_t npoint, float period)
{
    pmesg(DEBUG,"protocol::acquire().\n");
    //! 1. Call binary::acquire()
    this->capture.acquire(npoint,period);
printf("got %i points on %i pins\n",this->capture.npoint,this->capture.npin);
}

// decode() need to be implemented for each protocol
/* This is a template decode() function, for a full exemple look at microwire::decode()
void protocol::decode (void)
{
//With pins[0] connected to CS, HIGHV as active value and cs as member activity object we can do:
    cs.init(&capture,0,HIGHV);
//With pins[1] connected to CLK and clk as member transition object we can do:
    clk.init(&capture, 1,&cs);
//With pins[2] connected to a data pin, the data being available on LOWV to HIGHV transition and with mosi the member binary object we can do:
    mosi.init(&capture, &clk, 2, 'u');
//If we declared a member function called decode_mosi() which translates binary data to messages we can do:
    this->decode_mosi();
}*/

// Draw() also need to be implemented for each protocol
/* This is a template Draw() function, for a full exemple look at microwire::Draw()
int protocol::Draw (mglGraph * gr)
{
//! The draw function should :
    float logic_values[]={0, 1, 2, 3};
    const char *ylabels[]={"0V", "HR", "ERR", "3V3"};
    const char *plot_labels[4]={"CS","CLK","MOSI","MISO"};
    gr->SetTicksVal('y',4,logic_values,ylabels);
    gr->SetPlotFactor(1.15);
//! 1. Plot raw data
    capture.Draw(gr,plot_labels);
//! 2. Set background of all subplots according to the member activity object
    for (uint8_t pin=0;pin<capture.npin;pin++)
        this->cs.Draw(gr,pin);
//! 3. plot clok period stats according to the member transition object.
    this->clk.Draw(gr);
//! 4. plot arrows showing relevant transitions on subplot with data accordingto the member transition object.
    this->clk.Draw(gr,'u',2);
//! 5. display binary values.
    this->mosi.Draw(gr);
//! 6. Display messages decoded by the decode() function.
    if(this->mosi_mess!=NULL)
    {
        for (uint32_t i=0;i<this->nmessage;i++)
        {
            this->mosi_mess[i].Draw(gr);
        }
    }
//! 7. return 0 if no error occured.
    return 0;
}*/

//! Save() does not have to be reimplemented, this is the default behaviour:
/* If you wish, you could overload it to add saving of each objects of your protocol (you will then need to overload Load() too).*/
void protocol::Save(const char* filename)
{
    pmesg(DEBUG,"protocol::Save().\n");
    //Save the capture object
    this->capture.Save(filename);
}

//! Load() does not have to be reimplemented, this is the default behaviour:
/* If you wish, you could overload it to add loading of each objects of your protocol (you will then need to overload Save() too).*/
void protocol::Load(const char* filename)
{
    pmesg(DEBUG,"protocol::Load().\n");
    //Load the capture object
    this->capture.Load(filename);
}

