
#include "FFmpegParameters.hpp"

#include <string>
#include <iostream>
#include <sstream>

extern "C"
{
    #include <libavutil/parseutils.h>
    #include <libavutil/pixdesc.h>
}

inline AVPixelFormat osg_av_get_pix_fmt(const char *name) { return av_get_pix_fmt(name); }


namespace osgFFmpeg {



FFmpegParameters::FFmpegParameters() :
    m_format(0),
    m_context(0),
    m_options(0)
{
    // Initialize the dictionary
    av_dict_set(&m_options, "foo", "bar", 0);
}

FFmpegParameters::~FFmpegParameters()
{
    av_dict_free(&m_options);
}


void FFmpegParameters::parse(const std::string& name, const std::string& value)
{
    if (value.empty())
    {
        return;
    }
    if (name == "format")
    {
#ifndef ANDROID
        avdevice_register_all();
#endif
        m_format = av_find_input_format(value.c_str());
        if (!m_format)
            OSG_NOTICE<<"Failed to apply input video format: "<<value.c_str()<<std::endl;
    }
    else if (name == "frame_rate")
        av_dict_set(&m_options, "framerate", value.c_str(), 0);
    else
        av_dict_set(&m_options, name.c_str(), value.c_str(), 0);
}



} // namespace osgFFmpeg
