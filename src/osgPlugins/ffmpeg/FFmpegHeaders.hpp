
#ifndef HEADER_GUARD_FFMPEG_HEADERS_H
#define HEADER_GUARD_FFMPEG_HEADERS_H


extern "C"
{
#define FF_API_OLD_SAMPLE_FMT 0
#include <errno.h>    // for error codes defined in avformat.h
#include <stdint.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

#ifdef USE_AVRESAMPLE    // To compile using libav instead of ffmpeg

#  include <libavresample/avresample.h>

#  define SwrContext AVAudioResampleContext
#  define swr_init avresample_open
#  define swr_free(ctx) avresample_free(ctx)
#  define swr_convert(ctx, out, out_size, in, in_size) avresample_convert(ctx, out, 0, out_size, (uint8_t **)in, 0, in_size)
#  define swr_alloc_set_opts swr_alloc_set_opts_proxy

#  include <libavutil/opt.h>

  inline AVAudioResampleContext * swr_alloc_set_opts_proxy(SwrContext* /*ctx*/, int64_t out_ch_layout, enum AVSampleFormat out_sample_format, int out_sample_rate, int64_t in_ch_layout, enum AVSampleFormat in_sample_format, int in_sample_rate, int /*log_offset*/, void * /*log_ctx*/)
  {
    AVAudioResampleContext *avr = avresample_alloc_context();
    av_opt_set_int(avr, "in_channel_layout",  in_ch_layout, 0);
    av_opt_set_int(avr, "out_channel_layout", out_ch_layout, 0);
    av_opt_set_int(avr, "in_sample_rate", in_sample_rate, 0);
    av_opt_set_int(avr, "out_sample_rate", out_sample_rate, 0);
    av_opt_set_int(avr, "in_sample_fmt", in_sample_format, 0);
    av_opt_set_int(avr, "out_sample_fmt", out_sample_format, 0);
    return avr;
  }

#else
#  include <libswresample/swresample.h>
#endif

#ifndef ANDROID
#include <libavdevice/avdevice.h>
#endif

#include <libavutil/mathematics.h>
#include <libavutil/imgutils.h>

#ifdef USE_SWSCALE
    #include <libswscale/swscale.h>
#endif

}



#endif // HEADER_GUARD_FFMPEG_HEADERS_H
