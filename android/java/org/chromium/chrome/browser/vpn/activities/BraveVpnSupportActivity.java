/**
 * Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.vpn.activities;

import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.RadioGroup;
import androidx.appcompat.widget.AppCompatRadioButton;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.widget.SwitchCompat;
import androidx.appcompat.widget.Toolbar;

import org.chromium.chrome.R;
import org.chromium.chrome.browser.about_settings.AboutChromeSettings;
import org.chromium.chrome.browser.about_settings.AboutSettingsBridge;
import org.chromium.chrome.browser.firstrun.BraveFirstRunFlowSequencer;
import org.chromium.chrome.browser.init.AsyncInitializationActivity;
import org.chromium.chrome.browser.vpn.utils.BraveVpnPrefUtils;

import java.util.TimeZone;

public class BraveVpnSupportActivity extends AsyncInitializationActivity {
    private BraveFirstRunFlowSequencer mFirstRunFlowSequencer;

    private void initializeViews() {
        setContentView(R.layout.activity_brave_vpn_support);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        ActionBar actionBar = getSupportActionBar();
        assert actionBar != null;
        actionBar.setDisplayHomeAsUpEnabled(true);
        actionBar.setTitle(getResources().getString(R.string.contact_technical_support));

        SwitchCompat vpnHostnameSwitch = findViewById(R.id.vpn_hostname_switch);
        SwitchCompat subscriptionTypeSwitch = findViewById(R.id.subscription_type_switch);
        SwitchCompat appReceiptSwitch = findViewById(R.id.app_receipt_switch);
        SwitchCompat appVersionSwitch = findViewById(R.id.app_version_switch);
        SwitchCompat timezoneSwitch = findViewById(R.id.timezone_switch);
        SwitchCompat networkTypeSwitch = findViewById(R.id.network_type_switch);
        SwitchCompat cellularCarrierSwitch = findViewById(R.id.cellular_carrier_switch);

        RadioGroup otherIssuesRadioGroup = findViewById(R.id.other_issues_radiogroup);

        TextView otherIssuesText = findViewById(R.id.other_issues_text);
        otherIssuesText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (otherIssuesRadioGroup.isShown()) {
                    otherIssuesText.setCompoundDrawablesWithIntrinsicBounds(
                            0, 0, R.drawable.ic_toggle_down, 0);
                    otherIssuesRadioGroup.setVisibility(View.GONE);
                } else {
                    otherIssuesText.setCompoundDrawablesWithIntrinsicBounds(
                            0, 0, R.drawable.ic_toggle_up, 0);
                    otherIssuesRadioGroup.setVisibility(View.VISIBLE);
                }
            }
        });

        Button btnContinueToEmail = findViewById(R.id.btn_continue_to_email);
        otherIssuesRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if (!btnContinueToEmail.isEnabled()) {
                    btnContinueToEmail.setEnabled(true);
                    btnContinueToEmail.setBackgroundResource(R.drawable.orange_rounded_button);
                }
            }
        });

        
        btnContinueToEmail.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                StringBuilder bodyText = new StringBuilder(
                        "\n\n\n\n\n#### Please do not edit any information below ####\n");
                if (vpnHostnameSwitch.isChecked()) {
                    bodyText.append("\n\nVPN Hostname\n" + BraveVpnPrefUtils.getHostname());
                }
                if (subscriptionTypeSwitch.isChecked()) {
                    bodyText.append("\n\nSubscription Type\n" + BraveVpnPrefUtils.getProductId());
                }
                if (appReceiptSwitch.isChecked()) {
                    bodyText.append(
                            "\n\nPlay store token\n" + BraveVpnPrefUtils.getPurchaseToken());
                }
                if (appVersionSwitch.isChecked()) {
                    bodyText.append("\n\nApp Version\n"
                            + AboutChromeSettings.getApplicationVersion(
                                    BraveVpnSupportActivity.this,
                                    AboutSettingsBridge.getApplicationVersion()));
                }
                if (timezoneSwitch.isChecked()) {
                    bodyText.append("\n\nTimezone\n").append(TimeZone.getDefault().getID());
                }
                if (networkTypeSwitch.isChecked()) {
                    bodyText.append("\n\nNetwork Type\n").append(getNetworkType());
                }
                if (cellularCarrierSwitch.isChecked()) {
                    bodyText.append("\n\nCellular Carrier\n").append(getCellularCarrier());
                }

                bodyText.append("\n\nOther Issue\n");
                AppCompatRadioButton checkedRadioButton =
                        findViewById(otherIssuesRadioGroup.getCheckedRadioButtonId());
                bodyText.append(checkedRadioButton.getText() + "\n");
                bodyText.append("\n\nPlatform\n")
                        .append("Android"
                                + "\n");

                composeEmail(bodyText.toString());
            }
        });
    }

    @Override
    protected void triggerLayoutInflation() {
        mFirstRunFlowSequencer = new BraveFirstRunFlowSequencer(this) {
            @Override
            public void onFlowIsKnown(Bundle freProperties) {
                initializeViews();
            }
        };
        mFirstRunFlowSequencer.start();
        onInitialLayoutInflationComplete();
    }

    @Override
    public boolean shouldStartGpuProcess() {
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
        }
        return super.onOptionsItemSelected(item);
    }

    private void composeEmail(String body) {
        Intent intent = new Intent(Intent.ACTION_SENDTO);
        intent.setData(Uri.parse("mailto:")); // only email apps should handle this
        intent.putExtra(Intent.EXTRA_EMAIL, new String[] {"braveandroid@guardianapp.com"});
        intent.putExtra(Intent.EXTRA_SUBJECT, "Brave Firewall + VPN Issue");
        intent.putExtra(Intent.EXTRA_TEXT, body);
        finish();
        startActivity(intent);
    }

    private String getNetworkType() {
        ConnectivityManager cm =
                (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
        if (activeNetwork != null) {
            // connected to the internet
            if (activeNetwork.getType() == ConnectivityManager.TYPE_WIFI) {
                // connected to wifi
                return activeNetwork.getTypeName();
            } else if (activeNetwork.getType() == ConnectivityManager.TYPE_MOBILE) {
                // connected to the mobile provider's data plan
                return activeNetwork.getTypeName();
            }
        }
        return "";
    }

    private String getCellularCarrier() {
        TelephonyManager telephonyManager =
                ((TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE));
        return telephonyManager.getNetworkOperatorName();
    }
}
