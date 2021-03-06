/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
#ifndef __UI_H__
#define __UI_H__

#include <time.h>
#include "../base/newzpost.h"

extern time_t post_delay;
extern boolean verbosity;
extern Buff * tmpdir_ptr;

extern pthread_rwlock_t *progress_lock;

void ui_tmpdir_create_failed(const char *dirname, int error);

void ui_sfv_gen_start();
void ui_sfv_gen_done(const char *filename);
void ui_sfv_gen_error(const char *filename, int error);

void ui_crc_start();
void ui_crc_done();
void ui_crc_error(const char *filename, int error);

void ui_par_gen_start();
void ui_par_gen_error();
void ui_par_file_add_done(const char *filename);
void ui_par_volume_create_start();
void ui_par_volume_created(const char *filename);

void ui_post_start(newzpost_data *data, SList *file_list, SList *parfiles);

void ui_socket_connect_start(newzpost_threadinfo *tinfo, const char *servername);
void ui_socket_connect_failed(newzpost_threadinfo *tinfo, int retval);
void ui_socket_connect_done(newzpost_threadinfo *tinfo);

void ui_nntp_logon_start(newzpost_threadinfo *tinfo, const char *servername);
void ui_nntp_logon_done(newzpost_threadinfo *tinfo);
void ui_nntp_authentication_failed(newzpost_threadinfo *tinfo, const char *response);
void ui_nntp_command_issued(newzpost_threadinfo *tinfo, const char *command);
void ui_nntp_server_response(newzpost_threadinfo *tinfo, const char *response);
void ui_nntp_unknown_response(newzpost_threadinfo *tinfo, const char *response);

void ui_posting_file_start(newzpost_data *data, file_entry *filedata);
void ui_posting_file_done(newzpost_data *data, file_entry *filedata);

int ui_chunk_posted(newzpost_threadinfo *tinfo, long chunksize, long bytes_written);

void ui_posting_part_start(newzpost_threadinfo *tinfo, file_entry *filedata, int part_number);

void ui_posting_part_done(newzpost_threadinfo *tinfo, file_entry *filedata, int part_number);

void ui_nntp_posting_failed(newzpost_threadinfo *tinfo, const char *response);
void ui_nntp_posting_retry(newzpost_threadinfo *tinfo);

void ui_post_done();

void ui_generic_error(int error);

void ui_posting_too_many_failures(newzpost_threadinfo *tinfo);
void ui_connecting_too_many_failures(newzpost_threadinfo *tinfo);

void ui_socket_error(int error);

#endif /* __UI_H__ */
