/* 
 * File:   stepper.h
 * Author: miyakoshi_macbookpro
 *
 * Created on May 12, 2022, 4:11 PM
 */

#ifndef STEPPER_H
#define	STEPPER_H

//------------------------------------------------
//  プロトタイプ宣言(Prototype declaration)
//------------------------------------------------
void turnStepperMotor(int excitation, bool isForward, int motorPinNumber);
void onePhaseOn(bool isForward, int motorPinNumber);
void twoPhaseOn(bool isForward, int motorPinNumber);

void countUp(bool isForward, int motorPinNumber);
void setMotorPinOutput(int motorPinNumber);

//------------------------------------------------
#endif

