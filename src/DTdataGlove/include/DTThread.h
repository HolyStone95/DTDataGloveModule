// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
  * Copyright (C)2019  Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
  * Author:Dario Pasquali
  * email: dario.pasquali@iit.it
  * Permission is granted to copy, distribute, and/or modify this program
  * under the terms of the GNU General Public License, version 2 or any
  * later version published by the Free Software Foundation.
  *
  * A copy of the license can be found at
  * http://www.robotcub.org/icub/license/gpl.txt
  *
  * This program is distributed in the hope that it will be useful, but
  * WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
  * Public License for more details
*/

/**
 * @file DTThread.h
 * @brief Definition of a thread to control the eyelids of iCub in the Head_Upgrade setup
 */


#ifndef _MY_MODULE_THREAD_H_
#define _MY_MODULE_THREAD_H_

//#include <fglove.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <time.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <yarp/dev/SerialInterfaces.h>
#include <yarp/dev/PolyDriver.h>

#define CMD_DO		    createVocab32('d', 'o', 0, 0)

class DTThread : public yarp::os::Thread {

private:
	yarp::os::ResourceFinder rf;
	yarp::os::Bottle* gloveBottleIn;
  yarp::os::BufferedPort<yarp::os::Bottle> outPort;		// Output port
	yarp::os::BufferedPort<yarp::os::Bottle> inPort;		// Output port
	std::string name;		//rootname of all the ports opened by this thread

public:

	DTThread(); // constructor default
	DTThread(yarp::os::ResourceFinder &rf); // constructor  @param robotname name of the robot
  ~DTThread();

	// ======= Generich Thread Methods ===========

	bool threadInit();
	void threadRelease();
	void run();
  void onStop(); // function in charge of correctly closing the thread
	void close();

  void setName(std::string str);
	std::string getName(const char* p);

	// ======= Project Specific Methods ===========

/*void extractGloveData(char const *port);*/
};

#endif  //_MY_MODULE_THREAD_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------
