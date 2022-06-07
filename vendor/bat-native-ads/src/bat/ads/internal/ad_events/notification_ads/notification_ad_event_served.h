/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_SERVED_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_SERVED_H_

#include "bat/ads/internal/ad_events/ad_event_interface.h"
#include "bat/ads/notification_ad_info.h"

namespace ads {
namespace notification_ads {

class AdEventServed final : public AdEventInterface<NotificationAdInfo> {
 public:
  AdEventServed();
  ~AdEventServed() override;
  AdEventServed(const AdEventServed&) = delete;
  AdEventServed& operator=(const AdEventServed&) = delete;

  void FireEvent(const NotificationAdInfo& ad) override;
};

}  // namespace notification_ads
}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_EVENTS_NOTIFICATION_ADS_NOTIFICATION_AD_EVENT_SERVED_H_