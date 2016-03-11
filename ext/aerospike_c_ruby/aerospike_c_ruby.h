#ifndef AEROSPIKE_C_RUBY_H
#define AEROSPIKE_C_RUBY_H

#define AEROSPIKE_C_RUBY_DEBUG

#include <ruby.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#include <aerospike/aerospike.h>
#include <aerospike/aerospike_index.h>
#include <aerospike/aerospike_key.h>
#include <aerospike/aerospike_udf.h>
#include <aerospike/as_bin.h>
#include <aerospike/as_bytes.h>
#include <aerospike/as_error.h>
#include <aerospike/as_config.h>
#include <aerospike/as_key.h>
#include <aerospike/as_operations.h>
#include <aerospike/as_record.h>
#include <aerospike/as_record_iterator.h>
#include <aerospike/as_status.h>
#include <aerospike/as_string.h>
#include <aerospike/as_val.h>
#include <aerospike/as_list.h>
#include <aerospike/as_arraylist.h>
#include <aerospike/as_list_iterator.h>
#include <aerospike/as_map.h>
#include <aerospike/as_hashmap.h>
#include <aerospike/as_hashmap_iterator.h>
#include <aerospike/as_stringmap.h>
#include <aerospike/as_log.h>
#include <aerospike/aerospike_batch.h>
#include <aerospike/aerospike_scan.h>
#include <aerospike/aerospike_query.h>
#include <aerospike/as_ldt.h>
#include <aerospike/as_password.h>


// ---------------------------------------------------
// macros
//
#define RB_FN_ANY() (VALUE(*)(ANYARGS))

#define rb_zero INT2FIX(0)

#define with_header_sym         ID2SYM(rb_intern("with_header"))        // :with_header
#define ttl_sym                 ID2SYM(rb_intern("ttl"))                // :ttl
#define write_sym               ID2SYM(rb_intern("write"))              // :write
#define read_sym                ID2SYM(rb_intern("read"))               // :read
#define increment_sym           ID2SYM(rb_intern("increment"))          // :increment
#define append_sym              ID2SYM(rb_intern("append"))             // :append
#define prepend_sym             ID2SYM(rb_intern("prepend"))            // :prepend
#define touch_sym               ID2SYM(rb_intern("touch"))              // :touch
#define operation_sym           ID2SYM(rb_intern("operation"))          // :operation
#define bin_sym                 ID2SYM(rb_intern("bin"))                // :bin
#define value_sym               ID2SYM(rb_intern("value"))              // :value
#define numeric_sym             ID2SYM(rb_intern("numeric"))            // :numeric
#define string_sym              ID2SYM(rb_intern("string"))             // :string
#define lua_sym                 ID2SYM(rb_intern("lua"))                // :lua
#define name_sym                ID2SYM(rb_intern("name"))               // :name
#define udf_type_sym            ID2SYM(rb_intern("udf_type"))           // :udf_type
#define hash_sym                ID2SYM(rb_intern("hash"))               // :hash
#define size_sym                ID2SYM(rb_intern("size"))               // :size
#define type_sym                ID2SYM(rb_intern("type"))               // :type
#define filter_type_sym         ID2SYM(rb_intern("filter_type"))        // :filter_type
#define eql_sym                 ID2SYM(rb_intern("eql"))                // :eql
#define range_sym               ID2SYM(rb_intern("range"))              // :range
#define min_sym                 ID2SYM(rb_intern("min"))                // :min
#define max_sym                 ID2SYM(rb_intern("max"))                // :max
#define asc_sym                 ID2SYM(rb_intern("asc"))                // :asc
#define desc_sym                ID2SYM(rb_intern("desc"))               // :desc
#define order_sym               ID2SYM(rb_intern("order"))              // :order
#define at_sym                  ID2SYM(rb_intern("at"))                 // :at
;
#define lua_path_sym            ID2SYM(rb_intern("lua_path"))           // :lua_path
#define password_sym            ID2SYM(rb_intern("password"))           // :password
#define logger_sym              ID2SYM(rb_intern("logger"))             // :logger
#define hosts_sym               ID2SYM(rb_intern("hosts"))              // :hosts
#define host_sym                ID2SYM(rb_intern("host"))               // :host
#define port_sym                ID2SYM(rb_intern("port"))               // :port
#define interval_sym            ID2SYM(rb_intern("interval"))           // :interval
#define user_sym                ID2SYM(rb_intern("user"))               // :user
#define thread_pool_size_sym    ID2SYM(rb_intern("thread_pool_size"))   // :thread_pool_size
#define max_threads_sym         ID2SYM(rb_intern("max_threads"))        // :max_threads
#define conn_timeout_sym        ID2SYM(rb_intern("conn_timeout"))       // :conn_timeout
#define fail_not_connected_sym  ID2SYM(rb_intern("fail_not_connected")) // :fail_not_connected
#define commit_level_sym        ID2SYM(rb_intern("commit_level"))       // :commit_level
#define exists_sym              ID2SYM(rb_intern("exists"))             // :exists
#define gen_sym                 ID2SYM(rb_intern("gen"))                // :gen
#define key_sym                 ID2SYM(rb_intern("key"))                // :key
#define retry_sym               ID2SYM(rb_intern("retry"))              // :retry
#define timeout_sym             ID2SYM(rb_intern("timeout"))            // :timeout
#define consistency_level_sym   ID2SYM(rb_intern("consistency_level"))  // :consistency_level
#define replica_sym             ID2SYM(rb_intern("replica"))            // :replica
#define remove_sym              ID2SYM(rb_intern("remove"))             // :remove
#define generation_sym          ID2SYM(rb_intern("generation"))         // :generation
#define policy_sym              ID2SYM(rb_intern("policy"))             // :policy
#define apply_sym               ID2SYM(rb_intern("apply"))              // :apply
#define priority_sym            ID2SYM(rb_intern("priority"))           // :priority
#define query_sym               ID2SYM(rb_intern("query"))              // :query
#define module_sym              ID2SYM(rb_intern("module"))             // :module
#define ldt_proxy_sym           ID2SYM(rb_intern("ldt_proxy"))          // :ldt_proxy
#define geo_json_sym            ID2SYM(rb_intern("geo_json"))           // :geo_json
#define geo_contains_sym        ID2SYM(rb_intern("geo_contains"))       // :geo_contains
#define geo_within_sym          ID2SYM(rb_intern("geo_within"))         // :geo_within
#define geo_sphere_sym          ID2SYM(rb_intern("geo_sphere"))         // :geo_sphere
#define cost_sym                ID2SYM(rb_intern("cost"))               // :cost
#define count_sym               ID2SYM(rb_intern("count"))              // :count
#define operate_sym             ID2SYM(rb_intern("operate"))            // :operate
;

