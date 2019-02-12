/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBTEXTCLASSIFIER_UTILS_INTENTS_JNI_H_
#define LIBTEXTCLASSIFIER_UTILS_INTENTS_JNI_H_

#include <jni.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "utils/intents/intent-generator.h"
#include "utils/java/jni-base.h"
#include "utils/optional.h"
#include "utils/variant.h"

#ifndef TC3_REMOTE_ACTION_TEMPLATE_CLASS_NAME
#define TC3_REMOTE_ACTION_TEMPLATE_CLASS_NAME RemoteActionTemplate
#endif

#define TC3_REMOTE_ACTION_TEMPLATE_CLASS_NAME_STR \
  TC3_ADD_QUOTES(TC3_REMOTE_ACTION_TEMPLATE_CLASS_NAME)

#ifndef TC3_NAMED_VARIANT_CLASS_NAME
#define TC3_NAMED_VARIANT_CLASS_NAME NamedVariant
#endif

#define TC3_NAMED_VARIANT_CLASS_NAME_STR \
  TC3_ADD_QUOTES(TC3_NAMED_VARIANT_CLASS_NAME)

namespace libtextclassifier3 {

// A helper class to create RemoteActionTemplate object from model results.
class RemoteActionTemplatesHandler {
 public:
  static std::unique_ptr<RemoteActionTemplatesHandler> Create(JNIEnv* env);

  explicit RemoteActionTemplatesHandler(JNIEnv* env)
      : env_(env),
        string_class_(nullptr, env),
        integer_class_(nullptr, env),
        remote_action_template_class_(nullptr, env),
        named_variant_class_(nullptr, env) {}

  jstring AsUTF8String(const Optional<std::string>& optional);
  jobject AsInteger(const Optional<int>& optional);
  jobjectArray AsStringArray(const std::vector<std::string>& values);
  jobject AsNamedVariant(const std::string& name, const Variant& value);
  jobjectArray AsNamedVariantArray(
      const std::map<std::string, Variant>& values);

  jobjectArray RemoteActionTemplatesToJObjectArray(
      const std::vector<RemoteActionTemplate>& remote_actions);

 private:
  JNIEnv* env_;

  // java.lang.String
  ScopedLocalRef<jclass> string_class_;

  // java.lang.Integer
  ScopedLocalRef<jclass> integer_class_;
  jmethodID integer_init_ = nullptr;

  // RemoteActionTemplate
  ScopedLocalRef<jclass> remote_action_template_class_;
  jmethodID remote_action_template_init_ = nullptr;

  // NamedVariant
  ScopedLocalRef<jclass> named_variant_class_;
  jmethodID named_variant_from_int_ = nullptr;
  jmethodID named_variant_from_long_ = nullptr;
  jmethodID named_variant_from_float_ = nullptr;
  jmethodID named_variant_from_double_ = nullptr;
  jmethodID named_variant_from_bool_ = nullptr;
  jmethodID named_variant_from_string_ = nullptr;
};

}  // namespace libtextclassifier3

#endif  // LIBTEXTCLASSIFIER_UTILS_INTENTS_JNI_H_
