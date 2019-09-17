/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import '../css/banner.css'

// Helpers
import { delegateClickEvent }  from '../utils'

const div = document.createElement('div')
div.className = 'banner-wayback-machine-banner'
div.innerHTML = `
  <div>
    <h1>404</h1>
  </div>
  <div>
    <strong>Sorry, that page is missing.</strong> Do you want to check if a saved version is available on the Wayback Machine?
  </div>
  <div>
    <button id="action" class="button-wayback-machine-banner">Check for saved version</button>
    <button id="close" class="close-button-wayback-machine-banner" title="Close this banner">&times;</button>
  </div>
`
document.body.appendChild(div)

delegateClickEvent('button-wayback-machine-banner', () => {
  chrome.runtime.sendMessage({ authorizeRedirect: true })
})

delegateClickEvent('close-button-wayback-machine-banner', () => {
  div.classList.add('banner-wayback-machine-banner-hidden')
})