#define list_append_sym         ID2SYM(rb_intern("list_append"))        // :list_append
#define list_set_sym            ID2SYM(rb_intern("list_set"))           // :list_set
#define list_trim_sym           ID2SYM(rb_intern("list_trim"))          // :list_trim
#define list_clear_sym          ID2SYM(rb_intern("list_clear"))         // :list_clear
#define list_size_sym           ID2SYM(rb_intern("list_size"))          // :list_size
#define list_pop_sym            ID2SYM(rb_intern("list_pop"))           // :list_pop
#define list_pop_range_sym      ID2SYM(rb_intern("list_pop_range"))     // :list_pop_range
#define list_pop_range_from_sym ID2SYM(rb_intern("list_pop_range_from"))// :list_pop_range_from
#define list_remove_sym            ID2SYM(rb_intern("list_remove"))           // :list_remove
#define list_remove_range_sym      ID2SYM(rb_intern("list_remove_range"))     // :list_remove_range
#define list_remove_range_from_sym ID2SYM(rb_intern("list_remove_range_from"))// :list_remove_range_from
#define list_get_sym            ID2SYM(rb_intern("list_get"))           // :list_get
#define list_get_range_sym      ID2SYM(rb_intern("list_get_range"))     // :list_get_range
#define list_get_range_from_sym ID2SYM(rb_intern("list_get_range_from"))// :list_get_range_from
;

#define as_val_int_2_val(val) LONG2FIX( as_integer_get( as_integer_fromval(val) ) )         //(int)    as_val * -> VALUE
#define as_val_str_2_val(val) rb_str_new2( as_string_tostring( as_string_fromval(val) ) )   //(string) as_val * -> VALUE
#define as_val_dbl_2_val(val) rb_float_new( as_double_get( as_double_fromval(val) ) )       //(double) as_val * -> VALUE
#define rb_ary_len_int(ary) FIX2INT( rb_funcall(ary, rb_intern("length"), 0) )              //(int)    VALUE -> int
#define rb_ary_len_long(ary) FIX2LONG( rb_funcall(ary, rb_intern("length"), 0) )            //(long)   VALUE -> long

#define destroy_query(query) as_query_destroy(query); xfree(query)

#define rb_foreach_ary_int(ary) for(int i = 0; i < rb_ary_len_int(ary); ++i)
#define rb_foreach_ary_long(ary) for(long i = 0; i < rb_ary_len_long(ary); ++i)

#define RB_LLIST_WORAROUND_BIN rb_str_new2("_rblliststat_")
;

#define rb_mJSON() rb_const_get(rb_cObject, rb_intern("JSON"))

#define DEFAULT_GEO_JSON_ELSE "GEO_JSON_NULL_VALUE"
#define RB_COORDINATES_STR rb_str_new2("coordinates")
#define RB_POLYGON_STR rb_str_new2("Polygon")
#define RB_POINT_STR rb_str_new2("Point")
#define RB_CIRCLE_STR rb_str_new2("AeroCircle")
;

