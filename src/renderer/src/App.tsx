import Viewport from './components/Viewport/Viewport'

function App(): JSX.Element {
  function createComponent() {
    console.log('NOT GATE')
  }
  return (
    <div className="container">
      {/* --- LEFT PANEL --- */}
      <div className="left-panel">
        <h2>Gates</h2>
        <button onClick={createComponent}>NOT GATE</button>
      </div>

      {/* --- MAIN PANEL --- */}
      <div className="main-panel">
        <Viewport />
      </div>

      {/* --- RIGHT PANEL --- */}
      <div className="right-panel">
        <h2>Properties</h2>
      </div>
    </div>
  )
}

export default App
