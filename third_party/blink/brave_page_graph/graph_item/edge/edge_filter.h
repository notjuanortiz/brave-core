/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_FILTER_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_FILTER_H_

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include <string>
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class NodeFilter;
class NodeShield;
class PageGraph;

class EdgeFilter : public Edge {
friend class PageGraph;
 public:
  EdgeFilter() = delete;
  ~EdgeFilter() override;

  ItemName GetItemName() const override;

 protected:
  EdgeFilter(PageGraph* const graph, NodeShield* const out_node,
    NodeFilter* const in_node);

  GraphMLXMLList GraphMLAttributes() const override;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_FILTER_H_
