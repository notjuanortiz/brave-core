/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_NODE_PARSER_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_NODE_PARSER_H_

#include <string>
#include "brave/third_party/blink/brave_page_graph/graph_item/node/node_actor.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class PageGraph;

class NodeParser final : public NodeActor {
friend class PageGraph;
 public:
  NodeParser() = delete;
  ~NodeParser() override;
  ItemName GetItemName() const override;
  bool IsParser() const override;

 protected:
  NodeParser(PageGraph* const graph);
  GraphMLXMLList GraphMLAttributes() const override;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_NODE_NODE_PARSER_H_
