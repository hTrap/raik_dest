#include "riak.h"
#include "riak-parser.h"
#include "plugin.h"
#include "messages.h"
#include "misc.h"
#include "stats/stats-registry.h"
#include "logqueue.h"
#include "driver.h"
#include "plugin-types.h"
#include "logthrdestdrv.h"

typedef enum
{
  RIAK_BUCKET_MODE_STORE,
  RIAK_BUCKET_MODE_SET
} RiakBucketMode;

typedef struct
{
  LogThrDestDriver super;
  LogTemplateOptions template_options;
  char *host;
  int port;

  LogTemplate *bucket;
  char *bucket_type;
  LogTemplate *key;
  LogTemplate *value;

  RiakBucketMode mode;

  riak_client_t *client;
} RiakDestDriver;

/*
 * Configuration
 */

void
riak_dd_set_host(LogDriver *d, char *host)
{
  RiakDestDriver *self = (RiakDestDriver *)d;

  free(self->host);
  self->host = strdup(host);
}

void
riak_dd_set_port(LogDriver *d, int port)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  self->port = port;
}

void
riak_dd_set_bucket(LogDriver *d, LogTemplate *bucket)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  
  log_template_unref(self->bucket);
  self->bucket = log_template_ref(bucket);
  
}

void
riak_dd_set_mode(LogDriver *d, char *mode)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  if(strcmp(mode,"store") == 0)
    self->mode = RIAK_BUCKET_MODE_STORE;
  else if(strcmp(mode, "set") == 0)
    self->mode = RIAK_BUCKET_MODE_SET;
}

void 
riak_dd_set_type(LogDriver *d, char *type)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  free(self->bucket_type);
  self->bucket_type = strdup(type);

void
riak_dd_set_key(LogDriver *d, LogTemplate *key)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  
  log_template_unref(self->key);
  self->key = log_template_ref(key);
  
}

void
riak_dd_set_value(LogDriver *d, LogTemplate *value)
{
  RiakDestDriver *self = (RiakDestDriver *)d;
  
  log_template_unref(self->value);
  self->value = log_template_ref(value);
}


LogTemplateOptions *
riak_dd_get_template_options(LogDriver *d)
{
  RiakDriver *self = (RiakDriver *)d;

  return &self->template_options;
}

/*
 * Utilities
 */


