# module.mk — minizip-ng embedded port (NRC SDK)
#
# Included by make/Makefile.feature.lib when CONFIG_MINIZIP=y.
# Requires:
#   MINIZIP_NG_ROOT — path to this directory
#   ZLIB_ROOT       — path to the zlib source tree
#   MBEDTLS_BASE    — path to mbedTLS (set by Makefile.feature.lib)
#
# Crypto control (set in Makefile.feature.lib or .config):
#   CONFIG_MINIZIP_ZIPCRYPTO=y   enable ZipCrypto (PKWARE traditional)  [default y]
#   CONFIG_MINIZIP_WZAES=y       enable WinZip AES-256 (method=99)       [default y]

MINIZIP_NG_PATH = $(MINIZIP_NG_ROOT)

VPATH   += $(MINIZIP_NG_PATH)
INCLUDE += -I$(MINIZIP_NG_PATH)
INCLUDE += -I$(ZLIB_ROOT)

CSRCS   += mz_strm.c
CSRCS   += mz_strm_mem.c
CSRCS   += mz_strm_zlib.c
CSRCS   += mz_zip.c
CSRCS   += mz_compat.c
CSRCS   += mz_os_embedded.c

# mz_crypt_mbedtls.c provides mz_crypt_rand() which is always needed:
# mz_os_rand() in mz_os_embedded.c calls mz_crypt_rand() unconditionally,
# and pkcrypt uses it for key initialisation even in ZipCrypto-only mode.
CSRCS  += mz_crypt.c
CSRCS  += mz_crypt_mbedtls.c

# ZipCrypto (PKWARE traditional encryption, ~1 KB)
# mz_zip.c uses #ifdef HAVE_PKCRYPT — must be defined when ZipCrypto is enabled
ifeq ($(CONFIG_MINIZIP_ZIPCRYPTO),y)
CSRCS  += mz_strm_pkcrypt.c
DEFINE += -DHAVE_PKCRYPT
endif
# When ZIPCRYPTO=n: HAVE_PKCRYPT is simply not defined → #ifdef HAVE_PKCRYPT blocks excluded

# WinZip AES (method=99, ~1.4 KB on top of mz_crypt_mbedtls)
# mz_zip.c uses #ifdef HAVE_WZAES — must be defined when WinZip AES is enabled
ifeq ($(CONFIG_MINIZIP_WZAES),y)
CSRCS  += mz_strm_wzaes.c
DEFINE += -DHAVE_WZAES
endif
# When WZAES=n: HAVE_WZAES is simply not defined → #ifdef HAVE_WZAES blocks excluded
