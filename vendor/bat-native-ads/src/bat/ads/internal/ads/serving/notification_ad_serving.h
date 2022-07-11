/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_NOTIFICATION_AD_SERVING_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_NOTIFICATION_AD_SERVING_H_

#include <memory>
#include <string>

#include "base/observer_list.h"
#include "bat/ads/internal/ads/serving/notification_ad_serving_observer.h"
#include "bat/ads/internal/base/timer/timer.h"
#include "bat/ads/internal/prefs/pref_manager_observer.h"
#include "bat/ads/internal/segments/segments_aliases.h"

namespace base {
class Time;
class TimeDelta;
}  // namespace base

namespace ads {

namespace geographic {
class SubdivisionTargeting;
}  // namespace geographic

namespace resource {
class AntiTargeting;
}  // namespace resource

struct NotificationAdInfo;

namespace notification_ads {

class EligibleAdsBase;

class Serving final : public PrefManagerObserver {
 public:
  Serving(geographic::SubdivisionTargeting* subdivision_targeting,
          resource::AntiTargeting* anti_targeting_resource);
  ~Serving() override;
  Serving(const Serving&) = delete;
  Serving& operator=(const Serving&) = delete;

  void AddObserver(ServingObserver* observer);
  void RemoveObserver(ServingObserver* observer);

  void StartServingAdsAtRegularIntervals();
  void StopServingAdsAtRegularIntervals();

  void MaybeServeAd();

 private:
  void OnAdsPerHourPrefChanged();

  bool IsSupported() const;

  bool ShouldServeAdsAtRegularIntervals() const;
  bool HasPreviouslyServedAnAd() const;
  bool ShouldServeAd() const;
  base::TimeDelta CalculateDelayBeforeServingAnAd() const;
  void MaybeServeAdAtNextRegularInterval();
  void RetryServingAdAtNextInterval();
  base::Time MaybeServeAdAfter(const base::TimeDelta delay);

  void ServeAd(const NotificationAdInfo& ad);
  void FailedToServeAd();

  void NotifyOpportunityAroseToServeNotificationAd(
      const SegmentList& segments) const;
  void NotifyDidServeNotificationAd(const NotificationAdInfo& ad) const;
  void NotifyFailedToServeNotificationAd() const;

  // PrefManagerObserver:
  void OnPrefChanged(const std::string& path) override;

  base::ObserverList<ServingObserver> observers_;

  bool is_serving_ = false;

  Timer timer_;

  std::unique_ptr<EligibleAdsBase> eligible_ads_;
};

}  // namespace notification_ads
}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_SERVING_NOTIFICATION_AD_SERVING_H_