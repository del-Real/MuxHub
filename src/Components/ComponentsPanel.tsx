import ComponentButton from "./ComponentButton";

function ComponentsPanel({ onAddNode }: { onAddNode: () => void }) {
  return (
    <div className="components-panel">
      <h3>Components</h3>
      <ComponentButton title="NOT" onClick={onAddNode} />
    </div>
  );
}

export default ComponentsPanel;
