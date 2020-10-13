// Auto-generated file. Do not edit!
//   Template: src/f32-sigmoid/sse-lut64-p2-div.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <emmintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


extern XNN_INTERNAL const float xnn_table_exp2minus_k_over_64[64];

void xnn_f32_sigmoid_ukernel__sse2_lut64_p2_div_x24(
    size_t n,
    const float* x,
    float* y,
    const void* params) XNN_DISABLE_TSAN
{
  assert(n % sizeof(float) == 0);

  const __m128 vsign_mask = _mm_set1_ps(-0.0f);
  const __m128 vmagic_bias = _mm_set1_ps(0x1.800000p17f);
  const __m128 vlog2e = _mm_set1_ps(0x1.715476p0f);
  const __m128i vindex_mask = _mm_set1_epi32(INT32_C(0x3F));
  const __m128 vminus_ln2_hi = _mm_set1_ps(-0x1.630000p-1f);
  const __m128 vminus_ln2_lo = _mm_set1_ps(0x1.BD0106p-13f);
  const __m128 vc2 = _mm_set1_ps(0x1.FFFF0Ap-2f);
  const __m128 vone = _mm_set1_ps(1.0f);
  const __m128 vdenorm_cutoff = _mm_set1_ps(-0x1.5D589Ep+6f);

  for (; n >= 24 * sizeof(float); n -= 24 * sizeof(float)) {
    const __m128 vx0123 = _mm_loadu_ps(x);
    const __m128 vx4567 = _mm_loadu_ps(x + 4);
    const __m128 vx89AB = _mm_loadu_ps(x + 8);
    const __m128 vxCDEF = _mm_loadu_ps(x + 12);
    const __m128 vxGHIJ = _mm_loadu_ps(x + 16);
    const __m128 vxKLMN = _mm_loadu_ps(x + 20);
    x += 24;

    const __m128 vz0123 = _mm_or_ps(vx0123, vsign_mask);
    const __m128 vz4567 = _mm_or_ps(vx4567, vsign_mask);
    const __m128 vz89AB = _mm_or_ps(vx89AB, vsign_mask);
    const __m128 vzCDEF = _mm_or_ps(vxCDEF, vsign_mask);
    const __m128 vzGHIJ = _mm_or_ps(vxGHIJ, vsign_mask);
    const __m128 vzKLMN = _mm_or_ps(vxKLMN, vsign_mask);

    __m128 vn0123 = _mm_add_ps(_mm_mul_ps(vz0123, vlog2e), vmagic_bias);
    __m128 vn4567 = _mm_add_ps(_mm_mul_ps(vz4567, vlog2e), vmagic_bias);
    __m128 vn89AB = _mm_add_ps(_mm_mul_ps(vz89AB, vlog2e), vmagic_bias);
    __m128 vnCDEF = _mm_add_ps(_mm_mul_ps(vzCDEF, vlog2e), vmagic_bias);
    __m128 vnGHIJ = _mm_add_ps(_mm_mul_ps(vzGHIJ, vlog2e), vmagic_bias);
    __m128 vnKLMN = _mm_add_ps(_mm_mul_ps(vzKLMN, vlog2e), vmagic_bias);

    const __m128i ve0123 = _mm_slli_epi32(_mm_castps_si128(vn0123), 17);
    const __m128i ve4567 = _mm_slli_epi32(_mm_castps_si128(vn4567), 17);
    const __m128i ve89AB = _mm_slli_epi32(_mm_castps_si128(vn89AB), 17);
    const __m128i veCDEF = _mm_slli_epi32(_mm_castps_si128(vnCDEF), 17);
    const __m128i veGHIJ = _mm_slli_epi32(_mm_castps_si128(vnGHIJ), 17);
    const __m128i veKLMN = _mm_slli_epi32(_mm_castps_si128(vnKLMN), 17);

    const __m128i vidx0123 = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn0123), vindex_mask), 2);
    const __m128i vidx4567 = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn4567), vindex_mask), 2);
    const __m128i vidx89AB = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn89AB), vindex_mask), 2);
    const __m128i vidxCDEF = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vnCDEF), vindex_mask), 2);
    const __m128i vidxGHIJ = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vnGHIJ), vindex_mask), 2);
    const __m128i vidxKLMN = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vnKLMN), vindex_mask), 2);

    #if XNN_ARCH_X86_64
      const uint64_t vidx01 = (uint64_t) _mm_cvtsi128_si64(vidx0123);
      const uint64_t vidx23 = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidx0123, vidx0123));
      const __m128i vl0   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx01)));
      const __m128i vl2 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx23)));
      const __m128i vl1 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx01 >> 32))));
      const __m128i vl01 = _mm_unpacklo_epi32(vl0, vl1);
      const __m128i vl3 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx23 >> 32))));
      const __m128i vl23 = _mm_unpacklo_epi32(vl2, vl3);
      const __m128i vl0123 = _mm_unpacklo_epi64(vl01, vl23);
      const uint64_t vidx45 = (uint64_t) _mm_cvtsi128_si64(vidx4567);
      const uint64_t vidx67 = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidx4567, vidx4567));
      const __m128i vl4   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx45)));
      const __m128i vl6 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx67)));
      const __m128i vl5 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx45 >> 32))));
      const __m128i vl45 = _mm_unpacklo_epi32(vl4, vl5);
      const __m128i vl7 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx67 >> 32))));
      const __m128i vl67 = _mm_unpacklo_epi32(vl6, vl7);
      const __m128i vl4567 = _mm_unpacklo_epi64(vl45, vl67);
      const uint64_t vidx89 = (uint64_t) _mm_cvtsi128_si64(vidx89AB);
      const uint64_t vidxAB = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidx89AB, vidx89AB));
      const __m128i vl8   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx89)));
      const __m128i vlA = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxAB)));
      const __m128i vl9 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx89 >> 32))));
      const __m128i vl89 = _mm_unpacklo_epi32(vl8, vl9);
      const __m128i vlB = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxAB >> 32))));
      const __m128i vlAB = _mm_unpacklo_epi32(vlA, vlB);
      const __m128i vl89AB = _mm_unpacklo_epi64(vl89, vlAB);
      const uint64_t vidxCD = (uint64_t) _mm_cvtsi128_si64(vidxCDEF);
      const uint64_t vidxEF = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidxCDEF, vidxCDEF));
      const __m128i vlC   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxCD)));
      const __m128i vlE = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxEF)));
      const __m128i vlD = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxCD >> 32))));
      const __m128i vlCD = _mm_unpacklo_epi32(vlC, vlD);
      const __m128i vlF = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxEF >> 32))));
      const __m128i vlEF = _mm_unpacklo_epi32(vlE, vlF);
      const __m128i vlCDEF = _mm_unpacklo_epi64(vlCD, vlEF);
      const uint64_t vidxGH = (uint64_t) _mm_cvtsi128_si64(vidxGHIJ);
      const uint64_t vidxIJ = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidxGHIJ, vidxGHIJ));
      const __m128i vlG   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxGH)));
      const __m128i vlI = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxIJ)));
      const __m128i vlH = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxGH >> 32))));
      const __m128i vlGH = _mm_unpacklo_epi32(vlG, vlH);
      const __m128i vlJ = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxIJ >> 32))));
      const __m128i vlIJ = _mm_unpacklo_epi32(vlI, vlJ);
      const __m128i vlGHIJ = _mm_unpacklo_epi64(vlGH, vlIJ);
      const uint64_t vidxKL = (uint64_t) _mm_cvtsi128_si64(vidxKLMN);
      const uint64_t vidxMN = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidxKLMN, vidxKLMN));
      const __m128i vlK   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxKL)));
      const __m128i vlM = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidxMN)));
      const __m128i vlL = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxKL >> 32))));
      const __m128i vlKL = _mm_unpacklo_epi32(vlK, vlL);
      const __m128i vlN = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidxMN >> 32))));
      const __m128i vlMN = _mm_unpacklo_epi32(vlM, vlN);
      const __m128i vlKLMN = _mm_unpacklo_epi64(vlKL, vlMN);
    #else  // !XNN_ARCH_X86_64
      const uint32_t vidx0 = (uint32_t) _mm_cvtsi128_si32(vidx0123);
      const uint32_t vidx1 = (uint32_t) _mm_extract_epi16(vidx0123, 2);
      const uint32_t vidx2 = (uint32_t) _mm_extract_epi16(vidx0123, 4);
      const uint32_t vidx3 = (uint32_t) _mm_extract_epi16(vidx0123, 6);
      const __m128i vl0   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx0)));
      const __m128i vl2 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx2)));
      const __m128i vl1 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx1)));
      const __m128i vl01 = _mm_unpacklo_epi32(vl0, vl1);
      const __m128i vl3 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx3)));
      const __m128i vl23 = _mm_unpacklo_epi32(vl2, vl3);
      const __m128i vl0123 = _mm_unpacklo_epi64(vl01, vl23);
      const uint32_t vidx4 = (uint32_t) _mm_cvtsi128_si32(vidx4567);
      const uint32_t vidx5 = (uint32_t) _mm_extract_epi16(vidx4567, 2);
      const uint32_t vidx6 = (uint32_t) _mm_extract_epi16(vidx4567, 4);
      const uint32_t vidx7 = (uint32_t) _mm_extract_epi16(vidx4567, 6);
      const __m128i vl4   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx4)));
      const __m128i vl6 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx6)));
      const __m128i vl5 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx5)));
      const __m128i vl45 = _mm_unpacklo_epi32(vl4, vl5);
      const __m128i vl7 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx7)));
      const __m128i vl67 = _mm_unpacklo_epi32(vl6, vl7);
      const __m128i vl4567 = _mm_unpacklo_epi64(vl45, vl67);
      const uint32_t vidx8 = (uint32_t) _mm_cvtsi128_si32(vidx89AB);
      const uint32_t vidx9 = (uint32_t) _mm_extract_epi16(vidx89AB, 2);
      const uint32_t vidxA = (uint32_t) _mm_extract_epi16(vidx89AB, 4);
      const uint32_t vidxB = (uint32_t) _mm_extract_epi16(vidx89AB, 6);
      const __m128i vl8   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx8)));
      const __m128i vlA = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxA)));
      const __m128i vl9 = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidx9)));
      const __m128i vl89 = _mm_unpacklo_epi32(vl8, vl9);
      const __m128i vlB = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxB)));
      const __m128i vlAB = _mm_unpacklo_epi32(vlA, vlB);
      const __m128i vl89AB = _mm_unpacklo_epi64(vl89, vlAB);
      const uint32_t vidxC = (uint32_t) _mm_cvtsi128_si32(vidxCDEF);
      const uint32_t vidxD = (uint32_t) _mm_extract_epi16(vidxCDEF, 2);
      const uint32_t vidxE = (uint32_t) _mm_extract_epi16(vidxCDEF, 4);
      const uint32_t vidxF = (uint32_t) _mm_extract_epi16(vidxCDEF, 6);
      const __m128i vlC   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxC)));
      const __m128i vlE = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxE)));
      const __m128i vlD = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxD)));
      const __m128i vlCD = _mm_unpacklo_epi32(vlC, vlD);
      const __m128i vlF = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxF)));
      const __m128i vlEF = _mm_unpacklo_epi32(vlE, vlF);
      const __m128i vlCDEF = _mm_unpacklo_epi64(vlCD, vlEF);
      const uint32_t vidxG = (uint32_t) _mm_cvtsi128_si32(vidxGHIJ);
      const uint32_t vidxH = (uint32_t) _mm_extract_epi16(vidxGHIJ, 2);
      const uint32_t vidxI = (uint32_t) _mm_extract_epi16(vidxGHIJ, 4);
      const uint32_t vidxJ = (uint32_t) _mm_extract_epi16(vidxGHIJ, 6);
      const __m128i vlG   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxG)));
      const __m128i vlI = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxI)));
      const __m128i vlH = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxH)));
      const __m128i vlGH = _mm_unpacklo_epi32(vlG, vlH);
      const __m128i vlJ = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxJ)));
      const __m128i vlIJ = _mm_unpacklo_epi32(vlI, vlJ);
      const __m128i vlGHIJ = _mm_unpacklo_epi64(vlGH, vlIJ);
      const uint32_t vidxK = (uint32_t) _mm_cvtsi128_si32(vidxKLMN);
      const uint32_t vidxL = (uint32_t) _mm_extract_epi16(vidxKLMN, 2);
      const uint32_t vidxM = (uint32_t) _mm_extract_epi16(vidxKLMN, 4);
      const uint32_t vidxN = (uint32_t) _mm_extract_epi16(vidxKLMN, 6);
      const __m128i vlK   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxK)));
      const __m128i vlM = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxM)));
      const __m128i vlL = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxL)));
      const __m128i vlKL = _mm_unpacklo_epi32(vlK, vlL);
      const __m128i vlN = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + vidxN)));
      const __m128i vlMN = _mm_unpacklo_epi32(vlM, vlN);
      const __m128i vlKLMN = _mm_unpacklo_epi64(vlKL, vlMN);
    #endif  // XNN_ARCH_X86_64

    const __m128 vs0123 = _mm_castsi128_ps(_mm_add_epi32(vl0123, ve0123));
    const __m128 vs4567 = _mm_castsi128_ps(_mm_add_epi32(vl4567, ve4567));
    const __m128 vs89AB = _mm_castsi128_ps(_mm_add_epi32(vl89AB, ve89AB));
    const __m128 vsCDEF = _mm_castsi128_ps(_mm_add_epi32(vlCDEF, veCDEF));
    const __m128 vsGHIJ = _mm_castsi128_ps(_mm_add_epi32(vlGHIJ, veGHIJ));
    const __m128 vsKLMN = _mm_castsi128_ps(_mm_add_epi32(vlKLMN, veKLMN));

    vn0123 = _mm_sub_ps(vn0123, vmagic_bias);
    vn4567 = _mm_sub_ps(vn4567, vmagic_bias);
    vn89AB = _mm_sub_ps(vn89AB, vmagic_bias);
    vnCDEF = _mm_sub_ps(vnCDEF, vmagic_bias);
    vnGHIJ = _mm_sub_ps(vnGHIJ, vmagic_bias);
    vnKLMN = _mm_sub_ps(vnKLMN, vmagic_bias);

    __m128 vt0123 = _mm_add_ps(vz0123, _mm_mul_ps(vn0123, vminus_ln2_hi));
    __m128 vt4567 = _mm_add_ps(vz4567, _mm_mul_ps(vn4567, vminus_ln2_hi));
    __m128 vt89AB = _mm_add_ps(vz89AB, _mm_mul_ps(vn89AB, vminus_ln2_hi));
    __m128 vtCDEF = _mm_add_ps(vzCDEF, _mm_mul_ps(vnCDEF, vminus_ln2_hi));
    __m128 vtGHIJ = _mm_add_ps(vzGHIJ, _mm_mul_ps(vnGHIJ, vminus_ln2_hi));
    __m128 vtKLMN = _mm_add_ps(vzKLMN, _mm_mul_ps(vnKLMN, vminus_ln2_hi));

    vt0123 = _mm_add_ps(vt0123, _mm_mul_ps(vn0123, vminus_ln2_lo));
    vt4567 = _mm_add_ps(vt4567, _mm_mul_ps(vn4567, vminus_ln2_lo));
    vt89AB = _mm_add_ps(vt89AB, _mm_mul_ps(vn89AB, vminus_ln2_lo));
    vtCDEF = _mm_add_ps(vtCDEF, _mm_mul_ps(vnCDEF, vminus_ln2_lo));
    vtGHIJ = _mm_add_ps(vtGHIJ, _mm_mul_ps(vnGHIJ, vminus_ln2_lo));
    vtKLMN = _mm_add_ps(vtKLMN, _mm_mul_ps(vnKLMN, vminus_ln2_lo));

    __m128 vp0123 = _mm_mul_ps(vt0123, vc2);
    __m128 vp4567 = _mm_mul_ps(vt4567, vc2);
    __m128 vp89AB = _mm_mul_ps(vt89AB, vc2);
    __m128 vpCDEF = _mm_mul_ps(vtCDEF, vc2);
    __m128 vpGHIJ = _mm_mul_ps(vtGHIJ, vc2);
    __m128 vpKLMN = _mm_mul_ps(vtKLMN, vc2);

    vp0123 = _mm_add_ps(vt0123, _mm_mul_ps(vp0123, vt0123));
    vp4567 = _mm_add_ps(vt4567, _mm_mul_ps(vp4567, vt4567));
    vp89AB = _mm_add_ps(vt89AB, _mm_mul_ps(vp89AB, vt89AB));
    vpCDEF = _mm_add_ps(vtCDEF, _mm_mul_ps(vpCDEF, vtCDEF));
    vpGHIJ = _mm_add_ps(vtGHIJ, _mm_mul_ps(vpGHIJ, vtGHIJ));
    vpKLMN = _mm_add_ps(vtKLMN, _mm_mul_ps(vpKLMN, vtKLMN));

    const __m128 vy0123 = _mm_add_ps(vs0123, _mm_mul_ps(vs0123, vp0123));
    const __m128 vy4567 = _mm_add_ps(vs4567, _mm_mul_ps(vs4567, vp4567));
    const __m128 vy89AB = _mm_add_ps(vs89AB, _mm_mul_ps(vs89AB, vp89AB));
    const __m128 vyCDEF = _mm_add_ps(vsCDEF, _mm_mul_ps(vsCDEF, vpCDEF));
    const __m128 vyGHIJ = _mm_add_ps(vsGHIJ, _mm_mul_ps(vsGHIJ, vpGHIJ));
    const __m128 vyKLMN = _mm_add_ps(vsKLMN, _mm_mul_ps(vsKLMN, vpKLMN));

    __m128 vf0123 = _mm_div_ps(vy0123, _mm_add_ps(vy0123, vone));
    __m128 vf4567 = _mm_div_ps(vy4567, _mm_add_ps(vy4567, vone));
    __m128 vf89AB = _mm_div_ps(vy89AB, _mm_add_ps(vy89AB, vone));
    __m128 vfCDEF = _mm_div_ps(vyCDEF, _mm_add_ps(vyCDEF, vone));
    __m128 vfGHIJ = _mm_div_ps(vyGHIJ, _mm_add_ps(vyGHIJ, vone));
    __m128 vfKLMN = _mm_div_ps(vyKLMN, _mm_add_ps(vyKLMN, vone));

    vf0123 = _mm_andnot_ps(_mm_cmplt_ps(vz0123, vdenorm_cutoff), vf0123);
    vf4567 = _mm_andnot_ps(_mm_cmplt_ps(vz4567, vdenorm_cutoff), vf4567);
    vf89AB = _mm_andnot_ps(_mm_cmplt_ps(vz89AB, vdenorm_cutoff), vf89AB);
    vfCDEF = _mm_andnot_ps(_mm_cmplt_ps(vzCDEF, vdenorm_cutoff), vfCDEF);
    vfGHIJ = _mm_andnot_ps(_mm_cmplt_ps(vzGHIJ, vdenorm_cutoff), vfGHIJ);
    vfKLMN = _mm_andnot_ps(_mm_cmplt_ps(vzKLMN, vdenorm_cutoff), vfKLMN);

    const __m128 vm0123 = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx0123)));
    const __m128 vm4567 = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx4567)));
    const __m128 vm89AB = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx89AB)));
    const __m128 vmCDEF = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vxCDEF)));
    const __m128 vmGHIJ = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vxGHIJ)));
    const __m128 vmKLMN = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vxKLMN)));

    vf0123 = _mm_or_ps(_mm_and_ps(vf0123, vm0123), _mm_andnot_ps(vm0123, _mm_sub_ps(vone, vf0123)));
    vf4567 = _mm_or_ps(_mm_and_ps(vf4567, vm4567), _mm_andnot_ps(vm4567, _mm_sub_ps(vone, vf4567)));
    vf89AB = _mm_or_ps(_mm_and_ps(vf89AB, vm89AB), _mm_andnot_ps(vm89AB, _mm_sub_ps(vone, vf89AB)));
    vfCDEF = _mm_or_ps(_mm_and_ps(vfCDEF, vmCDEF), _mm_andnot_ps(vmCDEF, _mm_sub_ps(vone, vfCDEF)));
    vfGHIJ = _mm_or_ps(_mm_and_ps(vfGHIJ, vmGHIJ), _mm_andnot_ps(vmGHIJ, _mm_sub_ps(vone, vfGHIJ)));
    vfKLMN = _mm_or_ps(_mm_and_ps(vfKLMN, vmKLMN), _mm_andnot_ps(vmKLMN, _mm_sub_ps(vone, vfKLMN)));

    _mm_storeu_ps(y, vf0123);
    _mm_storeu_ps(y + 4, vf4567);
    _mm_storeu_ps(y + 8, vf89AB);
    _mm_storeu_ps(y + 12, vfCDEF);
    _mm_storeu_ps(y + 16, vfGHIJ);
    _mm_storeu_ps(y + 20, vfKLMN);
    y += 24;
  }
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    const __m128 vx = _mm_loadu_ps(x);
    x += 4;

    const __m128 vz = _mm_or_ps(vx, vsign_mask);

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);
    const __m128i ve = _mm_slli_epi32(_mm_castps_si128(vn), 17);

    const __m128i vidx = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn), vindex_mask), 2);
    #if XNN_ARCH_X86_64
      const uint64_t vidx_lo = (uint64_t) _mm_cvtsi128_si64(vidx);
      const uint64_t vidx_hi = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidx, vidx));
      const __m128i vl_ll   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_lo)));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_hi)));
      const __m128i vl_lh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_lo >> 32))));
      const __m128i vl_lo = _mm_unpacklo_epi32(vl_ll, vl_lh);
      const __m128i vl_hh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_hi >> 32))));
      const __m128i vl_hi = _mm_unpacklo_epi32(vl_hl, vl_hh);
    #else  // !XNN_ARCH_X86_64
      const __m128i vl_ll = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_cvtsi128_si32(vidx))));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 4))));
      const __m128i vl_lh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 2))));
      const __m128i vl_lo = _mm_unpacklo_epi32(vl_ll, vl_lh);
      const __m128i vl_hh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 6))));
      const __m128i vl_hi = _mm_unpacklo_epi32(vl_hl, vl_hh);
    #endif  // XNN_ARCH_X86_64
    const __m128i vl = _mm_unpacklo_epi64(vl_lo, vl_hi);

    const __m128 vs = _mm_castsi128_ps(_mm_add_epi32(vl, ve));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(vz, _mm_mul_ps(vn, vminus_ln2_hi));
    vt = _mm_add_ps(vt, _mm_mul_ps(vn, vminus_ln2_lo));

    __m128 vp = _mm_mul_ps(vt, vc2);
    vp = _mm_add_ps(vt, _mm_mul_ps(vp, vt));

    const __m128 vy = _mm_add_ps(vs, _mm_mul_ps(vs, vp));

    __m128 vf = _mm_div_ps(vy, _mm_add_ps(vy, vone));
    vf = _mm_andnot_ps(_mm_cmplt_ps(vz, vdenorm_cutoff), vf);
    const __m128 vm = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx)));
    vf = _mm_or_ps(_mm_and_ps(vf, vm), _mm_andnot_ps(vm, _mm_sub_ps(vone, vf)));

    _mm_storeu_ps(y, vf);
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    const __m128 vx = _mm_loadu_ps(x);

    const __m128 vz = _mm_or_ps(vx, vsign_mask);

    __m128 vn = _mm_add_ps(_mm_mul_ps(vz, vlog2e), vmagic_bias);
    const __m128i ve = _mm_slli_epi32(_mm_castps_si128(vn), 17);

    const __m128i vidx = _mm_slli_epi32(_mm_and_si128(_mm_castps_si128(vn), vindex_mask), 2);
    #if XNN_ARCH_X86_64
      const uint64_t vidx_lo = (uint64_t) _mm_cvtsi128_si64(vidx);
      const uint64_t vidx_hi = (uint64_t) _mm_cvtsi128_si64(_mm_unpackhi_epi64(vidx, vidx));
      const __m128i vl_ll   = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_lo)));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) vidx_hi)));
      const __m128i vl_lh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_lo >> 32))));
      const __m128i vl_lo = _mm_unpacklo_epi32(vl_ll, vl_lh);
      const __m128i vl_hh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) (vidx_hi >> 32))));
      const __m128i vl_hi = _mm_unpacklo_epi32(vl_hl, vl_hh);
    #else  // !XNN_ARCH_X86_64
      const __m128i vl_ll = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_cvtsi128_si32(vidx))));
      const __m128i vl_hl = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 4))));
      const __m128i vl_lh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 2))));
      const __m128i vl_lo = _mm_unpacklo_epi32(vl_ll, vl_lh);
      const __m128i vl_hh = _mm_cvtsi32_si128(*((const int*) ((uintptr_t) xnn_table_exp2minus_k_over_64 + (uint32_t) _mm_extract_epi16(vidx, 6))));
      const __m128i vl_hi = _mm_unpacklo_epi32(vl_hl, vl_hh);
    #endif  // XNN_ARCH_X86_64
    const __m128i vl = _mm_unpacklo_epi64(vl_lo, vl_hi);

    const __m128 vs = _mm_castsi128_ps(_mm_add_epi32(vl, ve));
    vn = _mm_sub_ps(vn, vmagic_bias);

    __m128 vt = _mm_add_ps(vz, _mm_mul_ps(vn, vminus_ln2_hi));
    vt = _mm_add_ps(vt, _mm_mul_ps(vn, vminus_ln2_lo));

    __m128 vp = _mm_mul_ps(vt, vc2);
    vp = _mm_add_ps(vt, _mm_mul_ps(vp, vt));

    const __m128 vy = _mm_add_ps(vs, _mm_mul_ps(vs, vp));

    __m128 vf = _mm_div_ps(vy, _mm_add_ps(vy, vone));
    vf = _mm_andnot_ps(_mm_cmplt_ps(vz, vdenorm_cutoff), vf);
    const __m128 vm = _mm_castsi128_ps(_mm_cmpgt_epi32(_mm_setzero_si128(), _mm_castps_si128(vx)));
    vf = _mm_or_ps(_mm_and_ps(vf, vm), _mm_andnot_ps(vm, _mm_sub_ps(vone, vf)));

    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vf);
      vf = _mm_movehl_ps(vf, vf);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vf);
    }
  }
}