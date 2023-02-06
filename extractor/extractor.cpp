/*
 * SPDX-FileCopyrightText: 2006-2021 Istituto Italiano di Tecnologia (IIT)
 * SPDX-FileCopyrightText: 2006-2010 RobotCub Consortium
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <yarp/os/Bottle.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>
#include <yarp/os/Port.h>
#include <yarp/os/Time.h>
#include <filesystem>
#include </usr/local/src/robot/cognitiveInteraction/DTDataGloveModule/src/DTdataGlove/include/progressbar.hpp>

#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sys/time.h>
#include <ctime>

using yarp::os::BufferedPort;
using yarp::os::Bottle;
using yarp::os::Network;
using yarp::os::Port;

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/dev/all.h>
#include <fglove.h>

using namespace std;

constexpr double loop_delay = 0.1;/**< delay for controlling flow */
constexpr size_t top = 100;/**< size for a loop */

string testFlag; /**<  string to check the usability of the module ( test or full )*/

string path = "/usr/local/src/robot/cognitiveInteraction/DTDataGloveModule/saved_data/"; /**<  path prefix to save new csv files*/

fdGlove* pGloveA = NULL;/**< initialization of an fdGlove pointer pointing
                             to the glove
                             */

float finger_values[18];/**< array containing the actual data from the glove */
short unsigned int finger_values_raw[18];

vector<float> finger_values_vec(18);
vector<vector<float>> finger_table;/**< stores everyhting from exploration */

uint64_t ms; /**< variable for storing timestamps */
uint64_t timestamps[top];

ofstream myfile; /**< variable for storing filepath */

int counter = 0;

string partName;

progressbar barra(100); /**< progress bar for glove calibration */

/**getGesture function
 *
 * This function simply implements a switch case in order to display
 * in a readable format the gesture inferred by the glove
 *
 * @param gesture Is an integer representing the gesture index. It's returned
 * by a call to the SDK function called *fdGetGesture*
 *
 *@returns *void*
 */
void getGestures(int gesture){
  switch (gesture) {
    case 0:
      yInfo("CLOSE FIST");
      break;
    case 1:
      yInfo("INDEX FINGER POINT");
      break;
    case 2:
      yInfo("MIDDLE FINGER POINT");
      break;
    case 3:
      yInfo("INDEX/MIDDLE FINGERS POINT");
      break;
    case 4:
      yInfo("RING FINGER POINT");
      break;
    case 5:
      yInfo("RING/INDEX FINGERS POINT");
      break;
    case 6:
      yInfo("RING/MIDDLE FINGERS POINT");
      break;
    case 7:
      yInfo("FIRST 3 FINGERS POINT");
      break;
    case 8:
      yInfo("LITTLE FINGER POINT");
      break;
    case 9:
      yInfo("INDEX/LITTLE FINGERS POINT");
      break;
    case 10:
      yInfo("MIDDLE/LITTLE FINGERS POINT");
      break;
    case 11:
      yInfo("NOT-RING FINGERS POINT");
      break;
    case 12:
      yInfo("RING/LITTLE FINGERS POINT");
      break;
    case 13:
      yInfo("NOT-MIDDLE FINGERS POINT");
      break;
    case 14:
      yInfo("NOT INDEX FINGERS POINT");
      break;
    case 15:
      yInfo("OPEN HAND");
      break;
  }
}



/**printFingersValue function
 *
 * This function take as parameter the glove extracted finger_values
 * and prints them in a format representing the various fingers.
 * The values are normalized between 0 and 1.
 *
 * @param gloveA_scaled Is a float pointer containing the normalized
 * values. Is returned after an SDK call to the function
 * called *fdGetSensorScaledAll*.
 *
 *@returns *void*
 */
void printFingersValue(float* gloveA_value){
    yInfo("A:%0.5f %0.5f||%0.5f||%0.5f %0.5f||%0.5f||%0.5f %0.5f||%0.5f||%0.5f %0.5f||%0.5f||%0.5f %0.5f",
    gloveA_value[FD_THUMBNEAR],
    gloveA_value[FD_THUMBFAR],
    gloveA_value[FD_THUMBINDEX],
    gloveA_value[FD_INDEXNEAR],
    gloveA_value[FD_INDEXFAR],
    gloveA_value[FD_INDEXMIDDLE],
    gloveA_value[FD_MIDDLENEAR],
    gloveA_value[FD_MIDDLEFAR],
    gloveA_value[FD_MIDDLERING],
    gloveA_value[FD_RINGNEAR],
    gloveA_value[FD_RINGFAR],
    gloveA_value[FD_RINGLITTLE],
    gloveA_value[FD_LITTLENEAR],
    gloveA_value[FD_LITTLEFAR]);

    int gesture = fdGetGesture(pGloveA);

    yInfo(" >>>>>>>GESTURE>>>>>>> %d , which is : ",gesture);
    getGestures(gesture);
}


