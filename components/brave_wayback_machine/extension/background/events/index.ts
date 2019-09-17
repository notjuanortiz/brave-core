/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { shouldRedirectUsers } from '../actions'
import { statusCode } from '../../utils'

chrome.webRequest.onHeadersReceived.addListener(details => {
  // Once headers are received, listen to tab updates.
  // TODO: this is only needed as a way to fire the execution of our content script.
  // Once this banner is implemented in the way it should, all the code below should be removed.
  chrome.tabs.onUpdated.addListener(_ => {
    // only proceed this call if header response is something we care about
    if (!statusCode.includes(details.statusCode)) {
      return
    }
    // Execute the script that will generate the HTML banner
    // TODO: this should call the C++ back-end that shows the native
    // banner dialog and no script should be executed. This is for demo only.
    chrome.tabs.executeScript(details.tabId, {
      file: 'extension/out/brave_wayback_machine_content.bundle.js',
      runAt: 'document_end'
    }, () => {
      // listen to the button click thta will send the message
      // authorizing the page redirect.
      // TODO: This should not be included when the proper banner is implemented.
      chrome.runtime.onMessage.addListener(message => {
        if (message.authorizeRedirect) {
          if (details.url) {
            shouldRedirectUsers(details.tabId, details.url)
          }
        }
      })
    })
  })
},
  {
    urls: [ '<all_urls>' ],
    types: ['main_frame']
  },
  ['blocking']
)
