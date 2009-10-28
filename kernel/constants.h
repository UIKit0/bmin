/*
 * constants.h - main constants for other bmin classes
 * created date: 2009/08/04
 *
 * Copyright (C) 2007-2009 Jakub Zelenka.
 *
 * Bmin is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * Bmin is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with Bmin; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// version
#define BMIN_VERSION_MAJOR   0
#define BMIN_VERSION_MINOR   4
#define BMIN_VERSION_RELEASE 0

#define STRINGIFY_INTERNAL(_s) #_s
#define STRINGIFY(_s) STRINGIFY_INTERNAL(_s)

#define BMIN_VESION_STRING STRINGIFY(BMIN_VERSION_MAJOR) \
    "." STRINGIFY(BMIN_VERSION_MINOR) \
    "." STRINGIFY(BMIN_VERSION_RELEASE)

namespace Constants {

    // Version string
    const char * const VERSION = BMIN_VESION_STRING;

    // Whether show default formula
    const bool DEFAULT_FORMULA = false;

    // Color in grey scale for main widget separator
    const int SEP_COLOR_GS = 180;

}

#endif // CONSTANTS_H