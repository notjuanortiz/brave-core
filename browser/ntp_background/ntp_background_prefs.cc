/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ntp_background/ntp_background_prefs.h"

#include <memory>
#include <utility>

#include "base/notreached.h"
#include "brave/components/constants/pref_names.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_service.h"
#include "services/preferences/public/cpp/dictionary_value_update.h"
#include "services/preferences/public/cpp/scoped_pref_update.h"

namespace {

constexpr char kTypeKey[] = "type";
constexpr char kRandomKey[] = "random";
constexpr char kSelectedValueKey[] = "selected_value";

const char* TypeToString(NTPBackgroundPrefs::Type type) {
  switch (type) {
    case NTPBackgroundPrefs::Type::kBrave:
      return "brave";
    case NTPBackgroundPrefs::Type::kCustomImage:
      return "custom_image";
    case NTPBackgroundPrefs::Type::kSolidColor:
      return "solid_color";
    case NTPBackgroundPrefs::Type::kGradientColor:
      return "gradient_color";
  }
}

NTPBackgroundPrefs::Type StringToType(const std::string& type_string) {
  if (type_string == "brave")
    return NTPBackgroundPrefs::Type::kBrave;
  if (type_string == "custom_image")
    return NTPBackgroundPrefs::Type::kCustomImage;
  if (type_string == "solid_color")
    return NTPBackgroundPrefs::Type::kSolidColor;
  if (type_string == "gradient_color")
    return NTPBackgroundPrefs::Type::kGradientColor;

  NOTREACHED();
  return NTPBackgroundPrefs::Type::kBrave;
}

}  // namespace

NTPBackgroundPrefs::NTPBackgroundPrefs(PrefService* service)
    : service_(service) {}

NTPBackgroundPrefs::~NTPBackgroundPrefs() = default;

// static
void NTPBackgroundPrefs::RegisterPref(
    user_prefs::PrefRegistrySyncable* registry) {
  base::Value::Dict dict;
  dict.Set(kTypeKey, TypeToString(Type::kBrave));
  dict.Set(kRandomKey, false);
  dict.Set(kSelectedValueKey, "");
  registry->RegisterDictionaryPref(kPrefName, base::Value(std::move(dict)));
}

void NTPBackgroundPrefs::MigrateOldPref() {
  if (!service_->HasPrefPath(kDeprecatedPrefName))
    return;

  if (service_->GetBoolean(kDeprecatedPrefName))
    SetType(Type::kCustomImage);

  service_->ClearPref(kDeprecatedPrefName);
}

NTPBackgroundPrefs::Type NTPBackgroundPrefs::GetType() const {
  const auto* value = GetPrefValue();
  const auto* type_string = value->FindString(kTypeKey);
  return StringToType(*type_string);
}

void NTPBackgroundPrefs::SetType(Type type) {
  if (type == GetType())
    return;

  prefs::ScopedDictionaryPrefUpdate update(service_, kPrefName);
  update->Set(kTypeKey, std::make_unique<base::Value>(TypeToString(type)));
}

bool NTPBackgroundPrefs::IsBraveType() const {
  return GetType() == Type::kBrave;
}

bool NTPBackgroundPrefs::IsCustomImageType() const {
  return GetType() == Type::kCustomImage;
}

bool NTPBackgroundPrefs::IsSolidColorType() const {
  return GetType() == Type::kSolidColor;
}

bool NTPBackgroundPrefs::IsGradientColorType() const {
  return GetType() == Type::kGradientColor;
}

bool NTPBackgroundPrefs::ShouldUseRandomValue() const {
  const auto* value = GetPrefValue();
  auto optional_bool = value->FindBool(kRandomKey);
  return optional_bool.value_or(false);
}

void NTPBackgroundPrefs::SetShouldUseRandomValue(bool random) {
  NOTIMPLEMENTED();
}

void NTPBackgroundPrefs::SetSelectedValue(const std::string& value) {
  prefs::ScopedDictionaryPrefUpdate update(service_, kPrefName);
  update->Set(kSelectedValueKey, std::make_unique<base::Value>(value));
}

absl::variant<GURL, std::string> NTPBackgroundPrefs::GetSelectedValue() const {
  const auto* value = GetPrefValue();
  const auto* selected_value = value->FindString(kSelectedValueKey);
  DCHECK(selected_value);

  if (auto type = GetType();
      type == Type::kSolidColor || type == Type::kGradientColor)
    return *selected_value;

  return GURL(*selected_value);
}

absl::variant<GURL, std::string> NTPBackgroundPrefs::GetRandomValue() const {
  NOTIMPLEMENTED();
  return std::string{};
}

const base::Value::Dict* NTPBackgroundPrefs::GetPrefValue() const {
  const auto* value = service_->GetDictionary(kPrefName);
  DCHECK(value && value->is_dict());
  return value->GetIfDict();
}
