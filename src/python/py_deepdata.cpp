/*
  Copyright 2015 Larry Gritz and the other authors and contributors.
  All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the software's owners nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  (This is the Modified BSD License)
*/

#include "py_oiio.h"

namespace PyOpenImageIO
{
using namespace boost::python;
using self_ns::str;



void
DeepData_init (DeepData &dd, int npix, int nchan, tuple p)
{
    std::vector<TypeDesc> chantypes;
    py_to_stdvector (chantypes, p);
    ScopedGILRelease gil;
    dd.init (npix, nchan, chantypes);
}



void
DeepData_init_spec (DeepData &dd, const ImageSpec &spec)
{
    ScopedGILRelease gil;
    dd.init (spec);
}



int
DeepData_get_samples (DeepData &dd, int pixel)
{
    return int (dd.samples(pixel));
}


void
DeepData_set_nsamples (DeepData &dd, int pixel, int nsamples)
{
    dd.set_samples (pixel, uint32_t(nsamples));
}



void
DeepData_set_deep_value_float (DeepData &dd, int pixel,
                               int channel, int sample, float value)
{
    dd.set_deep_value (pixel, channel, sample, value);
}



void
DeepData_set_deep_value_uint (DeepData &dd, int pixel,
                              int channel, int sample, uint32_t value)
{
    dd.set_deep_value (pixel, channel, sample, value);
}



// Declare the OIIO DeepData class to Python
void declare_deepdata()
{
    class_<DeepData>("DeepData")
        .def_readonly ("npixels",    &DeepData::pixels)   //DEPRECATED(1.7)
        .def_readonly ("nchannels",  &DeepData::channels) //DEPRECATED(1.7)
        .def_readonly ("pixels",     &DeepData::pixels)
        .def_readonly ("channels",   &DeepData::channels)

        .def("init",  &DeepData_init)
        .def("init",  &DeepData_init_spec)
        .def("clear", &DeepData::clear)
        .def("free",  &DeepData::free)

        .def("samples",         &DeepData_get_samples,
             (arg("pixel")))
        .def("set_samples",     &DeepData::set_samples,
             (arg("pixel"), arg("nsamples")))
        .def("insert_samples",  &DeepData::insert_samples,
             (arg("pixel"), arg("samplepos"), arg("nsamples")=1))
        .def("erase_samples",   &DeepData::erase_samples,
             (arg("pixel"), arg("samplepos"), arg("nsamples")=1))
        .def("channeltype",     &DeepData::channeltype)
        .def("deep_value",      &DeepData::deep_value,
             (arg("pixel"), arg("channel"), arg("sample")))
        .def("deep_value_uint", &DeepData::deep_value_uint,
             (arg("pixel"), arg("channel"), arg("sample")))
        .def("set_deep_value",  &DeepData_set_deep_value_float,
             (arg("pixel"), arg("channel"), arg("sample"), arg("value")))
        .def("set_deep_value_uint", &DeepData_set_deep_value_uint,
             (arg("pixel"), arg("channel"), arg("sample"), arg("value")))
    ;
}

} // namespace PyOpenImageIO

