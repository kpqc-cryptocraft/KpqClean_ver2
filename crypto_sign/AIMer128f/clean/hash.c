// SPDX-License-Identifier: MIT

#include <stdint.h>
#include "hash.h"
#include "portable_endian.h"

void hash_init(hash_instance* ctx)
{
  shake128_inc_init(ctx);
}

void hash_init_prefix(hash_instance* ctx, const uint8_t prefix)
{
  hash_init(ctx);
  hash_update(ctx, &prefix, sizeof(prefix));
}

void hash_update(hash_instance* ctx, const uint8_t* data, size_t data_byte_len)
{
  shake128_inc_absorb(ctx, data, data_byte_len);
}

void hash_update_GF(hash_instance* ctx, const GF g)
{
  uint8_t buf[AIM2_NUM_BYTES_FIELD];
  GF_to_bytes(g, buf);
  hash_update(ctx, buf, AIM2_NUM_BYTES_FIELD);
}

void hash_final(hash_instance* ctx)
{
  shake128_inc_finalize(ctx);
}

void hash_squeeze(hash_instance* ctx, uint8_t* buffer, size_t buffer_len)
{
  shake128_inc_squeeze(buffer, buffer_len, ctx);
}

void hash_squeeze_GF(hash_instance* ctx, GF g)
{
  uint8_t buf[AIM2_NUM_BYTES_FIELD];
  shake128_inc_squeeze(buf, AIM2_NUM_BYTES_FIELD, ctx);
  GF_from_bytes(buf, g);
}
