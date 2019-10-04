/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_storage_delete.h"
#include <string>
#include "brave/third_party/blink/brave_page_graph/graphml.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_storage.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_actor.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_storage.h"
#include "brave/third_party/blink/brave_page_graph/page_graph.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

using ::std::string;

namespace brave_page_graph {

EdgeStorageDelete::EdgeStorageDelete(PageGraph* const graph,
    NodeActor* const out_node, NodeStorage* const in_node,
    const string& key) :
      EdgeStorage(graph, out_node, in_node, key) {}

EdgeStorageDelete::~EdgeStorageDelete() {}

ItemName EdgeStorageDelete::GetItemName() const {
  return "EdgeStorageDelete#" + ::std::to_string(id_);
}

GraphMLXMLList EdgeStorageDelete::GraphMLAttributes() const {
  GraphMLXMLList items = EdgeStorage::GraphMLAttributes();
  items.push_back(
    graphml_attr_def_for_type(kGraphMLAttrDefEdgeType)->ToValue("delete"));
  return items;
}

}  // namespace brave_page_graph
