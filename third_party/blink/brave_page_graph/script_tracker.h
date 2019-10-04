/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_SCRIPT_TRACKER_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_SCRIPT_TRACKER_H_

#include <map>
#include <vector>
#include "brave/third_party/blink/brave_page_graph/types.h"

// Tracking <script> elements to compiled V8 code units.
//
// This will likely exist as one-to-one with instances of
// brave_page_graph::PageGraph objects, but is all hoisted here to keep
// that class from getting out of control in size.
// ---
// The following eight maps are all used for keeping track of which
// script unit belongs to which page element.  Because different pieces
// of information are available at different points in time (and processed
// away at other points), we need this semi-convoluted system.  At
// a high level, we do the following (indexed and reverse indexed):
//   1) Associate the <script> element with the JS code unit (either
//      by the code itself, for inline script, or the URL of the code
//      for remote code).
//   2) For remote fetched code, associate the fetched / compiled JS
//      with the URL it came from.
//   3) Associate the compiled JS code with the V8 assigned "script id"
//      (the identifer v8 uses internally for referring to each script within
//      a context).
// 
// Maps used for step 1.  Maps are from node id to multiple script hashes
// because its possible that the text of a script tag could change over time,
// (e.g. changing the src attr of the script element to point to a new
// URL, changing the innerText of the <script> element).

namespace brave_page_graph {

typedef enum {
  kScriptTrackerScriptSourceUnknown = 0,
  kScriptTrackerScriptSourceExtension,
  kScriptTrackerScriptSourcePage,  
} ScriptTrackerScriptSource;

class ScriptTracker {
 public:
  ScriptTracker();
  ~ScriptTracker();

  // Public methods used for step 1 above.
  void AddScriptUrlForElm(const blink::KURL& url,
    const blink::DOMNodeId node_id);
  void AddScriptSourceForElm(const blink::ScriptSourceCode& code,
    const blink::DOMNodeId node_id);

  // Method used for step 2 above.
  void AddCodeFetchedFromUrl(const blink::ScriptSourceCode& code,
    const blink::KURL& url);
  void AddExtensionCodeFetchedFromUrl(const SourceCodeHash code_hash,
    const UrlHash url_hash);

  // Method used for step 3 above.
  void SetScriptIdForCode(const ScriptId script_id,
    const blink::ScriptSourceCode& code);

  ScriptTrackerScriptSource GetSourceOfScript(const ScriptId script_id) const;

  std::vector<blink::DOMNodeId> GetElmsForScriptId(
    const ScriptId script_id) const;
  std::vector<ScriptId> GetScriptIdsForElm(
    const blink::DOMNodeId node_id) const;

  void AddTopLevelScriptId(const ScriptId script_id);
  void AddChildScriptIdForParentScriptId(const ScriptId child_script_id,
    const ScriptId parent_script_id);
  ScriptId TopLevelScriptIdForScriptId(const ScriptId script_id) const;

 private:
   ScriptId GetParentScriptIdForChildScriptId(const ScriptId script_id) const;

  // Data structures used for step 1 above (note that values are vectors
  // since the same script element can be made to multiple URLs and / or
  // change in-place code over time).  Similarly, there can be multiple
  // <script> nodes on the page that point to the same URL (unlikely, but
  // valid).
  std::map<blink::DOMNodeId, std::vector<UrlHash>> node_id_to_script_url_hashes_;
  std::map<UrlHash, std::vector<blink::DOMNodeId>> script_src_hash_to_node_ids_;
  std::map<blink::DOMNodeId, std::vector<SourceCodeHash>> node_id_to_source_hashes_;
  std::map<SourceCodeHash, std::vector<blink::DOMNodeId>> source_hash_to_node_ids_;

  //  Maps used for step 2.
  std::map<UrlHash, SourceCodeHash> script_url_hash_to_source_hash_;
  std::map<SourceCodeHash, UrlHash> source_hash_to_script_url_hash_;

  std::map<SourceCodeHash, UrlHash> extension_source_hash_to_script_url_hash_;
  std::map<UrlHash, SourceCodeHash> extension_script_url_hash_to_source_hash_;

  //  Maps used for step 3.
  std::map<SourceCodeHash, ScriptId> source_hash_to_script_id_;
  std::map<ScriptId, SourceCodeHash> script_id_to_source_hash_;

  std::map<SourceCodeHash, ScriptId> extension_source_hash_to_script_id_;
  std::map<ScriptId, SourceCodeHash> script_id_to_extension_source_hash_;

  // Maps used for associating child scripts with a parent script.
  std::map<ScriptId, ScriptId> parent_script_ids_;
  std::map<ScriptId, ScriptId> child_to_parent_script_;
  ScriptId max_script_id_ = 0;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_SCRIPT_TRACKER_H_
