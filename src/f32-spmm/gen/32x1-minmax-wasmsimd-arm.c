// Auto-generated file. Do not edit!
//   Template: src/f32-spmm/wasmsimd.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/spmm.h>


void xnn_f32_spmm_minmax_ukernel_32x1__wasmsimd_arm(
    uint32_t batch_size,
    uint32_t output_channels,
    const float*restrict input,
    const float*restrict weights,
    const int32_t*restrict widx_dmap,
    const uint32_t*restrict nidx_nnzmap,
    float*restrict output,
    const union xnn_f32_minmax_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch_size != 0);

  const uintptr_t output_stride = 1 * batch_size * sizeof(float);
  const v128_t vmin = wasm_v32x4_load_splat(&params->scalar.min);
  const v128_t vmax = wasm_v32x4_load_splat(&params->scalar.max);
  size_t n = batch_size;
  while XNN_LIKELY(n >= 32) {
    const float*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    size_t c = output_channels;
    do {
      uint32_t nnz = *nnzmap++;
      v128_t vacc0123 = wasm_v32x4_load_splat(w); w += 1;
      v128_t vacc4567 = vacc0123;
      v128_t vacc89AB = vacc0123;
      v128_t vaccCDEF = vacc0123;
      v128_t vaccGHIJ = vacc0123;
      v128_t vaccKLMN = vacc0123;
      v128_t vaccOPQR = vacc0123;
      v128_t vaccSTUV = vacc0123;
      if XNN_LIKELY(nnz != 0) {
        do {
          const intptr_t diff = *dmap++;
          const v128_t vi0123 = wasm_v128_load(input);
          const v128_t vi4567 = wasm_v128_load(input + 4);
          const v128_t vi89AB = wasm_v128_load(input + 8);
          const v128_t viCDEF = wasm_v128_load(input + 12);
          const v128_t viGHIJ = wasm_v128_load(input + 16);
          const v128_t viKLMN = wasm_v128_load(input + 20);
          const v128_t viOPQR = wasm_v128_load(input + 24);
          const v128_t viSTUV = wasm_v128_load(input + 28);
          input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
          const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
          vacc0123 = wasm_f32x4_add(vacc0123, wasm_f32x4_mul(vi0123, vw));
          vacc4567 = wasm_f32x4_add(vacc4567, wasm_f32x4_mul(vi4567, vw));
          vacc89AB = wasm_f32x4_add(vacc89AB, wasm_f32x4_mul(vi89AB, vw));
          vaccCDEF = wasm_f32x4_add(vaccCDEF, wasm_f32x4_mul(viCDEF, vw));
          vaccGHIJ = wasm_f32x4_add(vaccGHIJ, wasm_f32x4_mul(viGHIJ, vw));
          vaccKLMN = wasm_f32x4_add(vaccKLMN, wasm_f32x4_mul(viKLMN, vw));
          vaccOPQR = wasm_f32x4_add(vaccOPQR, wasm_f32x4_mul(viOPQR, vw));
          vaccSTUV = wasm_f32x4_add(vaccSTUV, wasm_f32x4_mul(viSTUV, vw));
        } while (--nnz != 0);
      }
      v128_t vout0123 = wasm_f32x4_min(vacc0123, vmax);
      v128_t vout4567 = wasm_f32x4_min(vacc4567, vmax);
      v128_t vout89AB = wasm_f32x4_min(vacc89AB, vmax);
      v128_t voutCDEF = wasm_f32x4_min(vaccCDEF, vmax);
      v128_t voutGHIJ = wasm_f32x4_min(vaccGHIJ, vmax);
      v128_t voutKLMN = wasm_f32x4_min(vaccKLMN, vmax);
      v128_t voutOPQR = wasm_f32x4_min(vaccOPQR, vmax);
      v128_t voutSTUV = wasm_f32x4_min(vaccSTUV, vmax);
      vout0123 = wasm_f32x4_max(vout0123, vmin);
      vout4567 = wasm_f32x4_max(vout4567, vmin);
      vout89AB = wasm_f32x4_max(vout89AB, vmin);
      voutCDEF = wasm_f32x4_max(voutCDEF, vmin);
      voutGHIJ = wasm_f32x4_max(voutGHIJ, vmin);
      voutKLMN = wasm_f32x4_max(voutKLMN, vmin);
      voutOPQR = wasm_f32x4_max(voutOPQR, vmin);
      voutSTUV = wasm_f32x4_max(voutSTUV, vmin);
      wasm_v128_store(output, vout0123);
      wasm_v128_store(output + 4, vout4567);
      wasm_v128_store(output + 8, vout89AB);
      wasm_v128_store(output + 12, voutCDEF);
      wasm_v128_store(output + 16, voutGHIJ);
      wasm_v128_store(output + 20, voutKLMN);
      wasm_v128_store(output + 24, voutOPQR);
      wasm_v128_store(output + 28, voutSTUV);
      output = (float*restrict) ((uintptr_t) output + output_stride);
    } while (--c != 0);
    output -= batch_size * output_channels;
    output += 32;
    input += 32;
    n -= 32;
  }
  if XNN_UNLIKELY(n != 0) {
    if (n & 16) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        v128_t vacc0123 = wasm_v32x4_load_splat(w); w += 1;
        v128_t vacc4567 = vacc0123;
        v128_t vacc89AB = vacc0123;
        v128_t vaccCDEF = vacc0123;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const v128_t vi0123 = wasm_v128_load(input);
            const v128_t vi4567 = wasm_v128_load(input + 4);
            const v128_t vi89AB = wasm_v128_load(input + 8);
            const v128_t viCDEF = wasm_v128_load(input + 12);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
            vacc0123 = wasm_f32x4_add(vacc0123, wasm_f32x4_mul(vi0123, vw));
            vacc4567 = wasm_f32x4_add(vacc4567, wasm_f32x4_mul(vi4567, vw));
            vacc89AB = wasm_f32x4_add(vacc89AB, wasm_f32x4_mul(vi89AB, vw));
            vaccCDEF = wasm_f32x4_add(vaccCDEF, wasm_f32x4_mul(viCDEF, vw));
          } while (--nnz != 0);
        }
        v128_t vout0123 = wasm_f32x4_min(vacc0123, vmax);
        v128_t vout4567 = wasm_f32x4_min(vacc4567, vmax);
        v128_t vout89AB = wasm_f32x4_min(vacc89AB, vmax);
        v128_t voutCDEF = wasm_f32x4_min(vaccCDEF, vmax);
        vout0123 = wasm_f32x4_max(vout0123, vmin);
        vout4567 = wasm_f32x4_max(vout4567, vmin);
        vout89AB = wasm_f32x4_max(vout89AB, vmin);
        voutCDEF = wasm_f32x4_max(voutCDEF, vmin);
        wasm_v128_store(output, vout0123);

        wasm_v128_store(output + 4, vout4567);
        wasm_v128_store(output + 8, vout89AB);
        wasm_v128_store(output + 12, voutCDEF);
        output = (float*restrict) ((uintptr_t) output + output_stride);
      } while (--c != 0);
      output -= batch_size * output_channels;
      output += 16;
      input += 16;
    }
    if (n & 8) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        v128_t vacc0123 = wasm_v32x4_load_splat(w); w += 1;
        v128_t vacc4567 = vacc0123;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const v128_t vi0123 = wasm_v128_load(input);
            const v128_t vi4567 = wasm_v128_load(input + 4);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
            vacc0123 = wasm_f32x4_add(vacc0123, wasm_f32x4_mul(vi0123, vw));
            vacc4567 = wasm_f32x4_add(vacc4567, wasm_f32x4_mul(vi4567, vw));
          } while (--nnz != 0);
        }
        v128_t vout0123 = wasm_f32x4_min(vacc0123, vmax);
        v128_t vout4567 = wasm_f32x4_min(vacc4567, vmax);
        vout0123 = wasm_f32x4_max(vout0123, vmin);
        vout4567 = wasm_f32x4_max(vout4567, vmin);
        wasm_v128_store(output, vout0123);

        wasm_v128_store(output + 4, vout4567);
        output = (float*restrict) ((uintptr_t) output + output_stride);
      } while (--c != 0);
      output -= batch_size * output_channels;
      output += 8;
      input += 8;
    }
    if (n & 4) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        v128_t vacc0123 = wasm_v32x4_load_splat(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const v128_t vi0123 = wasm_v128_load(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
            vacc0123 = wasm_f32x4_add(vacc0123, wasm_f32x4_mul(vi0123, vw));
          } while (--nnz != 0);
        }
        v128_t vout0123 = wasm_f32x4_min(vacc0123, vmax);
        vout0123 = wasm_f32x4_max(vout0123, vmin);
        wasm_v128_store(output, vout0123);

        output = (float*restrict) ((uintptr_t) output + output_stride);
      } while (--c != 0);
      output -= batch_size * output_channels;
      output += 4;
      input += 4;
    }
    if (n & 2) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        v128_t vacc01 = wasm_v32x4_load_splat(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const v128_t vi01 = wasm_v64x2_load_splat(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
            vacc01 = wasm_f32x4_add(vacc01, wasm_f32x4_mul(vi01, vw));
          } while (--nnz != 0);
        }
        v128_t vout01 = wasm_f32x4_min(vacc01, vmax);
        vout01 = wasm_f32x4_max(vout01, vmin);
        *((double*) output) = wasm_f64x2_extract_lane(vout01, 0);

        output = (float*restrict) ((uintptr_t) output + output_stride);
      } while (--c != 0);
      output -= batch_size * output_channels;
      output += 2;
      input += 2;
    }
    if (n & 1) {
      const float*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t c = output_channels;
      do {
        uint32_t nnz = *nnzmap++;
        v128_t vacc0 = wasm_v32x4_load_splat(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const v128_t vi0 = wasm_v32x4_load_splat(input);
            input = (const float*restrict) ((uintptr_t) input + (uintptr_t) diff);
            const v128_t vw = wasm_v32x4_load_splat(w); w += 1;
            vacc0 = wasm_f32x4_add(vacc0, wasm_f32x4_mul(vi0, vw));
          } while (--nnz != 0);
        }
        v128_t vout0 = wasm_f32x4_min(vacc0, vmax);
        vout0 = wasm_f32x4_max(vout0, vmin);
        *output = wasm_f32x4_extract_lane(vout0, 0);

        output = (float*restrict) ((uintptr_t) output + output_stride);
      } while (--c != 0);
      output -= batch_size * output_channels;
      output += 1;
      input += 1;
    }
  }
}
