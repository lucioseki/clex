/*
 * Exception.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include<iostream>

using namespace std;

/**
 *  @author Vinicius Lopes
 *  @since 27/02/10
 *  @version 1.0
 */

/// Exception class throwed by the calculate method with one parameter of VI, NMI and CR classes
/** All the exception that occured in MOCLE is gonna be treated in this class*/
class Exception {
 public:
		/** Does nothing */
        Exception();

        /** Calculate the distance euclidean */
    	/** @return the distance euclidean beween the dois pattern passed to the method  */
        void showError();

 private:
        const char *cErrorMessage;

};

#endif /* EXCEPTION_H_ */
