/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.preferences;

import android.os.Bundle;
import android.support.v7.preference.Preference;

import org.chromium.chrome.browser.preferences.ChromeBasePreferenceCompat;
import org.chromium.chrome.browser.search_engines.TemplateUrlServiceFactory;

public class BraveMainPreferences extends MainPreferences {
    public static final String PREF_STANDARD_SEARCH_ENGINE = "standard_search_engine";
    public static final String PREF_PRIVATE_SEARCH_ENGINE = "private_search_engine";

    private void updateSearchEnginePreference(String prefSearchName) {
        if (!TemplateUrlServiceFactory.get().isLoaded()) {
            ChromeBasePreferenceCompat searchEnginePref =
                    (ChromeBasePreferenceCompat) findPreference(prefSearchName);
            searchEnginePref.setEnabled(false);
            return;
        }

        String defaultSearchEngineName = TemplateUrlServiceFactory.get().getDefaultSearchEngineName(
                prefSearchName.equals(PREF_PRIVATE_SEARCH_ENGINE));
        Preference searchEnginePreference = findPreference(prefSearchName);
        searchEnginePreference.setEnabled(true);
        searchEnginePreference.setSummary(defaultSearchEngineName);
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setManagedPreferenceDelegateForPreference(PREF_STANDARD_SEARCH_ENGINE);
        setManagedPreferenceDelegateForPreference(PREF_PRIVATE_SEARCH_ENGINE);
    }

    @Override
    public void onResume() {
        super.onResume();
        updateSearchEnginePreference(PREF_STANDARD_SEARCH_ENGINE);
        updateSearchEnginePreference(PREF_PRIVATE_SEARCH_ENGINE);
    }

    @Override
    public void onTemplateUrlServiceLoaded() {
        super.onTemplateUrlServiceLoaded();
        updateSearchEnginePreference(PREF_STANDARD_SEARCH_ENGINE);
        updateSearchEnginePreference(PREF_PRIVATE_SEARCH_ENGINE);
    }
}
