import { useCallback } from 'react'
import { Handle, Position } from 'reactflow'
import NOT_ANSI from './NOT_ANSI.svg'

function NOT_gate() {
  const onChange = useCallback((evt) => {
    console.log(evt.target.value)
  }, [])

  return (
    <>
      <div
        style={{
          background: '#fff',
          padding: 10,
          borderRadius: 5,
          border: '1px solid #ccc',
          width: 50,
          height: 25
        }}
      >
        <img src={NOT_ANSI} style={{ width: '100%', height: 'auto' }} />
      </div>
      <Handle type="source" position={Position.Left} id="a" />
      <Handle type="source" position={Position.Right} id="b" />
    </>
  )
}

export default NOT_gate
