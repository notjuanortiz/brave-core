/* Copyright (c) 2019 The Brave Software Team. Distributed under the MPL2
 * license. This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_HTML_H_
#define BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_HTML_H_

#include "brave/third_party/blink/brave_page_graph/graph_item/edge/edge.h"
#include "brave/third_party/blink/brave_page_graph/types.h"

namespace brave_page_graph {

class NodeHTML;
class NodeHTMLElement;
class PageGraph;

class EdgeHTML : public Edge {
// Needed for generating edges during GraphML export
friend class NodeHTMLElement;
friend class PageGraph;
 public:
  EdgeHTML() = delete;
  ~EdgeHTML() override;
  ItemName GetItemName() const override;

 protected:
  EdgeHTML(PageGraph* const graph, NodeHTMLElement* const out_node,
    NodeHTML* const in_node);

  // Only used for generating edges during GraphML export.
  EdgeHTML(const NodeHTMLElement* const out_node,
    NodeHTML* const in_node);
  GraphMLXML GetGraphMLTag() const override;
  GraphMLXMLList GraphMLAttributes() const override;
};

}  // namespace brave_page_graph

#endif  // BRAVE_COMPONENTS_BRAVE_PAGE_GRAPH_GRAPH_ITEM_EDGE_EDGE_HTML_H_
