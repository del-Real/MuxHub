import Versions from './components/Versions'

function App(): JSX.Element {
  return (
    <div className="container">
      {/* --- LEFT PANEL --- */}
      <div className="left-panel">
        <h2>LEFT PANEL</h2>
        <Versions></Versions>
      </div>

      {/* --- MAIN PANEL --- */}
      <div className="main-panel">
        <h2>MAIN PANEL</h2>
        <Versions></Versions>
      </div>

      {/* --- RIGHT PANEL --- */}
      <div className="right-panel">
        <h2>RIGHT PANEL</h2>
        <Versions></Versions>
      </div>
    </div>
  )
}

export default App
