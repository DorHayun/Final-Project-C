#pragma once

#ifndef DELETE_APT_H
#define DELETE_APT_H

#include <stdlib.h>
#include<stdio.h>
#include<time.h>
#define _CRT_SECURE_NO_WARNINGS

#include "readLines.h"
#include "apartment.h"

void delApartment(COMMAND cmd, ApartmentTable *db);

#endif 