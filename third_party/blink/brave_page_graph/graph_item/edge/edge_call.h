/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_CALL_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_CALL_H_

#include <string>
#include <vector>
#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class Node;
class NodeScript;
class NodeWebAPI;
class PageGraph;

class EdgeCall final : public virtual Edge {
friend class PageGraph;
 public:
  EdgeCall() = delete;
  ~EdgeCall() override;
  ItemName GetItemName() const override;
  const std::vector<const std::string>& GetArguments() const;
  std::string GetArgumentsString() const;

 protected:
  EdgeCall(PageGraph* const graph, NodeScript* const out_node,
    NodeWebAPI* const in_node, const std::string& method,
    const std::vector<const std::string>& arguments);
  ItemDesc GetDescBody() const override;
  GraphMLXMLList GraphMLAttributes() const override;

  const std::string method_;
  const std::vector<const std::string> arguments_;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_CALL_H_
