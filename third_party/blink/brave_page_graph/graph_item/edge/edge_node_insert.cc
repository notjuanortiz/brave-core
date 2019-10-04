/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_node_insert.h"
#include <string>
#include "third_party/blink/renderer/core/dom/dom_node_ids.h"
#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_node.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_html_element.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_html.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_actor.h"
#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

using ::blink::DOMNodeId;
using ::std::string;
using ::std::to_string;

namespace brave_page_graph {

EdgeNodeInsert::EdgeNodeInsert(PageGraph* const graph,
    NodeActor* const out_node, NodeHTML* const in_node,
    const DOMNodeId parent_id, const DOMNodeId prior_sibling_id) :
      EdgeNode(graph, out_node, in_node),
      parent_id_(parent_id),
      prior_sibling_id_(prior_sibling_id) {}

EdgeNodeInsert::~EdgeNodeInsert() {}

NodeHTMLElement* EdgeNodeInsert::GetParentNode() const {
  return parent_id_ ? graph_->GetHTMLElementNode(parent_id_) : nullptr;
}

NodeHTML* EdgeNodeInsert::GetPriorSiblingNode() const {
  return prior_sibling_id_ ? graph_->GetHTMLNode(prior_sibling_id_) : nullptr;
}

ItemName EdgeNodeInsert::GetItemName() const {
  return "EdgeNodeInsert#" + to_string(id_);
}

ItemDesc EdgeNodeInsert::GetDescBody() const {
  return GetItemName() +
    " [parent:" + to_string(parent_id_) +
    ", sibling:" + to_string(prior_sibling_id_) + "]";
}

GraphMLXMLList EdgeNodeInsert::GraphMLAttributes() const {
  GraphMLXMLList attrs; {
  attrs.push_back(graphml_attr_def_for_type(kGraphMLAttrDefEdgeType)
      ->ToValue("insert"));

  if (parent_id_) {
    attrs.push_back(graphml_attr_def_for_type(kGraphMLAttrDefParentNodeId)
        ->ToValue(parent_id_));
  }

  if (prior_sibling_id_)
    attrs.push_back(graphml_attr_def_for_type(kGraphMLAttrDefBeforeNodeId)
        ->ToValue(prior_sibling_id_));
  }

  return attrs;
}

}  // namespace brave_page_graph
