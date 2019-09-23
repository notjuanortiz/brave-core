/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.preferences;

import android.os.Bundle;
import org.chromium.chrome.R;

/**
* A preference fragment for selecting a default private search engine.
*/
public class PrivateSearchEnginePreference extends SearchEnginePreference {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getActivity().setTitle(R.string.prefs_private_search_engine);
        // mSearchEngineAdapter = new SearchEngineAdapter(getActivity(), true);
    }
}
