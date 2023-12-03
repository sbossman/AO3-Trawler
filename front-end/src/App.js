
import './App.css';
import GraphGenerator from './components/graphGenerator';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <h1>🦈AO3-TRAWLER🦈</h1>
      </header>
      <div className="box">
        <div className="p">Welcome to AO3 TRAWLER!</div>
        <div className="p">Choose your 2 Fanction works from the lists below.</div> 
        <GraphGenerator/>
      </div>
    </div>
  );
}

export default App;
