/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/android/preferences/background_video_playback_tab_helper.h"

#include <string>

#include "base/strings/utf_string_conversions.h"
#include "brave/common/pref_names.h"
#include "chrome/browser/profiles/profile.h"
#include "components/prefs/pref_service.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/navigation_entry.h"
#include "content/public/browser/web_contents.h"
#include "content/public/renderer/render_frame.h"
#include "content/public/browser/navigation_handle.h"
#include "url/gurl.h"

namespace {
const char k_youtube_background_playback_script[] =
    "(function() {"
    "    var lastTimeHidden = null;"
    "    document.addEventListener('visibilitychange', function() {"
    "        if (document.hidden) {"
    "            lastTimeHidden = Date.now();"
    "        }"
    "    }, false);"
    "    var doReplacePause = function(video) {"
    "        if (video.originalPause === undefined) {"
    "            video.originalPause = video.pause;"
    "            video.pause = function() {"
    "                if (document.visibilityState == 'visible' ||"
    "                    lastTimeHidden == null ||"
    "                    (lastTimeHidden != null &&"
    "                         Date.now() - lastTimeHidden > 200)) {"
    "                    video.originalPause();"
    "                } else {"
    "                    callUndefinedFn();"
    "                }"
    "            }"
    "        }"
    "    };"
    "    var setupObserverAttempts = 0;"
    "    var setupObserver = function() {"
    "        var observer = new MutationObserver(function(mutations) {"
    "            mutations.forEach(function(mutation) {"
    "                if (mutation.type === 'attributes' &&"
    "                     mutation.attributeName === 'src' &&"
    "                     mutation.target.nodeName === 'VIDEO') {"
    "                    doReplacePause(mutation.target);"
    "                }"
    "                if (mutation.type === 'childList') {"
    "                    for (var i = 0; i < mutation.addedNodes.length; i++) {"
    "                        if (mutation.addedNodes[i].nodeName === 'VIDEO') {"
    "                            doReplacePause(mutation.addedNodes[i]);"
    "                        }"
    "                    }"
    "                }"
    "            });"
    "        });"
    "        var target = document.querySelector('html');"
    "        var config = {"
    "            childList: true,"
    "            attributes: true,"
    "            subtree: true,"
    "            characterData: true"
    "        };"
    "        if (target) {"
    "            observer.observe(target, config);"
    "        } else if (setupObserverAttempts < 10) {"
    "            setTimeout(setupObserver, 100);"
    "            ++setupObserverAttempts;"
    "        }"
    "    };"
    "    setTimeout(setupObserver, 100);"
    "}());";

bool IsBackgroundVideoPlaybackEnabled(content::WebContents* contents) {
  PrefService* prefs =
      static_cast<Profile*>(contents->GetBrowserContext())->GetPrefs();
  const std::string url = contents->GetLastCommittedURL().spec();
  return url.find("https://m.youtube.com/watch?v") != std::string::npos &&
         prefs->GetBoolean(kBackgroundVideoPlaybackEnabled);
}

}  // namespace

BackgroundVideoPlaybackTabHelper::BackgroundVideoPlaybackTabHelper(
    content::WebContents* contents)
    : WebContentsObserver(contents) {
}

BackgroundVideoPlaybackTabHelper::~BackgroundVideoPlaybackTabHelper() {
}

void BackgroundVideoPlaybackTabHelper::DidFinishNavigation(
    content::NavigationHandle* navigation_handle) {
  if (IsBackgroundVideoPlaybackEnabled(web_contents())) {
    web_contents()->GetMainFrame()->ExecuteJavaScript(
        base::UTF8ToUTF16(k_youtube_background_playback_script),
        base::NullCallback());
  }
}

WEB_CONTENTS_USER_DATA_KEY_IMPL(BackgroundVideoPlaybackTabHelper)
