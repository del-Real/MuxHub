import React, { useState, useCallback } from 'react'
import ReactFlow, {
  Background,
  Controls,
  applyNodeChanges,
  applyEdgeChanges,
  addEdge,
  Position
} from 'reactflow'
import 'reactflow/dist/style.css'
import NOT_gate from './components/Gates/NOT_gate'

const attrb = { hideAttribution: true }

const nodeDefaults = {
  sourcePosition: Position.Right,
  targetPosition: Position.Left
}

const initialNodes = [
  {
    id: 'node-1',
    type: 'NOT_gate',
    position: { x: 0, y: 0 },
    data: { value: 123 }
  },
  {
    id: '2',
    position: { x: 250, y: 0 },
    data: { label: 'Output' },
    ...nodeDefaults
  }
]

const initialEdges = []
const nodeTypes = { NOT_gate: NOT_gate }

function Flow() {
  const [nodes, setNodes] = useState(initialNodes)
  const [edges, setEdges] = useState(initialEdges)

  const onNodesChange = useCallback(
    (changes) => setNodes((nds) => applyNodeChanges(changes, nds)),
    []
  )

  const onEdgesChange = useCallback(
    (changes) => setEdges((eds) => applyEdgeChanges(changes, eds)),
    []
  )

  const onConnect = useCallback((params) => setEdges((eds) => addEdge(params, eds)), [])

  const createNode = () => {
    const newNode = {
      id: (nodes.length + 1).toString(), // Generate unique ID
      type: 'NOT_gate', // Specify the type of the node
      position: { x: 50, y: 50 }, // Initial position of the new node
      data: { label: `NOT Gate ${nodes.length + 1}` } // Label for the new node
    }
    setNodes((prevNodes) => [...prevNodes, newNode]) // Add the new node to the nodes array
  }

  return (
    <div>
      <div className="container">
        {/* --- LEFT PANEL --- */}
        <div className="left-panel">
          <h2>Gates</h2>
          <button onClick={createNode}>NOT GATE</button> {/* Button to create a new node */}
        </div>

        {/* --- VIEWPORT --- */}
        <div className="main-panel">
          <div style={{ height: '100%' }}>
            <ReactFlow
              nodes={nodes}
              nodeTypes={nodeTypes}
              onNodesChange={onNodesChange}
              edges={edges}
              onEdgesChange={onEdgesChange}
              onConnect={onConnect}
              fitView
              proOptions={attrb}
            >
              <Background />
              <Controls />
            </ReactFlow>
          </div>
        </div>

        {/* --- RIGHT PANEL --- */}
        <div className="right-panel">
          <h2>Properties</h2>
        </div>
      </div>
    </div>
  )
}

export default Flow
