#pragma once

#define MBEDTLS_HKDF_C
#define MBEDTLS_X509_CREATE_C
#define MBEDTLS_X509_CSR_WRITE_C

#if defined(CONFIG_ATM_AES_HW) || defined(CONFIG_ATM_SHA2_HW)
#include "atm34-mbedtls-config.h"
#endif
