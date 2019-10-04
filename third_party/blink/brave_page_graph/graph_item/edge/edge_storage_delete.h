/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_STORAGE_DELETE_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_STORAGE_DELETE_H_

#include <string>
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge_storage.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class Node;
class NodeActor;
class NodeStorage;
class PageGraph;

class EdgeStorageDelete final : public EdgeStorage {
friend class PageGraph;
 public:
  EdgeStorageDelete() = delete;
  ~EdgeStorageDelete() override;
  ItemName GetItemName() const override;

 protected:
  EdgeStorageDelete(PageGraph* const graph, NodeActor* const out_node,
    NodeStorage* const in_node, const std::string& key);
  GraphMLXMLList GraphMLAttributes() const override;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_STORAGE_DELETE_H_
