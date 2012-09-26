/*
 * Exception.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Marcus
 */

#include"Exception.h"


/* Implementation of Exception methods */

Exception::Exception() : cErrorMessage("Invalid Method Called"){}

void Exception::showError(){
    cout << cErrorMessage << endl;
}

