/* Automatically generated nanopb header */
/* Generated by nanopb-1.0.0-dev */

#ifndef PB_DATA_TYPE_PB_H_INCLUDED
#define PB_DATA_TYPE_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Struct definitions */
typedef struct _sensor_data_t {
    uint32_t sensor_id;
    uint32_t function_code;
    uint64_t data;
} sensor_data_t;


#ifdef __cplusplus
extern "C" {
#endif

/* Initializer values for message structs */
#define sensor_data_t_init_default               {0, 0, 0}
#define sensor_data_t_init_zero                  {0, 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define sensor_data_t_sensor_id_tag              1
#define sensor_data_t_function_code_tag          2
#define sensor_data_t_data_tag                   3

/* Struct field encoding specification for nanopb */
#define sensor_data_t_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UINT32,   sensor_id,         1) \
X(a, STATIC,   SINGULAR, UINT32,   function_code,     2) \
X(a, STATIC,   SINGULAR, UINT64,   data,              3)
#define sensor_data_t_CALLBACK NULL
#define sensor_data_t_DEFAULT NULL

extern const pb_msgdesc_t sensor_data_t_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define sensor_data_t_fields &sensor_data_t_msg

/* Maximum encoded size of messages (where known) */
#define DATA_TYPE_PB_H_MAX_SIZE                  sensor_data_t_size
#define sensor_data_t_size                       23

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
