export interface ComponentsItemProps {
  type: string;
  icon: string;
  onClick: () => void;
  width: number;
  height: number;
}

function ComponentsItem({
  type,
  icon,
  width,
  height,
  onClick,
}: ComponentsItemProps) {
  return <button onClick={onClick}>{type}</button>;
}

export default ComponentsItem;
