/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_storage.h"
#include <string>
#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_actor.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_storage.h"
#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

using ::std::string;

namespace brave_page_graph {

EdgeStorage::EdgeStorage(PageGraph* const graph,
    NodeActor* const out_node, NodeStorage* const in_node,
    const string& key) :
      Edge(graph, out_node, in_node),
      key_(key) {}

ItemName EdgeStorage::GetDescBody() const {
  return GetItemName() + " [key:" + key_ + "]";
}

GraphMLXMLList EdgeStorage::GraphMLAttributes() const {
  return {
    graphml_attr_def_for_type(kGraphMLAttrDefKey)
      ->ToValue(key_)
  };
}

}  // namespace brave_page_graph
