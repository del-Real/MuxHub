import ComponentsItem from "./ComponentsItem";
import type { ComponentsItemProps } from "./ComponentsItem";

function ComponentsGroup({
  title,
  items,
}: {
  title: string;
  items: Array<ComponentsItemProps>;
}) {
  return (
    <div>
      <h1>{title}</h1>
      {items.map((item) => (
        <ComponentsItem key={item.type} {...item} />
      ))}
    </div>
  );
}

export default ComponentsGroup;
