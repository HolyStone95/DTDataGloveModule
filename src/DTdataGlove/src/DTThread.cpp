// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C)2019  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 *
 * Revision: Dario Pasquali
 * email: dario.pasquali@iit.it
 *
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

/**
 * \file DTThread.cpp
 * \brief Implementation of DTThread.h.
 */

#include <unistd.h>
#include <DTThread.h>
//#include <fglove.h>

//using namespace yarp::dev;
//using namespace yarp::os;
//using namespace yarp::sig;
using namespace std;

/**Normal constructor
 *
 */
DTThread::DTThread() :Thread() {
}

/**Parametrized constructor
 *
 */
DTThread::DTThread(yarp::os::ResourceFinder &_rf):Thread(){
	rf = _rf;
}

/**Destructor
 *
 */
DTThread::~DTThread() {
    // do nothing
}


/**Thread Init function
 *
 * This function handles the initialization phase of the thread
 * specifically it opens two BufferedPorts, one for input, one for output.
 */
bool DTThread::threadInit()
{
    yInfo("DTThread::threadInit: initialization in the method");

		inPort.setStrict();

	  yInfo("Open Output Port called /output:out");
		if (!outPort.open(getName("/outport:out").c_str())) {
				yError(": unable to open port ");
				return false;  // unable to open; let RFModule know so that it won't run
		}

		yInfo("Open Input Port called /input:in");
		if (!inPort.open(getName("/input:in").c_str())) {
				yError(": unable to open port ");
				return false;
		}

	yInfo("Thread correctly initialised \n");
    return true;
}

/**The run function
 *
 * This function simply reads from the input port and prints out
 * the received values representing normalized values of the fingers
 */
void DTThread::run() {

	while (isRunning()&!isStopping()) {

		for (size_t i = 0; i < 1000; i++) {
			gloveBottleIn = inPort.read();
			yInfo("Input bottle size : %ld", gloveBottleIn->size());
			yInfo("str message : %s", gloveBottleIn->toString().c_str());
		}
	}
	
}


/**The stop thread function
 *
 * This function simply interrupts and closes the two ports.
 */
void DTThread::onStop(){
	outPort.interrupt();
	outPort.close();

	inPort.interrupt();
	inPort.close();

	yDebug("Executing code in onStop");
}


/**The thread release function
 *
 * This function is in charge of releasing the thread
 */
void DTThread::threadRelease() {
    yDebug("Executing code in threadRelease");
}

/**The set name function
 *
 * This function sets the name of the thread
 *
 *@param str Is a string containing the desired thread name.
 */
void DTThread::setName(string str) {
	this->name = str;
}

/**The get name function
 *
 * This function gets the name of the thread
 *
 *@param p Is a const char* containing the desired thread name.
 */
std::string DTThread::getName(const char* p) {
	string str(name);
	str.append(p);
	return str;
}
