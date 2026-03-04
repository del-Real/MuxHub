import { useCallback, useState } from "react";
import {
  ReactFlow,
  Controls,
  Background,
  addEdge,
  applyNodeChanges,
  applyEdgeChanges,
  type Node,
  type Edge,
  type FitViewOptions,
  type OnConnect,
  type OnNodesChange,
  type OnEdgesChange,
  type DefaultEdgeOptions,
  type OnSelectionChangeParams,
} from "@xyflow/react";
import "@xyflow/react/dist/style.css";
import TestNode from "./gates/TestNode.tsx";
import type { NodeData } from "./NodeData";

const styles = { display: "flex", width: "100vw", height: "100vh" };
const fitViewOptions: FitViewOptions = { padding: 0.2 };
const defaultEdgeOptions: DefaultEdgeOptions = { animated: true };
const proOptions = { hideAttribution: true };
const nodeTypes = { TestNode: TestNode };

function Viewport({
  nodes,
  setNodes,
  edges,
  setEdges,
}: {
  nodes: Node[];
  setNodes: React.Dispatch<React.SetStateAction<Node[]>>;
  edges: Edge[];
  setEdges: React.Dispatch<React.SetStateAction<Edge[]>>;
}) {
  const [selectedNode, setSelectedNode] = useState<Node<NodeData> | null>(null);

  const onNodesChange: OnNodesChange = useCallback(
    (changes) => setNodes((nds) => applyNodeChanges(changes, nds)),
    [setNodes],
  );

  const onEdgesChange: OnEdgesChange = useCallback(
    (changes) => setEdges((eds) => applyEdgeChanges(changes, eds)),
    [setEdges],
  );

  const onConnect: OnConnect = useCallback(
    (connection) => setEdges((eds) => addEdge(connection, eds)),
    [setEdges],
  );

  const onSelectionChange = useCallback(
    ({ nodes }: OnSelectionChangeParams) => {
      setSelectedNode((nodes[0] as Node<NodeData>) ?? null);
    },
    [],
  );

  return (
    <div style={styles}>
      <ReactFlow
        nodes={nodes}
        edges={edges}
        nodeTypes={nodeTypes}
        onNodesChange={onNodesChange}
        onEdgesChange={onEdgesChange}
        onSelectionChange={onSelectionChange}
        onConnect={onConnect}
        fitView
        fitViewOptions={fitViewOptions}
        defaultEdgeOptions={defaultEdgeOptions}
        proOptions={proOptions}
      >
        {selectedNode && (
          <div
            style={{
              position: "absolute",
              right: 0,
              top: 0,
              padding: 16,
              background: "#fff",
              zIndex: 3,
            }}
          >
            <h3>{selectedNode.data.label}</h3>
            <p>ID: {selectedNode.id}</p>
            {selectedNode.data.bytes && (
              <p>Bytes: {selectedNode.data.bytes.join(", ")}</p>
            )}
          </div>
        )}
        <Background />
        <Controls position="top-right" style={{ right: "13vw" }} />
      </ReactFlow>
    </div>
  );
}

export default Viewport;
