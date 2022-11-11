#ifndef KK2_LOG_TARGET_H
#define KK2_LOG_TARGET_H

#include <kk2/core/array.h>
#include <kk2/core/string.h>

KK2_OBJ_BEGIN(kk2_log_target)
    KK2_OBJ_CALLBACK(log, void, (kk2_string_t))
KK2_OBJ_END(kk2_log_target)

#endif