/**printFingersValueRaw function
 *
 * This function take as parameter the glove extracted finger_values
 * and prints them in a format representing the various fingers.
 * The values are normalized between 0 and 1.
 *
 * @param gloveA_scaled Is a float pointer containing the normalized
 * values. Is returned after an SDK call to the function
 * called *fdGetSensorScaledAll*.
 *
 *@returns *void*
 */
void printFingersValueRaw(short unsigned int* gloveA_value){
    yInfo("A:%d %d||%d||%d %d||%d||%d %d||%d||%d %d||%d||%d %d",
    gloveA_value[FD_THUMBNEAR],
    gloveA_value[FD_THUMBFAR],
    gloveA_value[FD_THUMBINDEX],
    gloveA_value[FD_INDEXNEAR],
    gloveA_value[FD_INDEXFAR],
    gloveA_value[FD_INDEXMIDDLE],
    gloveA_value[FD_MIDDLENEAR],
    gloveA_value[FD_MIDDLEFAR],
    gloveA_value[FD_MIDDLERING],
    gloveA_value[FD_RINGNEAR],
    gloveA_value[FD_RINGFAR],
    gloveA_value[FD_RINGLITTLE],
    gloveA_value[FD_LITTLENEAR],
    gloveA_value[FD_LITTLEFAR]);

    int gesture = fdGetGesture(pGloveA);

    yInfo(" >>>>>>>GESTURE>>>>>>> %d , which is : ",gesture);
    getGestures(gesture);
}


/**getGloveInfo function
 *
 * This function simply prints some information about the glove connected.
 * It uses two SDK functions in order to retrive the infos.
 *
 * called *fdGetSensorScaledAll*.
 *
 *@returns *void*
 */
void getGloveInfo(){
  char *szType = (char*)"?";

	int glovetype = fdGetGloveType(pGloveA);
	switch (glovetype)
	{
		case FD_GLOVENONE:    szType = (char*)"None"; break;
		case FD_GLOVE5U:      szType = (char*)"Data Glove 5 Ultra"; break;
		case FD_GLOVE5UW:     szType = (char*)"Data Glove 5 Ultra W"; break;
		case FD_GLOVE5U_USB:  szType = (char*)"Data Glove 5 Ultra USB"; break;
		case FD_GLOVE7:       szType = (char*)"Data Glove 5"; break;
		case FD_GLOVE7W:      szType = (char*)"Data Glove 5W"; break;
		case FD_GLOVE16:      szType = (char*)"Data Glove 16"; break;
		case FD_GLOVE16W:     szType = (char*)"Data Glove 16W"; break;
		case FD_GLOVE14U:     szType = (char*)"DG14 Ultra serial"; break;
		case FD_GLOVE14UW:    szType = (char*)"DG14 Ultra W"; break;
		case FD_GLOVE14U_USB: szType = (char*)"DG14 Ultra USB"; break;
	}

	printf("Glove type: %s\n", szType );
	printf("Glove handedness: %s\n", fdGetGloveHand(pGloveA)==FD_HAND_RIGHT?"Right":"Left" );
	printf("Data rate: %iHz\n", fdGetPacketRate(pGloveA));
}


/**openFile function
 *
 * This function opens the cvs file for the session
 *
 *@returns *void*.
 */
void setParticipant(){

  cout << "Now the experiment will start\n";
  cout << "First of all insert your name, the data will be saved in 'saved_data/{yourname}' : \n";
  cin  >> partName;

  cout << "Do you want to use the main purpose of the module (gesture recognition)?"
              "otherwise the continuos raw values will be displayed (testing).\n";
  do {
    cout << "y-yes/n-no \n?";
    cin  >> testFlag;
  } while(testFlag != "yes" && testFlag != "y" && testFlag != "Yes" && testFlag != "no" && testFlag != "n" && testFlag != "No");

}


/**configureGlove function
 *
 * This function simply opens the glove and prints out the number
 * of gestures that the glove can infer from the sensors.
 *
 * @param port char pointer to the port(usb).
 *
 *@returns *boolean* used to check if successful or not.
 */
