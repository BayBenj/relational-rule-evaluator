//
//  Scheme.cpp
//  Project 3
//
//  Created by Benjamin Elvon Bay on 7/7/15.
//  Copyright (c) 2015 Benjamin Elvon Bay. All rights reserved.
//

#include "Scheme.h"

Scheme::Scheme() {}
Scheme::~Scheme() {}

void Scheme::deleter(int position) {
    erase(begin() + position);
}