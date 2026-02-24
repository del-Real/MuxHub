import { useState, useCallback } from "react";
import { Position, type Node, type Edge } from "@xyflow/react";
import Viewport from "./Components/Viewport.tsx";
import ComponentsPanel from "./Components/ComponentsPanel.tsx";
import PropertiesPanel from "./Components/PropertiesPanel.tsx";

let id = 6;
const getId = () => `${id++}`;

const nodeDefaults = {
  sourcePosition: Position.Right,
  targetPosition: Position.Left,
};

const initialNodes: Node[] = [
  {
    id: "1",
    position: { x: 0, y: 150 },
    data: { label: "Node 1" },
    ...nodeDefaults,
  },
  {
    id: "2",
    position: { x: 250, y: 0 },
    data: { label: "Node 2" },
    ...nodeDefaults,
  },
  {
    id: "3",
    position: { x: 250, y: 150 },
    data: { label: "n 3" },
    ...nodeDefaults,
  },
  {
    id: "4",
    position: { x: 250, y: 300 },
    data: { label: "nn4" },
    ...nodeDefaults,
  },
  {
    id: "5",
    position: { x: 350, y: 600 },
    data: {},
    type: "TestNode",
    ...nodeDefaults,
  },
];

const initialEdges: Edge[] = [
  { id: "e1-2", source: "1", target: "2", animated: true },
  { id: "e1-3", source: "1", target: "3" },
  { id: "e1-4", source: "1", target: "4" },
];

function App() {
  const [nodes, setNodes] = useState<Node[]>(initialNodes);
  const [edges, setEdges] = useState<Edge[]>(initialEdges);

  const addNode = useCallback(() => {
    const newNode: Node = {
      id: getId(),
      position: { x: Math.random() * 400, y: Math.random() * 400 },
      data: { label: `Node ${id - 1}` },
      ...nodeDefaults,
    };
    setNodes((prev) => [...prev, newNode]);
  }, []);

  return (
    <div style={{ display: "flex", width: "100vw", height: "100vh" }}>
      <ComponentsPanel onAddNode={addNode} />
      <Viewport
        nodes={nodes}
        setNodes={setNodes}
        edges={edges}
        setEdges={setEdges}
      />
      <PropertiesPanel />
    </div>
  );
}

export default App;
