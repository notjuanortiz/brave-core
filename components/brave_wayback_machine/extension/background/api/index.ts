/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * Updates a given tab with the specified URL
 * @param {number} tabId - The specified tab id
 * @param {string} url - The page url
 */
export function updateURL (tabId: number, url: string) {
  chrome.tabs.update(tabId, { url })
}

