MBEDTLS_PORT = $(MBEDTLS_BASE)/port
MBEDTLS_PORT_SHA = $(MBEDTLS_PORT)/sha
MBEDTLS_LIB	= $(MBEDTLS_BASE)/mbedtls
MBEDTLS_LIB_SRC	= $(MBEDTLS_LIB)/library

MBEDTLS_PORT_INC = $(MBEDTLS_PORT)/include
MBEDTLS_LIB_INC	= $(MBEDTLS_LIB)/include
MBEDTLS_BASE_INC = $(MBEDTLS_BASE)/include

INCLUDE	+= -I$(MBEDTLS_PORT_INC)
INCLUDE	+= -I$(MBEDTLS_LIB_INC)
INCLUDE	+= -I$(MBEDTLS_BASE_INC)

DEFINE += -DMBEDTLS_CONFIG_FILE=\"config-nrc-basic.h\"
DEFINE += -DSUPPORT_MBEDTLS

VPATH	+= $(MBEDTLS_BASE)
VPATH	+= $(MBEDTLS_PORT)
VPATH	+= $(MBEDTLS_PORT_SHA)
VPATH	+= $(MBEDTLS_LIB_SRC)

DEFINE	+= -DNRC_MBEDTLS -DCONFIG_MBEDTLS_TLS_ENABLED

# crypto
CRYPTO_SRCS	+= \
    aes.c \
    aesni.c \
    aesce.c \
    aria.c \
    asn1parse.c \
    asn1write.c \
    base64.c \
    bignum.c \
    bignum_core.c \
    bignum_mod.c \
    bignum_mod_raw.c \
    block_cipher.c \
    camellia.c \
    ccm.c \
    chacha20.c \
    chachapoly.c \
    cipher.c \
    cipher_wrap.c \
    cmac.c \
    constant_time.c \
    ctr_drbg.c \
    des.c \
    dhm.c \
    ecdh.c \
    ecdsa.c \
    ecjpake.c \
    ecp.c \
    ecp_curves.c \
    ecp_curves_new.c \
    entropy.c \
    entropy_poll.c \
    error.c \
    gcm.c \
    hkdf.c \
    hmac_drbg.c \
    lmots.c \
    lms.c \
    md.c \
    md5.c \
    memory_buffer_alloc.c \
    nist_kw.c \
    oid.c \
    padlock.c \
    pem.c \
    pk.c \
    pk_ecc.c \
    pk_wrap.c \
    pkcs12.c \
    pkcs5.c \
    pkparse.c \
    pkwrite.c \
    platform.c \
    platform_util.c \
    poly1305.c \
    psa_crypto.c \
    psa_crypto_aead.c \
    psa_crypto_cipher.c \
    psa_crypto_client.c \
    psa_crypto_driver_wrappers_no_static.c \
    psa_crypto_ecp.c \
    psa_crypto_ffdh.c \
    psa_crypto_hash.c \
    psa_crypto_mac.c \
    psa_crypto_pake.c \
    psa_crypto_rsa.c \
    psa_crypto_se.c \
    psa_crypto_slot_management.c \
    psa_crypto_storage.c \
    psa_its_file.c \
    psa_util.c \
    ripemd160.c \
    rsa.c \
    rsa_alt_helpers.c \
    sha3.c \
    threading.c \
    timing.c \
    version.c \
    version_features.c \
    # This line is intentionally left blank

# x509
X509_SRCS += \
    x509.c \
    x509_create.c \
    x509_crl.c \
    x509_crt.c \
    x509_csr.c \
    x509write_crt.c \
    x509write_csr.c \
    pkcs7.c \
    # This line is intentionally left blank

# tls
TLS_SRCS += \
    debug.c \
    mps_reader.c \
    mps_trace.c \
    net_sockets.c \
    ssl_cache.c \
    ssl_ciphersuites.c \
    ssl_client.c \
    ssl_cookie.c \
    ssl_debug_helpers_generated.c \
    ssl_msg.c \
    ssl_ticket.c \
    ssl_tls.c \
    ssl_tls12_client.c \
    ssl_tls12_server.c \
    ssl_tls13_keys.c \
    ssl_tls13_client.c \
    ssl_tls13_server.c \
    ssl_tls13_generic.c \
    # This line is intentionally left blank

# porting layer
PORTING_SRCS += \
	timing_alt.c

ifeq ($(CONFIG_USE_HW_SECURITY_ACC_SHA),y)
CRYPTO_SRCS += sha1_hw.c
CRYPTO_SRCS += sha256_hw.c
CRYPTO_SRCS += sha512_hw.c
else
CRYPTO_SRCS += sha1.c
CRYPTO_SRCS += sha256.c
CRYPTO_SRCS += sha512.c
endif # CONFIG_USE_HW_SECURITY_ACC_SHA

ifeq ($(CONFIG_USE_HW_SECURITY_ACC_BN),y)
CRYPTO_SRCS += bignum_hw.c
endif # CONFIG_USE_HW_SECURITY_ACC_BN

CSRCS += $(CRYPTO_SRCS)
CSRCS += $(X509_SRCS)
CSRCS += $(PORTING_SRCS)
ifeq ($(CONFIG_LWIP), y)
CSRCS += $(TLS_SRCS)
endif #CONFIG_LWIP
