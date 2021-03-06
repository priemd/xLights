/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Vamp

    An API for audio analysis and feature extraction plugins.

    Centre for Digital Music, Queen Mary, University of London.
    Copyright 2006 Chris Cannam.
  
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
    ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the names of the Centre for
    Digital Music; Queen Mary, University of London; and Chris Cannam
    shall not be used in advertising or otherwise to promote the sale,
    use or other dealings in this Software without prior written
    authorization.
*/

#ifndef _VAMP_HOSTSDK_HOSTGUARD_H_
#define _VAMP_HOSTSDK_HOSTGUARD_H_

#ifdef _VAMP_IN_PLUGINSDK
#error You have included headers from both vamp-sdk and vamp-hostsdk in the same source file. Please include only vamp-sdk headers in plugin code, and only vamp-hostsdk headers in host code.
#else

#define _VAMP_IN_HOSTSDK 1

#define VAMP_SDK_VERSION "2.8"
#define VAMP_SDK_MAJOR_VERSION 2
#define VAMP_SDK_MINOR_VERSION 8

#ifdef _VAMP_NO_HOST_NAMESPACE
#define _VAMP_SDK_HOSTSPACE_BEGIN(h)
#define _VAMP_SDK_HOSTSPACE_END(h)
#define _VAMP_SDK_PLUGSPACE_BEGIN(h)
#define _VAMP_SDK_PLUGSPACE_END(h)
#else
#define _VAMP_SDK_HOSTSPACE_BEGIN(h) \
	namespace _VampHost {

#define _VAMP_SDK_HOSTSPACE_END(h) \
	} \
	using namespace _VampHost;
#define _VAMP_SDK_PLUGSPACE_BEGIN(h) \
	namespace _VampHost {

#define _VAMP_SDK_PLUGSPACE_END(h) \
	} \
	using namespace _VampHost;
#endif

#endif

#endif

