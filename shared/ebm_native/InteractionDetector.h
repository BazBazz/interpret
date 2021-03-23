// Copyright (c) 2018 Microsoft Corporation
// Licensed under the MIT license.
// Author: Paul Koch <ebm@koch.ninja>

#ifndef EBM_INTERACTION_DETECTOR_H
#define EBM_INTERACTION_DETECTOR_H

#include <stdlib.h> // free
#include <stddef.h> // size_t, ptrdiff_t
#include <limits> // numeric_limits

#include "ebm_native.h"
#include "EbmInternal.h"
#include "logging.h" // EBM_ASSERT & LOG
// feature includes
#include "FeatureAtomic.h"
// dataset depends on features
#include "DataFrameInteraction.h"

class InteractionDetector final {
   ptrdiff_t m_runtimeLearningTypeOrCountTargetClasses;

   size_t m_cFeatureAtomics;
   FeatureAtomic * m_aFeatureAtomics;

   DataFrameInteraction m_dataFrame;

   int m_cLogEnterMessages;
   int m_cLogExitMessages;

public:

   InteractionDetector() = default; // preserve our POD status
   ~InteractionDetector() = default; // preserve our POD status
   void * operator new(std::size_t) = delete; // we only use malloc/free in this library
   void operator delete (void *) = delete; // we only use malloc/free in this library

   INLINE_ALWAYS void InitializeZero() {
      m_runtimeLearningTypeOrCountTargetClasses = 0;

      m_cFeatureAtomics = 0;
      m_aFeatureAtomics = nullptr;

      m_dataFrame.InitializeZero();

      m_cLogEnterMessages = 0;
      m_cLogExitMessages = 0;
   }

   INLINE_ALWAYS ptrdiff_t GetRuntimeLearningTypeOrCountTargetClasses() {
      return m_runtimeLearningTypeOrCountTargetClasses;
   }

   INLINE_ALWAYS int * GetPointerCountLogEnterMessages() {
      return &m_cLogEnterMessages;
   }

   INLINE_ALWAYS int * GetPointerCountLogExitMessages() {
      return &m_cLogExitMessages;
   }

   INLINE_ALWAYS const DataFrameInteraction * GetDataFrameInteraction() const {
      return &m_dataFrame;
   }

   INLINE_ALWAYS const FeatureAtomic * GetFeatureAtomics() const {
      return m_aFeatureAtomics;
   }

   INLINE_ALWAYS size_t GetCountFeatureAtomics() const {
      return m_cFeatureAtomics;
   }

   static void Free(InteractionDetector * const pInteractionDetector);
   static InteractionDetector * Allocate(
      const ptrdiff_t runtimeLearningTypeOrCountTargetClasses,
      const size_t cFeatureAtomics,
      const FloatEbmType * const optionalTempParams,
      const BoolEbmType * const aFeatureAtomicsCategorical,
      const IntEbmType * const aFeatureAtomicsBinCount,
      const size_t cSamples,
      const void * const aTargets,
      const IntEbmType * const aBinnedData,
      const FloatEbmType * const aWeights,
      const FloatEbmType * const aPredictorScores
   );
};
static_assert(std::is_standard_layout<InteractionDetector>::value,
   "We use the struct hack in several places, so disallow non-standard_layout types in general");
static_assert(std::is_trivial<InteractionDetector>::value,
   "We use memcpy in several places, so disallow non-trivial types in general");
static_assert(std::is_pod<InteractionDetector>::value,
   "We use a lot of C constructs, so disallow non-POD types in general");

#endif // EBM_INTERACTION_DETECTOR_H
