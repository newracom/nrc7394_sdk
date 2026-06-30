/* multi_role_proto.h */

#pragma once

#include <stdint.h>

#ifndef NRC_APP_NAME_MAX
#define NRC_APP_NAME_MAX 16
#endif

/* Control + Data ports */
#define NRC_FOTA_CTRL_PORT	60000	/* UDP: directory register/status, TCP: list query */
#define NRC_FOTA_DATA_PORT	60010	/* TCP: firmware transfer */

/* Magic values */
#define NRC_MAGIC_DIR		0x4E524344	/* 'NRCD' */
#define NRC_MAGIC_FOTA		0x4E524346	/* 'NRCF' */

/* ---------------- Directory message types ---------------- */

typedef enum {
	NRC_DIR_MSG_REGISTER = 1,
	NRC_DIR_MSG_STATUS,
	NRC_DIR_MSG_GET_LIST,
	NRC_DIR_MSG_LIST_RESP,
	NRC_DIR_MSG_ACK,
	NRC_DIR_MSG_HEARTBEAT
} nrc_dir_msg_type_t;

/* ---------------- FOTA message types ---------------- */

typedef enum {
	NRC_FOTA_MSG_START = 1,
	NRC_FOTA_MSG_CHUNK,
	NRC_FOTA_MSG_END,
	NRC_FOTA_MSG_REBOOT,
	NRC_FOTA_MSG_ACK
} nrc_fota_msg_type_t;

/* ---------------- FOTA status ---------------- */

typedef enum {
	NRC_FOTA_STATUS_IDLE = 0,
	NRC_FOTA_STATUS_IN_PROGRESS,
	NRC_FOTA_STATUS_READY_TO_REBOOT,
	NRC_FOTA_STATUS_REBOOTING,
	NRC_FOTA_STATUS_DONE,
	NRC_FOTA_STATUS_FAILED
} nrc_fota_status_t;

/* ---------------- Common directory header ---------------- */

typedef struct __attribute__((packed)) {
	uint32_t	magic;		/* NRC_MAGIC_DIR */
	uint16_t	type;		/* nrc_dir_msg_type_t */
	uint16_t	len;		/* total bytes including header */
	uint32_t	seq;
} nrc_dir_hdr_t;

/* ---------------- Directory REGISTER ----------------
 * Node -> Root (UDP)
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;

	uint32_t	node_id;
	uint8_t		mac[6];
	uint8_t		parent_mac[6];

	uint8_t		role;
	uint8_t		hop;
	uint16_t	rsvd0;

	uint32_t	ipv4_addr;			/* NBO */
	uint32_t	fw_ver_packed;			/* app-defined packed ver */
	char		app_name[NRC_APP_NAME_MAX];	/* null-terminated */
} nrc_dir_register_t;

/* ---------------- Directory STATUS ----------------
 * Node -> Root (UDP)
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;

	uint32_t	node_id;
	uint8_t		mac[6];

	uint32_t	session_id;
	uint8_t		fota_status;			/* nrc_fota_status_t */
	uint8_t		progress_percent;		/* 0..100 */
	uint16_t	rsvd0;

	uint32_t	fw_ver_packed;			/* new ver after reboot (if known) */
} nrc_dir_status_t;

/* ---------------- Directory HEARTBEAT ----------------
 * Node -> Root (UDP)
 * Lightweight liveness signal to support fast offline detection.
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;

	uint8_t		mac[6];
	uint8_t		rsvd0[2];

	uint32_t	ipv4_addr;			/* NBO */
	uint32_t	uptime_ms;
} nrc_dir_heartbeat_t;

/* ---------------- Directory GET_LIST ----------------
 * Host -> Root (TCP)
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;
	uint16_t	max_nodes;			/* host-side cap; 0 = default */
	uint16_t	rsvd0;
} nrc_dir_get_list_t;

/* ---------------- Directory NODE_INFO ----------------
 * Root -> Host payload element
 */
typedef struct __attribute__((packed)) {
	uint32_t	node_id;
	uint8_t		mac[6];
	uint8_t		parent_mac[6];

	uint8_t		role;
	uint8_t		hop;
	uint8_t		online;
	uint8_t		rsvd0;

	uint32_t	ipv4_addr;			/* NBO */
	uint32_t	fw_ver_packed;

	uint32_t	session_id;
	uint8_t		fota_status;
	uint8_t		progress_percent;
	uint16_t	rsvd1;
	char		app_name[NRC_APP_NAME_MAX];	/* null-terminated */
} nrc_dir_node_info_t;

/* ---------------- Directory LIST_RESP ----------------
 * Root -> Host (TCP)
 * Followed by count * nrc_dir_node_info_t
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;

	uint16_t	count;
	uint16_t	rsvd0;
	uint32_t	dir_version;

	uint8_t		payload[];			/* node infos */
} nrc_dir_list_resp_t;

/* ---------------- FOTA wire header ---------------- */

typedef struct __attribute__((packed)) {
	uint32_t	magic;		/* NRC_MAGIC_FOTA */
	uint16_t	type;		/* nrc_fota_msg_type_t */
	uint16_t	len;		/* total bytes including header */
	uint32_t	seq;
	uint32_t	session_id;
} nrc_fota_hdr_t;

typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;
	uint32_t	fw_ver_packed;
	uint32_t	fw_len;
	uint32_t	fw_crc;
	uint32_t	chunk_size;
	char		target_app_name[NRC_APP_NAME_MAX];	/* required match on receiver */
} nrc_fota_start_t;

typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;
	uint32_t	offset;
	uint16_t	payload_len;
	uint16_t	rsvd0;
	uint8_t		payload[];
} nrc_fota_chunk_t;

/* ---------------- Directory ACK ----------------
 * Root -> Node (UDP)
 * Used for reliability on NRC_DIR_MSG_REGISTER (and optionally others).
 */
typedef struct __attribute__((packed)) {
	nrc_dir_hdr_t	hdr;
	uint16_t	acked_type;     /* nrc_dir_msg_type_t */
	uint16_t	code;           /* 0 = OK */
	uint32_t	dir_version;    /* root directory version */
	uint32_t	node_id;
	uint8_t		mac[6];
	uint8_t		rsvd0[2];
} nrc_dir_ack_t;

/* ---------------- FOTA ACK ----------------
 * Server -> Client (TCP)
 * Application-level flow control: server sends ACK after chunk is written.
 */
typedef struct __attribute__((packed)) {
	nrc_fota_hdr_t	hdr;            /* type = NRC_FOTA_MSG_ACK */
	uint32_t	written;         /* total bytes written so far */
	uint32_t	next_offset;     /* next expected offset */
	uint8_t		progress_percent;/* 0..100 */
	uint8_t		status;         /* nrc_fota_status_t */
	uint16_t	rsvd0;
} nrc_fota_ack_t;
