cc_library(
    name = 'glog',
    srcs = [
        'src/demangle.cc',
        'src/logging.cc',
        'src/raw_logging.cc',
        'src/signalhandler.cc',
        'src/symbolize.cc',
        'src/utilities.cc',
        'src/vlog_is_on.cc',
    ],
    incs = [
        'src',
        'src/linux',
    ],
    deps = [
        '#pthread',
        '#rt',
    ],
    warning = 'no',
)
