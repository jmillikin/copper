/* macros.hpp - Preprocessor macros to ease test building
 * Copyright (C) 2006 John Millikin
 * For conditions of distribution and use, see COPYING
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef assert
#undef assert
#endif

#if HAVE_EXCEPTIONS
#include <copper/macros_exceptions.hpp>
#else
#include <copper/macros_noexceptions.hpp>
#endif
