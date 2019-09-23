/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.ntp;

import android.content.Context;
import android.content.DialogInterface;
import android.support.v7.app.AlertDialog;
import android.util.AttributeSet;
import android.view.View;

import org.chromium.base.ContextUtils;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.preferences.BraveSearchEngineUtils;

public class BraveIncognitoNewTabPageView extends IncognitoNewTabPageView {
    public static String INCOGNITO_DEFAULT_SEARCH_ENGINE_NAME = "DuckDuckGo";
    public static String INCOGNITO_DEFAULT_SEARCH_ENGINE_KEYWORD = "duckduckgo.com";
    public static String PREF_DDG_OFFER_SHOWN = "brave_ddg_offer_shown";

    private Context mContext;
    private View mDDGOfferLink;

    public BraveIncognitoNewTabPageView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();

        mDDGOfferLink = findViewById(R.id.ddg_offer_link);
        mDDGOfferLink.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                showDDGOffer(true);
            }
        });

        showDDGOffer(false);
    }

    public void showDDGOffer(boolean forceShow) {
        if (BraveSearchEngineUtils.getDSEKeyword(true).equals(
                    INCOGNITO_DEFAULT_SEARCH_ENGINE_KEYWORD)) {
            mDDGOfferLink.setVisibility(View.GONE);
            return;
        }
        if (!forceShow
                && ContextUtils.getAppSharedPreferences().getBoolean(PREF_DDG_OFFER_SHOWN, false)) {
            return;
        }
        ContextUtils.getAppSharedPreferences()
                .edit()
                .putBoolean(PREF_DDG_OFFER_SHOWN, true)
                .apply();
        new AlertDialog.Builder(mContext, R.style.BraveDialogTheme)
                .setView(R.layout.ddg_offer_layout)
                .setPositiveButton(R.string.ddg_offer_positive,
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                // BraveSearchEngineUtils.setSearchEngine(
                                //          INCOGNITO_DEFAULT_SEARCH_ENGINE_NAME,
                                //          INCOGNITO_DEFAULT_SEARCH_ENGINE_KEYWORD, true);
                                mDDGOfferLink.setVisibility(View.GONE);
                            }
                        })
                .setNegativeButton(R.string.ddg_offer_negative, null)
                .show();
    }
}
