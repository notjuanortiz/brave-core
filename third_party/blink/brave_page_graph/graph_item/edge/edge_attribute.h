/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_ATTRIBUTE_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_ATTRIBUTE_H_

#include <string>
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class Node;
class NodeActor;
class PageGraph;

class EdgeAttribute : public Edge {
friend class PageGraph;
 public:
  EdgeAttribute() = delete;
  const std::string& GetAttributeName() const;
  bool GetIsStyle() const;

 protected:
  EdgeAttribute(PageGraph* const graph, NodeActor* const out_node,
    Node* const in_node, const std::string& name,
    const bool is_style = false);
  GraphMLXMLList GraphMLAttributes() const override;

  const bool is_style_;
  const std::string name_;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_ATTRIBUTE_H_