bool configureGlove(char *port){

  yInfo("\nAttempting to open glove on %s .. ", port );
	pGloveA = fdOpen(port);
	if (pGloveA == NULL)
	{
		yError("Failed to open the glove, please verify that you're trying to check the glove on the right port.\n");
    return false;
	}
	yInfo("Succeeded in opening the glove.\n");
  yInfo("The glove can represent %d different gestures.\n", fdGetNumGestures(pGloveA));
  getGloveInfo();

  yInfo("Glove Calibration, please open and close your hand in order to better configure the device.\n");

  barra.set_todo_char(" ");
  barra.set_done_char("█");
  barra.set_opening_bracket_char("(-");
  barra.set_closing_bracket_char("-)");

  for (size_t i = 0; i < 100; i++) {
    barra.update();
    yarp::os::Time::delay(loop_delay);
    }

  yInfo("\nGlove Calibration completed, thank you.\n");

  setParticipant();
  return true;
}


/**saveGloveData function
 *
 * This function saves the data extracted from the
 * glove and stores it in a csv file format.
 *
 *@returns *void*.
 */
void saveGloveData(){

  //myfile << timestamp;
  //myfile << ",";
  myfile.open (path + partName + "_run.csv");
  myfile << "timestamp, value1, value2, value3, value4, value5, value6, value7, value8, value9, value10, value11, value12, value13, value14, value15, value16, value17, value18";
  myfile << "\n";

  for (size_t i = 0; i < top; i++) {
    myfile << timestamps[i];
    myfile << ",";
    for (size_t j = 0; j < finger_table[i].size(); j++) {
      myfile << finger_table[i][j];
      myfile << ",";
    }
    myfile << "\n";
  }
  myfile.close();
}


/**storeValuesInTable function
 *
 * This function saves the data extracted from the
 * glove and stores it in a csv file format.
 *
 *@returns *void*.
 */
void storeValuesInTable(){
    finger_values_vec.assign(begin(finger_values), end(finger_values));
    finger_table.push_back(finger_values_vec);
}


/**extractGloveData function
 *
 * This function simply extract the glove data with a call
 * to SDK function called fdGetSensorScaledAll and calls
 * the functions in charge of printing the values.
 *
 *
 *@returns *void*.
 */
void extractGloveData(){

  fdGetSensorScaledAll(pGloveA, finger_values);

  /*ms = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count();*/
  /*struct timeval time_now{};
  gettimeofday(&time_now, nullptr);
  timestamps[counter] = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);*/
  timestamps[counter] = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count(); // / 1000 ;
  counter++;

  storeValuesInTable();
  printFingersValue(finger_values);
}

/**extractGloveDataRaw function
 *
 * This function simply extract the glove raw data with a call
 * to SDK function called fdGetSensorRawAll and calls
 * the functions in charge of printing the values.
 *
 *
 *@returns *void*.
 */
void extractGloveDataRaw(){

  fdGetSensorRawAll(pGloveA, finger_values_raw);

  printFingersValueRaw(finger_values_raw);
}


/**closeGlove function
 *
 * This function simply closes the glove once the usage is finished.
 *
 *@returns *boolean* used to check if successful or not.
 */
bool closeGlove(){

  if (fdClose(pGloveA) == 0){
    yError("Error in closing the glove, aborting...\n");
    return false;
  }
  yInfo("Glove closed correctly.\n");
  return true;
}



/**main function
 *
 * The main function simply set's a yarp communication and then,
 * in a loop, keeps to extract the data and sends it through
 * a buffered port to the receiver, namely *extractor.cpp*
 *
 * @param port char pointer to the port(usb).
 *
 *@returns *integer* used to check if successful or not.
 */
int main(int argc, char* argv[])
{
    YARP_UNUSED(argc);
    YARP_UNUSED(argv);

    Network yarp;
    BufferedPort<Bottle> output;
    output.open("/DTDataGlove/sender:out");
    Network::connect("/DTDataGlove/sender:out", "/DTDataGlove/input:in");


    char *glovePort = (char*)"/dev/usb/hiddev0";
    if (configureGlove(glovePort) == false){
      yError("Not able to open the glove, aborting...\n");
      return -1;
    }

    if (testFlag == "no" || testFlag == "n" || testFlag == "No") {
        for (size_t i = 1; i <= top; i++) {
          extractGloveDataRaw();
        }
    }
    else{
        for (size_t i = 1; i <= top; i++) {
          Bottle& gloveBottle = output.prepare();
      		gloveBottle.clear();
      		extractGloveData();

          for (size_t i = 0; i < 14; i++) {
            gloveBottle.addFloat32(finger_values[i]);
          }
      		output.writeStrict();
          yarp::os::Time::delay(loop_delay);
        }
        saveGloveData();
    }


    output.close();
    if (closeGlove()==false){
      return -1;
    }
    return 0;
}
