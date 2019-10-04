/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/types.h"
#include <string>
#include "third_party/blink/renderer/core/dom/dom_node_ids.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource.h"

using ::std::string;

namespace brave_page_graph {

string graphml_type_to_string(const GraphMLAttrType type) noexcept {
  switch (type) {
    case kGraphMLAttrTypeString:
      return "string";
    case kGraphMLAttrTypeBoolean:
      return "boolean";
    case kGraphMLAttrTypeInt:
      return "int";
    case kGraphMLAttrTypeLong:
      return "long";
    case kGraphMLAttrTypeFloat:
      return "float";
    case kGraphMLAttrTypeDouble:
      return "double";
    case kGraphMLAttrTypeUnknown:
    default:
      return "unknown";
  }
}

string graphml_for_to_string(const GraphMLAttrForType type) noexcept {
  switch (type) {
    case kGraphMLAttrForTypeNode:
      return "node";
    case kGraphMLAttrForTypeEdge:
      return "edge";
    case kGraphMLAttrForTypeUnknown:
    default:
      return "unknown";
  }
}

string request_type_to_string(const RequestType type) noexcept {
  switch (type) {
    case kRequestTypeImage:
      return "Image";
    case kRequestTypeScriptClassic:
      return "ScriptClassic";
    case kRequestTypeScriptModule:
      return "ScriptModule";
    case kRequestTypeCSS:
      return "CSS";
    case kRequestTypeVideo:
      return "Video";
    case kRequestTypeAudio:
      return "Audio";
    case kRequestTypeSVG:
      return "SVG";
    case kRequestTypeFont:
      return "Font";
    case kRequestTypeDocument:
      return "Document";
    case kRequestTypeUnknown:
    default:
      return "Unknown";
  }
}

string resource_type_to_string(const blink::ResourceType type) noexcept {
  switch (type) {
    case blink::ResourceType::kImage:
      return "image";
    case blink::ResourceType::kCSSStyleSheet:
      return "css";
    case blink::ResourceType::kScript:
      return "script";
    case blink::ResourceType::kFont:
      return "font";
    case blink::ResourceType::kRaw:
      return "raw";
    case blink::ResourceType::kSVGDocument:
      return "svg";
    case blink::ResourceType::kXSLStyleSheet:
      return "XSL style sheet";
    case blink::ResourceType::kLinkPrefetch:
      return "link prefetch";
    case blink::ResourceType::kTextTrack:
      return "text track";
    case blink::ResourceType::kImportResource:
      return "import resource";
    case blink::ResourceType::kAudio:
      return "audio";
    case blink::ResourceType::kVideo:
      return "video";
    case blink::ResourceType::kManifest:
      return "manifest";
    default:
      return "unknown";
  }
}

string script_type_to_string(const ScriptType type) noexcept {
  switch (type) {
    case kScriptTypeClassic:
      return "classic";
    case kScriptTypeModule:
      return "module";
    case kScriptTypeExtension:
      return "extension";
    case kScriptTypeUnknown:
    default:
      return "unknown";
  }
}

string request_status_to_string(const RequestStatus status) noexcept {
  switch (status) {
    case kRequestStatusStart:
      return "started";
    case kRequestStatusComplete:
      return "complete";
    case kRequestStatusError:
      return "error";
    case kRequestStatusBlocked:
      return "blocked";
  }
}

}  // namespace brave_page_graph