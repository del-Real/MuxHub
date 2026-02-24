import { Background, Handle, Position } from "@xyflow/react";

function TestNode() {
  return (
    <div className="testnode-main">
      <div>TestNode</div>
      <Handle
        type="target"
        position={Position.Left}
        style={{ background: "#fff" }}
        id="005"
      />
      <Handle type="source" position={Position.Right} id="002" />
    </div>
  );
}

export default TestNode;
