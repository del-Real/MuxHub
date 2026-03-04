import ComponentsGroup from "./ComponentsGroup";
import type { ComponentsItemProps } from "./ComponentsItem";

const IOComponents: Array<ComponentsItemProps> = [
  {
    type: "Constant",
    icon: "null",
    width: 50,
    height: 50,
    onClick: () => console.log("Constant clicked"),
  },
];

const GatesComponents: Array<ComponentsItemProps> = [
  {
    type: "NOT",
    icon: "null",
    width: 100,
    height: 50,
    onClick: () => console.log("NOT clicked"),
  },
];

function ComponentsPanel({ onAddNode }: { onAddNode: () => void }) {
  return (
    <div className="components-panel">
      <ComponentsGroup title="I/O" items={IOComponents} />
      <ComponentsGroup title="Gates" items={GatesComponents} />
    </div>
  );
}

export default ComponentsPanel;
