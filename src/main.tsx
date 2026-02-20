import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import "./index.css";
import Viewport from "./App.tsx";
import ComponentsPanel from "./ComponentsPanel.tsx";
import PropertiesPanel from "./PropertiesPanel.tsx";

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <ComponentsPanel />
    <PropertiesPanel />
    <Viewport />
  </StrictMode>,
);
