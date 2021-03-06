# ================================================
# pre-create openssl_include_prepared folder:
file(MAKE_DIRECTORY "${DEPS_DIR}/openssl_include_prepared")
file(MAKE_DIRECTORY "${DEPS_DIR}/openssl_include_prepared/openssl")

set(HEADERS "")
FILE(GLOB HEADERS_TMP
	${DEPS_DIR}/openssl/*.h
	${DEPS_DIR}/openssl/ssl/*.h
	)
set(HEADERS ${HEADERS} ${HEADERS_TMP})

FILE(GLOB_RECURSE HEADERS_TMP
	${DEPS_DIR}/openssl/crypto/*.h
	)
set(HEADERS ${HEADERS} ${HEADERS_TMP})

file(COPY ${HEADERS} DESTINATION "${DEPS_DIR}/openssl_include_prepared/openssl")
# ================================================

set(CPPSOURCES "")

FILE(GLOB CPPSOURCES_TMP
	${DEPS_DIR}/openssl/*.h
	${DEPS_DIR}/openssl/ssl/*.c
	${DEPS_DIR}/openssl/ssl/*.h
	${DEPS_DIR}/openssl/ssl/record/*.c
	${DEPS_DIR}/openssl/ssl/record/*.h
	)
set(CPPSOURCES ${CPPSOURCES} ${CPPSOURCES_TMP})

# Include recursively:
FILE(GLOB_RECURSE CPPSOURCES_TMP
	${DEPS_DIR}/openssl/crypto/*.c
	${DEPS_DIR}/openssl/crypto/*.h
	)
set(CPPSOURCES ${CPPSOURCES} ${CPPSOURCES_TMP})

if(WIN32)
	FILE(GLOB CPPSOURCES_TMP
		${DEPS_DIR}/openssl/ms/*.c
		${DEPS_DIR}/openssl/ms/*.h
		)
set(CPPSOURCES ${CPPSOURCES} ${CPPSOURCES_TMP})
endif()

# Exclude some files (could not be compiled for me):
# 1.1.0:
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/conf/cnf_save.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/conf/test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ec/ecp_nistz256_table.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/evp/e_dsa.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/jpake/jpake.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/jpake/jpake_err.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/lhash/lh_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_nyi.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_unix.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_vms.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_win.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_win32.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/LPdir_wince.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md2/md2_dgst.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md2/md2_one.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/o_dir_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ppccap.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/pqueue/pq_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5cfb64.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5ofb64.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5_ecb.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5_enc.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5_skey.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/s390xcap.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sparcv9cap.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/store/str_err.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/store/str_lib.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/store/str_mem.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/store/str_meth.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/threads/mttest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/x509v3/v3conf.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/x509v3/v3prin.c")
# 1.0.2a specific (added later):
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/ssl/ssl_task.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bf/bfspeed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bf/bf_opts.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bio/bss_rtcp.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/exp.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/cast/castopts.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/cast/cast_spd.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/des.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/des_opts.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/read_pwd.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/speed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/idea/idea_spd.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md2/md2.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc2/rc2speed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc4/rc4.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc4/rc4speed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5speed.c")

# Exclude some files (duplicated functions defined or main function defined):
# 1.1.0:
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/ncbc_enc.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/asm/x86_64-gcc.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bf/bf_cbc.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/armcap.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/aes/aes_x86core.c")
# 1.0.2a specific (added later):
# some files with bad unused code inside (bad for gcc, good for msvc):
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/pkcs7/pk7_enc.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/threads/th-lock.c")
# duplicated functions/data:
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/sha1.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md5/md5.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md4/md4.c")
# test files with main function implemented:
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/x509v3/v3nametest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/x509v3/tabtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/whrlpool/wp_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/srp/srptest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/shatest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/sha512t.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/sha256t.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/sha1test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/sha/sha.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rsa/rsa_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ripemd/rmdtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ripemd/rmd160.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc5/rc5test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc4/rc4test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc2/tab.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rc2/rc2test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/rand/randtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/mdc2/mdc2test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md5/md5test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md4/md4test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/md2/md2test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/jpake/jpaketest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/idea/ideatest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/hmac/hmactest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/evp/evp_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/evp/evp_extra_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/engine/enginetest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ecdsa/ecdsatest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ecdh/ecdhtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ec/ectest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ecdsa/ecdsatest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/dsa/dsagen.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/dh/p512.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/dh/p192.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/dh/p1024.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/ecdh/ecdhtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/rpw.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/des/destest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/constant_time_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/cast/casttest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/exptest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/expspeed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/divtest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/bntest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bn/bnspeed.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/bf/bftest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/ssl/ssltest.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/ssl/heartbeat_test.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/ssl/kssl.c")
list(REMOVE_ITEM CPPSOURCES "${DEPS_DIR}/openssl/crypto/dh/dhtest.c")

add_library(openssl STATIC ${CPPSOURCES} ${CPPSOURCES_2} ${CPPSOURCES_3})

target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl)
target_include_directories(openssl PUBLIC ${DEPS_DIR}/openssl/include)
target_include_directories(openssl PUBLIC ${DEPS_DIR}/openssl_include_prepared)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl/crypto)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl/crypto/asn1)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl/crypto/evp)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl/crypto/modes)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/openssl/crypto/include)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/build.projects)
target_include_directories(openssl PRIVATE ${DEPS_DIR}/build.projects/openssl)


target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_DEPRECATED)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_ASM)
target_compile_definitions(openssl PRIVATE -DOPENSSL_THREADS)
target_compile_definitions(openssl PRIVATE -DOPENSSL_USE_APPLINK)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_RC5)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_MD2)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_KRB5)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_JPAKE)
target_compile_definitions(openssl PRIVATE -DOPENSSL_NO_STATIC_ENGINE)

if(WIN32)
	target_compile_definitions(openssl PRIVATE -DOPENSSL_SYSNAME_WIN32)
	target_compile_definitions(openssl PRIVATE -DNO_WINDOWS_BRAINDEATH)
	target_compile_definitions(openssl PRIVATE -DWIN32_LEAN_AND_MEAN)
endif()

if(MSVC)
	target_compile_definitions(openssl PRIVATE -D_CRT_SECURE_NO_DEPRECATE)
	target_compile_definitions(openssl PRIVATE -D_CRT_NONSTDC_NO_WARNINGS)
	target_compile_definitions(openssl PRIVATE -D_WINSOCK_DEPRECATED_NO_WARNINGS)
endif()
