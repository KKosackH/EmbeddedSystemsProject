/*
 * detectionFunctions.h
 *
 *  Created on: Feb 14, 2023
 *      Author: kkh19
 */

#ifndef SRC_DETECTIONFUNCTIONS_H_
#define SRC_DETECTIONFUNCTIONS_H_

#include <stdint.h>

#define RANGING_SENSOR_NB_TARGET_PER_ZONE (1U)
#define RANGING_SENSOR_MAX_NB_ZONES (16U)

typedef struct
{
  uint32_t NumberOfTargets;
  uint32_t Distance[RANGING_SENSOR_NB_TARGET_PER_ZONE];  /*!< millimeters */
  uint32_t Status[RANGING_SENSOR_NB_TARGET_PER_ZONE];    /*!< OK: 0, NOK: !0 */
  float Ambient[RANGING_SENSOR_NB_TARGET_PER_ZONE];    /*!< kcps / spad */
  float Signal[RANGING_SENSOR_NB_TARGET_PER_ZONE];     /*!< kcps / spad */
} RANGING_SENSOR_ZoneResult_t;

typedef struct
{
  uint32_t NumberOfZones;
  RANGING_SENSOR_ZoneResult_t ZoneResult[RANGING_SENSOR_MAX_NB_ZONES];
} RANGING_SENSOR_Result_t;

void initDetectionFunction(int8_t res);
void fillDataInStructs();
void alterData();
void gotoxy(int8_t r, int8_t c);
void clrscr();
void checkEvent();
void printChange(int8_t zone);
void printStatement();


#endif /* SRC_DETECTIONFUNCTIONS_H_ */
