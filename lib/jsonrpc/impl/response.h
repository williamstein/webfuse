#ifndef JSONRPC_IMPL_RESPONSE_H
#define JSONRPC_IMPL_RESPONSE_H

#ifndef __cplusplus
#include <stdbool.h>
#include <stddef.h>
#else
#include <cstddef>
using std::size_t;
#endif

#include <jansson.h>

#ifdef __cplusplus
extern "C" {
#endif

struct jsonrpc_response
{
	json_t * result;	
	json_t * error;
	int id;
};

extern bool jsonrpc_impl_is_response(
    json_t * message);

extern void jsonrpc_impl_response_init(
	struct jsonrpc_response * response,
    json_t * message);

extern void jsonrpc_impl_response_cleanup(
	struct jsonrpc_response * response);

#ifdef __cplusplus
}
#endif

#endif

