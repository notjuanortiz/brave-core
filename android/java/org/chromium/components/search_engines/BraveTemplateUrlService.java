/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.components.search_engines;

import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

import org.chromium.base.ContextUtils;
import org.chromium.base.ThreadUtils;
import org.chromium.components.search_engines.TemplateUrlService;

public class BraveTemplateUrlService extends TemplateUrlService {
    public static final String PREF_STANDARD_SEARCH_ENGINE = "brave_standard_search_engine";
    public static final String PREF_STANDARD_SEARCH_ENGINE_KEYWORD = "brave_standard_search_engine_keyword";
    public static final String PREF_PRIVATE_SEARCH_ENGINE = "brave_private_search_engine";
    public static final String PREF_PRIVATE_SEARCH_ENGINE_KEYWORD = "brave_private_search_engine_keyword";

    private boolean mCurrentDefaultSearchEnginePrivate;

    protected BraveTemplateUrlService(long nativeTemplateUrlServiceAndroid) {
        super(nativeTemplateUrlServiceAndroid);
        mCurrentDefaultSearchEnginePrivate = false;
    }

    public void setSearchEngine(String name, String keyword, boolean is_private) {
        ThreadUtils.assertOnUiThread();

        updateDefaultSearchEngineInfo(!is_private);

        SharedPreferences.Editor sharedPreferencesEditor =
                ContextUtils.getAppSharedPreferences().edit();
        sharedPreferencesEditor.putString(
                is_private ? PREF_PRIVATE_SEARCH_ENGINE : PREF_STANDARD_SEARCH_ENGINE, name);
        sharedPreferencesEditor.putString(is_private ? PREF_PRIVATE_SEARCH_ENGINE_KEYWORD
                                                     : PREF_STANDARD_SEARCH_ENGINE_KEYWORD,
                keyword);
        sharedPreferencesEditor.apply();

        mCurrentDefaultSearchEnginePrivate = is_private;

        super.setSearchEngine(keyword);
    }

    private void updateDefaultSearchEngineInfo(boolean is_private) {
        SharedPreferences preferences = ContextUtils.getAppSharedPreferences();
        if (!preferences.contains(
                    is_private ? PREF_PRIVATE_SEARCH_ENGINE : PREF_STANDARD_SEARCH_ENGINE)
                || !preferences.contains(is_private ? PREF_PRIVATE_SEARCH_ENGINE_KEYWORD
                                                    : PREF_STANDARD_SEARCH_ENGINE_KEYWORD)) {
            TemplateUrl defaultSearchEngineTemplateUrl = getDefaultSearchEngineTemplateUrl();
            if (defaultSearchEngineTemplateUrl != null) {
                SharedPreferences.Editor sharedPreferencesEditor = preferences.edit();
                sharedPreferencesEditor.putString(
                        is_private ? PREF_PRIVATE_SEARCH_ENGINE : PREF_STANDARD_SEARCH_ENGINE,
                        defaultSearchEngineTemplateUrl.getShortName());
                sharedPreferencesEditor.putString(is_private ? PREF_PRIVATE_SEARCH_ENGINE_KEYWORD
                                                             : PREF_STANDARD_SEARCH_ENGINE_KEYWORD,
                        defaultSearchEngineTemplateUrl.getKeyword());
                sharedPreferencesEditor.apply();
            }
        }
    }

    public String getDefaultSearchEngineName(boolean is_private) {
        updateDefaultSearchEngineInfo(is_private);
        return ContextUtils.getAppSharedPreferences().getString(
                is_private ? PREF_PRIVATE_SEARCH_ENGINE : PREF_STANDARD_SEARCH_ENGINE, null);
    }

    public String getDefaultSearchEngineKeyword(boolean is_private) {
        updateDefaultSearchEngineInfo(is_private);
        return ContextUtils.getAppSharedPreferences().getString(is_private
                        ? PREF_PRIVATE_SEARCH_ENGINE_KEYWORD
                        : PREF_STANDARD_SEARCH_ENGINE_KEYWORD,
                null);
    }

    public void updateCurrentDefaultSearchEngine(boolean is_private) {
        if (mCurrentDefaultSearchEnginePrivate != is_private) {
            mCurrentDefaultSearchEnginePrivate = is_private;
            setSearchEngine(getDefaultSearchEngineKeyword(is_private));
        }
    }
}
