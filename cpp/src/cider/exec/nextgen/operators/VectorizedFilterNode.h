/*
 * Copyright(c) 2022-2023 Intel Corporation.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef NEXTGEN_OPERATORS_VECTORIZEDFILTERNODE_H
#define NEXTGEN_OPERATORS_VECTORIZEDFILTERNODE_H

#include "exec/nextgen/operators/OpNode.h"

namespace cider::exec::nextgen::operators {
class VectorizedFilterNode : public OpNode {
 public:
  explicit VectorizedFilterNode(ExprPtrVector&& conditions)
      : OpNode("VectorizedFilterNode", std::move(conditions), JITExprValueType::BATCH) {}

  explicit VectorizedFilterNode(const ExprPtrVector& output_exprs)
      : OpNode("VectorizedFilterNode", output_exprs, JITExprValueType::BATCH) {}

  TranslatorPtr toTranslator(const TranslatorPtr& successor = nullptr) override;
};

class VectorizedFilterTranslator : public Translator {
 public:
  using Translator::Translator;

  void consume(context::CodegenContext& context) override;

 private:
  void codegenImpl(SuccessorEmitter successor_wrapper,
                   context::CodegenContext& context,
                   void* successor) override;

  jitlib::JITValuePointer generateFilterCondition(context::CodegenContext& context);
};
}  // namespace cider::exec::nextgen::operators

#endif  // NEXTGEN_OPERATORS_VECTORIZEDFILTERNODE_H