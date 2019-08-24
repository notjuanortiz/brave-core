/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "chrome/browser/profiles/pref_service_builder_utils.h"

#include "brave/browser/brave_profile_prefs.h"
#include "brave/browser/profiles/brave_profile_impl.h"
#include "brave/browser/profiles/profile_util.h"
#include "brave/browser/themes/brave_theme_service.h"
#include "brave/browser/tor/buildflags.h"
#include "brave/common/pref_names.h"
#include "brave/components/brave_rewards/browser/rewards_service.h"
#include "chrome/browser/prefs/pref_service_syncable_util.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "components/spellcheck/browser/pref_names.h"

#if BUILDFLAG(ENABLE_TOR)
#include "brave/browser/tor/tor_profile_service.h"
#endif

#define CreatePrefService CreatePrefService_ChromiumImpl
#define RegisterProfilePrefs RegisterProfilePrefs_ChromiumImpl
#include "../../../../../chrome/browser/profiles/pref_service_builder_utils.cc"
#undef CreatePrefService
#undef RegisterProfilePrefs

// Prefs for KeyedService
void RegisterProfilePrefs(bool is_signin_profile,
                          const std::string& locale,
                          user_prefs::PrefRegistrySyncable* registry) {
  RegisterProfilePrefs_ChromiumImpl(is_signin_profile, locale, registry);

  // appearance
#if !defined(OS_ANDROID)
  BraveThemeService::RegisterProfilePrefs(registry);
#endif

#if BUILDFLAG(ENABLE_TOR)
  tor::TorProfileService::RegisterProfilePrefs(registry);
#endif

  brave_rewards::RewardsService::RegisterProfilePrefs(registry);

  // Disable spell check service
  registry->SetDefaultPrefValue(
      spellcheck::prefs::kSpellCheckUseSpellingService, base::Value(false));

  // Make sure sign into Brave is not enabled
  // The older kSigninAllowed is deprecated and only in use in Android until
  // C71.
  registry->SetDefaultPrefValue(prefs::kSigninAllowedOnNextStartup,
                                base::Value(false));

#if defined(OS_LINUX)
  // Use brave theme by default instead of gtk theme.
  registry->SetDefaultPrefValue(prefs::kUsesSystemTheme, base::Value(false));
#endif
}

std::unique_ptr<sync_preferences::PrefServiceSyncable> CreatePrefService(
    scoped_refptr<user_prefs::PrefRegistrySyncable> pref_registry,
    PrefStore* extension_pref_store,
    policy::PolicyService* policy_service,
    policy::ChromeBrowserPolicyConnector* browser_policy_connector,
    prefs::mojom::TrackedPreferenceValidationDelegatePtr
        pref_validation_delegate,
    scoped_refptr<base::SequencedTaskRunner> io_task_runner,
    SimpleFactoryKey* key,
    const base::FilePath& path,
    bool async_prefs) {
#if BUILDFLAG(ENABLE_TOR)
  // Create prefs using the same approach that chromium used when creating an
  // off-the-record profile from its original profile.
  if (brave::IsTorProfile(path)) {
    Profile* original_profile = brave::GetTorParentProfile(path);
    return CreateIncognitoPrefServiceSyncable(
        PrefServiceSyncableFromProfile(original_profile),
        BraveProfileImpl::CreateExtensionPrefStore(original_profile, false),
        InProcessPrefServiceFactoryFactory::GetInstanceForKey(key)
            ->CreateDelegate());
  }
#endif

  return CreatePrefService_ChromiumImpl(
      pref_registry, extension_pref_store, policy_service,
      browser_policy_connector, std::move(pref_validation_delegate),
      io_task_runner, key, path, async_prefs);
}
