/* config.h for Mini-XML v4.0.4 - NRC embedded build */
#ifndef MXML_CONFIG_H
#  define MXML_CONFIG_H
#  include <stdio.h>
#  include <stdlib.h>
#  include <string.h>
#  include <stdarg.h>
#  include <ctype.h>

#  define MXML_VERSION "Mini-XML v4.0.4"

/* inline is supported */
/* #  define inline */

/* No POSIX threads on embedded */
#  undef HAVE_PTHREAD_H

#endif /* !MXML_CONFIG_H */