// ---------------------------------------------------
// definitions
//
void init_aerospike_c_client(VALUE AerospikeC);     // client.c
void init_aerospike_c_key   (VALUE AerospikeC);     // key.c
void init_aerospike_c_record(VALUE AerospikeC);     // record.c
void init_aerospike_c_udf_task(VALUE AerospikeC);   // udf_task.c
void init_aerospike_c_scan_task(VALUE AerospikeC);  // scan_task.c
void init_aerospike_c_query(VALUE AerospikeC);      // query.c
void init_aerospike_c_policy(VALUE AerospikeC);     // policy.c
void init_aerospike_c_llist(VALUE AerospikeC);      // llist.c
void init_aerospike_c_ldt_proxy(VALUE AerospikeC);  // ldt_proxy.c
void init_aerospike_c_exceptions(AerospikeC);       // exceptions.c
void init_aerospike_c_geo_json(VALUE AerospikeC);   // geo_json.c
void init_aerospike_c_password(VALUE AerospikeC);   // password.c

// query_task.c
void init_aerospike_c_query_task(VALUE AerospikeC);
void query_task_deallocate(as_query * query);

// index_task.c
void init_aerospike_c_index_task(VALUE AerospikeC);
void index_task_deallocate(as_index_task * task);

// utils.c
void log_debug (const char * msg);
void log_info  (const char * msg);
void log_warn  (const char * msg);
void log_error (const char * msg);
void log_fatal (const char * msg);

void log_info_with_time(const char * msg, struct timeval * tm);
void log_info_with_time_v(const char * msg, struct timeval * tm, VALUE val);
void log_info_with_time_v2(const char * msg, struct timeval * tm, VALUE val, VALUE val2);

void start_timing(struct timeval * tm);

aerospike *  get_client_struct(VALUE client);
as_key *     get_key_struct(VALUE key);
as_record *  get_record_struct(VALUE rec);
as_geojson * get_geo_json_struct(VALUE rb_geo);

void raise_as_err(as_error err);

VALUE record2hash(as_record * rec);
void  hash2record(VALUE hash, VALUE rec);

as_arraylist * array2as_list(VALUE ary);
VALUE          as_list2array(as_arraylist * list);

char ** rb_array2inputArray(VALUE ary);
void    inputArray_destroy(char ** inputArray);

char ** rb_array2bin_names(VALUE ary);
void    bin_names_destroy(char ** bin_names, long len);

VALUE  value_to_s(VALUE val);
char * value_to_s_cstr(VALUE val);
char * val_inspect(VALUE val);

VALUE bool2rb_bool(bool val);
bool  rb_bool2bool(VALUE val);

VALUE    as_val2rb_val(as_val * value);
as_val * rb_val2as_val(VALUE value);

void as_val_free(as_val * value);

const char * as_val_type_as_str(as_val * val);
const char * rb_val_type_as_str(VALUE value);

as_query * query_obj2as_query(VALUE query_obj);

as_hashmap * hash2as_hashmap(VALUE hash);
VALUE        as_hashmap2hash(as_hashmap * map);

void * rb_policy2as_policy(VALUE rb_policy);
void * get_policy(VALUE options);

VALUE enable_rb_GC();
VALUE disable_rb_GC();

VALUE as_geojson_2_val(as_geojson * geo);

as_integer * rb_copy_as_integer(as_integer * value);
as_integer * rb_copy_as_integer_from_val(as_val * value);
as_double * rb_copy_as_double(as_double * value);
as_double * rb_copy_as_double_from_val(as_val * value);
as_string * rb_copy_as_string(as_string * value);
as_string * rb_copy_as_string_from_val(as_val * value);
as_geojson * rb_copy_as_geojson(as_geojson * value);
as_geojson * rb_copy_as_geojson_from_val(as_val * value);
as_arraylist * rb_copy_as_arraylist(as_arraylist * value);
as_arraylist * rb_copy_as_arraylist_from_val(as_val * value);
as_hashmap * rb_copy_as_hashmap(as_hashmap * value);
as_hashmap * rb_copy_as_hashmap_from_val(as_val * value);
as_val * rb_copy_as_val(as_val * value);

as_record * rb_copy_as_record(as_record * record);

as_operations * rb_operations2as_operations(VALUE operations);

// ---------------------------------------------------
//
// extern variables
//
extern VALUE AerospikeC;
extern VALUE Client;

extern VALUE Record;
extern VALUE Key;
extern VALUE GeoJson;

extern VALUE Logger;

extern VALUE IndexTask;
extern VALUE UdfTask;
extern VALUE ScanTask;
extern VALUE QueryTask;

extern VALUE Query;

extern VALUE Policy;
extern VALUE WritePolicy;
extern VALUE ReadPolicy;
extern VALUE RemovePolicy;
extern VALUE ApplyPolicy;
extern VALUE QueryPolicy;
extern VALUE OperatePolicy;

extern VALUE Llist;
extern VALUE LdtProxy;

extern VALUE AsError;
extern VALUE MemoryError;
extern VALUE ParseError;
extern VALUE OptionError;
extern VALUE PasswordEngine;

extern pthread_mutex_t G_CALLBACK_MUTEX;

#endif // AEROSPIKE_C_RUBY_H